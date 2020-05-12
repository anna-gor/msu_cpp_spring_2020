#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

template<class T>
class Allocator
{
public:
    T* allocate(size_t n)
    {
        T* ptr = (T*)malloc(sizeof(T) * n);
        if (!ptr) throw std::bad_alloc();
        return ptr;
    }

    void deallocate(T* ptr){
        free(ptr);

    }

    template <class Args>
    void construct(T* ptr, Args&& arg){
        ptr = new(ptr) T(std::forward<Args>(arg));
    }


    void construct(T* ptr){
        ptr = new(ptr) T();
    }

    void destroy(T* ptr){
        ptr->~T();
    }
};

template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T> {
    T *ptr_;
 public:
    using iter = Iterator<T>;
    using type = T;
    using pointer = T*;
    using reference = T&;

    Iterator(T* ptr):
            ptr_(ptr)
            {}

    Iterator(const iter& it):
            ptr_(it.ptr_)
            {}

    bool operator==(const iter& other) {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const iter& other) {
        return !(*this == other);
    }

    bool operator<(const iter& other) {
        return ptr_ < other.ptr_;
    }

    bool operator>(const iter& other) {
        return ptr_ > other.ptr_;
    }

    reference operator*() {
        return *ptr_;
    }

    iter& operator++() {
        ++ptr_;
        return *this;
    }

    iter& operator--() {
        --ptr_;
        return *this;
    }

    iter& operator+=(size_t count) {
        ptr_ += count;
        return *this;
    }

    iter& operator-=(size_t count) {
        ptr_ -= count;
        return *this;
    }

    iter operator+(size_t count) {
        iter tmp(ptr_ + count);
        return tmp;
    }

    iter operator-(size_t count) {
        iter tmp(ptr_ - count);
        return tmp;
    }

   iter operator+(const iter& other) {
      iter tmp(ptr_ + other.ptr_);
      return tmp;
   }

   iter operator-(const iter& other) {
      iter tmp(ptr_ - other.ptr_);
      return tmp;
   }


    reference operator[](size_t count) {
        return ptr_[count];
    }
};



template<class T,
    class Alloc = Allocator<T>>
class Vector
{
public:
    using size_type = size_t;
    using type = T;
    using reference = T&;
    using const_reference = const T&;
	using allocator_type = Alloc;
    using pointer = T*;
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    pointer data;
    allocator_type aloc;
    size_type length;
    size_type capac;

    explicit Vector(size_type count = 1): data(aloc.allocate(count*2)), length(0), capac(count*2){
    }

    ~Vector(){
        clear();
        aloc.deallocate(data);
    }

    iterator begin(){
        return iterator(data);
   }

    iterator end(){
        return iterator(data + length);
   }

    reverse_iterator rbegin(){
        return reverse_iterator(data + length);
   }

    reverse_iterator rend(){
        return reverse_iterator(data);
   }

    const_reference operator[](size_t val) const{
        if (val > length-1) throw std::out_of_range("out");
        else return (*(data+val));
    }
    bool empty() const {
        return (!length);
    }

    void pop_back() {
        if (length > 0) {
            aloc.destroy(data + length - 1);
            --length;
        }
    }

    void push_back(type&& value){
        if (capac == length){
            reserve(2*capac);
        }
        aloc.construct(data + length, std::move(value));
        ++length;

    }

    void push_back(const type& value){
        if (capac == length){
            reserve(2*capac);
        }
        aloc.construct(data + length, value);
        ++length;
    }

    void reserve(size_type count){
        if (count > capac){
            T*ptr_tmp = aloc.allocate(count);
            for (size_t i = 0; i < length; ++i) {
                aloc.construct(ptr_tmp + i, data[i]);
            }
             for (size_t i = 0; i < length; ++i) {
                 aloc.destroy(ptr_tmp + i);
          }
             aloc.deallocate(data);
             data = ptr_tmp;
             capac = count;
         }
    }

    size_type capacity() const noexcept{
        return capac;
    }

    void resize(size_type newSize){
        if (newSize > length){
            if (capac < newSize) reserve(newSize);
            for (size_t i = length; i < newSize; ++i){
                aloc.construct(data+i);
            }
        }
        else {
            for (size_t i = newSize; i < length; ++i) {
                aloc.destroy(data+i);
            }
        }
        length = newSize;
    }

    size_t size() const{
        return length;
    }

    void clear() noexcept{
        for (size_t i=0; i<length; ++i) {
              aloc.destroy(data + i);
          }
        length = 0;
    }

};