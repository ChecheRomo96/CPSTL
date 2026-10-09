#include <CPSTL.h>
#include <CPmemory.h>
#include <CPutility.h>


/*
  Goal: Exclusive ownership: hand a hardware object from one subsystem to another.
  Interfaces: cpstd::make_unique(), cpstd::move(), unique_ptr::operator->().
  Observe: After move(), the source is empty and the destination is the only owner.
*/
struct Sensor {
    explicit Sensor(int value) : id(value) {}
    int id;
    int Read() const { return id * 10; }
};

void setup() {
    Serial.begin(9600);
    cpstd::unique_ptr<Sensor> driver = cpstd::make_unique<Sensor>(42);
    Serial.print("Driver owns sensor #"); Serial.println(driver->id);
    cpstd::unique_ptr<Sensor> logger = cpstd::move(driver);
    Serial.print("After move, driver is "); Serial.println(driver ? "still owner" : "empty");
    Serial.print("Logger reads: "); Serial.println(logger->Read());
    Serial.println("Only logger may use the sensor now; it deletes it automatically.");
}

void loop() {}
