#ifndef CPSTL_FUNCTIONAL_H
#define CPSTL_FUNCTIONAL_H

    #include <CPSTL_BuildSettings.h>
    #include <CPutility.h>
    #include <CPmemory.h>
    
    namespace cpstd {

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // forward 
            #if defined CPSTL_USING_STL
                template <typename T>
                using forward = std::forward<T>;
            #else
                template <typename T>
                constexpr T&& forward(typename cpstd::remove_reference<T>::type& arg) noexcept {
                    return static_cast<T&&>(arg);
                }

                template <typename T>
                constexpr T&& forward(typename cpstd::remove_reference<T>::type&& arg) noexcept {
                    static_assert(!cpstd::is_lvalue_reference<T>::value, "Can't forward an rvalue as an lvalue.");
                    return static_cast<T&&>(arg);
                }
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // function
        
            #if defined CPSTL_USING_STL
                template <typename ReturnType, typename... Args>
                using function = std::function<ReturnType(Args...)>;
            #else
                template <typename Signature>
                class function;

                template <typename ReturnType, typename... Args>
                class function<ReturnType(Args...)> {
                private:
                    // Base interface for storing and invoking callable objects
                    class Concept {
                    public:
                        virtual ~Concept() = default;
                        virtual ReturnType invoke(Args&&...) const = 0;
                        virtual cpstd::unique_ptr<Concept> clone() const = 0;
                    };

                    // Model template to store and invoke callable objects
                    template <typename F>
                    class Model final : public Concept {
                    public:
                        Model(F&& f) : func(std::forward<F>(f)) {}

                        ReturnType invoke(Args&&... args) const override {
                            return func(std::forward<Args>(args)...);
                        }

                        cpstd::unique_ptr<Concept> clone() const override {
                            return std::make_unique<Model>(func);
                        }

                    private:
                        F func;
                    };

                public:
                    // Constructor for function wrapper
                    template <typename F>
                    function(F&& func) : target(new Model<F>(cpstd::forward<F>(func))) {}

                    // Copy constructor
                    function(const function& other) : target(other.target->clone()) {}

                    // Move constructor
                    function(function&& other) noexcept : target(cpstd::move(other.target)) {}

                    // Assignment operator
                    function& operator=(const function& other) {
                        if (this != &other) {
                            target = other.target->clone();
                        }
                        return *this;
                    }

                    // Move assignment operator
                    function& operator=(function&& other) noexcept {
                        target = std::move(other.target);
                        return *this;
                    }

                    // Function call operator
                    ReturnType operator()(Args... args) const {
                        return target->invoke(cpstd::forward<Args>(args)...);
                    }

                private:
                    // Pointer to the concept base class
                    std::unique_ptr<Concept> target;
                };
            #endif
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

    }
    

#endif//CPSTL_FUNCTIONAL_H