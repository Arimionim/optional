#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <iostream>
#include <type_traits>
#include <string>

template<class T>
class optional {
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data[1];
    bool full = 0;

public:
    optional() = default;

    optional(T const & val){
        clear();
        full = 1;
        new(reinterpret_cast<T *>(data)) T(val);
    }

    optional(optional const &other): full(other.full) {
        if (full) {
            new(reinterpret_cast<T*>(data)) T(*reinterpret_cast<const T *>(other.data));
        }
    }

    optional &operator=(optional const &other) {
        optional tmp = other;
        swap(tmp);
        return *this;
    }

    ~optional() {
        clear();
    }

    explicit operator bool() const {
        return full;
    }

    void clear() {
        if (full) {
            reinterpret_cast<T *>(data)->~T();
            full = 0;
        }
    }

    void swap(optional &other){
        std::swap(data, other.data);
        std::swap(full, other.full);
    }


    T &operator*() {
        return *reinterpret_cast<T*>(data);
    }

    T *operator->() {
        return (reinterpret_cast<T*>(data));
    }
};

template <typename T>
void swap(optional<T> a, optional<T> b){
    a.swap(b);
}

#endif //OPTIONAL_H