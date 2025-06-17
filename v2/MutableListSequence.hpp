#ifndef MUTABLE_LIST_SEQUENCE_HPP
#define MUTABLE_LIST_SEQUENCE_HPP
#include <functional>
#include "ListSequence.hpp"

template<typename T>
class MutableListSequence : public ListSequence<T> {
public:
    MutableListSequence(const T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(const MutableListSequence<T>& other) : ListSequence<T>(other) {}
    MutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}

    // MutableListSequence<T>* GetSubsequence(int startIndex, int endIndex) override {
    //     return dynamic_cast<MutableListSequence<T>*>(ListSequence<T>::GetSubsequence(startIndex, endIndex)); 
    // }

    MutableListSequence<T>* GetSubsequence(int startIndex, int endIndex) override {
        LinkedList<T>* subList = this->listSeq->GetSubList(startIndex, endIndex);
        MutableListSequence<T>* result = new MutableListSequence<T>(*subList);
        delete subList;
        return result;
    }

    MutableListSequence<T>* Append(T item) override {
        return dynamic_cast<MutableListSequence<T>*>(ListSequence<T>::Append(item));
    }

    MutableListSequence<T>* Prepend(T item) override {
        return dynamic_cast<MutableListSequence<T>*>(ListSequence<T>::Prepend(item));
    }

    MutableListSequence<T>* InsertAt(T item, int index) override {
        return dynamic_cast<MutableListSequence<T>*>(ListSequence<T>::InsertAt(item, index));
    }

    MutableListSequence<T>* Concat(Sequence<T>* other) override {
        return dynamic_cast<MutableListSequence<T>*>(ListSequence<T>::Concat(other));
    }

    //map-reduce
    MutableListSequence<T>* Map(std::function<T(T)> f) override {
        return dynamic_cast<MutableListSequence<T>*>(ListSequence<T>::Map(f));
    }

    MutableListSequence<T>* Where(std::function<bool(T)> predicate) override {
        return dynamic_cast<MutableListSequence<T>*>(ListSequence<T>::Where(predicate));
    }

    T Reduce(std::function<T(T, T)> f, T initial) const override {
        return ListSequence<T>::Reduce(f, initial);
    }

    bool ContainsSubsequence(Sequence<T>* sub) const override {
        MutableListSequence<T>* subList = dynamic_cast<MutableListSequence<T>*>(sub);
        if (subList) {
            return this->listSeq->ContainsSubsequence(subList->listSeq);
        }
        LinkedList<T>* temp = new LinkedList<T>();
        for (int i = 0; i < sub->GetLength(); i++) {
            temp->Append(sub->Get(i));
        }
        bool result = this->listSeq->ContainsSubsequence(temp);
        delete temp;
        return result;
    }

    MutableListSequence<T>* Instance() override {
        return this;
    }
};
#endif