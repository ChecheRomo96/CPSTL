#include <CPSTL.h>
#include <CPmemory.h>
#include <CPutility.h>

// Transfer ownership of a simulated sensor to a logger.
struct Sensor {
    explicit Sensor(int value) : id(value) {}
    int id;
    int Read() const { return id * 10; }
};

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("Transfer ownership of a simulated sensor to a logger.");
    cpstd::unique_ptr<Sensor> driver = cpstd::make_unique<Sensor>(42);
    if (!driver) { Serial.println("Could not allocate the simulated sensor."); return; }
    Serial.print("Before move, driver owns sensor ID: "); Serial.println(static_cast<long>(driver->id));
    cpstd::unique_ptr<Sensor> logger = cpstd::move(driver);
    Serial.print("After move, driver is empty: "); Serial.println(!driver ? "yes" : "no");
    Serial.print("After move, logger owns sensor ID: "); Serial.println(static_cast<long>(logger->id));
    Serial.print("Simulated logger reading (ID * 10): "); Serial.println(static_cast<long>(logger->Read()));
    Serial.println("The sensor was transferred, not copied; logger releases it automatically on exit.");
}

void loop() {}
