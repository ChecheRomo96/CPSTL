#include "TestSupport.h"

namespace cpstl_test {

    int Tracked::Live = 0;
    int Tracked::Copies = 0;

#if !defined(CPSTL_USING_STL)
    int AllocationBudget::Remaining = -1;
    int AllocationBudget::Outstanding = 0;
#endif

}
