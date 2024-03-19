#include "CPSTL_basic_ios.h"

namespace cpstd{
#if !__has_include(<ios>)

    // Constructors

        template <class charT, class traits>
        basic_ios<charT, traits>::basic_ios(basic_streambuf<charT, traits>* sb)
        : tie_(nullptr), fill_(traits::to_char_type(' ')){
            init(sb);
        }

        template <class charT, class traits>
        basic_ios<charT, traits>::basic_ios()
        : tie_(nullptr), fill_(traits::to_char_type(' ')){
            init(nullptr);
        }

        template <class charT, class traits>
        basic_ios<charT, traits>::~basic_ios(){
        }

    // State flag functions:

        template <class charT, class traits>
        bool basic_ios<charT, traits>::good() const{
            return rdstate() == goodbit;
        }

        template <class charT, class traits>
        bool basic_ios<charT, traits>::eof() const {
            return (rdstate() & ios_base::eofbit);
        }

        template <class charT, class traits>
        bool basic_ios<charT, traits>::fail() const {
            return (rdstate() & (ios_base::failbit | ios_base::badbit));
        }

        template <class charT, class traits>
        bool basic_ios<charT, traits>::bad() const {
            return (rdstate() & ios_base::badbit);
        }

        template <class charT, class traits>
        bool basic_ios<charT, traits>::operator!() const{
            if(fail()){ return false; }
            return true;
        }

        template <class charT, class traits>
        basic_ios<charT, traits>::operator bool() const{
            return (fail()) ? false : true;
        }

        template <class charT, class traits>
        typename basic_ios<charT, traits>::iostate basic_ios<charT, traits>::rdstate() const{
            return state_;
        }

        template <class charT, class traits>
        void basic_ios<charT, traits>::setstate (iostate state) {
            clear(rdstate()|state);
        }

        template <class charT, class traits>
        void basic_ios<charT, traits>::clear (iostate state){
            state_ = state;
        }
        
    // Formatting:  

        template <class charT, class traits>
        basic_ios<charT, traits>& basic_ios<charT, traits>::copyfmt(const basic_ios<charT, traits>& rhs){
            flags(rhs.flags());
            width(rhs.width());
            precision(rhs.precision());
            // imbue(rhs.getloc()); // Not yet implemented
            fill(rhs.fill());
            tie(rhs.tie());
            exceptions(rhs.exceptions());

            return *this;
        }

        template <class charT, class traits>
        charT basic_ios<charT, traits>::fill() const{
            return fill_;
        }

        template <class charT, class traits>
        charT basic_ios<charT, traits>::fill (charT fillch){
            charT oldFill = fill_;
            fill_ = fillch;
            return oldFill;
        }

    // Other:

        template <class charT, class traits>
        typename basic_ios<charT, traits>::iostate basic_ios<charT, traits>::exceptions() const{
            return exceptions_;
        }

        template <class charT, class traits>
        void basic_ios<charT, traits>::exceptions (iostate except){    
            exceptions_ = except;
        }

        //template <class charT, class traits>
        // locale imbue (const locale& loc){
        //
        //}
        
        template <class charT, class traits>
        basic_ostream<charT, traits>* basic_ios<charT, traits>::tie() const{
            return tie_;
        }

        template <class charT, class traits>
        basic_ostream<charT, traits>* basic_ios<charT, traits>::tie (basic_ostream<charT, traits>* tiestr){
            basic_ostream<charT, traits>* old_tie = tie_;
            tie_ = tiestr;
            return old_tie;
        }

        template <class charT, class traits>
        basic_streambuf<charT,traits>* basic_ios<charT, traits>::rdbuf() const{
            return streambuf_;
        }

        template <class charT, class traits>
        basic_streambuf<charT,traits>* basic_ios<charT, traits>::rdbuf (basic_streambuf<charT,traits>* sb){
            basic_streambuf<charT, traits>* old_buf = streambuf_;
            streambuf_ = sb;
            return old_buf;
        }
                
    //Protected member functions

        template <class charT, class traits>
        void basic_ios<charT, traits>::init(basic_streambuf<charT,traits>* sb){
            streambuf_ = sb;

            // Initialize internal flags and member variables
            if (sb) {
                // If sb is not null, set rdstate to goodbit
                state_ = goodbit;
            } else {
                // If sb is null, set rdstate to badbit
                state_ = badbit;
            }
            
            // Initialize other member variables
            exceptions_ = goodbit;
            fill_ = traits::to_char_type(' '); // Initialize fill with whitespace
            flags(skipws | dec); // Set flags to skip whitespace and use decimal base
            width(0); // Initialize width to 0
            precision(6); // Initialize precision to 6

            // Initialize the tie pointer to null
            tie_ = nullptr;

            // Initialize the internal extensible array (iword, pword) as empty
            _internalBuffer.clear();
            _CallbackVector.clear();
        }

        template <class charT, class traits>
        void basic_ios<charT, traits>::move (basic_ios<charT, traits>&  x){
            // Move the data from x to the current object
            state_ = std::move(x.state_);
            exceptions_ = std::move(x.exceptions_);
            fill_ = std::move(x.fill_);
            tie_ = std::move(x.tie_);
            _internalBuffer = std::move(x._internalBuffer);
            _CallbackVector = std::move(x._CallbackVector);

            // Reset x's members
            x.state_ = goodbit;
            x.exceptions_ = goodbit;
            x.fill_ = traits::to_char_type(' '); // Reset fill to default value
            x.tie_ = nullptr;
            x._internalBuffer.clear();
            x._CallbackVector.clear();
        }

        template <class charT, class traits>
        void basic_ios<charT, traits>::move (basic_ios<charT, traits>&& x){
            // Move the data from x to the current object
            state_ = std::move(x.state_);
            exceptions_ = std::move(x.exceptions_);
            fill_ = std::move(x.fill_);
            tie_ = std::move(x.tie_);
            _internalBuffer = std::move(x._internalBuffer);
            _CallbackVector = std::move(x._CallbackVector);

            // Reset x's members
            x.state_ = goodbit;
            x.exceptions_ = goodbit;
            x.fill_ = traits::to_char_type(' '); // Reset fill to default value
            x.tie_ = nullptr;
            x._internalBuffer.clear();
            x._CallbackVector.clear();
        }

        template <class charT, class traits>
        void basic_ios<charT, traits>::swap(basic_ios<charT, traits>& x) noexcept{
            using cpstd::swap; // Import std::swap

            // Swap each member individually
            swap(state_, x.state_);
            swap(exceptions_, x.exceptions_);
            swap(fill_, x.fill_);
            swap(tie_, x.tie_);
            swap(_internalBuffer, x._internalBuffer);
            swap(_CallbackVector, x._CallbackVector);
        }

        template <class charT, class traits>
        void basic_ios<charT, traits>::set_rdbuf(basic_streambuf<char_type,traits_type>* sb){
            using cpstd::swap; // Import std::swap

            // Swap each member individually
            swap(this->state_, sb->state_);
            swap(this->exceptions_, sb->exceptions_);
            swap(this->fill_, sb->fill_);
            swap(this->tie_, sb->tie_);
            swap(this->_internalBuffer, sb->_internalBuffer);
            swap(this->_CallbackVector, sb->_CallbackVector);
        }

#endif
}
