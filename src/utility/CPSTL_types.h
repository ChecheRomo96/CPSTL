#ifndef CPSTL_TYPES_H
#define CPSTL_TYPES_H

    #if defined CPSTL_USING_STL
        #include <cstddef>
        #include <cstdint>
    #else
        #include <stddef.h>
        #include <stdint.h>
    #endif

    namespace cpstd {

    #ifdef CPSTL_USING_STL
        // Define types using the STL
        using std::size_t;
        using std::ptrdiff_t;
        using std::nullptr_t;

        using std::uint8_t;
        using std::uint16_t;
        using std::uint32_t;
        using std::uint64_t;

        using std::int8_t;
        using std::int16_t;
        using std::int32_t;
        using std::int64_t;

    #else

        using size_t = ::size_t;
        using ptrdiff_t = ::ptrdiff_t;

        using nullptr_t = decltype(nullptr);
        constexpr  nullptr_t nullptr = nullptr;

        using uint8_t = ::uint8_t;
        using uint16_t = ::uint16_t;
        using uint32_t = ::uint32_t;
        using uint64_t = ::uint64_t;

        using int8_t = ::int8_t;
        using int16_t = ::int16_t;
        using int32_t = ::int32_t;
        using int64_t = ::int64_t;
    #endif


    }

#endif  // CPSTL_TYPES_H