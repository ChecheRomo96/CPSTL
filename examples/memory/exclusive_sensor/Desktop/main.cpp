#include <CPSTL.h>
#include <CPmemory.h>
#include <CPutility.h>
#include <stdio.h>

// Transfer ownership of a simulated sensor to a logger.
struct Sensor {
    explicit Sensor(int value) : id(value) {}
    int id;
    int Read() const { return id * 10; }
};

int main() {
    printf("Transfer ownership of a simulated sensor to a logger.\n");
    cpstd::unique_ptr<Sensor> driver = cpstd::make_unique<Sensor>(42);
    if (!driver) { printf("Could not allocate the simulated sensor.\n"); return 1; }
    printf("Before move, driver owns sensor ID: %ld\n", static_cast<long>(driver->id));
    cpstd::unique_ptr<Sensor> logger = cpstd::move(driver);
    printf("After move, driver is empty: %s\n", !driver ? "yes" : "no");
    printf("After move, logger owns sensor ID: %ld\n", static_cast<long>(logger->id));
    printf("Simulated logger reading (ID * 10): %ld\n", static_cast<long>(logger->Read()));
    printf("The sensor was transferred, not copied; logger releases it automatically on exit.\n");
    return 0;
}
