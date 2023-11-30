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
    
    int32_t x = INT32_MIN;
    std::cout<< cpstd::to_string(x) <<std::endl;
    
    x = INT32_MAX;
    std::cout<< cpstd::to_string(x) <<std::endl;

    return 0;
}
