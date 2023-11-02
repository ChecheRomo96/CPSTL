#ifndef CPSTL_MOVE_H
#define CPSTL_MOVE_H

    #include <CPSTL_BuildSettings.h>
    #include<CPtype_traits.h>    

    namespace cpstd
    {
        template <typename T>
        typename cpstd::remove_reference<T>::type&& move(T&& t) {
            return static_cast<typename cpstd::remove_reference<T>::type&&>(t);
        }

    }

#endif//CPSTL_MOVE_H