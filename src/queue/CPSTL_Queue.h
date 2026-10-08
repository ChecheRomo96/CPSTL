#ifndef CPSTL_QUEUE_TEMPLATE_H
#define CPSTL_QUEUE_TEMPLATE_H

    #include <CPSTL_BuildSettings.h>
    #include <CPutility.h>
    #include <utility/CPSTL_types.h>

    #if defined(CPSTL_USING_STL)
        #include <deque>
        #include <queue>
    #else
        #include "../vector/CPSTL_Vector.h"
    #endif

    namespace cpstd {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //! @brief First-in, first-out container adapter.
        //!
        //! With CPSTL_USING_STL, `cpstd::queue` is `std::queue` (default
        //! container `std::deque`). Otherwise it is an adapter with the
        //! `std::queue` interface whose default container is `cpstd::vector`,
        //! because CPSTL has no `deque` or `list`.
        //!
        //! **Cost of pop.** `pop` uses the container's `pop_front` when it has
        //! one; otherwise, as with the default `cpstd::vector`, it erases the
        //! first element, which moves the remaining elements: O(n). That suits
        //! the short queues of embedded code (and keeps the elements
        //! contiguous, with no allocation once the capacity is reserved); for
        //! long queues pass a container with a constant-time `pop_front`.
        //! `Container` needs `front`, `back`, `push_back`, `emplace_back`,
        //! `size`, `empty`, the comparison operators, `swap`, and either
        //! `pop_front` or `begin` and `erase`.
        //!
        //! **Allocation.** `push` and `emplace` may allocate. With the default
        //! container an allocation failure leaves the queue unchanged; check
        //! `size()` to detect it, or `reserve` the container beforehand (pass
        //! a prepared container to the constructor) for time-critical code.
        //! `pop` never allocates and keeps the capacity.
        //!
        //! **Differences from std.** `emplace` returns nothing (as in C++11;
        //! read `back()` instead), the allocator-extended constructors are not
        //! provided, and `pop` on an empty queue has no effect. `front` and
        //! `back` on an empty queue are undefined, as in std.
        //!
        //! @tparam T Element type.
        //! @tparam Container Underlying sequence container.

        #if defined(CPSTL_USING_STL)

            template <class T, class Container = std::deque<T> >
            using queue = std::queue<T, Container>;

        #else

            namespace detail {
                // Removes the first element: pop_front when the container has
                // one, erase(begin()) otherwise.
                template <class Container>
                auto QueuePopFront(Container& c, int) -> decltype(c.pop_front(), void()) {
                    c.pop_front();
                }

                template <class Container>
                void QueuePopFront(Container& c, long) {
                    c.erase(c.begin());
                }
            }

            template <class T, class Container = cpstd::vector<T> >
            class queue {
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

                queue() : c() {}
                explicit queue(const Container& cont) : c(cont) {}
                explicit queue(Container&& cont) : c(cpstd::move(cont)) {}

                //! @}
                //! @name Element access and capacity
                //! @{

                reference front() { return c.front(); }
                const_reference front() const { return c.front(); }
                reference back() { return c.back(); }
                const_reference back() const { return c.back(); }

                bool empty() const { return c.empty(); }
                size_type size() const { return c.size(); }

                //! @}
                //! @name Modifiers
                //! @{

                //! @brief Appends a copy of `value`; no effect on allocation failure.
                void push(const value_type& value) { c.push_back(value); }
                //! @brief Appends `value` by move; no effect on allocation failure.
                void push(value_type&& value) { c.push_back(cpstd::move(value)); }

                //! @brief Constructs an element at the back from `args`; no effect on allocation failure.
                template <class... Args>
                void emplace(Args&&... args) { c.emplace_back(cpstd::forward<Args>(args)...); }

                //! @brief Removes the front element; no effect when empty.
                void pop() {
                    if (!c.empty()) {
                        detail::QueuePopFront(c, 0);
                    }
                }

                void swap(queue& other) {
                    using cpstd::swap;
                    swap(c, other.c);
                }

                //! @}

                friend bool operator==(const queue& lhs, const queue& rhs) { return lhs.c == rhs.c; }
                friend bool operator!=(const queue& lhs, const queue& rhs) { return lhs.c != rhs.c; }
                friend bool operator<(const queue& lhs, const queue& rhs) { return lhs.c < rhs.c; }
                friend bool operator<=(const queue& lhs, const queue& rhs) { return lhs.c <= rhs.c; }
                friend bool operator>(const queue& lhs, const queue& rhs) { return lhs.c > rhs.c; }
                friend bool operator>=(const queue& lhs, const queue& rhs) { return lhs.c >= rhs.c; }
            };

            template <class T, class Container>
            void swap(queue<T, Container>& lhs, queue<T, Container>& rhs) {
                lhs.swap(rhs);
            }

        #endif
    }

#endif//CPSTL_QUEUE_TEMPLATE_H
