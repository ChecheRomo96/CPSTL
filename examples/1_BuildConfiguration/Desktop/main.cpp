#include <CPSTL.h>
#include <iostream>
#include <CPinitializer_list>

void SplitFilename(const cpstd::string& str, cpstd::string& path, cpstd::string& file)
{
    std::cout << "Splitting: " << str << '\n';
    auto found = str.find_last_of("/\\");

    path = str.substr(0, found);
    file = str.substr(found + 1);
}

int main(){
    std::cout<<"This project uses CPSTL version: "<<CPSTL_VERSION << std::endl << std::endl;
    
    
    #ifdef CPSTL_VECTOR_ENABLED
        std::cout << "  cpstd::vector enabled" << std::endl;



        std::cout << std::endl;
    #endif

    #ifdef CPSTL_STRING_ENABLED
            std::cout << "  cpstd::string enabled" << std::endl;



            std::cout << std::endl;
    #endif
            cpstd::string str("Please, erase trailing white-spaces   \n");
            cpstd::string whitespaces(" \t\f\v\n\r");

            size_t found = str.find_last_not_of(whitespaces);

            if (found != cpstd::string::npos) { str.erase(found + 1); }
            else { str.clear(); }

            std::cout << str << std::endl;

    return 0;
}
