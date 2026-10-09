#include <CPSTL.h>
#include <CPmemory.h>
#include <CPutility.h>

struct Sensor {
    explicit Sensor(int value) : id(value) {}
    int id;
};

void setup() {
    Serial.begin(9600);
    cpstd::unique_ptr<Sensor> source = cpstd::make_unique<Sensor>(42);
    cpstd::unique_ptr<Sensor> owner = cpstd::move(source);
    Serial.print("Sensor owner: ");
    Serial.println(owner->id);
}

void loop() {}
