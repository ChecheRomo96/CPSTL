#include <CPvector>

#include <stdio.h>

int main() {
    cpstd::vector<int> steps;
    steps.push_back(10);
    steps.push_back(30);
    steps.insert(steps.begin() + 1, 20);
    steps.erase(steps.begin());
    printf("Remaining steps: %d, %d\n", steps[0], steps[1]);
    return 0;
}
