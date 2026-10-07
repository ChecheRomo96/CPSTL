#ifndef CPSTL_ALLOCATOR_CLASS_H
#define CPSTL_ALLOCATOR_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPlimits.h>
    #include <CPutility.h>
    #include "CPSTL_types.h"

    #if defined(CPSTL_USING_STD_ALLOCATION)
        #include <memory>
    #else
        #include <stdlib.h>
    #endif

    // Placement new is needed to construct elements in raw storage. Hosted
    // toolchains and the Arduino cores provide it through <new>; bare AVR-GCC
    // provides no C++ headers, so CPSTL declares the standard inline form.
    #if defined(__has_include)
        #if __has_include(<new>)
            #include <new>
            #define CPSTL_DETAIL_HAS_NEW_HEADER 1
        #elif __has_include(<new.h>)
            #include <new.h>
            #define CPSTL_DETAIL_HAS_NEW_HEADER 1
        #endif
    #endif

    #if !defined(CPSTL_DETAIL_HAS_NEW_HEADER)
        inline void* operator new(size_t, void* place) noexcept { return place; }
        inline void operator delete(void*, void*) noexcept {}
    #endif

    namespace cpstd{

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //! @brief Default allocator.
        //!
        //! With CPSTL_USING_STD_ALLOCATION this is `std::allocator`. Otherwise
        //! it allocates raw storage with `malloc` (CPSTL_USING_C_ALLOCATION) or
        //! `::operator new(std::nothrow)` (CPSTL_USING_CPP_ALLOCATION) and
        //! returns `nullptr` on failure or size overflow instead of throwing, so
        //! containers can leave themselves unchanged. Elements are constructed
        //! with placement new and destroyed explicitly.

        #if defined(CPSTL_USING_STD_ALLOCATION)

            template <typename T>
            constexpr T* addressof(T& arg) noexcept {
                return std::addressof(arg);
            }

            template <typename T>
            using allocator = std::allocator<T>;

            template <typename T>
            using allocator_traits = std::allocator_traits<T>;

        #else

            template <typename T>
            constexpr T* addressof(T& arg) noexcept {
                return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
            }

            template <typename T>
            class allocator {
            public:
                using value_type = T;
                using pointer = value_type*;
                using reference       = value_type&;
                using const_pointer = const value_type*;
                using const_reference = const value_type&;
                using void_pointer        = void*;
                using const_void_pointer  = const void*;
                using size_type = cpstd::size_t;
                using difference_type = cpstd::ptrdiff_t;

                template <typename U>
                struct rebind {
                    using other = allocator<U>;
                };

                allocator() noexcept = default;
                allocator(const allocator& alloc) noexcept = default;
                template <class U>
                allocator(const allocator<U>&) noexcept {}
                ~allocator() {}

                pointer address(reference x) const noexcept {
                    return cpstd::addressof(x);
                }

                const_pointer address(const_reference x) const noexcept {
                    return cpstd::addressof(x);
                }

                //! @brief Returns raw storage for `n` objects, or `nullptr` when
                //! `n` is zero, the size overflows, or memory is exhausted.
                pointer allocate(size_type n, const_pointer hint = 0) noexcept {
                    (void)hint;
                    if (n == 0 || n > max_size()) {
                        return nullptr;
                    }
                #if defined(CPSTL_USING_CPP_ALLOCATION)
                    return static_cast<pointer>(::operator new(n * sizeof(T), std::nothrow));
                #else
                    return static_cast<pointer>(malloc(n * sizeof(T)));
                #endif
                }

                void deallocate(pointer ptr, size_type n) noexcept {
                    (void)n;
                    if (ptr == nullptr) {
                        return;
                    }
                #if defined(CPSTL_USING_CPP_ALLOCATION)
                    ::operator delete(static_cast<void*>(ptr));
                #else
                    free(static_cast<void*>(ptr));
                #endif
                }

                size_type max_size() const noexcept {
                    return cpstd::numeric_limits<size_type>::max() / sizeof(value_type);
                }

                template<typename... Args>
                void construct(pointer ptr, Args&&... args) {
                    ::new (static_cast<void*>(ptr)) value_type(cpstd::forward<Args>(args)...);
                }

                static void destroy(pointer ptr) {
                    ptr->~value_type();
                }
            };

            template <typename T, typename U>
            bool operator==(const allocator<T>&, const allocator<U>&) noexcept { return true; }

            template <typename T, typename U>
            bool operator!=(const allocator<T>&, const allocator<U>&) noexcept { return false; }

            template <typename Alloc>
            struct allocator_traits {
                using allocator_type = Alloc;
                using value_type = typename Alloc::value_type;
                using pointer = typename Alloc::pointer;
                using const_pointer = typename Alloc::const_pointer;
                using reference = typename Alloc::reference;
                using const_reference = typename Alloc::const_reference;
                using size_type = typename Alloc::size_type;
                using difference_type = typename Alloc::difference_type;

                template <typename U>
                struct rebind {
                    using other = typename Alloc::template rebind<U>::other;
                };

                static pointer allocate(allocator_type& alloc, size_type n) {
                    return alloc.allocate(n);
                }

                static void deallocate(allocator_type& alloc, pointer p, size_type n) {
                    alloc.deallocate(p, n);
                }

                template <typename... Args>
                static void construct(allocator_type& alloc, pointer p, Args&&... args) {
                    alloc.construct(p, cpstd::forward<Args>(args)...);
                }

                static void destroy(allocator_type& alloc, pointer p) {
                    alloc.destroy(p);
                }

                static size_type max_size(const allocator_type& alloc) noexcept {
                    return alloc.max_size();
                }
            };

        #endif
    }

#endif//CPSTL_ALLOCATOR_CLASS_H
