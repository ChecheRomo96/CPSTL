#include <CPSTL.h>
#include <cstdio>

int main()
{
    cpstd::vector<int> values;
    values.push_back(7);
    values.push_back(3);
    cpstd::sort(values.begin(), values.end());
    cpstd::string message("installed");
    message += " package";
    // to_string exercises the compiled library as well as installed headers.
    cpstd::string number = cpstd::to_string(values[0] + values[1]);
    if (values.size() != 2 || values[0] != 3 || values[1] != 7 ||
        message != "installed package" || number != "10") {
        return 1;
    }
    std::printf("CPSTL %s: installed package PASS\n", CPSTL_VERSION);
    return 0;
}
