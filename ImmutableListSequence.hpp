#ifndef IMMUTABLE_LIST_SEQUENCE_HPP
#define IMMUTABLE_LIST_SEQUENCE_HPP
#include <functional>
#include "ListSequence.hpp"

template<typename T>
class ImmutableListSequence : public ListSequence<T> {
public:
    ImmutableListSequence(const T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(const ImmutableListSequence<T>& other) : ListSequence<T>(other) {}
    ImmutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {}

    // ImmutableListSequence<T>* GetSubsequence(int startIndex, int endIndex) override {
    //     return dynamic_cast<ImmutableListSequence<T>*>(ListSequence<T>::GetSubsequence(startIndex, endIndex));
    // }

    ImmutableListSequence<T>* GetSubsequence(int startIndex, int endIndex) override {
        LinkedList<T>* subList = this->listSeq->GetSubList(startIndex, endIndex);
        ImmutableListSequence<T>* result = new ImmutableListSequence<T>(*subList);
        delete subList;
        return result;
    }

    ImmutableListSequence<T>* Append(T item) override {
        return dynamic_cast<ImmutableListSequence<T>*>(ListSequence<T>::Append(item));
    }

    ImmutableListSequence<T>* Prepend(T item) override {
        return dynamic_cast<ImmutableListSequence<T>*>(ListSequence<T>::Prepend(item));
    }

    ImmutableListSequence<T>* InsertAt(T item, int index) override {
        return dynamic_cast<ImmutableListSequence<T>*>(ListSequence<T>::InsertAt(item, index));
    }

    ImmutableListSequence<T>* Concat(Sequence<T>* other) override {
        return dynamic_cast<ImmutableListSequence<T>*>(ListSequence<T>::Concat(other));
    }

    //map-reduce
    ImmutableListSequence<T>* Map(std::function<T(T)> f) override {
        return dynamic_cast<ImmutableListSequence<T>*>(ListSequence<T>::Map(f));
    }

    ImmutableListSequence<T>* Where(std::function<bool(T)> predicate) override {
        return dynamic_cast<ImmutableListSequence<T>*>(ListSequence<T>::Where(predicate));
    }

    T Reduce(std::function<T(T, T)> f, T initial) const override {
        return ListSequence<T>::Reduce(f, initial);
    }

    bool ContainsSubsequence(Sequence<T>* sub) const override {
        ImmutableListSequence<T>* subList = dynamic_cast<ImmutableListSequence<T>*>(sub);
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

    ImmutableListSequence<T>* Instance() override {
        return new ImmutableListSequence<T>(*this);
    }
};
#endif