#include <CPfunctional.h>
#include <CPvector>

#include <stdio.h>

namespace {
    struct Recorder {
        int total;

        Recorder() : total(0) {}
        void operator()(int value) { total += value; }
    };
}

int main() {
    cpstd::vector<cpstd::function<void(int)> > listeners;
    listeners.reserve(1);
    Recorder recorder;
    listeners.push_back([&recorder](int value) { recorder(value); });
    listeners[0](12);
    listeners[0](8);

    printf("Event total: %d\n", recorder.total);
    return 0;
}
