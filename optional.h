//
// Created by Arslan on 13.10.2018.
//

#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include <algorithm>

template<typename T>
struct optional{
    optional() : empty(true){}

    optional(T const & val){
        data = val;
        empty = false;
    }

    optional(optional const & other){
        auto tmp = other;
        swap(tmp);
    }

    optional &operator=(optional const & other){
        empty = other.empty;
        if (!empty){
            data = other.data;
        }
        return *this;
    }

    void clear(){
        empty = true;
    }

    explicit operator bool() const{
        return !empty;
    }

    T &operator*(){
        if (!empty) {
            return data;
        }
        else{
            throw std::logic_error("optional is empty");
        }
    }

    T *operator->(){
        if (!empty) {
            return &data;
        }
        else{
            throw std::logic_error("optional is empty");
        }
    }

    void swap(optional<T> & other){
        std::swap(empty, other.empty);
        std::swap(data, other.data);
    }

private:
    bool empty;
    T data;
};

template <typename T>
void swap(optional<T> &a, optional<T> &b){
    a.swap(b);
}

#endif //OPTIONAL_OPTIONAL_H
