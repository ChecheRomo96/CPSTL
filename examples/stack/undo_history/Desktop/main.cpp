#include <CPSTL.h>
#include <CPstack.h>
#include <stdio.h>

// Restore previous brightness settings in reverse order (LIFO).
int main() {
    printf("Restore previous brightness settings in reverse order (LIFO).\n");
    cpstd::stack<int> undo;
    int brightness = 10;
    printf("Initial brightness: %ld\n", static_cast<long>(brightness));
    const int changes[] = {20, 40};
    for (cpstd::size_t i = 0; i < sizeof(changes) / sizeof(changes[0]); ++i) {
        const cpstd::size_t before = undo.size();
        undo.push(brightness);
        if (undo.size() != before + 1) { printf("Not enough memory to save undo history.\n"); return 1; }
        brightness = changes[i];
        printf("Changed brightness to: %ld\n", static_cast<long>(brightness));
    }
    printf("Undo saves the previous setting before each edit.\n");
    while (!undo.empty()) {
        brightness = undo.top();
        undo.pop();
        printf("Undo restored brightness: %ld\n", static_cast<long>(brightness));
        printf("  Remaining undo entries: %ld\n", static_cast<long>(undo.size()));
    }
    printf("No older setting remains; top() is never called on an empty stack.\n");
    return 0;
}
