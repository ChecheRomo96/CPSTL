#ifndef CPSTL_FPOS_H
#define CPSTL_FPOS_H

    #include <CPSTL_BuildSettings.h>

    namespace cpstd{
        #if __has_include(<ios>)

            template <class stateT> 
            using fpos = std::fpos<stateT>;

            using streampos = std::streampos;
            using wstreampos = std::wstreampos;

        #else
            // Define the fpos class template
            template <typename stateT>
            class fpos {
            public:
                // Constructors
                fpos() noexcept = default;

                // Destructor
                ~fpos() = default;

                // Conversion constructor from streampos
                explicit fpos(streampos pos) noexcept : m_pos(pos) {}

                // Conversion operator to streampos
                operator streampos() const noexcept { return m_pos; }

                // Member functions to access and modify the state
                stateT& state() noexcept { return m_state; }
                const stateT& state() const noexcept { return m_state; }

            private:
                // Private data members
                streampos m_pos;
                stateT m_state; // State associated with the file position

            };

            using streampos = cpstd::fpos<cpstd::mbstate_t>;
            using wstreampos = cpstd::fpos<cpstd::mbstate_t>;
            
        #endif
    }

#endif//CPSTL_FPOS_H