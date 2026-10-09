#include <CPstring.h>

#include <stdio.h>

int main() {
    cpstd::string status("Channel ");
    status += cpstd::to_string(2);
    status += " is ready";
    printf("%s\n", status.c_str());
    return 0;
}
