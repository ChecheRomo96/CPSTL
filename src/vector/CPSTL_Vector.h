#ifndef CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H
#define CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H

    #include <CPSTL_BuildSettings.h>
    #include <CPinitializer_list.h>
    #include <CPiterator.h>
    #include <CPmemory.h>
    #include <CPutility.h>
    #include <CPalgorithm.h>
    #include <CPtype_traits.h>
    #include <utility/CPSTL_types.h>
    #include <utility/CPSTL_Move.h>
    #include <utility/CPSTL_allocator.h>

    #if defined(CPSTL_USING_STL)
        #include <vector>
    #endif

    namespace cpstd {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //! @brief Cross-platform dynamic array.
        //!
        //! With CPSTL_USING_STL, `cpstd::vector` is `std::vector`. Otherwise it is
        //! a contiguous, growable array with the `std::vector` interface:
        //! elements are constructed in raw storage with placement new, so `T`
        //! needs no default constructor unless an operation creates elements
        //! without a value, and `push_back`/`emplace_back`/`insert` grow the
        //! capacity geometrically.
        //!
        //! **Memory exhaustion.** The CPSTL allocator returns `nullptr` instead
        //! of throwing. Every operation that needs more storage then has no
        //! effect: the size, capacity and elements stay as they were, so the
        //! caller can detect the failure by checking `size()` or `capacity()`.
        //! A copy constructor that cannot allocate yields an empty vector.
        //! `at()` does not check bounds in this mode; it behaves like
        //! `operator[]`.
        //!
        //! @tparam T Element type.
        //! @tparam Alloc Allocator; `cpstd::allocator<T>` by default.

        #if defined(CPSTL_USING_STL)

            template <class T, class Alloc = std::allocator<T> >
            using vector = std::vector<T, Alloc>;

        #else

            template <class T, class Alloc = cpstd::allocator<T>>
            class vector {
            public:
                using value_type = T;
                using allocator_type = Alloc;
                using reference = value_type&;
                using const_reference = const value_type&;
                using pointer = typename cpstd::allocator_traits<allocator_type>::pointer;
                using const_pointer = typename cpstd::allocator_traits<allocator_type>::const_pointer;
                using iterator = pointer;
                using const_iterator = const_pointer;
                using reverse_iterator = cpstd::reverse_iterator<iterator>;
                using const_reverse_iterator = cpstd::reverse_iterator<const_iterator>;
                using difference_type = cpstd::ptrdiff_t;
                using size_type = cpstd::size_t;

            private:
                using traits = cpstd::allocator_traits<allocator_type>;

                pointer _Buffer;
                size_type _Size;
                size_type _Capacity;
                allocator_type _Alloc;

                // Capacity for at least `needed` elements: double the current
                // one (starting at 1), never below `needed`, never above max_size().
                size_type GrownCapacity(size_type needed) const noexcept {
                    const size_type limit = max_size();
                    size_type grown = (_Capacity == 0) ? 1 : _Capacity;
                    if (grown <= limit / 2) {
                        grown = (_Capacity == 0) ? 1 : _Capacity * 2;
                    } else {
                        grown = limit;
                    }
                    return grown < needed ? needed : grown;
                }

                void DestroyRange(pointer first, pointer last) noexcept {
                    for (; first != last; ++first) {
                        traits::destroy(_Alloc, first);
                    }
                }

                // Moves every element into `storage` (capacity `capacity`),
                // leaving the slots in [gapIndex, gapIndex + gapSize) of the new
                // storage unconstructed, and releases the old storage.
                void AdoptStorage(pointer storage, size_type capacity,
                                  size_type gapIndex = 0, size_type gapSize = 0) noexcept {
                    for (size_type i = 0; i < _Size; ++i) {
                        const size_type target = (i < gapIndex) ? i : i + gapSize;
                        traits::construct(_Alloc, storage + target, cpstd::move(_Buffer[i]));
                        traits::destroy(_Alloc, _Buffer + i);
                    }
                    if (_Buffer != nullptr) {
                        traits::deallocate(_Alloc, _Buffer, _Capacity);
                    }
                    _Buffer = storage;
                    _Capacity = capacity;
                }

                bool Reallocate(size_type capacity) {
                    pointer storage = traits::allocate(_Alloc, capacity);
                    if (storage == nullptr) {
                        return false;
                    }
                    AdoptStorage(storage, capacity);
                    return true;
                }

                // Opens `count` slots at `index`. Slots below the old size hold
                // moved-from elements (assign into them); slots at or above it
                // are raw (construct into them). `constructedEnd` receives the
                // first raw slot of the gap. Returns false, unchanged, when no
                // storage can be obtained.
                bool OpenGap(size_type index, size_type count, size_type& constructedEnd) {
                    const size_type oldSize = _Size;
                    if (count > max_size() - oldSize) {
                        return false;
                    }
                    if (oldSize + count > _Capacity) {
                        const size_type capacity = GrownCapacity(oldSize + count);
                        pointer storage = traits::allocate(_Alloc, capacity);
                        if (storage == nullptr) {
                            return false;
                        }
                        AdoptStorage(storage, capacity, index, count);
                        constructedEnd = index;  // the whole gap is raw
                        return true;
                    }
                    const size_type tail = oldSize - index;
                    if (count <= tail) {
                        for (size_type i = 0; i < count; ++i) {
                            traits::construct(_Alloc, _Buffer + oldSize + i,
                                              cpstd::move(_Buffer[oldSize - count + i]));
                        }
                        for (size_type i = oldSize - count; i > index; --i) {
                            _Buffer[i - 1 + count] = cpstd::move(_Buffer[i - 1]);
                        }
                        constructedEnd = index + count;  // whole gap holds moved-from elements
                    } else {
                        for (size_type i = 0; i < tail; ++i) {
                            traits::construct(_Alloc, _Buffer + index + count + i,
                                              cpstd::move(_Buffer[index + i]));
                        }
                        constructedEnd = oldSize;  // [index, oldSize) moved-from, rest raw
                    }
                    return true;
                }

                // Fills the gap opened by OpenGap from `source[0, count)`.
                template <class Source>
                void FillGap(size_type index, size_type count, size_type constructedEnd, const Source& source) {
                    for (size_type i = 0; i < count; ++i) {
                        if (index + i < constructedEnd) {
                            _Buffer[index + i] = source(i);
                        } else {
                            traits::construct(_Alloc, _Buffer + index + i, source(i));
                        }
                    }
                    _Size += count;
                }

                struct FillSource {
                    const value_type& value;
                    const value_type& operator()(size_type) const { return value; }
                };

                struct ArraySource {
                    const value_type* values;
                    const value_type& operator()(size_type i) const { return values[i]; }
                };

            public:
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @name Construction and assignment
                //! @{

                vector() noexcept : _Buffer(nullptr), _Size(0), _Capacity(0), _Alloc() {}

                explicit vector(const allocator_type& alloc) noexcept
                    : _Buffer(nullptr), _Size(0), _Capacity(0), _Alloc(alloc) {}

                //! @brief `n` value-initialized elements; empty if storage is unavailable.
                explicit vector(size_type n, const allocator_type& alloc = allocator_type()) : vector(alloc) {
                    resize(n);
                }

                //! @brief `n` copies of `value`; empty if storage is unavailable.
                vector(size_type n, const value_type& value, const allocator_type& alloc = allocator_type())
                    : vector(alloc) {
                    resize(n, value);
                }

                //! @brief Copies `[first, last)`; partially filled if storage runs out.
                template <class InputIterator,
                          typename cpstd::enable_if<!cpstd::is_integral<InputIterator>::value, int>::type = 0>
                vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
                    : vector(alloc) {
                    for (; first != last; ++first) {
                        if (!TryEmplaceBack(*first)) {
                            break;
                        }
                    }
                }

                //! @brief Copies `other` into storage of exactly its size; empty on failure.
                vector(const vector& other) : vector(other._Alloc) {
                    CopyFrom(other);
                }

                vector(const vector& other, const allocator_type& alloc) : vector(alloc) {
                    CopyFrom(other);
                }

                //! @brief Takes `source`'s storage and leaves it empty.
                vector(vector&& source) noexcept
                    : _Buffer(source._Buffer), _Size(source._Size), _Capacity(source._Capacity),
                      _Alloc(cpstd::move(source._Alloc)) {
                    source._Buffer = nullptr;
                    source._Size = 0;
                    source._Capacity = 0;
                }

                vector(cpstd::initializer_list<T> list, const allocator_type& alloc = allocator_type())
                    : vector(alloc) {
                    if (list.size() != 0 && Reallocate(list.size())) {
                        for (const value_type& item : list) {
                            traits::construct(_Alloc, _Buffer + _Size, item);
                            ++_Size;
                        }
                    }
                }

                ~vector() {
                    clear();
                    if (_Buffer != nullptr) {
                        traits::deallocate(_Alloc, _Buffer, _Capacity);
                    }
                }

                //! @brief Copies `source`; unchanged if storage is unavailable.
                vector& operator=(const vector& source) {
                    if (this != &source) {
                        AssignRange(source._Buffer, source._Size);
                    }
                    return *this;
                }

                vector& operator=(vector&& source) noexcept {
                    if (this != &source) {
                        clear();
                        if (_Buffer != nullptr) {
                            traits::deallocate(_Alloc, _Buffer, _Capacity);
                        }
                        _Buffer = source._Buffer;
                        _Size = source._Size;
                        _Capacity = source._Capacity;
                        _Alloc = cpstd::move(source._Alloc);
                        source._Buffer = nullptr;
                        source._Size = 0;
                        source._Capacity = 0;
                    }
                    return *this;
                }

                vector& operator=(cpstd::initializer_list<T> list) {
                    AssignRange(list.begin(), list.size());
                    return *this;
                }

                //! @brief Replaces the contents with `[first, last)`; unchanged if storage is unavailable.
                template <class InputIterator,
                          typename cpstd::enable_if<!cpstd::is_integral<InputIterator>::value, int>::type = 0>
                void assign(InputIterator first, InputIterator last) {
                    vector copy(first, last, _Alloc);
                    swap(copy);
                }

                //! @brief Replaces the contents with `n` copies of `value`; unchanged if storage is unavailable.
                void assign(size_type n, const value_type& value) {
                    if (n > _Capacity) {
                        vector copy(n, value, _Alloc);
                        if (copy.size() == n) {
                            swap(copy);
                        }
                        return;
                    }
                    const size_type common = (n < _Size) ? n : _Size;
                    const value_type copy = value;  // `value` may be an element
                    for (size_type i = 0; i < common; ++i) {
                        _Buffer[i] = copy;
                    }
                    for (size_type i = common; i < n; ++i) {
                        traits::construct(_Alloc, _Buffer + i, copy);
                    }
                    DestroyRange(_Buffer + n, _Buffer + _Size);
                    _Size = n;
                }

                void assign(cpstd::initializer_list<T> list) {
                    AssignRange(list.begin(), list.size());
                }

                allocator_type get_allocator() const { return _Alloc; }

                //! @}
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @name Iterators
                //! @{

                iterator begin() noexcept { return _Buffer; }
                const_iterator begin() const noexcept { return _Buffer; }
                iterator end() noexcept { return _Buffer + _Size; }
                const_iterator end() const noexcept { return _Buffer + _Size; }
                reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
                const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
                reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
                const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
                const_iterator cbegin() const noexcept { return begin(); }
                const_iterator cend() const noexcept { return end(); }
                const_reverse_iterator crbegin() const noexcept { return rbegin(); }
                const_reverse_iterator crend() const noexcept { return rend(); }

                //! @}
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @name Capacity
                //! @{

                size_type size() const noexcept { return _Size; }
                size_type capacity() const noexcept { return _Capacity; }
                bool empty() const noexcept { return _Size == 0; }
                size_type max_size() const noexcept { return traits::max_size(_Alloc); }

                //! @brief Ensures room for `new_cap` elements; no effect on failure.
                void reserve(size_type new_cap) {
                    if (new_cap > _Capacity && new_cap <= max_size()) {
                        Reallocate(new_cap);
                    }
                }

                //! @brief Releases unused capacity; no effect on failure.
                void shrink_to_fit() {
                    if (_Capacity == _Size) {
                        return;
                    }
                    if (_Size == 0) {
                        traits::deallocate(_Alloc, _Buffer, _Capacity);
                        _Buffer = nullptr;
                        _Capacity = 0;
                        return;
                    }
                    Reallocate(_Size);
                }

                //! @brief Changes the size, value-initializing new elements; no effect on failure.
                void resize(size_type n) {
                    ResizeImpl(n, ValueInitializer());
                }

                //! @brief Changes the size, copying `value` into new elements; no effect on failure.
                void resize(size_type n, const value_type& value) {
                    ResizeImpl(n, CopyInitializer{value});
                }

                //! @}
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @name Element access
                //! @{

                reference operator[](size_type position) { return _Buffer[position]; }
                const_reference operator[](size_type position) const { return _Buffer[position]; }
                reference at(size_type position) { return _Buffer[position]; }
                const_reference at(size_type position) const { return _Buffer[position]; }
                reference front() { return _Buffer[0]; }
                const_reference front() const { return _Buffer[0]; }
                reference back() { return _Buffer[_Size - 1]; }
                const_reference back() const { return _Buffer[_Size - 1]; }
                pointer data() noexcept { return _Buffer; }
                const_pointer data() const noexcept { return _Buffer; }

                //! @}
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //! @name Modifiers
                //! @{

                //! @brief Appends a copy of `value` (which may be an element); no effect on failure.
                void push_back(const value_type& value) { TryEmplaceBack(value); }

                //! @brief Appends `value` by move; no effect on failure.
                void push_back(value_type&& value) { TryEmplaceBack(cpstd::move(value)); }

                //! @brief Constructs an element at the end from `args`; no effect on failure.
                template <class... Args>
                void emplace_back(Args&&... args) { TryEmplaceBack(cpstd::forward<Args>(args)...); }

                //! @brief Removes the last element; no effect when empty.
                void pop_back() {
                    if (_Size != 0) {
                        --_Size;
                        traits::destroy(_Alloc, _Buffer + _Size);
                    }
                }

                //! @brief Inserts a copy of `value` before `position`.
                //! @return The inserted element; on failure the vector is unchanged
                //! and the iterator points at `position`.
                iterator insert(const_iterator position, const value_type& value) {
                    return insert(position, size_type(1), value);
                }

                iterator insert(const_iterator position, value_type&& value) {
                    return emplace(position, cpstd::move(value));
                }

                iterator insert(const_iterator position, size_type n, const value_type& value) {
                    const size_type index = static_cast<size_type>(position - cbegin());
                    if (n == 0) {
                        return _Buffer + index;
                    }
                    const value_type copy = value;  // `value` may be an element that moves
                    size_type constructedEnd = 0;
                    if (!OpenGap(index, n, constructedEnd)) {
                        return _Buffer + index;
                    }
                    FillGap(index, n, constructedEnd, FillSource{copy});
                    return _Buffer + index;
                }

                template <class InputIterator,
                          typename cpstd::enable_if<!cpstd::is_integral<InputIterator>::value, int>::type = 0>
                iterator insert(const_iterator position, InputIterator first, InputIterator last) {
                    const size_type index = static_cast<size_type>(position - cbegin());
                    vector values(first, last, _Alloc);  // also guards against ranges into *this
                    if (values.empty()) {
                        return _Buffer + index;
                    }
                    size_type constructedEnd = 0;
                    if (!OpenGap(index, values.size(), constructedEnd)) {
                        return _Buffer + index;
                    }
                    FillGap(index, values.size(), constructedEnd, ArraySource{values.data()});
                    return _Buffer + index;
                }

                iterator insert(const_iterator position, cpstd::initializer_list<T> list) {
                    const size_type index = static_cast<size_type>(position - cbegin());
                    if (list.size() == 0) {
                        return _Buffer + index;
                    }
                    size_type constructedEnd = 0;
                    if (!OpenGap(index, list.size(), constructedEnd)) {
                        return _Buffer + index;
                    }
                    FillGap(index, list.size(), constructedEnd, ArraySource{list.begin()});
                    return _Buffer + index;
                }

                //! @brief Constructs an element before `position` from `args`.
                template <class... Args>
                iterator emplace(const_iterator position, Args&&... args) {
                    const size_type index = static_cast<size_type>(position - cbegin());
                    value_type element(cpstd::forward<Args>(args)...);  // args may refer to elements
                    size_type constructedEnd = 0;
                    if (!OpenGap(index, 1, constructedEnd)) {
                        return _Buffer + index;
                    }
                    if (index < constructedEnd) {
                        _Buffer[index] = cpstd::move(element);
                    } else {
                        traits::construct(_Alloc, _Buffer + index, cpstd::move(element));
                    }
                    ++_Size;
                    return _Buffer + index;
                }

                iterator erase(const_iterator position) {
                    return erase(position, position + 1);
                }

                iterator erase(const_iterator first, const_iterator last) {
                    const size_type start = static_cast<size_type>(first - cbegin());
                    const size_type stop = static_cast<size_type>(last - cbegin());
                    if (start >= stop || stop > _Size) {
                        return _Buffer + start;
                    }
                    const size_type count = stop - start;
                    for (size_type i = start; i + count < _Size; ++i) {
                        _Buffer[i] = cpstd::move(_Buffer[i + count]);
                    }
                    DestroyRange(_Buffer + _Size - count, _Buffer + _Size);
                    _Size -= count;
                    return _Buffer + start;
                }

                void swap(vector& other) noexcept {
                    cpstd::swap(_Buffer, other._Buffer);
                    cpstd::swap(_Size, other._Size);
                    cpstd::swap(_Capacity, other._Capacity);
                    cpstd::swap(_Alloc, other._Alloc);
                }

                //! @brief Destroys every element, keeping the capacity.
                void clear() noexcept {
                    DestroyRange(_Buffer, _Buffer + _Size);
                    _Size = 0;
                }

                //! @}

            private:
                template <class... Args>
                bool TryEmplaceBack(Args&&... args) {
                    if (_Size < _Capacity) {
                        traits::construct(_Alloc, _Buffer + _Size, cpstd::forward<Args>(args)...);
                        ++_Size;
                        return true;
                    }
                    if (_Size == max_size()) {
                        return false;
                    }
                    const size_type capacity = GrownCapacity(_Size + 1);
                    pointer storage = traits::allocate(_Alloc, capacity);
                    if (storage == nullptr) {
                        return false;
                    }
                    // Construct first: args may refer to an element of the old storage.
                    traits::construct(_Alloc, storage + _Size, cpstd::forward<Args>(args)...);
                    AdoptStorage(storage, capacity);
                    ++_Size;
                    return true;
                }

                struct ValueInitializer {
                    void operator()(allocator_type& alloc, pointer slot) const { traits::construct(alloc, slot); }
                };

                struct CopyInitializer {
                    const value_type& value;
                    void operator()(allocator_type& alloc, pointer slot) const { traits::construct(alloc, slot, value); }
                };

                // Grows or shrinks to `n`, constructing new elements with `init`.
                template <class Initializer>
                void ResizeImpl(size_type n, const Initializer& init) {
                    if (n <= _Size) {
                        DestroyRange(_Buffer + n, _Buffer + _Size);
                        _Size = n;
                        return;
                    }
                    if (n > max_size()) {
                        return;
                    }
                    if (n > _Capacity) {
                        pointer storage = traits::allocate(_Alloc, n);
                        if (storage == nullptr) {
                            return;
                        }
                        // Construct the new tail first: a copied value may be an element.
                        for (size_type i = _Size; i < n; ++i) {
                            init(_Alloc, storage + i);
                        }
                        AdoptStorage(storage, n);
                    } else {
                        for (size_type i = _Size; i < n; ++i) {
                            init(_Alloc, _Buffer + i);
                        }
                    }
                    _Size = n;
                }

                void CopyFrom(const vector& other) {
                    if (other._Size != 0 && Reallocate(other._Size)) {
                        for (size_type i = 0; i < other._Size; ++i) {
                            traits::construct(_Alloc, _Buffer + i, other._Buffer[i]);
                        }
                        _Size = other._Size;
                    }
                }

                // Replaces the contents with values[0, count); unchanged on failure.
                void AssignRange(const value_type* values, size_type count) {
                    if (count > _Capacity) {
                        pointer storage = traits::allocate(_Alloc, count);
                        if (storage == nullptr) {
                            return;
                        }
                        for (size_type i = 0; i < count; ++i) {
                            traits::construct(_Alloc, storage + i, values[i]);
                        }
                        clear();
                        if (_Buffer != nullptr) {
                            traits::deallocate(_Alloc, _Buffer, _Capacity);
                        }
                        _Buffer = storage;
                        _Capacity = count;
                        _Size = count;
                        return;
                    }
                    const size_type common = (count < _Size) ? count : _Size;
                    for (size_type i = 0; i < common; ++i) {
                        _Buffer[i] = values[i];
                    }
                    for (size_type i = common; i < count; ++i) {
                        traits::construct(_Alloc, _Buffer + i, values[i]);
                    }
                    DestroyRange(_Buffer + count, _Buffer + _Size);
                    _Size = count;
                }
            };

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Comparisons: element-wise equality and lexicographic order

            template <class T, class Alloc>
            bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
                if (lhs.size() != rhs.size()) {
                    return false;
                }
                for (cpstd::size_t i = 0; i < lhs.size(); ++i) {
                    if (!(lhs[i] == rhs[i])) {
                        return false;
                    }
                }
                return true;
            }

            template <class T, class Alloc>
            bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs == rhs); }

            template <class T, class Alloc>
            bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
                const cpstd::size_t common = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
                for (cpstd::size_t i = 0; i < common; ++i) {
                    if (lhs[i] < rhs[i]) {
                        return true;
                    }
                    if (rhs[i] < lhs[i]) {
                        return false;
                    }
                }
                return lhs.size() < rhs.size();
            }

            template <class T, class Alloc>
            bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return rhs < lhs; }

            template <class T, class Alloc>
            bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(rhs < lhs); }

            template <class T, class Alloc>
            bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs < rhs); }

            template <class T, class Alloc>
            void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) noexcept {
                lhs.swap(rhs);
            }

        #endif
    }

#endif//CROSS_PLATFFORM_STL_VECTOR_TEMPLATE_H
