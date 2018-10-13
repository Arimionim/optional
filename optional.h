#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <iostream>
#include <type_traits>
#include <string>
#include <cassert>

template<class T>
class optional {
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data;
    bool full = false;

public:
    optional() = default;

    optional(T const &val) {
        full = true;
        new(reinterpret_cast<T *>(&data)) T(val);
    }

    optional(optional const &other) : full(other.full) {
        if (full) {
            new(reinterpret_cast<T *>(&data)) T(*other);
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
            reinterpret_cast<T *>(&data)->~T();
            full = false;
        }
    }

    void swap(optional &other) {
        if (full && other.full) {
            std::swap(*reinterpret_cast<T *>(&data), *reinterpret_cast<T *>(&other.data));
            std::swap(full, other.full);
        }
        else if (full){
            new(reinterpret_cast<T *>(&other.data)) T(*(*this));
            this->clear();
            other.full = 1;
        }
        else if (other.full){
            new(reinterpret_cast<T *>(&data)) T(*other);
            other.clear();
            full = 1;
        }
    }


    T &operator*() {
        assert(full);
        return *reinterpret_cast<T *>(&data);
    }

    T const &operator* () const{
        assert(full);
        return *reinterpret_cast<T const *>(&data);
    }

    T *operator->() {
        assert(full);
        return (reinterpret_cast<T *>(&data));
    }

    T const *operator->() const{
        assert(full);
        return (reinterpret_cast<T const *>(&data));
    }
};

template<typename T>
void swap(optional<T> &a, optional<T> &b) {
    a.swap(b);
}

#endif //OPTIONAL_H