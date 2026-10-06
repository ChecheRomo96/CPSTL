// cpstd::function and cpstd::unique_ptr: storing callbacks and owning objects.

#include <CPfunctional.h>
#include <CPmemory.h>
#include <CPvector>

#include <stdio.h>

namespace {
    int Square(int x) { return x * x; }

    struct Accumulator {
        int total = 0;
        int operator()(int x) { return total += x; }
    };
}

int main() {
    cpstd::vector<cpstd::function<int(int)>> steps;
    steps.push_back(&Square);
    int offset = 3;  // captured by value: later changes do not affect the step
    steps.push_back([offset](int x) { return x + offset; });
    steps.push_back(Accumulator());

    int value = 2;
    for (cpstd::size_t i = 0; i < steps.size(); ++i) {
        value = steps[i](value);
        printf("after step %u: %d\n", static_cast<unsigned>(i), value);
    }

    cpstd::function<int(int)> none;
    printf("empty function is %s\n", none ? "callable" : "empty");

    cpstd::unique_ptr<int> owned = cpstd::make_unique<int>(value);
    cpstd::unique_ptr<int> moved(cpstd::move(owned));
    printf("unique_ptr moved: source %s, target %d\n", owned ? "full" : "empty", *moved);

    const bool ok = value == 7 && !none && !owned && *moved == 7;
    printf("Self-check: %s\n", ok ? "ok" : "FAILED");
    return ok ? 0 : 1;
}
