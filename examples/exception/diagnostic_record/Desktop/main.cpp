#include <CPexception.h>

#include <stdio.h>

int main() {
    const cpstd::out_of_range diagnostic("sample index is outside the buffer");
    printf("Diagnostic: %s\n", diagnostic.what());
    return 0;
}
