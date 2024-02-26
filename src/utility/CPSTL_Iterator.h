#ifndef CPSTL_ITERATOR_CLASS_H
#define CPSTL_ITERATOR_CLASS_H

    #include <CPSTL_BuildSettings.h>
    #include <CPtype_traits.h>    
    #include <CPiterator.h>

    
    #if defined(CPSTL_USING_STL)
        #include <iterator>
    #endif

    namespace cpstd {

    // Container version of std::end
    template <class Container>
    auto end(Container& cont) -> decltype(cont.end()) {
        return cont.end();
    }

    // Const Container version of std::end
    template <class Container>
    auto end(const Container& cont) -> decltype(cont.end()) {
        return cont.end();
    }

    // Array version of std::end
    template <class T, size_t N>
    constexpr T* end(T (&arr)[N]) noexcept {
        return arr + N;
    }

    // Container version of std::begin
    template <class Container>
    auto begin(Container& cont) -> decltype(cont.begin()) {
        return cont.begin();
    }

    // Const Container version of std::begin
    template <class Container>
    auto begin(const Container& cont) -> decltype(cont.begin()) {
        return cont.begin();
    }

    // Array version of std::begin
    template <class T, size_t N>
    constexpr T* begin(T (&arr)[N]) noexcept {
        return arr;
    }


    #if defined(CPSTL_USING_STL)
        // Conceptual representation of std::iterator as a base class
        template <class Category, class T, class Distance = cpstd::ptrdiff_t,
        class Pointer = T*, class Reference = T&>
        struct iterator {
            using value_type = T;
            using difference_type = Distance;
            using pointer = Pointer;
            using reference = Reference;
            using iterator_category = Category;
        };

        using input_iterator_tag = std::input_iterator_tag;
        using output_iterator_tag = std::output_iterator_tag;
        using forward_iterator_tag = std::forward_iterator_tag;
        using bidirectional_iterator_tag = std::bidirectional_iterator_tag;
        using random_access_iterator_tag = std::random_access_iterator_tag;

        //template <class Category, class T, class Distance = cpstd::ptrdiff_t,class Pointer = T*, class Reference = T&>

        template<typename Iterator>
        using iterator_traits = std::iterator_traits<Iterator>;

        template <typename InputIt, typename Distance>
        void advance(InputIt& it, Distance n) {
            std::advance(it, n);
        }

        template <typename InputIt>
        typename iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
            return std::distance(first, last);
        }

        template <typename InputIt, typename Distance>
        InputIt next(InputIt it, Distance n) {
            return std::next(it, n);
        }

        template <typename BidirIt, typename Distance>
        BidirIt prev(BidirIt it, Distance n) {
            return std::prev(it, n);
        }

        template<typename T>
        using reverse_iterator = std::reverse_iterator<T>;
    #else

        template<class Iterator> struct iterator_traits;
        template<class T> struct iterator_traits<T*>;
        template<class Category, class T, class Distance = cpstd::ptrdiff_t, class Pointer = T*, class Reference = T&> struct iterator;


        struct input_iterator_tag {};
        struct output_iterator_tag {};

        struct forward_iterator_tag : public input_iterator_tag {};
        struct bidirectional_iterator_tag : public forward_iterator_tag {};
        struct random_access_iterator_tag : public bidirectional_iterator_tag {};

        template <class InputIterator, class Distance> void advance(InputIterator& i, Distance n){
            while(n > 0){
                --n;
                ++i;
            }
        }

        template <class InputIterator> typename iterator_traits<InputIterator>::difference_type 
            distance(InputIterator first, InputIterator last) {    
            typename iterator_traits<InputIterator>::difference_type d = 0;
            while(first++ !=last){
                d++;
            }
            return d;
        }

        // subclause _lib.predef.iterators_, predefined iterators:
        template <class Iterator> class reverse_iterator;
        template <class Iterator> bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
        template <class Iterator> bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
        template <class Iterator> bool operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
        template <class Iterator> bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
        template <class Iterator> bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
        template <class Iterator> bool operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
        template <class Iterator> typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
        template <class Iterator> reverse_iterator<Iterator> operator+( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x);
        template <class Container> class back_insert_iterator;
        template <class Container> back_insert_iterator<Container> back_inserter(Container& x);
        template <class Container> class front_insert_iterator;
        template <class Container> front_insert_iterator<Container> front_inserter(Container& x);
        template <class Container> class insert_iterator;
        template <class Container, class Iterator> insert_iterator<Container> inserter(Container& x, Iterator i);

        template<class Iterator> struct iterator_traits {
            typedef typename Iterator::difference_type difference_type;
            typedef typename Iterator::value_type value_type;
            typedef typename Iterator::pointer pointer;
            typedef typename Iterator::reference reference;
            typedef typename Iterator::iterator_category iterator_category;
        };

        //Pointer specialization - required by standard
        template<class T> struct iterator_traits<T*> {
            typedef ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef random_access_iterator_tag iterator_category;
        };


        template <class Category, class T, class Distance, class Pointer, class Reference> 
        struct iterator {
            typedef T         value_type;
            typedef Distance  difference_type;
            typedef Pointer   pointer;
            typedef Reference reference;
            typedef Category  iterator_category;
        };


        template <class Iterator> class reverse_iterator
        : public iterator<typename iterator_traits<Iterator>::iterator_category,
        typename iterator_traits<Iterator>::value_type, typename iterator_traits<Iterator>::difference_type,
        typename iterator_traits<Iterator>::pointer, typename iterator_traits<Iterator>::reference> {
        protected:
            Iterator current;
            friend bool operator== <Iterator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);
            friend bool operator< <Iterator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y);

        public:
            typedef Iterator iterator_type;

            reverse_iterator() : current(){};
            explicit reverse_iterator(Iterator x) : current(x) { }
            template<class U> reverse_iterator(const reverse_iterator<U> &x) : current(x.base()){}

            Iterator base() const { return current; }        // explicit

            typename iterator_traits<Iterator>::reference operator*() const { Iterator tmp = current; return *--tmp; }
            typename iterator_traits<Iterator>::pointer   operator->() const { return &(operator*()); }
            typename iterator_traits<Iterator>::reference operator[](typename iterator_traits<Iterator>::difference_type n) const{
                return current[-n-1];
            }

            reverse_iterator& operator++(){ --current; return *this;    }
            reverse_iterator  operator++(int) {reverse_iterator tmp = *this; --current; return tmp; }
            reverse_iterator& operator--() { ++ current; return *this; }
            reverse_iterator  operator--(int) {reverse_iterator tmp = *this; ++current; return tmp; }

            reverse_iterator  operator+ (typename iterator_traits<Iterator>::difference_type n) const{
                reverse_iterator retval( *this );
                retval+=n;
                return retval;
            }
            reverse_iterator& operator+=(typename iterator_traits<Iterator>::difference_type n){
                current -= n;
                return *this;
            }
            reverse_iterator operator- (typename iterator_traits<Iterator>::difference_type n) const{
                reverse_iterator retval( *this );
                retval-=n;
                return retval;
            }
            reverse_iterator& operator-=(typename iterator_traits<Iterator>::difference_type n){
                current += n;
                return *this;
            }
        };


        template <class Iterator> bool
        operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
            return x.base() == y.base();
        }
        template <class Iterator> bool
            operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {    
            return x.base() < y.base();
        }
        template <class Iterator> bool
            operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {    
            return x.base() != y.base();
        }
        template <class Iterator> bool
            operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {    
            return x.base() > y.base();
        }
        template <class Iterator> bool
            operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {    
            return x.base() >= y.base();
        }
        template <class Iterator> bool
            operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {    
            return x.base() <= y.base();
        }
        template <class Iterator> typename reverse_iterator<Iterator>::difference_type
            operator-( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {    
            return y.base() - x.base();
        }
        template <class Iterator> reverse_iterator<Iterator>
            operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {    
            return reverse_iterator<Iterator> (x.base() - n);
        }

        template <class Container> 
        class back_insert_iterator : public iterator<output_iterator_tag,void,void,void,void> {
            protected:
                Container& container;
            public:
            typedef Container container_type;
            explicit back_insert_iterator(Container& x):container(x) {};
            back_insert_iterator<Container>& operator=(const typename Container::value_type& value){
                container.push_back(value);
                return *this;
            }
            back_insert_iterator<Container>& operator*(){
                return *this;
            }
            back_insert_iterator<Container>& operator++(){
                return *this;
            }
            back_insert_iterator<Container>  operator++(int){
                return *this;
            }
        };


        template <class Container> back_insert_iterator<Container>
        back_inserter(Container& x) {
            return back_insert_iterator<Container>(x);
        }

        template <class Container> 
        class front_insert_iterator : public iterator<output_iterator_tag,void,void,void,void> {
        protected:
            Container& container;
        public:
            typedef Container container_type;
            explicit front_insert_iterator(Container& x): container(x) {}
            front_insert_iterator<Container>& operator=(const typename Container::value_type& value){
                container.push_front(value);
                return *this;
            }

            front_insert_iterator<Container>& operator*() { return *this; }
            front_insert_iterator<Container>& operator++() { return *this; }
            front_insert_iterator<Container> operator++(int) { return *this; }
        };


        template <class Container> 
        front_insert_iterator<Container> front_inserter(Container& x) {
            return front_insert_iterator<Container>(x);
        }

        template <class Container> 
        class insert_iterator : public iterator<output_iterator_tag,void,void,void,void> {
        protected:
            Container& container;
            typename Container::iterator iter;
        public:
            typedef Container container_type;
            insert_iterator(Container& x, typename Container::iterator i) : container(x), iter(i) {}
            insert_iterator<Container>& operator=(const typename Container::value_type& value){
                iter = container.insert(iter, value);
                ++iter;
                return *this;
            }
            insert_iterator<Container>& operator*() { return *this; } 
            insert_iterator<Container>& operator++() { return *this; }
            insert_iterator<Container> operator++(int) { return *this; }
        };

        template <class Container, class Iterator> insert_iterator<Container>
            inserter(Container& x, Iterator i) {
            return insert_iterator<Container>(x,typename Container::iterator(i));
        }

    #endif
    }

#endif//CPSTL_ITERATOR_CLASS_H
