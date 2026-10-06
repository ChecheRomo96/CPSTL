cpstl_add_example(CPSTL_BuildConfiguration BuildConfiguration/Desktop/main.cpp)
cpstl_add_example(CPSTL_Algorithm_Sorting algorithm/Sorting/Desktop/main.cpp)

if(CPSTL_VECTOR)
    cpstl_add_example(CPSTL_Vector_BasicUsage vector/BasicUsage/Desktop/main.cpp)
    cpstl_add_example(CPSTL_Functional_Callbacks functional/Callbacks/Desktop/main.cpp)
endif()

if(CPSTL_STRING)
    cpstl_add_example(CPSTL_String_BasicUsage string/BasicUsage/Desktop/main.cpp)
endif()
