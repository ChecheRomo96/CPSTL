#ifndef CPSTL_MOVE_H
#define CPSTL_MOVE_H

    #include <CPSTL_BuildSettings.h>

    #ifdef CPSTL_USING_STL
    #include<type_traits>    
    #endif

    namespace cpstd
    {

    #ifndef CPSTL_USING_STL
    /**
     *  @defgroup Move Move
     *  @brief Functionality that enables Move semantics.
     */

        /**
         * @ingroup Move
         * @brief remove_reference<T> is a template class that removes any reference qualifiers from a given type.
         * 
         * It provides the member typedef 'type', which represents the type of T without any references.
         * This can be useful when you need to work with the base type of a reference or when implementing move semantics.
         * 
         * @tparam T The original type for which the reference qualifier needs to be removed.
         * 
         * @return The type 'type', which represents the original type T without any references.
         * 
         * Example Usage:
         *   using MyType = remove_reference<int&>::type;
         *   // MyType is now int, as the reference qualifier has been removed
         */
        template <class T>
        struct remove_reference {typedef T type;};

        /**
         * @ingroup Move
         * @brief Specialization for remove_reference<T&>, where T is the original type with an lvalue reference.
         * 
         * This specialization removes the lvalue reference qualifier from T and provides the member typedef 'type'.
         * 
         * @tparam T The original type with an lvalue reference.
         * 
         * @return The type 'type', which represents the original type T without the lvalue reference.
         */
        template <class T>
        struct remove_reference<T&> {typedef T type;};

        /**
         * @ingroup Move
         * @brief Specialization for remove_reference<T&&>, where T is the original type with an rvalue reference.
         * 
         * This specialization removes the rvalue reference qualifier from T and provides the member typedef 'type'.
         * 
         * @tparam T The original type with an rvalue reference.
         * 
         * @return The type 'type', which represents the original type T without the rvalue reference.
         */
        template <class T>
        struct remove_reference<T&&> {typedef T type;};

    #else
        /**
         * @brief Template alias to remove the reference from a type.
         *
         * The `remove_reference` template alias uses the `std::remove_reference` trait to remove the reference from the given type `T`. It provides a non-reference (rvalue) type as the result.
         * @tparam T The type from which to remove the reference.
         */
        template<class T>
        using remove_reference = std::remove_reference<T>;
    #endif

        /** @ingroup Move
         * @brief Used to indicate that an object may be "moved from".
         * 
         * This function allows the efficient transfer of resources from t to another object.
         * In particular, cpstd::move produces an xvalue expression that identifies its argument t. It is exactly equivalent to a static_cast to an rvalue reference type.
         * @param t The object to be moved 
         * @return The object to be moved casted to an RValue 
         */
        template <typename T>
        typename cpstd::remove_reference<T>::type&& move(T&& t){
            return static_cast<typename cpstd::remove_reference<T>::type&&>(t);
        }

    }

#endif//CPSTL_MOVE_H