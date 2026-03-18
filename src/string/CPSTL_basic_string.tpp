#ifndef CPSTL_BASIC_STRING_CLASS_TPP
#define CPSTL_BASIC_STRING_CLASS_TPP

namespace cpstd {

#ifndef CPSTL_USING_STL

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Helpers
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::InitEmpty() {
        _buffer = cpstd::allocator_traits<allocator_type>::allocate(_alloc, 1);
        _buffer[0] = CharT();
        _size = 0;
        _capacity = 0;
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::DestroyBuffer() {
        if (_buffer) {
            cpstd::allocator_traits<allocator_type>::deallocate(_alloc, _buffer, _capacity + 1);
            _buffer = nullptr;
        }
        _size = 0;
        _capacity = 0;
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::EnsureCapacity(size_type required) {
        if (required <= _capacity) {
            return;
        }

        size_type newCapacity = (_capacity == 0) ? required : _capacity * 2;
        if (newCapacity < required) {
            newCapacity = required;
        }

        pointer newBuffer = cpstd::allocator_traits<allocator_type>::allocate(_alloc, newCapacity + 1);

        for (size_type i = 0; i < _size; ++i) {
            newBuffer[i] = _buffer[i];
        }
        newBuffer[_size] = CharT();

        if (_buffer) {
            cpstd::allocator_traits<allocator_type>::deallocate(_alloc, _buffer, _capacity + 1);
        }

        _buffer = newBuffer;
        _capacity = newCapacity;
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::AssignFromBuffer(const_pointer s, size_type n) {
        if (!s || n == 0) {
            clear();
            return;
        }

        EnsureCapacity(n);
        for (size_type i = 0; i < n; ++i) {
            _buffer[i] = s[i];
        }
        _size = n;
        _buffer[_size] = CharT();
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::AssignFill(size_type n, value_type ch) {
        EnsureCapacity(n);
        for (size_type i = 0; i < n; ++i) {
            _buffer[i] = ch;
        }
        _size = n;
        _buffer[_size] = CharT();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors / Destructor
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string()
        : _buffer(nullptr), _size(0), _capacity(0), _alloc() {
        InitEmpty();
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(const basic_string& str)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(str._alloc) {
        InitEmpty();
        AssignFromBuffer(str._buffer, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(const basic_string& str, const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();
        AssignFromBuffer(str._buffer, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(const basic_string& str, size_type pos, size_type len, const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();

        if (pos > str._size) {
            pos = str._size;
        }

        size_type count = str._size - pos;
        if (len != npos && len < count) {
            count = len;
        }

        AssignFromBuffer(str._buffer + pos, count);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(const CharT* s, const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();
        if (s) {
            AssignFromBuffer(s, traits_type::length(s));
        }
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(const CharT* s, size_type n, const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();
        AssignFromBuffer(s, n);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(size_type n, CharT c, const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();
        AssignFill(n, c);
    }

    template <class CharT, class Traits, class Alloc>
    template <class InputIterator>
    basic_string<CharT, Traits, Alloc>::basic_string(InputIterator first, InputIterator last, const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();
        for (; first != last; ++first) {
            push_back(*first);
        }
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(cpstd::initializer_list<CharT> il, const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();
        append(il);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(basic_string&& str) noexcept
        : _buffer(str._buffer), _size(str._size), _capacity(str._capacity), _alloc(str._alloc) {
        str._buffer = nullptr;
        str._size = 0;
        str._capacity = 0;
        str.InitEmpty();
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::basic_string(basic_string&& str, const allocator_type& alloc)
        : _buffer(nullptr), _size(0), _capacity(0), _alloc(alloc) {
        InitEmpty();
        AssignFromBuffer(str._buffer, str._size);
        str.clear();
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>::~basic_string() {
        DestroyBuffer();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Iterators
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::iterator
    basic_string<CharT, Traits, Alloc>::begin() noexcept {
        return _buffer;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_iterator
    basic_string<CharT, Traits, Alloc>::begin() const noexcept {
        return _buffer;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::iterator
    basic_string<CharT, Traits, Alloc>::end() noexcept {
        return _buffer + _size;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_iterator
    basic_string<CharT, Traits, Alloc>::end() const noexcept {
        return _buffer + _size;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::reverse_iterator
    basic_string<CharT, Traits, Alloc>::rbegin() noexcept {
        return reverse_iterator(end());
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_reverse_iterator
    basic_string<CharT, Traits, Alloc>::rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::reverse_iterator
    basic_string<CharT, Traits, Alloc>::rend() noexcept {
        return reverse_iterator(begin());
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_reverse_iterator
    basic_string<CharT, Traits, Alloc>::rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_iterator
    basic_string<CharT, Traits, Alloc>::cbegin() const noexcept {
        return begin();
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_iterator
    basic_string<CharT, Traits, Alloc>::cend() const noexcept {
        return end();
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_reverse_iterator
    basic_string<CharT, Traits, Alloc>::crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_reverse_iterator
    basic_string<CharT, Traits, Alloc>::crend() const noexcept {
        return const_reverse_iterator(begin());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Capacity
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::size() const noexcept {
        return _size;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::length() const noexcept {
        return _size;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::max_size() const noexcept {
        return cpstd::allocator_traits<allocator_type>::max_size(_alloc) - 1;
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::resize(size_type n) {
        resize(n, CharT());
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::resize(size_type n, CharT c) {
        if (n < _size) {
            _size = n;
            _buffer[_size] = CharT();
            return;
        }

        if (n > _size) {
            EnsureCapacity(n);
            for (size_type i = _size; i < n; ++i) {
                _buffer[i] = c;
            }
            _size = n;
            _buffer[_size] = CharT();
        }
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::capacity() const noexcept {
        return _capacity;
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::reserve(size_type n) {
        if (n > _capacity) {
            EnsureCapacity(n);
        }
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::clear() noexcept {
        _size = 0;
        if (_buffer) {
            _buffer[0] = CharT();
        }
    }

    template <class CharT, class Traits, class Alloc>
    bool basic_string<CharT, Traits, Alloc>::empty() const noexcept {
        return _size == 0;
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::shrink_to_fit() {
        if (_size == _capacity) {
            return;
        }

        pointer newBuffer = cpstd::allocator_traits<allocator_type>::allocate(_alloc, _size + 1);
        for (size_type i = 0; i < _size; ++i) {
            newBuffer[i] = _buffer[i];
        }
        newBuffer[_size] = CharT();

        cpstd::allocator_traits<allocator_type>::deallocate(_alloc, _buffer, _capacity + 1);
        _buffer = newBuffer;
        _capacity = _size;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Element Access
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::reference
    basic_string<CharT, Traits, Alloc>::operator[](size_type pos) {
        return _buffer[pos];
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_reference
    basic_string<CharT, Traits, Alloc>::operator[](size_type pos) const {
        return _buffer[pos];
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::reference
    basic_string<CharT, Traits, Alloc>::at(size_type pos) {
        if (pos >= _size) {
        #if defined(CPSTL_STRING_EXCEPTIONS_ENABLED) && defined(CPSTL_EXCEPTIONS_ENABLED)
            throw "cpstd::basic_string::at out of range";
        #endif
        }
        return _buffer[pos];
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::const_reference
    basic_string<CharT, Traits, Alloc>::at(size_type pos) const {
        if (pos >= _size) {
        #if defined(CPSTL_STRING_EXCEPTIONS_ENABLED) && defined(CPSTL_EXCEPTIONS_ENABLED)
            throw "cpstd::basic_string::at out of range";
        #endif
        }
        return _buffer[pos];
    }

    template <class CharT, class Traits, class Alloc>
    CharT& basic_string<CharT, Traits, Alloc>::back() {
        return _buffer[_size - 1];
    }

    template <class CharT, class Traits, class Alloc>
    const CharT& basic_string<CharT, Traits, Alloc>::back() const {
        return _buffer[_size - 1];
    }

    template <class CharT, class Traits, class Alloc>
    CharT& basic_string<CharT, Traits, Alloc>::front() {
        return _buffer[0];
    }

    template <class CharT, class Traits, class Alloc>
    const CharT& basic_string<CharT, Traits, Alloc>::front() const {
        return _buffer[0];
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::operator+=(const basic_string& str) {
        return append(str);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::operator+=(const CharT* s) {
        return append(s);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::operator+=(CharT c) {
        push_back(c);
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::operator+=(cpstd::initializer_list<CharT> il) {
        return append(il);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::append(const basic_string& str) {
        return append(str._buffer, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::append(const basic_string& str, size_type subpos, size_type sublen) {
        if (subpos > str._size) {
            subpos = str._size;
        }

        size_type count = str._size - subpos;
        if (sublen != npos && sublen < count) {
            count = sublen;
        }

        return append(str._buffer + subpos, count);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::append(const CharT* s) {
        return append(s, traits_type::length(s));
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::append(const CharT* s, size_type n) {
        if (!s || n == 0) {
            return *this;
        }

        EnsureCapacity(_size + n);
        for (size_type i = 0; i < n; ++i) {
            _buffer[_size + i] = s[i];
        }
        _size += n;
        _buffer[_size] = CharT();
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::append(size_type n, CharT c) {
        EnsureCapacity(_size + n);
        for (size_type i = 0; i < n; ++i) {
            _buffer[_size + i] = c;
        }
        _size += n;
        _buffer[_size] = CharT();
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    template <class InputIterator>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::append(InputIterator first, InputIterator last) {
        for (; first != last; ++first) {
            push_back(*first);
        }
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::append(cpstd::initializer_list<CharT> il) {
        return append(il.begin(), il.end());
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::push_back(CharT c) {
        EnsureCapacity(_size + 1);
        _buffer[_size++] = c;
        _buffer[_size] = CharT();
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::assign(const basic_string& str) {
        AssignFromBuffer(str._buffer, str._size);
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::assign(const basic_string& str, size_type subpos, size_type sublen) {
        if (subpos > str._size) {
            subpos = str._size;
        }

        size_type count = str._size - subpos;
        if (sublen != npos && sublen < count) {
            count = sublen;
        }

        AssignFromBuffer(str._buffer + subpos, count);
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::assign(const CharT* s) {
        AssignFromBuffer(s, traits_type::length(s));
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::assign(const CharT* s, size_type n) {
        AssignFromBuffer(s, n);
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::assign(size_type n, CharT c) {
        AssignFill(n, c);
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    template <class InputIterator>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::assign(InputIterator first, InputIterator last) {
        clear();
        return append(first, last);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::assign(cpstd::initializer_list<CharT> il) {
        return assign(il.begin(), il.end());
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::assign(basic_string&& str) noexcept {
        if (this != &str) {
            swap(str);
        }
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::insert(size_type pos, const basic_string& str) {
        return insert(pos, str._buffer, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::insert(size_type pos, const basic_string& str, size_type subpos, size_type sublen) {
        if (subpos > str._size) {
            subpos = str._size;
        }

        size_type count = str._size - subpos;
        if (sublen != npos && sublen < count) {
            count = sublen;
        }

        return insert(pos, str._buffer + subpos, count);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::insert(size_type pos, const CharT* s) {
        return insert(pos, s, traits_type::length(s));
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::insert(size_type pos, const CharT* s, size_type n) {
        if (pos > _size) {
            pos = _size;
        }

        if (!s || n == 0) {
            return *this;
        }

        EnsureCapacity(_size + n);

        for (size_type i = _size + 1; i > pos; --i) {
            _buffer[i + n - 1] = _buffer[i - 1];
        }

        for (size_type i = 0; i < n; ++i) {
            _buffer[pos + i] = s[i];
        }

        _size += n;
        _buffer[_size] = CharT();
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::insert(size_type pos, size_type n, CharT c) {
        if (pos > _size) {
            pos = _size;
        }

        EnsureCapacity(_size + n);

        for (size_type i = _size + 1; i > pos; --i) {
            _buffer[i + n - 1] = _buffer[i - 1];
        }

        for (size_type i = 0; i < n; ++i) {
            _buffer[pos + i] = c;
        }

        _size += n;
        _buffer[_size] = CharT();
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::iterator
    basic_string<CharT, Traits, Alloc>::insert(const_iterator p, size_type n, CharT c) {
        size_type pos = static_cast<size_type>(p - cbegin());
        insert(pos, n, c);
        return begin() + pos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::iterator
    basic_string<CharT, Traits, Alloc>::insert(const_iterator p, CharT c) {
        size_type pos = static_cast<size_type>(p - cbegin());
        insert(pos, 1, c);
        return begin() + pos;
    }

    template <class CharT, class Traits, class Alloc>
    template <class InputIterator>
    typename basic_string<CharT, Traits, Alloc>::iterator
    basic_string<CharT, Traits, Alloc>::insert(iterator p, InputIterator first, InputIterator last) {
        size_type pos = static_cast<size_type>(p - begin());
        for (; first != last; ++first) {
            insert(pos, 1, *first);
            ++pos;
        }
        return begin() + pos;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::insert(const_iterator p, cpstd::initializer_list<CharT> il) {
        size_type pos = static_cast<size_type>(p - cbegin());
        for (typename cpstd::initializer_list<CharT>::const_iterator it = il.begin(); it != il.end(); ++it) {
            insert(pos, 1, *it);
            ++pos;
        }
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::erase(size_type pos, size_type len) {
        if (pos > _size) {
            pos = _size;
        }

        if (len == npos || pos + len > _size) {
            len = _size - pos;
        }

        for (size_type i = pos; i + len <= _size; ++i) {
            _buffer[i] = _buffer[i + len];
        }

        _size -= len;
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::iterator
    basic_string<CharT, Traits, Alloc>::erase(const_iterator p) {
        size_type pos = static_cast<size_type>(p - cbegin());
        erase(pos, 1);
        return begin() + pos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::iterator
    basic_string<CharT, Traits, Alloc>::erase(const_iterator first, const_iterator last) {
        size_type pos = static_cast<size_type>(first - cbegin());
        size_type len = static_cast<size_type>(last - first);
        erase(pos, len);
        return begin() + pos;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(size_type pos, size_type len, const basic_string& str) {
        erase(pos, len);
        return insert(pos, str);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, const basic_string& str) {
        size_type pos = static_cast<size_type>(i1 - cbegin());
        size_type len = static_cast<size_type>(i2 - i1);
        erase(pos, len);
        return insert(pos, str);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(size_type pos, size_type len, const basic_string& str, size_type subpos, size_type sublen) {
        erase(pos, len);
        return insert(pos, str, subpos, sublen);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(size_type pos, size_type len, const CharT* s) {
        erase(pos, len);
        return insert(pos, s);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, const CharT* s) {
        size_type pos = static_cast<size_type>(i1 - cbegin());
        size_type len = static_cast<size_type>(i2 - i1);
        erase(pos, len);
        return insert(pos, s);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(size_type pos, size_type len, const CharT* s, size_type n) {
        erase(pos, len);
        return insert(pos, s, n);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, const CharT* s, size_type n) {
        size_type pos = static_cast<size_type>(i1 - cbegin());
        size_type len = static_cast<size_type>(i2 - i1);
        erase(pos, len);
        return insert(pos, s, n);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(size_type pos, size_type len, size_type n, CharT c) {
        erase(pos, len);
        return insert(pos, n, c);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, size_type n, CharT c) {
        size_type pos = static_cast<size_type>(i1 - cbegin());
        size_type len = static_cast<size_type>(i2 - i1);
        erase(pos, len);
        return insert(pos, n, c);
    }

    template <class CharT, class Traits, class Alloc>
    template <class InputIterator>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, InputIterator first, InputIterator last) {
        size_type pos = static_cast<size_type>(i1 - cbegin());
        size_type len = static_cast<size_type>(i2 - i1);
        erase(pos, len);
        size_type insertPos = pos;
        for (; first != last; ++first) {
            insert(insertPos, 1, *first);
            ++insertPos;
        }
        return *this;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>&
    basic_string<CharT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, cpstd::initializer_list<CharT> il) {
        return replace(i1, i2, il.begin(), il.end());
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::swap(basic_string& str) {
        pointer tmpBuffer = _buffer;
        _buffer = str._buffer;
        str._buffer = tmpBuffer;

        size_type tmpSize = _size;
        _size = str._size;
        str._size = tmpSize;

        size_type tmpCapacity = _capacity;
        _capacity = str._capacity;
        str._capacity = tmpCapacity;

        allocator_type tmpAlloc = _alloc;
        _alloc = str._alloc;
        str._alloc = tmpAlloc;
    }

    template <class CharT, class Traits, class Alloc>
    void basic_string<CharT, Traits, Alloc>::pop_back() {
        if (_size > 0) {
            --_size;
            _buffer[_size] = CharT();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // String Operations
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT, class Traits, class Alloc>
    const CharT* basic_string<CharT, Traits, Alloc>::c_str() const noexcept {
        return _buffer;
    }

    template <class CharT, class Traits, class Alloc>
    const CharT* basic_string<CharT, Traits, Alloc>::data() const noexcept {
        return _buffer;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::allocator_type
    basic_string<CharT, Traits, Alloc>::get_allocator() const noexcept {
        return _alloc;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::copy(CharT* s, size_type len, size_type pos) const {
        if (pos > _size) {
            return 0;
        }

        size_type count = _size - pos;
        if (len < count) {
            count = len;
        }

        for (size_type i = 0; i < count; ++i) {
            s[i] = _buffer[pos + i];
        }
        return count;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find(const basic_string& str, size_type pos) const noexcept {
        return find(str._buffer, pos, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find(const CharT* s, size_type pos) const {
        return find(s, pos, traits_type::length(s));
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find(const CharT* s, size_type pos, size_type n) const {
        if (n == 0) {
            return pos <= _size ? pos : npos;
        }

        if (pos >= _size || n > (_size - pos)) {
            return npos;
        }

        for (size_type i = pos; i + n <= _size; ++i) {
            if (traits_type::compare(_buffer + i, s, n) == 0) {
                return i;
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find(CharT c, size_type pos) const noexcept {
        for (size_type i = pos; i < _size; ++i) {
            if (_buffer[i] == c) {
                return i;
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::rfind(const basic_string& str, size_type pos) const noexcept {
        return rfind(str._buffer, pos, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::rfind(const CharT* s, size_type pos) const {
        return rfind(s, pos, traits_type::length(s));
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::rfind(const CharT* s, size_type pos, size_type n) const {
        if (n == 0) {
            return pos < _size ? pos : _size;
        }

        if (n > _size) {
            return npos;
        }

        size_type start = (_size - n);
        if (pos != npos && pos < start) {
            start = pos;
        }

        for (size_type i = start + 1; i > 0; --i) {
            size_type idx = i - 1;
            if (traits_type::compare(_buffer + idx, s, n) == 0) {
                return idx;
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::rfind(CharT c, size_type pos) const noexcept {
        if (_size == 0) {
            return npos;
        }

        size_type start = (_size - 1);
        if (pos != npos && pos < start) {
            start = pos;
        }

        for (size_type i = start + 1; i > 0; --i) {
            size_type idx = i - 1;
            if (_buffer[idx] == c) {
                return idx;
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_first_of(const basic_string& str, size_type pos) const noexcept {
        return find_first_of(str._buffer, pos, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_first_of(const CharT* s, size_type pos) const {
        return find_first_of(s, pos, traits_type::length(s));
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_first_of(const CharT* s, size_type pos, size_type n) const {
        for (size_type i = pos; i < _size; ++i) {
            for (size_type j = 0; j < n; ++j) {
                if (_buffer[i] == s[j]) {
                    return i;
                }
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_first_of(CharT c, size_type pos) const noexcept {
        return find(c, pos);
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_last_of(const basic_string& str, size_type pos) const noexcept {
        return find_last_of(str._buffer, pos, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_last_of(const CharT* s, size_type pos) const {
        return find_last_of(s, pos, traits_type::length(s));
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_last_of(const CharT* s, size_type pos, size_type n) const {
        if (_size == 0) {
            return npos;
        }

        size_type start = (_size - 1);
        if (pos != npos && pos < start) {
            start = pos;
        }

        for (size_type i = start + 1; i > 0; --i) {
            size_type idx = i - 1;
            for (size_type j = 0; j < n; ++j) {
                if (_buffer[idx] == s[j]) {
                    return idx;
                }
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_last_of(CharT c, size_type pos) const noexcept {
        return rfind(c, pos);
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_first_not_of(const basic_string& str, size_type pos) const noexcept {
        return find_first_not_of(str._buffer, pos, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_first_not_of(const CharT* s, size_type pos) const {
        return find_first_not_of(s, pos, traits_type::length(s));
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_first_not_of(const CharT* s, size_type pos, size_type n) const {
        for (size_type i = pos; i < _size; ++i) {
            bool found = false;
            for (size_type j = 0; j < n; ++j) {
                if (_buffer[i] == s[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return i;
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_first_not_of(CharT c, size_type pos) const noexcept {
        for (size_type i = pos; i < _size; ++i) {
            if (_buffer[i] != c) {
                return i;
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_last_not_of(const basic_string& str, size_type pos) const noexcept {
        return find_last_not_of(str._buffer, pos, str._size);
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_last_not_of(const CharT* s, size_type pos) const {
        return find_last_not_of(s, pos, traits_type::length(s));
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_last_not_of(const CharT* s, size_type pos, size_type n) const {
        if (_size == 0) {
            return npos;
        }

        size_type start = (_size - 1);
        if (pos != npos && pos < start) {
            start = pos;
        }

        for (size_type i = start + 1; i > 0; --i) {
            size_type idx = i - 1;
            bool found = false;
            for (size_type j = 0; j < n; ++j) {
                if (_buffer[idx] == s[j]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                return idx;
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    typename basic_string<CharT, Traits, Alloc>::size_type
    basic_string<CharT, Traits, Alloc>::find_last_not_of(CharT c, size_type pos) const noexcept {
        if (_size == 0) {
            return npos;
        }

        size_type start = (_size - 1);
        if (pos != npos && pos < start) {
            start = pos;
        }

        for (size_type i = start + 1; i > 0; --i) {
            size_type idx = i - 1;
            if (_buffer[idx] != c) {
                return idx;
            }
        }
        return npos;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    basic_string<CharT, Traits, Alloc>::substr(size_type pos, size_type len) const {
        return basic_string(*this, pos, len, _alloc);
    }

    template <class CharT, class Traits, class Alloc>
    int basic_string<CharT, Traits, Alloc>::compare(const basic_string& str) const noexcept {
        size_type minLen = (_size < str._size) ? _size : str._size;
        int cmp = traits_type::compare(_buffer, str._buffer, minLen);
        if (cmp != 0) {
            return cmp;
        }
        if (_size < str._size) {
            return -1;
        }
        if (_size > str._size) {
            return 1;
        }
        return 0;
    }

    template <class CharT, class Traits, class Alloc>
    int basic_string<CharT, Traits, Alloc>::compare(size_type pos, size_type len, const basic_string& str) const {
        return substr(pos, len).compare(str);
    }

    template <class CharT, class Traits, class Alloc>
    int basic_string<CharT, Traits, Alloc>::compare(size_type pos, size_type len, const basic_string& str, size_type subpos, size_type sublen) const {
        return substr(pos, len).compare(str.substr(subpos, sublen));
    }

    template <class CharT, class Traits, class Alloc>
    int basic_string<CharT, Traits, Alloc>::compare(const CharT* s) const {
        basic_string tmp(s);
        return compare(tmp);
    }

    template <class CharT, class Traits, class Alloc>
    int basic_string<CharT, Traits, Alloc>::compare(size_type pos, size_type len, const CharT* s) const {
        return substr(pos, len).compare(s);
    }

    template <class CharT, class Traits, class Alloc>
    int basic_string<CharT, Traits, Alloc>::compare(size_type pos, size_type len, const CharT* s, size_type n) const {
        basic_string tmp(s, n);
        return substr(pos, len).compare(tmp);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Non-member operators
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        basic_string<CharT, Traits, Alloc> result(lhs);
        result.append(rhs);
        return result;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(basic_string<CharT, Traits, Alloc>&& lhs, basic_string<CharT, Traits, Alloc>&& rhs) {
        lhs.append(rhs);
        return cpstd::move(lhs);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(basic_string<CharT, Traits, Alloc>&& lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        lhs.append(rhs);
        return cpstd::move(lhs);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(const basic_string<CharT, Traits, Alloc>& lhs, basic_string<CharT, Traits, Alloc>&& rhs) {
        basic_string<CharT, Traits, Alloc> result(lhs);
        result.append(rhs);
        return result;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs) {
        basic_string<CharT, Traits, Alloc> result(lhs);
        result.append(rhs);
        return result;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(basic_string<CharT, Traits, Alloc>&& lhs, const CharT* rhs) {
        lhs.append(rhs);
        return cpstd::move(lhs);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        basic_string<CharT, Traits, Alloc> result(lhs);
        result.append(rhs);
        return result;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(const CharT* lhs, basic_string<CharT, Traits, Alloc>&& rhs) {
        basic_string<CharT, Traits, Alloc> result(lhs);
        result.append(rhs);
        return result;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(const basic_string<CharT, Traits, Alloc>& lhs, CharT rhs) {
        basic_string<CharT, Traits, Alloc> result(lhs);
        result.push_back(rhs);
        return result;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(basic_string<CharT, Traits, Alloc>&& lhs, CharT rhs) {
        lhs.push_back(rhs);
        return cpstd::move(lhs);
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(CharT lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        basic_string<CharT, Traits, Alloc> result(1, lhs);
        result.append(rhs);
        return result;
    }

    template <class CharT, class Traits, class Alloc>
    basic_string<CharT, Traits, Alloc>
    operator+(CharT lhs, basic_string<CharT, Traits, Alloc>&& rhs) {
        basic_string<CharT, Traits, Alloc> result(1, lhs);
        result.append(rhs);
        return result;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator==(const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept {
        return lhs.compare(rhs) == 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator==(const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        return rhs.compare(lhs) == 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator==(const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs) {
        return lhs.compare(rhs) == 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator!=(const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept {
        return !(lhs == rhs);
    }

    template <class CharT, class Traits, class Alloc>
    bool operator!=(const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class CharT, class Traits, class Alloc>
    bool operator!=(const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs) {
        return !(lhs == rhs);
    }

    template <class CharT, class Traits, class Alloc>
    bool operator<(const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept {
        return lhs.compare(rhs) < 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator<(const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        basic_string<CharT, Traits, Alloc> tmp(lhs);
        return tmp.compare(rhs) < 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator<(const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs) {
        return lhs.compare(rhs) < 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator<=(const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept {
        return lhs.compare(rhs) <= 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator<=(const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        basic_string<CharT, Traits, Alloc> tmp(lhs);
        return tmp.compare(rhs) <= 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator<=(const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs) {
        return lhs.compare(rhs) <= 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator>(const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept {
        return lhs.compare(rhs) > 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator>(const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        basic_string<CharT, Traits, Alloc> tmp(lhs);
        return tmp.compare(rhs) > 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator>(const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs) {
        return lhs.compare(rhs) > 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator>=(const basic_string<CharT, Traits, Alloc>& lhs, const basic_string<CharT, Traits, Alloc>& rhs) noexcept {
        return lhs.compare(rhs) >= 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator>=(const CharT* lhs, const basic_string<CharT, Traits, Alloc>& rhs) {
        basic_string<CharT, Traits, Alloc> tmp(lhs);
        return tmp.compare(rhs) >= 0;
    }

    template <class CharT, class Traits, class Alloc>
    bool operator>=(const basic_string<CharT, Traits, Alloc>& lhs, const CharT* rhs) {
        return lhs.compare(rhs) >= 0;
    }

    template <class CharT, class Traits, class Alloc>
    void swap(basic_string<CharT, Traits, Alloc>& x, basic_string<CharT, Traits, Alloc>& y) {
        x.swap(y);
    }

#endif

}

#endif // CPSTL_BASIC_STRING_CLASS_TPP