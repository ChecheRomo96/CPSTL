#include <CPSTL.h>
#include <iostream>
#include <CPinitializer_list>

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
            


            cpstd::vector<cpstd::vector<uint8_t>> myVector(8);

            std::cout<<myVector.size()<<std::endl;

            for (uint8_t i = 0; i < myVector.size(); i++) {
                std::cout << myVector[i].size()<<" - ";
                myVector[i].resize(8);
                std::cout << myVector[i].size() << std::endl;

                for (uint8_t j = 0; j < myVector[i].size(); j++) {
                    myVector[i][j] = (8 * i) + j;
                    //EXPECT_EQ(myVector[i][j], (8 * i) + j);
                    std::cout << myVector[i][j] << std::endl;
                }
            }

            for (uint8_t i = 0; i < myVector.size(); i++) {
                for (uint8_t j = 0; j < myVector[i].size(); j++) {
                    myVector[i][j] = (8 * i) + j;
                    std::cout << myVector[i][j] << std::endl;
                }
                myVector[i].clear();
            }

            myVector.clear();

    return 0;
}
