#include <CPSTL.h>
#include <iostream>
#include <CPiterator.h>


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
    
    cpstd::string str = "Hello, CPSTL!";
    std::cout << "cpstd::string str: " << str.c_str() << std::endl;

	cpstd::wstring wstr = L"Hello, CPSTL!";

    for (size_t i = 0; i < wstr.size(); ++i) {
        std::wcout << "wstr[" << i << "] = " << wstr[i] << std::endl;
	}
    return 0;
}
