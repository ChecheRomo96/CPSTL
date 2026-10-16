#include <CPSTL.h>
#include <stdio.h>

// Sort a report copy while preserving capture order.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    printf("%s: ", label);
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        printf(i == 0 ? "%d" : ", %d", values[i]);
    }
    printf("\n");
}

int main() {
    printf("Sort a report copy while preserving capture order.\n");
    cpstd::vector<int> readings = {42, 18, 31, 18, 27};
    if (readings.size() != 5) { printf("Not enough memory for the history.\n"); return 1; }
    PrintValues("Original capture order", readings);
    cpstd::vector<int> ranked(readings);
    if (ranked.size() != readings.size()) { printf("Not enough memory for the report copy.\n"); return 1; }
    cpstd::sort(ranked.begin(), ranked.end());
    PrintValues("Sorted report copy (lowest to highest)", ranked);
    PrintValues("Original history after sorting the copy", readings);
    printf("sort() changed the copy, so the capture order remains available.\n");
    return 0;
}
