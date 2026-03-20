#ifndef CPSTL_TYPE_TRAITS_HELPER_CLASSES_H
#define CPSTL_TYPE_TRAITS_HELPER_CLASSES_H

    #include <CPSTL_BuildSettings.h>
    
    namespace cpstd{

    #if defined(CPSTL_USING_STL)

        template <typename T, T v>
        using integral_constant = std::integral_constant<T, v>;

        template< bool B >
        using bool_constant = cpstd::integral_constant<bool, B>;

        using true_type = cpstd::integral_constant<bool, true>;
        using false_type = cpstd::integral_constant<bool, false>;

    #else
        
        template <class T, T v>
        struct integral_constant {
            static constexpr T value = v;
            using value_type = T;
            using type = integral_constant;

            constexpr operator T() const noexcept { return v; }
            constexpr T operator()() const noexcept { return v; }
        };

        template< bool B >
        using bool_constant = cpstd::integral_constant<bool, B>;

        using true_type = cpstd::integral_constant<bool, true>;
        using false_type = cpstd::integral_constant<bool, false>;

    #endif


    }

#endif//CPSTL_TYPE_TRAITS_HELPER_CLASSES_H