#include <CPstack.h>

#include <stdio.h>

int main() {
    cpstd::stack<int> undo;
    undo.push(10);
    undo.push(20);
    printf("Undo action: %d\n", undo.top());
    undo.pop();
    printf("Current action: %d\n", undo.top());
    return 0;
}
