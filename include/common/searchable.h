#ifndef TRTS_SEARCHABLE_H
#define TRTS_SEARCHABLE_H

#include <map>
#include <iostream>
#include <id_types.h>

template <typename T>
class Searchable {

    IndexType index_;
    static std::map<IndexType, T*> by_index_;

    explicit Searchable(IndexType index) : index_(index){
        by_index_[index_] = static_cast<T*>(this);
    }
    friend T;

    ~Searchable() {
        by_index_.erase(index_);
    }

public:
    static T* Search(IndexType index) {
        if (by_index_.count(index) > 0) {
            return by_index_[index];
        }
        return nullptr;
    }
};

template <typename T> std::map<IndexType, T*> Searchable<T>::by_index_;

#endif
