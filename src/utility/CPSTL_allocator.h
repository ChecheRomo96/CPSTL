#ifndef CPSTL_ALLOCATOR_CLASS_H
#define CPSTL_ALLOCATOR_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPmemory.h>
    #include <CPlimits.h>
    #include <CPutility.h>
    #include "CPSTL_types.h"

    #ifdef CPSTL_USING_STL
        #include <memory>
    #endif

    namespace cpstd{
        #ifdef CPSTL_USING_STL

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
                using reference = value_type&;
                using const_pointer = const value_type*;
                using const_reference = const value_type&;
                using size_type = cpstd::size_t;
                using difference_type = cpstd::ptrdiff_t;

                template <typename U>
                struct rebind {
                    using other = allocator<U>;
                };

                // Default constructor
                allocator() noexcept = default;

                // Copy constructor
                allocator(const allocator& alloc) noexcept = default;

                // Template copy constructor for different allocator types
                template <class U>
                allocator(const allocator<U>& alloc) noexcept {}

                ~allocator() {}

                pointer address(reference x) const noexcept {
                    // Get the address of the referenced object x
                    return cpstd::addressof(x);
                }

                const_pointer address(const_reference x) const noexcept {
                    // Get the address of the const referenced object x
                    return cpstd::addressof(x);
                }

                pointer allocate(size_type n, const_pointer hint = 0) {
                    (void)hint;
                #if defined(CPSTL_USING_CPP_ALLOCATION)
                    return static_cast<pointer>(::operator new(n * sizeof(T)));
                #elif defined(CPSTL_USING_C_ALLOCATION)
                    return static_cast<pointer>(calloc(n , sizeof(T)));
                #else
                    // Unknown allocation method
                    #error "Please specify the memory allocation mode (CPSTL_USING_CPP_ALLOCATION or CPSTL_USING_C_ALLOCATION)"
                #endif
                }

                void deallocate(pointer ptr, size_type n) {
                #if defined(CPSTL_USING_CPP_ALLOCATION)
                    ::operator delete(ptr);
                #elif defined(CPSTL_USING_C_ALLOCATION)
                    free(ptr);
                #else
                    // Unknown deallocation method or error handling
                    #error "Please specify the memory allocation mode (CPSTL_USING_CPP_ALLOCATION or CPSTL_USING_C_ALLOCATION)"
                #endif
                }

                // Maximum size possible to allocate
                size_type max_size() const noexcept {
                    return cpstd::numeric_limits<size_type>::max() / sizeof(value_type);
                }

                template<typename... Args>
                void construct(pointer ptr, Args&&... args) {
                #if defined(CPSTL_USING_CPP_ALLOCATION)
                    new (ptr) value_type(cpstd::forward<Args>(args)...);
                #elif defined(CPSTL_USING_C_ALLOCATION)
                    new (static_cast<void*>(p)) T(cpstd::forward<Args>(args)...);
                #else
                    // Unknown construction method or error handling
                    #error "Please specify the memory allocation mode (CPSTL_USING_CPP_ALLOCATION or CPSTL_USING_C_ALLOCATION)"
                #endif
                }

                static void destroy(pointer ptr) {
                #if defined(CPSTL_USING_CPP_ALLOCATION) || defined(CPSTL_USING_C_ALLOCATION)
                    ptr->~value_type();
                #else
                    #error "Please specify the memory allocation mode (CPSTL_USING_CPP_ALLOCATION or CPSTL_USING_C_ALLOCATION)"
                #endif
                }
            };


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