add_subdirectory(BuildConfiguration)

if(CPSTL_VECTOR)
    add_subdirectory(SortedReadings)
    add_subdirectory(FixedCapacityLog)
    add_subdirectory(EventPipeline)
endif()

if(CPSTL_STRING)
    add_subdirectory(TextCommand)
endif()
