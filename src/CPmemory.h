#ifndef CPSTL_MEMORY_H
#define CPSTL_MEMORY_H

    #include <CPSTL_BuildSettings.h>

    namespace cpstd {
    
        template <typename T>
        struct default_delete;

        template <typename T, typename Deleter = cpstd::default_delete<T>>
        class unique_ptr;

        template <typename T, typename... Args>
        cpstd::unique_ptr<T> make_unique(Args&&... args);
    }

    #include <utility/CPSTL_allocator.h>

    namespace cpstd {

        template <typename InputIt, typename NoThrowForwardIt>
        NoThrowForwardIt uninitialized_move(InputIt first, InputIt last, NoThrowForwardIt d_first) {
            using value_type = typename cpstd::iterator_traits<NoThrowForwardIt>::value_type;

            while (first != last) {
            #if defined(CPSTL_USING_CPP_ALLOCATION)
                ::new (cpstd::addressof(*d_first)) value_type(cpstd::move(*first));
            #elif defined(CPSTL_USING_C_ALLOCATION)
                *d_first = cpstd::move(*first);
            #endif
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


        template<class InputIterator, class ForwardIterator>
        ForwardIterator uninitialized_copy ( InputIterator first, InputIterator last, ForwardIterator result )
        {
          for (; first!=last; ++result, ++first)
            new (static_cast<void*>(&*result))
              typename iterator_traits<ForwardIterator>::value_type(*first);
          return result;
        }

        #if defined(CPSTL_USING_STL)
            template <typename T>
            using default_delete = std::default_delete<T>;
        #else
            template <typename T>
            struct default_delete {
                void operator()(T* p) const {
                    delete p;
                }
            };
        #endif



        #if defined(CPSTL_USING_STL)
            template <typename T, typename Deleter = std::default_delete<T>>
            using unique_ptr = std::unique_ptr<T, Deleter>;
        #else
            template <typename T, typename Deleter = cpstd::default_delete<T>>
            class unique_ptr {
            private:
                T* ptr;
                Deleter deleter;

            public:
                // Constructors
                explicit unique_ptr(T* p = nullptr) noexcept : ptr(p) {}

                // Move constructor
                unique_ptr(unique_ptr&& other) noexcept : ptr(other.release()) {}

                // Move assignment
                unique_ptr& operator=(unique_ptr&& other) noexcept {
                    if (this != &other) {
                        reset(other.release());
                    }
                    return *this;
                }

                // Destructor
                ~unique_ptr() noexcept {
                    reset();
                }

                // Release ownership
                T* release() noexcept {
                    T* released = ptr;
                    ptr = nullptr;
                    return released;
                }

                // Reset pointer
                void reset(T* p = nullptr) noexcept {
                    if (ptr != p) {
                        deleter(ptr);
                        ptr = p;
                    }
                }

                // Accessors
                T* get() const noexcept {
                    return ptr;
                }

                T& operator*() const noexcept {
                    return *ptr;
                }

                T* operator->() const noexcept {
                    return ptr;
                }

                // Conversion to bool
                explicit operator bool() const noexcept {
                    return ptr != nullptr;
                }

                // Disable copy operations
                unique_ptr(const unique_ptr&) = delete;
                unique_ptr& operator=(const unique_ptr&) = delete;
            };
        #endif
    }

    #include <CPfunctional.h>
    
    namespace cpstd {

        #if defined(CPSTL_USING_STL)
            template <typename T, typename Deleter = std::default_delete<T>>
            using make_unique = std::unique_ptr<T, std::default_delete<T>>(new T(std::declval<Args>()...));
        #else
            template <typename T, typename... Args>
            cpstd::unique_ptr<T> make_unique(Args&&... args) {
                return cpstd::unique_ptr<T>(new T(cpstd::forward<Args>(args)...));
            }
        #endif
            
    }

#endif//CPSTL_MEMORY_H