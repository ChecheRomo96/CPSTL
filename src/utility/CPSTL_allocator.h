#ifndef CPSTL_ALLOCATOR_CLASS_H
#define CPSTL_ALLOCATOR_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPmemory.h>

    #ifdef CPSTL_USING_STL
        #include <memory>
    #endif

    namespace cpstd{
        #ifdef CPSTL_USING_STL
            template <typename T>
            using allocator = std::allocator<T>;

            template <typename T>
            constexpr T* addressof(T& arg) noexcept {
                return std::addressof(arg);
            }

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
                using size_type = size_type;
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
                    return std::addressof(x);
                }

                const_pointer address(const_reference x) const noexcept {
                    // Get the address of the const referenced object x
                    return std::addressof(x);
                }

                pointer allocate(size_type n, cpstd::allocator<void>::const_pointer hint = 0) {
                    (void)hint;
                #if CPSTL_USING_CPP_ALLOCATION
                    return static_cast<pointer>(::operator new(n * sizeof(T)));
                #elif CPSTL_USING_C_ALLOCATION
                    return static_cast<pointer>(calloc(n , sizeof(T)));
                #else
                    // Unknown allocation method
                    #error "Please specify the memory allocation mode (CPSTL_USING_CPP_ALLOCATION or CPSTL_USING_C_ALLOCATION)"
                #endif
                }

                void deallocate(pointer ptr, size_type n) {
                #if CPSTL_USING_CPP_ALLOCATION
                    ::operator delete(ptr);
                #elif CPSTL_USING_C_ALLOCATION
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
                    #if CPSTL_USING_CPP_ALLOCATION
                        new (ptr) T(std::forward<Args>(args)...);
                    #elif CPSTL_USING_C_ALLOCATION
                        // Using constructor directly (avoiding new)
                        ::new (static_cast<void*>(ptr)) T(std::forward<Args>(args)...);
                    #else
                        // Unknown construction method or error handling
                        #error "Please specify the memory allocation mode (CPSTL_USING_CPP_ALLOCATION or CPSTL_USING_C_ALLOCATION)"
                    #endif
                }

                static void destroy(pointer ptr) {
                #if defined(CPSTL_USING_CPP_ALLOCATION) || defined(CPSTL_USING_C_ALLOCATION)
                    ptr->~T();
                #else
                    #error "Please specify the memory allocation mode (CPSTL_USING_CPP_ALLOCATION or CPSTL_USING_C_ALLOCATION)"
                #endif
                }
            };


        #endif
    }

#endif//CPSTL_ALLOCATOR_CLASS_H