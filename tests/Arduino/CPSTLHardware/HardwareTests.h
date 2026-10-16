#ifndef CPSTL_HARDWARE_TESTS_H
#define CPSTL_HARDWARE_TESTS_H

#include <CPSTL.h>
#include <CPmemory.h>
#include <CPlimits.h>
#include <limits.h>
#include <float.h>
#include <string.h>

#if !defined(__AVR_ATmega2560__) && !(defined(ARDUINO_ARCH_STM32) && defined(STM32G0B1xx))
#error "This fixture targets ATmega2560 or STM32G0B1 with its Arduino core"
#endif
#if defined(__AVR__) && (defined(CPSTL_USING_STL) || defined(CPSTL_USING_STD_ALLOCATION))
#error "The AVR physical suite requires CPSTL implementation mode"
#endif

namespace hardware_tests {
static unsigned assertions;
#define HW_CHECK(expression) do { ++assertions; if (!(expression)) { \
    Serial.print(F("CPSTL_HW_ASSERT line=")); Serial.println(__LINE__); \
    return false; } } while (0)

struct Tracked {
    static int live;
    int value;
    explicit Tracked(int n = 0) : value(n) { ++live; }
    Tracked(const Tracked& other) : value(other.value) { ++live; }
    Tracked(Tracked&& other) : value(other.value) { other.value = -1; ++live; }
    Tracked& operator=(const Tracked& other) { value = other.value; return *this; }
    Tracked& operator=(Tracked&& other) { value = other.value; other.value = -1; return *this; }
    ~Tracked() { --live; }
};
int Tracked::live = 0;

struct Budget { static int remaining; static int outstanding; };
int Budget::remaining = -1;
int Budget::outstanding = 0;

template<class T> struct FailingAllocator : cpstd::allocator<T> {
    template<class U> struct rebind { using other = FailingAllocator<U>; };
    T* allocate(cpstd::size_t count) {
        if (Budget::remaining == 0) return nullptr;
        T* p = cpstd::allocator<T>::allocate(count);
        if (p) { ++Budget::outstanding; if (Budget::remaining > 0) --Budget::remaining; }
        return p;
    }
    void deallocate(T* p, cpstd::size_t count) {
        if (p) --Budget::outstanding;
        cpstd::allocator<T>::deallocate(p, count);
    }
};
struct BudgetScope {
    BudgetScope() { Budget::remaining = -1; }
    ~BudgetScope() { Budget::remaining = -1; }
};

static bool TypeTraits() {
    static_assert(cpstd::is_same<cpstd::remove_cv<const volatile int>::type, int>::value, "remove_cv");
    static_assert(cpstd::is_integral<int>::value, "integral");
    static_assert(cpstd::is_pointer<int*>::value, "pointer");
    HW_CHECK((cpstd::is_same<cpstd::remove_reference<int&>::type, int>::value));
    HW_CHECK((cpstd::is_base_of<cpstd::input_iterator_tag, cpstd::random_access_iterator_tag>::value));
    return true;
}
static bool NumericLimits() {
#if defined(__AVR_ATmega2560__)
    HW_CHECK(sizeof(int) == 2);
#else
    HW_CHECK(sizeof(int) == 4);
#endif
    HW_CHECK(cpstd::numeric_limits<int>::max() == INT_MAX);
    HW_CHECK(cpstd::numeric_limits<int>::min() == INT_MIN);
    HW_CHECK(cpstd::numeric_limits<unsigned int>::max() == UINT_MAX);
    HW_CHECK(cpstd::numeric_limits<long>::max() == LONG_MAX);
    HW_CHECK(cpstd::numeric_limits<float>::epsilon() == FLT_EPSILON);
    HW_CHECK(cpstd::numeric_limits<double>::max() == DBL_MAX);
    return true;
}
static bool AlgorithmCopyFillFind() {
    int source[] = {1, 2, 3, 4}; int target[6] = {};
    HW_CHECK(cpstd::copy(source, source + 4, target) == target + 4);
    HW_CHECK(cpstd::equal(source, source + 4, target));
    cpstd::copy_backward(target, target + 4, target + 6);
    HW_CHECK(target[2] == 1 && target[5] == 4);
    cpstd::fill(target, target + 2, 9);
    HW_CHECK(target[0] == 9 && target[1] == 9);
    HW_CHECK(cpstd::find(source, source + 4, 3) == source + 2);
    HW_CHECK(cpstd::min(2, 7) == 2 && cpstd::max(2, 7) == 7);
    return true;
}
static bool AlgorithmSort() {
    int values[] = {5, 1, 3, 1, -2, 9};
    cpstd::sort(values, values + 6);
    int expected[] = {-2, 1, 1, 3, 5, 9};
    HW_CHECK(cpstd::equal(values, values + 6, expected));
    cpstd::sort(values, values + 6, [](int a, int b) { return a > b; });
    HW_CHECK(values[0] == 9 && values[5] == -2);
    return true;
}
static bool IteratorHelpers() {
    int values[] = {1, 2, 3, 4}; int* it = values;
    cpstd::advance(it, 3); HW_CHECK(*it == 4);
    cpstd::advance(it, -2); HW_CHECK(*it == 2);
    HW_CHECK(cpstd::distance(values + 4, values) == -4);
    HW_CHECK(*cpstd::next(values, 2) == 3 && *cpstd::prev(values + 4) == 4);
    HW_CHECK(cpstd::begin(values) == values && cpstd::end(values) == values + 4);
    return true;
}
static bool ReverseAndBackInsert() {
    int values[] = {1, 2, 3}; cpstd::vector<int> v;
    cpstd::copy(values, values + 3, cpstd::back_inserter(v));
    HW_CHECK(v.size() == 3 && v[2] == 3);
    cpstd::reverse_iterator<int*> r(values + 3);
    HW_CHECK(*r == 3); ++r; HW_CHECK(*r == 2);
    return true;
}
static bool VectorGrowth() {
    cpstd::vector<int> v;
    v.reserve(40); HW_CHECK(v.capacity() >= 40);
    for (int i = 0; i < 40; ++i) v.push_back(i);
    HW_CHECK(v.size() == 40);
    for (int i = 0; i < 40; ++i) HW_CHECK(v[i] == i);
    v.resize(10); v.shrink_to_fit();
    HW_CHECK(v.size() == 10 && v.capacity() >= 10);
    return true;
}
static bool VectorInsertErase() {
    cpstd::vector<int> v = {1, 4};
    v.insert(v.begin() + 1, 2, 3);
    HW_CHECK(v.size() == 4 && v[1] == 3 && v[3] == 4);
    v.erase(v.begin() + 1, v.begin() + 3);
    HW_CHECK(v.size() == 2 && v[1] == 4);
    v.pop_back(); HW_CHECK(v.back() == 1);
    v.clear(); HW_CHECK(v.empty()); return true;
}
static bool VectorCopyMove() {
    cpstd::vector<int> a = {2, 4, 6}; cpstd::vector<int> b(a);
    b[0] = 9; HW_CHECK(a[0] == 2 && b[0] == 9);
    cpstd::vector<int> c(cpstd::move(b)); HW_CHECK(c.size() == 3 && c[0] == 9);
    a = c; HW_CHECK(a == c); return true;
}
static bool VectorLifetime() {
    HW_CHECK(Tracked::live == 0);
    { cpstd::vector<Tracked> v; for (int i = 0; i < 8; ++i) v.emplace_back(i);
      HW_CHECK(Tracked::live == 8); v.erase(v.begin(), v.begin() + 3);
      HW_CHECK(Tracked::live == 5 && v[0].value == 3); }
    HW_CHECK(Tracked::live == 0); return true;
}
#if !defined(CPSTL_USING_STL)
static bool VectorAllocationFailure() {
    BudgetScope scope;
    { cpstd::vector<int, FailingAllocator<int> > v;
      v.push_back(7); v.shrink_to_fit(); Budget::remaining = 0;
      v.push_back(9); v.reserve(100);
      HW_CHECK(v.size() == 1 && v[0] == 7); }
    HW_CHECK(Budget::outstanding == 0); return true;
}
#endif
static bool StringConstruction() {
    cpstd::string empty; HW_CHECK(empty.empty() && empty.c_str()[0] == '\0');
    cpstd::string a("abcdef", 3); HW_CHECK(a == "abc");
    cpstd::string b(4, 'x'); HW_CHECK(b == "xxxx");
    cpstd::string c(a); a[0] = 'z'; HW_CHECK(c == "abc"); return true;
}
static bool StringMutation() {
    cpstd::string s("hello"); s += " world";
    HW_CHECK(s == "hello world"); HW_CHECK(s.find("world") == 6);
    HW_CHECK(s.substr(6) == "world"); s.insert(0, 2, '>');
    HW_CHECK(s == ">>hello world"); s.erase(0, 2);
    HW_CHECK(s == "hello world" && s.c_str()[s.size()] == '\0'); return true;
}
static bool StringConversions() {
    HW_CHECK(cpstd::to_string(-123) == "-123");
    HW_CHECK(cpstd::stoi(cpstd::string("-123")) == -123);
    HW_CHECK(cpstd::stol(cpstd::string("70000")) == 70000L);
#if !defined(CPSTL_USING_STL)
    HW_CHECK(cpstd::stoi(cpstd::string("invalid")) == 0);
#endif
    return true;
}
#if !defined(CPSTL_USING_STL)
static bool StringAllocationFailure() {
    BudgetScope scope;
    { cpstd::basic_string<char, cpstd::char_traits<char>, FailingAllocator<char> > s("abc");
      Budget::remaining = 0; s.append(100, 'x');
      HW_CHECK(strcmp(s.c_str(), "abc") == 0 && s.size() == 3); }
    HW_CHECK(Budget::outstanding == 0); return true;
}
#endif
static bool StackLifo() {
    cpstd::stack<int> s;
#if !defined(CPSTL_USING_STL)
    s.pop();
#endif
    HW_CHECK(s.empty());
    for (int i = 0; i < 8; ++i) s.emplace(i);
    for (int i = 7; i >= 0; --i) { HW_CHECK(s.top() == i); s.pop(); }
    HW_CHECK(s.empty()); return true;
}
static bool QueueFifo() {
    cpstd::queue<int> q;
#if !defined(CPSTL_USING_STL)
    q.pop();
#endif
    HW_CHECK(q.empty());
    for (int i = 0; i < 8; ++i) q.emplace(i);
    for (int i = 0; i < 8; ++i) { HW_CHECK(q.front() == i); q.pop(); }
    HW_CHECK(q.empty()); return true;
}
#if !defined(CPSTL_USING_STL)
static bool AdapterAllocationFailure() {
    BudgetScope scope;
    { using Storage = cpstd::vector<int, FailingAllocator<int> >;
      cpstd::stack<int, Storage> stack; cpstd::queue<int, Storage> queue;
      Budget::remaining = 0; stack.push(1); queue.push(1);
      HW_CHECK(stack.empty() && queue.empty()); }
    HW_CHECK(Budget::outstanding == 0); return true;
}
#endif
static bool UniqueOwnership() {
    { auto p = cpstd::make_unique<Tracked>(42); HW_CHECK(p && p->value == 42);
      cpstd::unique_ptr<Tracked> q(cpstd::move(p)); HW_CHECK(!p && q);
      Tracked* raw = q.release(); HW_CHECK(!q && Tracked::live == 1);
      q.reset(raw); q.reset(); HW_CHECK(Tracked::live == 0); }
    return true;
}
static bool UninitializedMemory() {
    cpstd::allocator<Tracked> alloc;
    { Tracked source[] = {Tracked(1), Tracked(2)};
      Tracked* slots = alloc.allocate(2); HW_CHECK(slots != nullptr);
      cpstd::uninitialized_copy(source, source + 2, slots);
      bool valid = slots[0].value == 1 && slots[1].value == 2 && Tracked::live == 4;
      alloc.destroy(slots); alloc.destroy(slots + 1); alloc.deallocate(slots, 2);
      HW_CHECK(valid); }
    HW_CHECK(Tracked::live == 0); return true;
}
static bool FunctionCopyMove() {
    int total = 0;
    cpstd::function<void(int)> f = [&total](int n) { total += n; };
    f(3); cpstd::function<void(int)> g(f); g(4);
    cpstd::function<void(int)> h(cpstd::move(g)); h(5);
    HW_CHECK(total == 12 && f && h); return true;
}
static bool UtilityMoveSwap() {
    int a = 2, b = 7; cpstd::swap(a, b); HW_CHECK(a == 7 && b == 2);
    cpstd::string source("moved"); cpstd::string dest(cpstd::move(source));
    HW_CHECK(dest == "moved"); return true;
}
static bool AllocatorBoundaries() {
    cpstd::allocator<int> alloc;
#if !defined(CPSTL_USING_STD_ALLOCATION)
    HW_CHECK(alloc.allocate(0) == nullptr);
    HW_CHECK(alloc.allocate(alloc.max_size() + 1) == nullptr);
#endif
    int* p = alloc.allocate(4); HW_CHECK(p != nullptr);
    alloc.deallocate(p, 4);
#if !defined(CPSTL_USING_STD_ALLOCATION)
    alloc.deallocate(nullptr, 0);
#endif
    return true;
}
#undef HW_CHECK
}
#endif
