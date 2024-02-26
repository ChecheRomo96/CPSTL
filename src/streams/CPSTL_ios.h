#ifndef CPSTL_ISO_IMPLEMENTATION_H
#define CPSTL_ISO_IMPLEMENTATION_H

    #include <CPSTL_BuildSettings.h>

    namespace cpstd{

    #if defined(CPSTL_USING_STL)

        using ios_base = std::ios_base;
        using streamsize = std::streamsize;
    #else

        typedef size_t streamsize;

        class ios_base{
        public:
            enum class fmtflags : uint16_t{
                // Independant Flags
                boolalpha   = 0b0000000000000001,
                showbase    = 0b0000000000000010,
                showpoint   = 0b0000000000000100,
                showpos     = 0b0000000000001000,
                skipws      = 0b0000000000010000,
                unitbuf     = 0b0000000000100000,
                uppercase   = 0b0000000001000000,

                // numerical base
                basefield   = 0b0000001110000000,
                dec         = 0b0000000010000000,
                hex         = 0b0000000100000000,
                oct         = 0b0000001000000000,

                // float format
                floatfield  = 0b0000110000000000,
                fixed       = 0b0000010000000000,
                scientific  = 0b0000100000000000,

                // adjustment
                adjustfield = 0b0000110000000000,
                internal    = 0b0000010000000000,
                left        = 0b0000010000000000,
                right       = 0b0000100000000000
            };

            typedef void (*event_callback) (event ev, ios_base& obj, int index);
        protected: 
            ios_base();
            ios_base (const ios_base&) = delete;
        
        private:
            streamsize _width;
            streamsize _precision;

        public:
            virtual ~ios_base();
            
            fmtflags flags() const;
            fmtflags flags (fmtflags fmtfl);

            fmtflags setf (fmtflags fmtfl);
            fmtflags setf (fmtflags fmtfl, fmtflags mask);

            void unsetf (fmtflags mask);

            streamsize width() const;
            streamsize width (streamsize wide);

            streamsize precision() const;
            streamsize precision (streamsize prec);

            //locale getloc() const;
            //locale imbue (const locale& loc);
            
            void register_callback (event_callback fn, int index);
        };

    #endif

    }
    

#endif//CPSTL_ISO_IMPLEMENTATION_H