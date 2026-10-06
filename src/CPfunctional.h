#ifndef CPSTL_FUNCTIONAL_H
#define CPSTL_FUNCTIONAL_H

    #include <CPSTL_BuildSettings.h>
    #include <CPmemory.h>
    #include <CPutility.h>
    #include <CPtype_traits.h>
    
    #ifdef CPSTL_USING_STL
        #include <functional>
    #endif

    namespace cpstd {

        //! @brief Type-erased callable, as `std::function`.
        //!
        //! In STL mode this is `std::function`. Otherwise it stores a copy of the
        //! callable on the heap (`new`). Calling an empty function is undefined
        //! (`std::function` throws `bad_function_call`); test it with
        //! `operator bool` first.
        #if defined(CPSTL_USING_STL)

            template <typename Signature>
            using function = std::function<Signature>;

        #else

            template <typename Signature>
            class function;

            template <typename ReturnType, typename... Args>
            class function<ReturnType(Args...)> {
            private:
                class Concept {
                public:
                    virtual ~Concept() {}
                    virtual ReturnType invoke(Args... args) const = 0;
                    virtual Concept* clone() const = 0;
                };

                template <typename F>
                class Model final : public Concept {
                public:
                    explicit Model(const F& f) : func(f) {}
                    explicit Model(F&& f) : func(cpstd::move(f)) {}

                    ReturnType invoke(Args... args) const override {
                        return static_cast<ReturnType>(func(cpstd::forward<Args>(args)...));
                    }

                    Concept* clone() const override { return new Model(func); }

                private:
                    mutable F func;
                };

                template <typename F>
                using Stored = typename cpstd::remove_cv<typename cpstd::remove_reference<F>::type>::type;

                cpstd::unique_ptr<Concept> target;

            public:
                function() noexcept : target() {}
                function(cpstd::nullptr_t) noexcept : target() {}

                template <typename F,
                          typename cpstd::enable_if<!cpstd::is_same<Stored<F>, function>::value, int>::type = 0>
                function(F&& func) : target(new Model<Stored<F>>(cpstd::forward<F>(func))) {}

                function(const function& other) : target(other.target ? other.target->clone() : nullptr) {}
                function(function&& other) noexcept : target(cpstd::move(other.target)) {}

                function& operator=(const function& other) {
                    if (this != &other) {
                        target.reset(other.target ? other.target->clone() : nullptr);
                    }
                    return *this;
                }

                function& operator=(function&& other) noexcept {
                    target = cpstd::move(other.target);
                    return *this;
                }

                function& operator=(cpstd::nullptr_t) noexcept {
                    target.reset();
                    return *this;
                }

                explicit operator bool() const noexcept { return static_cast<bool>(target); }

                ReturnType operator()(Args... args) const {
                    return target->invoke(cpstd::forward<Args>(args)...);
                }
            };

        #endif
    }

#endif//CPSTL_FUNCTIONAL_H
