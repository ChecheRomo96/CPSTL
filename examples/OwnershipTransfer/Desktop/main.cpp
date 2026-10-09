#include <CPmemory.h>
#include <CPutility.h>

#include <stdio.h>

namespace {
    struct Sensor {
        explicit Sensor(int id) : id(id) {}
        int id;
    };
}

int main() {
    cpstd::unique_ptr<Sensor> source = cpstd::make_unique<Sensor>(42);
    cpstd::unique_ptr<Sensor> owner = cpstd::move(source);
    printf("Sensor %d has one owner: %s\n", owner->id, source ? "no" : "yes");
    return 0;
}
