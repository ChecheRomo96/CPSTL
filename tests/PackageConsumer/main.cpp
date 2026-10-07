// Uses the installed headers and library (string conversions live in
// libCPSTL), and checks the exported configuration reached this target.

#include <CPSTL.h>

#include <string.h>

int main() {
#if !defined(CPSTL_VERSION) || !defined(CPSTL_VECTOR_ENABLED) || !defined(CPSTL_STRING_ENABLED) || \
    !defined(CPSTL_STACK_ENABLED) || !defined(CPSTL_QUEUE_ENABLED)
    return 1;
#else
    cpstd::vector<cpstd::string> words;
    words.push_back(cpstd::string("package"));
    words.push_back(cpstd::to_string(42));
    cpstd::sort(words.begin(), words.end());
    cpstd::queue<int> pending;
    pending.push(1);
    cpstd::stack<int> undo;
    undo.push(pending.front());
    if (undo.top() != 1) {
        return 1;
    }
    return (strcmp(words[0].c_str(), "42") == 0 && cpstd::stoi(words[0]) == 42) ? 0 : 1;
#endif
}
