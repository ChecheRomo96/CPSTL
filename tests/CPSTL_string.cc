// cpstd::basic_string / cpstd::string. Every expectation also holds for
// std::string, so the suite runs unchanged in STL mode.

#include <gtest/gtest.h>

#include <CPstring>

#include <string.h>

#include "TestSupport.h"

using cpstd::string;

namespace {
    // Compares through c_str() so a missing terminator is caught too.
    ::testing::AssertionResult Holds(const string& s, const char* expected) {
        if (strcmp(s.c_str(), expected) == 0 && s.size() == strlen(expected)) {
            return ::testing::AssertionSuccess();
        }
        return ::testing::AssertionFailure()
            << "\"" << s.c_str() << "\" (size " << s.size() << ") != \"" << expected << "\"";
    }
}

TEST(StringConstruction, EmptyStringIsTerminated) {
    const string s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
    ASSERT_NE(s.c_str(), nullptr);
    EXPECT_EQ(s.c_str()[0], '\0');
}

TEST(StringConstruction, AllConstructors) {
    EXPECT_TRUE(Holds(string("hello"), "hello"));
    EXPECT_TRUE(Holds(string("hello", 3), "hel"));
    EXPECT_TRUE(Holds(string(4, 'x'), "xxxx"));
    EXPECT_TRUE(Holds(string(3, 65), "AAA"));  // integers pick the fill constructor
    const string source("abcdef");
    EXPECT_TRUE(Holds(string(source), "abcdef"));
    EXPECT_TRUE(Holds(string(source, 2), "cdef"));
    EXPECT_TRUE(Holds(string(source, 1, 3), "bcd"));
    EXPECT_TRUE(Holds(string(source.begin() + 1, source.end() - 1), "bcde"));
    EXPECT_TRUE(Holds(string({'o', 'k'}), "ok"));

    string moved_from("payload");
    string moved(cpstd::move(moved_from));
    EXPECT_TRUE(Holds(moved, "payload"));
}

TEST(StringAssignment, CopyMoveAndOtherSources) {
    string a("first");
    string b("second, longer than first");
    a = b;
    EXPECT_TRUE(Holds(a, "second, longer than first"));
    b = "x";
    EXPECT_TRUE(Holds(b, "x"));
    EXPECT_TRUE(Holds(a, "second, longer than first"));  // a owns its own copy

    string c;
    c = cpstd::move(a);
    EXPECT_TRUE(Holds(c, "second, longer than first"));

    c = 'z';
    EXPECT_TRUE(Holds(c, "z"));
    c = {'h', 'i'};
    EXPECT_TRUE(Holds(c, "hi"));
    const string& alias = c;
    c = alias;  // self-assignment
    EXPECT_TRUE(Holds(c, "hi"));

    c.assign(3, '-');
    EXPECT_TRUE(Holds(c, "---"));
    c.assign("abcdef", 2);
    EXPECT_TRUE(Holds(c, "ab"));
}

TEST(StringModifiers, AppendAndPushBack) {
    string s;
    for (char c = 'a'; c <= 'z'; ++c) {
        s.push_back(c);
    }
    EXPECT_TRUE(Holds(s, "abcdefghijklmnopqrstuvwxyz"));
    s.append("0123", 2);
    s.append(2, '!');
    s += "?";
    s += string("<>");
    s += '.';
    EXPECT_TRUE(Holds(s, "abcdefghijklmnopqrstuvwxyz01!!?<>."));
}

TEST(StringModifiers, AppendOfOwnContentsDuringGrowth) {
    string s("abc");
    s.shrink_to_fit();
    s.append(s);
    EXPECT_TRUE(Holds(s, "abcabc"));
    s.append(s.c_str() + 1, 2);
    EXPECT_TRUE(Holds(s, "abcabcbc"));
    s += s;
    EXPECT_TRUE(Holds(s, "abcabcbcabcabcbc"));
}

TEST(StringModifiers, InsertEraseReplace) {
    string s("held");
    s.insert(2, "llo wor");
    EXPECT_TRUE(Holds(s, "hello world"));
    s.insert(0, 2, '>');
    EXPECT_TRUE(Holds(s, ">>hello world"));
    s.insert(s.size(), "!");
    EXPECT_TRUE(Holds(s, ">>hello world!"));
    s.insert(2, s.c_str() + 2, 5);  // insert part of itself
    EXPECT_TRUE(Holds(s, ">>hellohello world!"));

    s.erase(0, 2);
    EXPECT_TRUE(Holds(s, "hellohello world!"));
    s.erase(5, 5);
    EXPECT_TRUE(Holds(s, "hello world!"));
    s.erase(s.begin() + 5);
    EXPECT_TRUE(Holds(s, "helloworld!"));

    s.replace(0, 5, "HELLO");
    EXPECT_TRUE(Holds(s, "HELLOworld!"));
    s.replace(5, 5, "-");
    EXPECT_TRUE(Holds(s, "HELLO-!"));
    s.replace(0, 1, 3, 'h');
    EXPECT_TRUE(Holds(s, "hhhELLO-!"));
    s.pop_back();
    EXPECT_TRUE(Holds(s, "hhhELLO-"));
}

TEST(StringCapacity, ResizeReserveShrinkClear) {
    string s("abc");
    s.resize(6, '.');
    EXPECT_TRUE(Holds(s, "abc..."));
    s.resize(2);
    EXPECT_TRUE(Holds(s, "ab"));
    s.reserve(100);
    EXPECT_GE(s.capacity(), 100u);
    EXPECT_TRUE(Holds(s, "ab"));
    s.shrink_to_fit();
    EXPECT_TRUE(Holds(s, "ab"));
    s.clear();
    EXPECT_TRUE(Holds(s, ""));
    s.shrink_to_fit();
    EXPECT_TRUE(Holds(s, ""));
}

TEST(StringAccess, ElementsAndCopy) {
    string s("abc");
    EXPECT_EQ(s.front(), 'a');
    EXPECT_EQ(s.back(), 'c');
    EXPECT_EQ(s[1], 'b');
    s[1] = 'B';
    EXPECT_TRUE(Holds(s, "aBc"));
    char out[4] = {0, 0, 0, 0};
    EXPECT_EQ(s.copy(out, 2, 1), 2u);
    EXPECT_EQ(strcmp(out, "Bc"), 0);
    EXPECT_EQ(string(s.rbegin(), s.rend()), string("cBa"));
}

TEST(StringSearch, FindFamily) {
    const string s("abracadabra");
    EXPECT_EQ(s.find("bra"), 1u);
    EXPECT_EQ(s.find("bra", 2), 8u);
    EXPECT_EQ(s.find('c'), 4u);
    EXPECT_EQ(s.find("zzz"), string::npos);
    EXPECT_EQ(s.rfind("abra"), 7u);
    EXPECT_EQ(s.rfind('a'), 10u);
    EXPECT_EQ(s.find_first_of("dc"), 4u);
    EXPECT_EQ(s.find_last_of("b"), 8u);
    EXPECT_EQ(s.find_first_not_of("ab"), 2u);
    EXPECT_EQ(s.find_last_not_of("a"), 9u);
    EXPECT_EQ(s.find(""), 0u);
}

TEST(StringOperations, SubstrCompareConcatenate) {
    const string s("hello world");
    EXPECT_TRUE(Holds(s.substr(6), "world"));
    EXPECT_TRUE(Holds(s.substr(0, 5), "hello"));
    EXPECT_EQ(s.compare("hello world"), 0);
    EXPECT_LT(s.compare("help"), 0);
    EXPECT_GT(s.compare("hell"), 0);
    EXPECT_EQ(s.compare(0, 5, "hello"), 0);

    EXPECT_TRUE(string("a") < string("b"));
    EXPECT_TRUE(string("ab") < string("abc"));
    EXPECT_TRUE(string("abc") == "abc");
    EXPECT_TRUE("abc" != string("abd"));
    EXPECT_TRUE(Holds(string("foo") + string("bar"), "foobar"));
    EXPECT_TRUE(Holds(string("foo") + "bar", "foobar"));
    EXPECT_TRUE(Holds("foo" + string("bar"), "foobar"));
    EXPECT_TRUE(Holds(string("foo") + '!', "foo!"));
}

TEST(StringConversions, ToString) {
    EXPECT_TRUE(Holds(cpstd::to_string(0), "0"));
    EXPECT_TRUE(Holds(cpstd::to_string(-42), "-42"));
    EXPECT_TRUE(Holds(cpstd::to_string(2147483647), "2147483647"));
    EXPECT_TRUE(Holds(cpstd::to_string(-2147483647 - 1), "-2147483648"));
    EXPECT_TRUE(Holds(cpstd::to_string(18446744073709551615ULL), "18446744073709551615"));
    EXPECT_TRUE(Holds(cpstd::to_string(-9223372036854775807LL - 1), "-9223372036854775808"));
    EXPECT_TRUE(Holds(cpstd::to_string(3.14), "3.140000"));
    EXPECT_TRUE(Holds(cpstd::to_string(-0.5f), "-0.500000"));
    EXPECT_TRUE(Holds(cpstd::to_string(0.0), "0.000000"));
    EXPECT_TRUE(Holds(cpstd::to_string(2.0000005), "2.000001"));  // rounded, not truncated
}

TEST(StringConversions, FromString) {
    cpstd::size_t used = 0;
    EXPECT_EQ(cpstd::stoi(string("  -123abc"), &used), -123);
    EXPECT_EQ(used, 6u);
    EXPECT_EQ(cpstd::stoi(string("ff"), nullptr, 16), 255);
    EXPECT_EQ(cpstd::stoi(string("0x1A"), nullptr, 0), 26);
    EXPECT_EQ(cpstd::stoi(string("017"), nullptr, 0), 15);
    EXPECT_EQ(cpstd::stol(string("+77")), 77L);
    EXPECT_EQ(cpstd::stoul(string("4000000000")), 4000000000UL);
    EXPECT_EQ(cpstd::stoll(string("-9223372036854775808")), -9223372036854775807LL - 1);
    EXPECT_EQ(cpstd::stoull(string("18446744073709551615")), 18446744073709551615ULL);
    EXPECT_DOUBLE_EQ(cpstd::stod(string("2.5e3"), &used), 2500.0);
    EXPECT_EQ(used, 5u);
    EXPECT_FLOAT_EQ(cpstd::stof(string("-0.25")), -0.25f);
}

#if !defined(CPSTL_USING_STL)

// std::stoi throws on these inputs; CPSTL reports them without exceptions.
TEST(StringConversions, InvalidAndOutOfRangeInputWithoutExceptions) {
    cpstd::size_t used = 99;
    EXPECT_EQ(cpstd::stoi(string("abc"), &used), 0);
    EXPECT_EQ(used, 0u);
    EXPECT_EQ(cpstd::stoi(string("")), 0);
    EXPECT_EQ(cpstd::stoi(string("99999999999")), 2147483647);
    EXPECT_EQ(cpstd::stoi(string("-99999999999")), -2147483647 - 1);
    EXPECT_EQ(cpstd::stoull(string("99999999999999999999999")), 18446744073709551615ULL);
}

TEST(StringStorage, EmptyStringsDoNotAllocate) {
    string s;
    EXPECT_EQ(s.capacity(), 0u);
    string copy(s);
    EXPECT_EQ(copy.capacity(), 0u);
    s = "";
    EXPECT_EQ(s.capacity(), 0u);
}

using cpstl_test::BudgetScope;
using FailingString = cpstd::basic_string<char, cpstd::char_traits<char>, cpstl_test::FailingAllocator<char>>;

TEST(StringAllocationFailure, OperationsLeaveTheStringUnchanged) {
    BudgetScope scope(1);
    FailingString s("abc");
    ASSERT_EQ(s.size(), 3u);
    const cpstd::size_t capacity = s.capacity();
    s.append(capacity, 'x');
    EXPECT_EQ(strcmp(s.c_str(), "abc"), 0);
    s.push_back('d');
    s.insert(0, "123456789", 9);
    s.resize(1000, '.');
    s.reserve(1000);
    EXPECT_EQ(strcmp(s.c_str(), capacity > 3 ? "abcd" : "abc"), 0);

    FailingString copy(s);  // no storage left: empty, still terminated
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.c_str()[0], '\0');
}

TEST(StringAllocationFailure, NothingLeaks) {
    {
        BudgetScope scope(4);
        FailingString s;
        for (int i = 0; i < 200; ++i) {
            s.push_back('a');
        }
        EXPECT_GT(s.size(), 0u);
        EXPECT_LT(s.size(), 200u);
        EXPECT_EQ(s.c_str()[s.size()], '\0');
    }
    EXPECT_EQ(cpstl_test::AllocationBudget::Outstanding, 0);
}

#endif
