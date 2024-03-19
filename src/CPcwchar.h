#ifndef CPSTL_CWCHAR_H
#define CPSTL_CWCHAR_H


    #include <CPSTL_BuildSettings.h>
    #include <CPcstring.h>

    #ifdef CPSTL_USING_STL
        #include <cwchar.h>
    #endif

    namespace cpstd{

        // Types
        #ifdef CPSTL_USING_STL
            using mbstate_t = std::mbstate_t;
        #else
            struct mbstate_t {
                // Define necessary members to maintain state
                // For example:
                int shift_state; // Example member to hold shift state information

                // Default constructor to initialize to the initial state
                mbstate_t() : shift_state(0) {}

                // Function to set the state to initial state
                void reset() {
                    cpstd::memset(this, 0, sizeof(*this));
                }
            };
        #endif



    }


#endif//CPSTL_CWCHAR_H