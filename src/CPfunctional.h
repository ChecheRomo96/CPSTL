#ifndef CPSTL_FUNCTIONAL_H
#define CPSTL_FUNCTIONAL_H

    #include <CPSTL_BuildSettings.h>
    
    #ifdef CPSTL_USING_STL
        #include <functional>
    #endif

    namespace cpstd {
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
                        Model(F&& f) : func(cpstd::forward<F>(f)) {}

                        ReturnType invoke(Args&&... args) const override {
                            return func(cpstd::forward<Args>(args)...);
                        }

                        cpstd::unique_ptr<Concept> clone() const override {
                            return cpstd::make_unique<Model>(func);
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
                        target = cpstd::move(other.target);
                        return *this;
                    }

                    // Function call operator
                    ReturnType operator()(Args... args) const {
                        return target->invoke(cpstd::forward<Args>(args)...);
                    }

                private:
                    // Pointer to the concept base class
                    cpstd::unique_ptr<Concept> target;
                };
            #endif
        //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    }

    #include <CPutility.h>
    #include <CPmemory.h>

    

#endif//CPSTL_FUNCTIONAL_H