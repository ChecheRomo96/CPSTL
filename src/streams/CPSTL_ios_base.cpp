#include "CPSTL_ios_base.h"

namespace cpstd{
    #if !__has_include(<ios>)
    ////////////////////////////////////////////////////////////////////////////
    // ios_base 

        ////////////////////////////////////////////////////////////////////////
        // Constructors and Destructor

            ios_base::ios_base(){
                _fmtflags = 0;
                _width = 0;
                _precision = 0;
                sync_enabled = false;
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // Formatting

            ios_base::fmtflags ios_base::flags() const{
                return _fmtflags;
            }

            ios_base::fmtflags ios_base::flags(fmtflags fmtfl){
                fmtflags ret = _fmtflags;
                _fmtflags = fmtfl;
                return ret;
            }


            ios_base::fmtflags ios_base::setf(fmtflags fmtfl){
                fmtflags ret = _fmtflags;
                _fmtflags |= fmtfl;
                return ret;
            }

            ios_base::fmtflags ios_base::setf(fmtflags fmtfl, fmtflags mask){
                fmtflags ret = _fmtflags;
                _fmtflags = (fmtfl&mask)|(_fmtflags&~mask);
                return ret;
            }

            void ios_base::unsetf(fmtflags mask){
                _fmtflags &= ~mask;
            }

            streamsize ios_base::width() const{
                return _width;
            }

            streamsize ios_base::width(streamsize wide){
                streamsize ret = _width;
                _width = wide;
                return ret;
            }

            streamsize ios_base::precision() const{
                return _precision;
            }

            streamsize ios_base::precision(streamsize prec){
                streamsize ret = _precision;
                _precision = prec;
                return ret;
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // Formatting

            int ios_base::xalloc(){
                static int index_counter = 0;
                return index_counter++;
            }

            long& ios_base::iword(int idx) {
                if (idx < 0 || idx >= _internalBuffer.size()) {
                    #ifdef CPSTL_EXCEPTIONS_ENABLED
                        throw std::out_of_range("Index out of range");
                    #endif

                    static long dummy = 0; // Return a dummy value if exceptions are disabled
                    return dummy;
                }
                return *reinterpret_cast<long*>(_internalBuffer[idx]);
            }

            void*& ios_base::pword(int idx) {
                if (idx < 0 || idx >= _internalBuffer.size()) {
                    #ifdef CPSTL_EXCEPTIONS_ENABLED
                        throw std::out_of_range("Index out of range");
                    #else
                        static void* null_ptr = nullptr;
                        return null_ptr;
                    #endif
                }
                return _internalBuffer[idx];
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // Formatting

            void ios_base::register_callback(event_callback fn, int index){
                _CallbackVector.push_back(fn);
            }

            bool ios_base::sync_with_stdio(bool sync){
                bool previous_sync = sync_enabled; // Store previous state
                sync_enabled = sync; // Update synchronization state
                return previous_sync; // Return previous state
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // Init
    
            ios_base::Init::Init(){
                
            }

            ios_base::Init::~Init(){
                
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // failure

            #ifdef CPSTL_EXCEPTIONS_ENABLED
              explicit ios_base::failure::failure(const string& msg, const error_code& ec){
                
              }

              explicit ios_base::failure::failure(const char*   msg, const error_code& ec){
                
              }    
            #endif
        //
        ////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////
    // Format flag manipulators (functions)
    
        ////////////////////////////////////////////////////////////////////////
        // Independent flags (switch on):

            ios_base& boolalpha(ios_base& str) {
                str.setf(ios_base::boolalpha);
                return str;
            }

            ios_base& showbase(ios_base& str) {
                str.setf(ios_base::showbase);
                return str;
            }

            ios_base& showpoint(ios_base& str) {
                str.setf(ios_base::showpoint);
                return str;
            }

            ios_base& showpos(ios_base& str) {
                str.setf(ios_base::showpos);
                return str;
            }

            ios_base& skipws(ios_base& str) {
                str.setf(ios_base::skipws);
                return str;
            }

            ios_base& unitbuf(ios_base& str) {
                str.setf(ios_base::unitbuf);
                return str;
            }

            ios_base& uppercase(ios_base& str) {
                str.setf(ios_base::uppercase);
                return str;
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // Independent flags (switch off):

            ios_base& noboolalpha(ios_base& str) {
                str.unsetf(ios_base::boolalpha);
                return str;
            }

            ios_base& noshowbase(ios_base& str) {
                str.unsetf(ios_base::showbase);
                return str;
            }

            ios_base& noshowpoint(ios_base& str) {
                str.unsetf(ios_base::showpoint);
                return str;
            }

            ios_base& noshowpos(ios_base& str) {
                str.unsetf(ios_base::showpos);
                return str;
            }

            ios_base& noskipws(ios_base& str) {
                str.unsetf(ios_base::skipws);
                return str;
            }

            ios_base& nounitbuf(ios_base& str) {
                str.unsetf(ios_base::unitbuf);
                return str;
            }

            ios_base& nouppercase(ios_base& str) {
                str.unsetf(ios_base::uppercase);
                return str;
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // Numerical base format flags ("basefield" flags):

            ios_base& dec(ios_base& str) {
                str.unsetf(ios_base::hex | ios_base::oct);
                return str;
            }

            ios_base& hex(ios_base& str) {
                str.unsetf(ios_base::dec | ios_base::oct);
                return str;
            }

            ios_base& oct(ios_base& str) {
                str.unsetf(ios_base::hex | ios_base::dec);
                return str;
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // Floating-point format flags ("floatfield" flags):

            ios_base& fixed(ios_base& str) {
                str.setf(ios_base::fixed, ios_base::floatfield);
                return str;
            }

            ios_base& scientific(ios_base& str) {
                str.setf(ios_base::scientific, ios_base::floatfield);
                return str;
            }
        //
        ////////////////////////////////////////////////////////////////////////
        // Adustment format flags ("adjustfield" flags):

            ios_base& internal(ios_base& str) {
                str.setf(ios_base::internal, ios_base::adjustfield);
                return str;
            }

            ios_base& left(ios_base& str) {
                str.setf(ios_base::left, ios_base::adjustfield);
                return str;
            }

            ios_base& right(ios_base& str) {
                str.setf(ios_base::right, ios_base::adjustfield);
                return str;
            }
        //
        ////////////////////////////////////////////////////////////////////////


    //
    ////////////////////////////////////////////////////////////////////////////


    
    #endif


}