#include <CPfunctional.h>
#include <CPmemory.h>
#include <CPutility.h>
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
    cpstd::unique_ptr<Recorder> recorder = cpstd::make_unique<Recorder>();
    Recorder* const destination = recorder.get();
    cpstd::vector<cpstd::function<void(int)> > listeners;
    listeners.reserve(1);
    listeners.push_back([destination](int value) { (*destination)(value); });
    listeners[0](12);
    listeners[0](8);

    cpstd::unique_ptr<Recorder> owner = cpstd::move(recorder);
    printf("Event total: %d\n", owner->total);
    return 0;
}
