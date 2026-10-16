#include <CPSTL.h>

// Copy a packet into an independent log.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    Serial.print(label); Serial.print(": ");
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        if (i != 0) Serial.print(", ");
        Serial.print(values[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
    Serial.println("Copy a packet into an independent log.");
    cpstd::vector<int> source = {3, 5, 8};
    if (source.size() != 3) { Serial.println("Not enough memory for the packet."); return; }
    cpstd::vector<int> destination;
    destination.reserve(source.size());
    if (destination.capacity() < source.size()) { Serial.println("Not enough memory for the log."); return; }
    PrintValues("Source packet", source);
    Serial.print("Destination size before copy: "); Serial.println(static_cast<long>(destination.size()));
    cpstd::copy(source.begin(), source.end(), cpstd::back_inserter(destination));
    PrintValues("Destination after copy with back_inserter", destination);
    destination[0] = 99;
    PrintValues("Destination after changing its first sample to 99", destination);
    PrintValues("Source packet remains unchanged", source);
    Serial.println("The copied vector owns independent storage.");
}

void loop() {}
