#ifndef CPSTL_MEMORY_H
#define CPSTL_MEMORY_H

    #include <CPSTL_BuildSettings.h>
    #include <utility/CPSTL_allocator.h>

    namespace cpstd{

        template <typename InputIt, typename NoThrowForwardIt>
        NoThrowForwardIt uninitialized_move(InputIt first, InputIt last, NoThrowForwardIt d_first) {
            using ValueType = typename cpstd::iterator_traits<NoThrowForwardIt>::value_type;

            while (first != last) {
                ::new (cpstd::addressof(*d_first)) ValueType(cpstd::move(*first));
                ++first;
                ++d_first;
            }

            return d_first;
        }

        template <class ExecutionPolicy, class ForwardIt, class NoThrowForwardIt>
        NoThrowForwardIt uninitialized_move(ExecutionPolicy&& policy,
                                            ForwardIt first, ForwardIt last,
                                            NoThrowForwardIt d_first) {
            // Placeholder for parallel execution logic
            // In a real implementation, consider parallelizing the move operation based on the policy
            return uninitialized_move(first, last, d_first);
        }
    }


    #include "utility/CPSTL_allocator.h"

#endif//CPSTL_MEMORY_H