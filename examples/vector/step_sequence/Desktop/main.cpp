#include <CPSTL.h>
#include <stdio.h>

// Edit control steps and inspect each resulting sequence.
void PrintValues(const char* label, const cpstd::vector<int>& values) {
    printf("%s: ", label);
    for (cpstd::size_t i = 0; i < values.size(); ++i) {
        printf(i == 0 ? "%d" : ", %d", values[i]);
    }
    printf("\n");
}

int main() {
    printf("Edit control steps and inspect each resulting sequence.\n");
    cpstd::vector<int> steps;
    steps.reserve(3);
    if (steps.capacity() < 3) { printf("Not enough memory for the control steps.\n"); return 1; }
    steps.push_back(10);
    steps.push_back(30);
    printf("Step codes: 10=warm-up, 20=calibration, 30=run.\n");
    PrintValues("Original program", steps);
    steps.insert(steps.begin() + 1, 20);
    PrintValues("After insert at zero-based index 1", steps);
    steps.erase(steps.begin());
    PrintValues("After erase of the first step", steps);
    printf("The remaining program calibrates, then runs; warm-up was removed.\n");
    return 0;
}
