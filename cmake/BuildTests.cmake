# GoogleTest for the native test suite. Set FETCHCONTENT_SOURCE_DIR_GOOGLETEST
# to a local checkout to build offline.
include(CTest)
include(FetchContent)
enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL "https://github.com/google/googletest/archive/063de7e9578f82b369302001269680b4b1553359.zip"
    URL_HASH "SHA256=f933817755e14daf4afa36230b994c5e9ab5a0476dbd659b1d70163e876b4b91"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
