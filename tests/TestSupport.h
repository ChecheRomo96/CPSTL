#ifndef CPSTL_TESTS_TEST_SUPPORT_H
#define CPSTL_TESTS_TEST_SUPPORT_H

// Helpers shared by the CPSTL unit tests.

#include <CPSTL.h>

#include <new>
#include <stdlib.h>

namespace cpstl_test {

    //! Counts live instances and copies to check element lifetimes.
    struct Tracked {
        static int Live;
        static int Copies;

        int value;

        explicit Tracked(int v = 0) : value(v) { ++Live; }
        Tracked(const Tracked& other) : value(other.value) { ++Live; ++Copies; }
        Tracked(Tracked&& other) noexcept : value(other.value) { other.value = -1; ++Live; }
        Tracked& operator=(const Tracked& other) { value = other.value; ++Copies; return *this; }
        Tracked& operator=(Tracked&& other) noexcept { value = other.value; other.value = -1; return *this; }
        ~Tracked() { --Live; }

        friend bool operator==(const Tracked& a, const Tracked& b) { return a.value == b.value; }
        friend bool operator<(const Tracked& a, const Tracked& b) { return a.value < b.value; }

        static void Reset() { Live = 0; Copies = 0; }
    };

    //! A type without a default constructor.
    struct NoDefault {
        explicit NoDefault(int v) : value(v) {}
        int value;
        friend bool operator==(const NoDefault& a, const NoDefault& b) { return a.value == b.value; }
    };

#if !defined(CPSTL_USING_STL)

    //! Allocation budget shared by every FailingAllocator: allocations succeed
    //! while it is positive (or negative = unlimited) and return nullptr once it
    //! reaches zero, imitating cpstd::allocator on an exhausted heap.
    struct AllocationBudget {
        static int Remaining;
        static int Outstanding;
    };

    template <class T>
    struct FailingAllocator {
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = cpstd::size_t;
        using difference_type = cpstd::ptrdiff_t;

        template <class U>
        struct rebind {
            using other = FailingAllocator<U>;
        };

        FailingAllocator() noexcept = default;
        template <class U>
        FailingAllocator(const FailingAllocator<U>&) noexcept {}

        pointer allocate(size_type n) {
            if (AllocationBudget::Remaining == 0 || n == 0) {
                return nullptr;
            }
            if (AllocationBudget::Remaining > 0) {
                --AllocationBudget::Remaining;
            }
            ++AllocationBudget::Outstanding;
            return static_cast<pointer>(malloc(n * sizeof(T)));
        }

        void deallocate(pointer p, size_type) {
            if (p != nullptr) {
                --AllocationBudget::Outstanding;
                free(p);
            }
        }

        template <class... Args>
        void construct(pointer p, Args&&... args) {
            ::new (static_cast<void*>(p)) T(cpstd::forward<Args>(args)...);
        }

        void destroy(pointer p) { p->~T(); }

        size_type max_size() const noexcept { return static_cast<size_type>(-1) / sizeof(T); }
    };

    //! Sets the allocation budget for one test and checks for leaks after it.
    struct BudgetScope {
        explicit BudgetScope(int budget) {
            AllocationBudget::Remaining = budget;
            AllocationBudget::Outstanding = 0;
        }
        ~BudgetScope() { AllocationBudget::Remaining = -1; }
    };

#endif

}

#endif
