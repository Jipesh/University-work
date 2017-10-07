#ifndef PEP_VECTOR_H
#define PEP_VECTOR_H

#include <vector>


namespace pep {

template<class T, class Alloc = std::allocator<T> >
class vector : std::vector<T, Alloc> {

protected:
    typedef typename std::vector<T> base;

public:

    typedef typename base::value_type value_type;
    typedef typename base::allocator_type allocator_type;
    typedef typename base::reference reference;
    typedef typename base::const_reference const_reference;
    typedef typename base::pointer pointer;
    typedef typename base::const_pointer const_pointer;
    typedef typename base::iterator iterator;
    typedef typename base::const_iterator const_iterator;
    typedef typename base::reverse_iterator reverse_iterator;
    typedef typename base::const_reverse_iterator const_reverse_iterator;
    typedef typename base::difference_type difference_type;
    typedef typename base::size_type size_type;
    
    explicit vector(const allocator_type& alloc = allocator_type()) : base(alloc) {
    }
    
    explicit vector(size_type n) : base(n) {
    }    

    explicit vector(size_type n, const value_type& val, const allocator_type& alloc = allocator_type()) : base(n, val, alloc) {        
                
    }
    
    template <class InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : base(first, last, alloc) {        
    }
            
    vector(const vector & x) : base(static_cast<base>(x)) {        
        
    }
    
    vector(const vector & x, const allocator_type& alloc) : base(static_cast<base>(x), alloc) {
    }

    vector(vector && x) : base(x) {
    }

    vector(vector && x, const allocator_type & alloc) : base(x,alloc) {
    }

    ~vector() {
    }
    
    vector(std::initializer_list<value_type> && il, const allocator_type & alloc = allocator_type()) : base(il, alloc) {
    }
      
      
    vector & operator=(const vector & x) {
        base::operator=(static_cast<base>(x));        
        return *this;
    }
    vector & operator=(vector && x) {
        base::operator=(x);
        return *this;
    }
    vector & operator=(std::initializer_list<value_type> il) {
        base::operator=(il);         
        return *this;
    }
    
    iterator begin() noexcept { return base::begin(); }
    const_iterator begin() const noexcept { return base::begin(); }
    
    iterator end() noexcept { return base::end(); }
    const_iterator end() const noexcept { return base::end(); }
    
    reverse_iterator rbegin() noexcept { return base::rbegin(); }
    const_reverse_iterator rbegin() const noexcept { return base::rbegin(); }
    
    reverse_iterator rend() noexcept { return base::rend(); }
    const_reverse_iterator rend() const noexcept { return base::rend(); }
    
    const_iterator cbegin() const noexcept { return base::cbegin(); }
    const_iterator cend() const noexcept { return base::cend(); }
    
    const_reverse_iterator crbegin() noexcept { return base::crbegin(); }
    const_reverse_iterator crend() noexcept { return base::crend(); }
            
    size_type size() const noexcept { return base::size(); }
    size_type max_size() const noexcept { return base::max_size(); }
    
    void resize(size_type n) { base::resize(n); }
    void resize(size_type n, const value_type & val) { base::resize(n, val); }
    
    size_type capacity() const noexcept { return base::capacity(); }
    bool empty() const noexcept { return base::empty(); }
    
    void reserve(size_type n) { base::reserve(n); }    
    void shrink_to_fit() { base::shrink_to_fit(); }
    
    
    reference operator[] (size_type n) { return base::operator[](n); }
    const_reference operator[] (size_type n) const { return base::operator[](n); }
    
    reference at(size_type n) { return base::at(n); }
    const_reference at(size_type n) const { return base::at(n); }
                    
    reference front() { return base::front(); }
    const_reference front() const { return base::front(); }
    
    reference back() { return base::back(); }
    const_reference back() const { return base::back(); }
    
    value_type* data() noexcept { return base::data(); }
    const value_type* data() const noexcept { return base::data(); }
    
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last) {
        base::assign(first,last);
    }

    void assign(size_type n, const value_type & val) { base::assign(n, val); }
    void assign(std::initializer_list<value_type> && il) { base::assign(il); }
    
    void push_back(const value_type & val) { base::push_back(val); }
    void push_back(value_type && val)  { base::push_back(val); }
    
    void pop_back() { base::pop_back(); }
    
    iterator insert(const_iterator position, const value_type & val) {
        return base::insert(position, val);
    }
        
    iterator insert(const_iterator position, size_type n, const value_type & val) {
        return base::insert(position, n, val);
    }

    template<class InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last) {
        return base::insert(position, first, last);
    }
        
    iterator insert(const_iterator position, value_type && val) {
        return base::insert(position, val);
    }
        
    iterator insert(const_iterator position, std::initializer_list<value_type> && il) {
        return base::insert(position, il);
    }
    
    iterator erase(const_iterator position) { return base::erase(position); }
    iterator erase(const_iterator first, const_iterator last) { return base::erase(first, last); }
    
    void swap(vector & x) { base::swap(static_cast<base>(x)); }
    
    void clear() noexcept { base::clear(); }
    
    template <class... Args>
    iterator emplace(const_iterator position, Args&&... args) {
        return base::emplace(position, args...);
    }
    
    template <class... Args>
    void emplace_back(Args&&... args) {
        base::emplace_back(args...);
    }
    
    allocator_type get_allocator() const noexcept { return base::get_allocator(); }
    
    
};

template <class T, class Alloc>
bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), lhs.begin(), lhs.end());    
}

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return (lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(rhs < lhs);
}

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return (rhs > lhs);
}


template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs < rhs);
}


}


#endif
