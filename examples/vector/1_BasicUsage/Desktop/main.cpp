#include <CPvector>
#include <iostream>

int main(){

    // Preallocating memory for a vector that will grow in size
    {
        std::cout << "Resizing a cpstd::vector -> [preallocating memory with reserve() ]:" << std::endl;
        cpstd::vector<uint8_t> myVector;
        myVector.reserve(UINT8_MAX);

        std::cout << "  -o cpstd::vector<uint8_t> myVector;" << std::endl;
        std::cout << "  -o myVector.reserve(UINT8_MAX);" << std::endl;
        std::cout << "  -o myVector.resize( rand() % UINT8_MAX );" << std::endl;
        
        for(uint8_t i = 0; i < 10; i++ )
        {
            myVector.resize( rand() % UINT8_MAX );
            std::cout << "  -> NewSize: " << myVector.size() << "." << std::endl;
        }
    } std::cout<<std::endl;

    // Resize constructor
    {
        std::cout << "Constructing a cpstd::vector with a predefined size -> [resize constructor]:" << std::endl;
        cpstd::vector<uint8_t> myVector(20);
        std::cout << "  -o cpstd::vector<uint8_t> myVector(20);" << std::endl;
        std::cout << "  -> myVector.size()     -> " << myVector.size() << "." << std::endl;
        std::cout << "  -> myVector.capacity() -> " << myVector.capacity() << "." << std::endl<< std::endl;
       
        myVector.clear();
        std::cout << "  -o myVector.clear();" << std::endl;
        std::cout << "  -> myVector.size()     -> " << myVector.size() << "." << std::endl;
        std::cout << "  -> myVector.capacity() -> " << myVector.capacity() << "." << std::endl<< std::endl;
    }

    return 0;
}