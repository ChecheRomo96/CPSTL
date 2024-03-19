#ifndef CPSTL_IOS_BASE_H
#define CPSTL_IOS_BASE_H

    #include <CPSTL_BuildSettings.h>
    #include <CPcwchar.h>
    #include <CPvector.h>

    namespace cpstd{

        ////////////////////////////////////////////////////////////////////////////
        // types 

            #if __has_include(<ios>)
                using streamsize = std::streamsize;
                using streamoff = std::streamoff;
            #else
                typedef size_t streamsize;
                typedef size_t streamoff;
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////
        // ios_base 
        
            #if __has_include(<ios>)
                using ios_base = std::ios_base;
            #else
                class ios_base{
                public:
                    ////////////////////////////////////////////////////////////////
                    // Classes, Types and Enums 

                        ////////////////////////////////////////////////////////////
                        // fmtflags

                            typedef uint16_t fmtflags;

                            static const fmtflags boolalpha   = 0b0000000000000001;
                            static const fmtflags showbase    = 0b0000000000000010;
                            static const fmtflags showpoint   = 0b0000000000000100;
                            static const fmtflags showpos     = 0b0000000000001000;
                            static const fmtflags skipws      = 0b0000000000010000;
                            static const fmtflags unitbuf     = 0b0000000000100000;
                            static const fmtflags uppercase   = 0b0000000001000000;
                        //
                        ////////////////////////////////////////////////////////////
                        // numerical base
                        
                            static const fmtflags basefield   = 0b0000001110000000;
                            static const fmtflags dec         = 0b0000000010000000;
                            static const fmtflags hex         = 0b0000000100000000;
                            static const fmtflags oct         = 0b0000001000000000;
                        //
                        ////////////////////////////////////////////////////////////
                        // float format

                            static const fmtflags floatfield  = 0b0000110000000000;
                            static const fmtflags fixed       = 0b0000010000000000;
                            static const fmtflags scientific  = 0b0000100000000000;
                        //
                        ////////////////////////////////////////////////////////////
                        // adjustment

                            static const fmtflags adjustfield = 0b0000110000000000;
                            static const fmtflags internal    = 0b0000010000000000;
                            static const fmtflags left        = 0b0000010000000000;
                            static const fmtflags right       = 0b0000100000000000;
                        //
                        ////////////////////////////////////////////////////////////
                        // iostate
                                
                            typedef uint8_t iostate;

                            static const iostate goodbit = 0;
                            static const iostate badbit  = 0b001;
                            static const iostate eofbit  = 0b010;
                            static const iostate failbit = 0b100;
                        //
                        ////////////////////////////////////////////////////////////
                        // openmode
                            
                           typedef uint8_t openmode;

                            static const iostate in     = 0b00000001;
                            static const iostate out    = 0b00000010;
                            static const iostate ate    = 0b00000100;
                            static const iostate app    = 0b00001000;
                            static const iostate trunc  = 0b00010000;
                            static const iostate binary = 0b00100000;
                        //
                        ////////////////////////////////////////////////////////////
                        // seekdir
                            
                            typedef uint8_t seekdir;
                            static const seekdir beg = 0;
                            static const seekdir cur = 1;
                            static const seekdir end = 2;
                        //
                        ////////////////////////////////////////////////////////////
                        // event
                                
                            enum class event : uint8_t{
                                copyfmt_event = 0,
                                erase_event = 1,
                                imbue_event = 2
                            };
                        //
                        ////////////////////////////////////////////////////////////
                        // event_callback
                            
                            typedef void (*event_callback) (event ev, ios_base& obj, int index);
                        //
                        ////////////////////////////////////////////////////////////
                        // failure
                        
                            #ifdef CPSTL_EXCEPTIONS_ENABLED
                                class failure : public cpstd::system_error{
                                public:
                                  explicit failure (const string& msg, const error_code& ec = io_errc::stream);
                                  explicit failure (const char*   msg, const error_code& ec = io_errc::stream);
                                };
                            #endif
                        //
                        ////////////////////////////////////////////////////////////
                        // Init
                        
                            class Init {
                            private:
                                static int init_cnt;
                            public:
                                Init();
                                ~Init();
                            };
                        //
                        ////////////////////////////////////////////////////////////
                    //
                    ////////////////////////////////////////////////////////////////
                    

                protected: 

                    ////////////////////////////////////////////////////////////////
                    // Constructors

                        ios_base();
                        ios_base (const ios_base&) = delete;
                    //
                    ////////////////////////////////////////////////////////////////

                public:
                 
                    ////////////////////////////////////////////////////////////////
                    // destructor

                        virtual ~ios_base();
                    //
                    ////////////////////////////////////////////////////////////////
                                        
                protected:

                    ////////////////////////////////////////////////////////////////
                    // protected members
                        
                        fmtflags _fmtflags;
                        streamsize _width;
                        streamsize _precision;

                        bool sync_enabled;
                        cpstd::vector<void*> _internalBuffer;
                        cpstd::vector<event_callback> _CallbackVector;
                    //
                    ////////////////////////////////////////////////////////////////

                public:

                    ////////////////////////////////////////////////////////////////
                    // Formatting

                        fmtflags flags() const;
                        fmtflags flags(fmtflags fmtfl);

                        fmtflags setf(fmtflags fmtfl);
                        fmtflags setf(fmtflags fmtfl, fmtflags mask);

                        void unsetf (fmtflags mask);

                        streamsize width() const;
                        streamsize width(streamsize wide);

                        streamsize precision() const;
                        streamsize precision(streamsize prec);
                    //
                    ////////////////////////////////////////////////////////////////
                    // Locales:
                    
                        //locale getloc() const;
                        //locale imbue (const locale& loc);
                    //
                    ////////////////////////////////////////////////////////////////
                    //Internal extensible array
                    
                        static int xalloc();
                        long& iword (int idx);
                        void*& pword (int idx);
                    //
                    ////////////////////////////////////////////////////////////////
                    // Other
                    
                        void register_callback (event_callback fn, int index);
                        bool sync_with_stdio (bool sync = true);
                    //
                    ////////////////////////////////////////////////////////////////
                };
            #endif
        //
        ////////////////////////////////////////////////////////////////////////////
        // Format flag manipulators (functions)

            ////////////////////////////////////////////////////////////////////////
            // Independent flags (switch on):

                ios_base& boolalpha(ios_base& str);
                ios_base& showbase(ios_base& str);
                ios_base& showpoint(ios_base& str);
                ios_base& showpos(ios_base& str);
                ios_base& skipws(ios_base& str);
                ios_base& unitbuf(ios_base& str);
                ios_base& uppercase(ios_base& str);
            //
            ////////////////////////////////////////////////////////////////////////
            // Independent flags (switch off):

                ios_base& noboolalpha(ios_base& str);
                ios_base& noshowbase(ios_base& str);
                ios_base& noshowpoint(ios_base& str);
                ios_base& noshowpos(ios_base& str);
                ios_base& noskipws(ios_base& str);
                ios_base& nounitbuf(ios_base& str);
                ios_base& nouppercase(ios_base& str);
            //
            ////////////////////////////////////////////////////////////////////////
            // Numerical base format flags ("basefield" flags):

                ios_base& dec(ios_base& str);
                ios_base& hex(ios_base& str);
                ios_base& oct(ios_base& str);
            //
            ////////////////////////////////////////////////////////////////////////
            // Floating-point format flags ("floatfield" flags):

                ios_base& fixed(ios_base& str);
                ios_base& scientific(ios_base& str);
            //
            ////////////////////////////////////////////////////////////////////////
            // Adustment format flags ("adjustfield" flags):

                ios_base& internal(ios_base& str);
                ios_base& left(ios_base& str);
                ios_base& right(ios_base& str);
            //
            ////////////////////////////////////////////////////////////////////////
        //
        ////////////////////////////////////////////////////////////////////////////
        // Other functions

            //const error_category& iostream_category() noexcept;
        //
        ////////////////////////////////////////////////////////////////////////////
    }
    

#endif//CPSTL_IOS_BASE_H