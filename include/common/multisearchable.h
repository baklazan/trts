#ifndef TRTS_MULTISEARCHABLE_H
#define TRTS_MULTISEARCHABLE_H

#include <map>

template <typename T>
class MultiSearchable {
    IndexType major_index_, minor_index_;
    static std::map<IndexType, std::map<IndexType, T*>> by_index_;

    MultiSearchable(IndexType major_index, IndexType minor_index) : minor_index_(minor_index), major_index_(major_index) {
        by_index_[major_index_][minor_index_] = static_cast<T*>(this);
    }
    friend T;

    ~MultiSearchable() {
        by_index_[major_index_].erase(minor_index_);
    }

public:
    static std::map<IndexType, T*> Search(IndexType major_index) {
        if (by_index_.count(major_index) > 0) {
            return by_index_[major_index];
        }
        return std::map<IndexType, T*>();
    }

    static T* Search(IndexType major_index, IndexType minor_index) {
        if (by_index_.count(major_index) > 0) {
            if (by_index_[major_index].count(minor_index) > 0) {
                return by_index_[major_index][minor_index];
            }
        }
        return nullptr;
    }
};

template <typename T> std::map<IndexType, std::map<IndexType, T*>> MultiSearchable<T>::by_index_;


#endif
