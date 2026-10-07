#ifndef CPSTL_MEMORY_H
#define CPSTL_MEMORY_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>
    #include <type_traits/CPSTL_TypeTraits.h>
    #include <CPutility.h>

    #if defined(CPSTL_USING_STL)
        #include <memory>
    #endif

    namespace cpstd {
    
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

                // Converting move constructor (derived to base, like std::unique_ptr)
                template <typename U, typename E,
                          typename cpstd::enable_if<cpstd::is_convertible<U*, T*>::value, int>::type = 0>
                unique_ptr(unique_ptr<U, E>&& other) noexcept : ptr(other.release()) {}

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
                    T* old = ptr;
                    ptr = p;
                    if (old != nullptr && old != p) {
                        deleter(old);
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

    #include <utility/CPSTL_allocator.h>

    namespace cpstd {

        //! @brief Move-constructs `[first, last)` into the raw storage at `d_first`.
        template <typename InputIt, typename NoThrowForwardIt>
        NoThrowForwardIt uninitialized_move(InputIt first, InputIt last, NoThrowForwardIt d_first) {
            using value_type = typename cpstd::iterator_traits<NoThrowForwardIt>::value_type;
            for (; first != last; ++first, ++d_first) {
                ::new (static_cast<void*>(cpstd::addressof(*d_first))) value_type(cpstd::move(*first));
            }
            return d_first;
        }

        //! @brief Copy-constructs `[first, last)` into the raw storage at `result`.
        template<class InputIterator, class ForwardIterator>
        ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
            using value_type = typename cpstd::iterator_traits<ForwardIterator>::value_type;
            for (; first != last; ++result, ++first) {
                ::new (static_cast<void*>(cpstd::addressof(*result))) value_type(*first);
            }
            return result;
        }
    }

    namespace cpstd{
    #if defined(CPSTL_USING_STL) && CPSTL_CPLUSPLUS >= 201402L
        using std::make_unique;
    #else
        //! @brief Allocates a `T` with `new` and wraps it (single objects only).
        template <typename T, typename... Args>
        cpstd::unique_ptr<T> make_unique(Args&&... args) {
            return cpstd::unique_ptr<T>(new T(cpstd::forward<Args>(args)...));
        }
    #endif
    }

#endif