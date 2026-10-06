// Compiled with CPSTL_CXX_STANDARD (C++11 by default), unlike the GoogleTest
// suites, which need C++17: instantiates every public header at the oldest
// supported language level and runs a few operations.

#include <CPSTL.h>
#include <CPalgorithm>
#include <CPexception>
#include <CPinitializer_list>
#include <CPlimits.h>
#include <CPmemory.h>
#include <CPtype_traits>
#include <CPutility>
#if defined(CPSTL_VECTOR_ENABLED)
    #include <CPvector>
#endif
#if defined(CPSTL_STRING_ENABLED)
    #include <CPstring>
#endif
#if defined(CPSTL_STACK_ENABLED)
    #include <CPstack>
#endif
#if defined(CPSTL_QUEUE_ENABLED)
    #include <CPqueue>
#endif

namespace {
    int failures = 0;
    void Check(bool condition) {
        if (!condition) {
            ++failures;
        }
    }
}

int main() {
    Check(cpstd::is_same<cpstd::remove_cv<const int>::type, int>::value);
    Check(cpstd::is_base_of<cpstd::input_iterator_tag, cpstd::random_access_iterator_tag>::value);
    Check(cpstd::numeric_limits<int>::max() == 2147483647);

    int values[] = {3, 1, 2};
    cpstd::sort(values, values + 3);
    Check(values[0] == 1 && values[2] == 3);
    Check(cpstd::distance(values, values + 3) == 3);

    cpstd::function<int(int)> twice = [](int x) { return 2 * x; };
    Check(twice(4) == 8);
    cpstd::unique_ptr<int> owned = cpstd::make_unique<int>(5);
    Check(*owned == 5);

#if defined(CPSTL_VECTOR_ENABLED)
    cpstd::vector<int> v = {1, 2, 3};
    v.insert(v.begin(), 0);
    v.erase(v.end() - 1);
    Check(v.size() == 3 && v[0] == 0 && v[2] == 2);
#endif

#if defined(CPSTL_STRING_ENABLED)
    cpstd::string s("abc");
    s += cpstd::to_string(42);
    Check(s == "abc42" && cpstd::stoi(s.substr(3)) == 42);
#endif

#if defined(CPSTL_STACK_ENABLED)
    cpstd::stack<int> lifo;
    lifo.push(1);
    lifo.emplace(2);
    Check(lifo.size() == 2 && lifo.top() == 2);
    lifo.pop();
    Check(lifo.top() == 1);
#endif

#if defined(CPSTL_QUEUE_ENABLED)
    cpstd::queue<int> fifo;
    fifo.push(1);
    fifo.emplace(2);
    Check(fifo.size() == 2 && fifo.front() == 1 && fifo.back() == 2);
    fifo.pop();
    Check(fifo.front() == 2);
#endif

    return failures;
}
