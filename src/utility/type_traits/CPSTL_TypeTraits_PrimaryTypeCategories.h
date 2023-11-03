#ifndef CPSTL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORIES_H
#define CPSTL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORIES_H

    #include <CPSTL_BuildSettings.h>
    #include "CPSTL_TypeTraits.h"
    
    namespace cpstd{

    #if defined(CPSTL_USING_STL)

        template <typename T>
        using is_array = std::is_array<T>;

        template <typename T> 
        inline constexpr bool is_array_v = is_array<T>::value;


        template <typename T>
        using is_class = std::is_class<T>;

        template <typename T> 
        inline constexpr bool is_class_v = is_class_v<T>::value;

        template <typename T>
        using is_enum = std::is_enum<T>;

        template <typename T>
        using is_floating_point = std::is_floating_point<T>;

        template <typename T>
        using is_function = std::is_function<T>;

        template <typename T>
        using is_integral = std::is_integral<T>;

        template <typename T>
        using is_lvalue_reference = std::is_lvalue_reference<T>;

        template <typename T>
        using is_member_function_pointer = std::is_member_function_pointer<T>;

        template <typename T>
        using is_member_object_pointer = std::is_member_object_pointer<T>;

        template <typename T>
        using is_pointer = std::is_pointer <T>;

        template <typename T>
        using is_rvalue_reference = std::is_rvalue_reference<T>;

        template <typename T>
        using is_union = std::is_union <T>;

        template <typename T>
        using is_void = std::is_void  <T>;

    #else 

        template<class T>
        struct is_array : cpstd::false_type {};

        template<class T>
        struct is_array<T[]> : cpstd::true_type {};

        template<class T, size_t N>
        struct is_array<T[N]> : cpstd::true_type {};

        template <typename T> 
        inline constexpr bool is_array_v = is_array<T>::value;



        template<typename T>
        struct is_class : cpstd::integral_constant<bool, __is_class(T)> {};

        template <typename T> 
        inline constexpr bool is_class_v = is_class<T>::value;


        template<typename T>
        struct is_enum {
            static constexpr bool value = __is_enum(T);
        };



        template<typename T>
        struct is_floating_point {
            static constexpr bool value =
                cpstd::is_same<cpstd::remove_cv_t<T>, float>::value ||
                cpstd::is_same<cpstd::remove_cv_t<T>, double>::value ||
                cpstd::is_same<cpstd::remove_cv_t<T>, long double>::value;
        };



        // This primary template is intentionally left undefined
        template <typename>
        struct is_function : cpstd::false_type {};

        // This specialization will be enabled only if the type is a function
        template <typename Ret, typename... Args>
        struct is_function<Ret(Args...)> : cpstd::true_type {};



        template <typename T>
        struct is_integral {
            static constexpr bool value =
                cpstd::is_same_v<T, int> ||
                cpstd::is_same_v<T, long> ||
                cpstd::is_same_v<T, long long> ||
                cpstd::is_same_v<T, short> ||
                cpstd::is_same_v<T, unsigned int> ||
                cpstd::is_same_v<T, unsigned long> ||
                cpstd::is_same_v<T, unsigned long long> ||
                cpstd::is_same_v<T, unsigned short> ||
                cpstd::is_same_v<T, char> ||
                cpstd::is_same_v<T, signed char> ||
                cpstd::is_same_v<T, unsigned char> ||
                cpstd::is_same_v<T, bool>;
        };



        template <typename T>
        struct is_lvalue_reference : cpstd::false_type {};

        template <typename T>
        struct is_lvalue_reference<T&> : cpstd::true_type {};



        template<typename T>
        struct is_member_function_pointer : cpstd::false_type {};

        template<typename T, typename C>
        struct is_member_function_pointer<T C::*> : cpstd::is_function<T> {};

        template<typename T>
        struct is_member_object_pointer : cpstd::false_type {};

        template<typename T, typename C>
        struct is_member_object_pointer<T C::*> : cpstd::true_type {};



        template<typename T>
        struct is_pointer : cpstd::false_type {};

        template<typename T>
        struct is_pointer<T*> : cpstd::true_type {};



        template<typename T>
        struct is_rvalue_reference : cpstd::false_type {};

        template<typename T>
        struct is_rvalue_reference<T&&> : cpstd::true_type {};



        template <typename T>
        struct is_union {
        private:
            template<typename U>
            static constexpr bool check_union(int U::* member) {
                return true;
            }

            template<typename U>
            static constexpr bool check_union(...) {
                return false;
            }

        public:
            static constexpr bool value = check_union<T>(nullptr);
        };


        template<typename T>
        struct is_void {
            static constexpr bool value = cpstd::is_same<void, typename cpstd::remove_cv<T>::type>::value;
        };
    #endif


    }

#endif//CPSTL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORIES_H