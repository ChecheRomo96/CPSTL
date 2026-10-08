#ifndef CPSTL_STACK_TEMPLATE_H
#define CPSTL_STACK_TEMPLATE_H

    #include <CPSTL_BuildSettings.h>
    #include <CPutility.h>
    #include <utility/CPSTL_types.h>

    #if defined(CPSTL_USING_STL)
        #include <deque>
        #include <stack>
    #else
        #include "../vector/CPSTL_Vector.h"
    #endif

    namespace cpstd {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //! @brief Last-in, first-out container adapter.
        //!
        //! With CPSTL_USING_STL, `cpstd::stack` is `std::stack` (default
        //! container `std::deque`). Otherwise it is an adapter with the
        //! `std::stack` interface whose default container is `cpstd::vector`.
        //! `Container` needs `back`, `push_back`, `emplace_back`, `pop_back`,
        //! `size`, `empty`, the comparison operators and `swap`.
        //!
        //! **Allocation.** `push` and `emplace` may allocate. With the default
        //! container an allocation failure leaves the stack unchanged; check
        //! `size()` to detect it, or `reserve` the container beforehand (pass
        //! a prepared container to the constructor) for time-critical code.
        //!
        //! **Differences from std.** `emplace` returns nothing (as in C++11;
        //! read `top()` instead), the allocator-extended constructors are not
        //! provided, and `pop` on an empty stack has no effect. `top` on an
        //! empty stack is undefined, as in std.
        //!
        //! @tparam T Element type.
        //! @tparam Container Underlying sequence container.

        #if defined(CPSTL_USING_STL)

            template <class T, class Container = std::deque<T> >
            using stack = std::stack<T, Container>;

        #else

            template <class T, class Container = cpstd::vector<T> >
            class stack {
            public:
                using container_type = Container;
                using value_type = typename Container::value_type;
                using size_type = typename Container::size_type;
                using reference = typename Container::reference;
                using const_reference = typename Container::const_reference;

            protected:
                //! @cond INTERNAL
                Container c;
                //! @endcond

            public:
                //! @name Construction
                //! @{

                stack() : c() {}
                explicit stack(const Container& cont) : c(cont) {}
                explicit stack(Container&& cont) : c(cpstd::move(cont)) {}

                //! @}
                //! @name Element access and capacity
                //! @{

                reference top() { return c.back(); }
                const_reference top() const { return c.back(); }

                bool empty() const { return c.empty(); }
                size_type size() const { return c.size(); }

                //! @}
                //! @name Modifiers
                //! @{

                //! @brief Pushes a copy of `value`; no effect on allocation failure.
                void push(const value_type& value) { c.push_back(value); }
                //! @brief Pushes `value` by move; no effect on allocation failure.
                void push(value_type&& value) { c.push_back(cpstd::move(value)); }

                //! @brief Constructs an element on top from `args`; no effect on allocation failure.
                template <class... Args>
                void emplace(Args&&... args) { c.emplace_back(cpstd::forward<Args>(args)...); }

                //! @brief Removes the top element; no effect when empty.
                void pop() {
                    if (!c.empty()) {
                        c.pop_back();
                    }
                }

                void swap(stack& other) {
                    using cpstd::swap;
                    swap(c, other.c);
                }

                //! @}

                friend bool operator==(const stack& lhs, const stack& rhs) { return lhs.c == rhs.c; }
                friend bool operator!=(const stack& lhs, const stack& rhs) { return lhs.c != rhs.c; }
                friend bool operator<(const stack& lhs, const stack& rhs) { return lhs.c < rhs.c; }
                friend bool operator<=(const stack& lhs, const stack& rhs) { return lhs.c <= rhs.c; }
                friend bool operator>(const stack& lhs, const stack& rhs) { return lhs.c > rhs.c; }
                friend bool operator>=(const stack& lhs, const stack& rhs) { return lhs.c >= rhs.c; }
            };

            template <class T, class Container>
            void swap(stack<T, Container>& lhs, stack<T, Container>& rhs) {
                lhs.swap(rhs);
            }

        #endif
    }

#endif//CPSTL_STACK_TEMPLATE_H
