#ifndef IMMUTABLE_ARRAY_SEQUENCE_HPP
#define IMMUTABLE_ARRAY_SEQUENCE_HPP
#include <functional>
#include "ArraySequence.hpp"

template<typename T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    ImmutableArraySequence(const T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(int size) : ArraySequence<T>(size) {}
    ImmutableArraySequence(const ImmutableArraySequence<T>& other) : ArraySequence<T>(other) {}
    ImmutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}

    // ImmutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) override {
    //     return dynamic_cast<ImmutableArraySequence<T>*>(ArraySequence<T>::GetSubsequence(startIndex, endIndex));
    // }

    ImmutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) override {
        DynamicArray<T>* subArray = this->arraySeq->GetSubArray(startIndex, endIndex);
        ImmutableArraySequence<T>* result = new ImmutableArraySequence<T>(*subArray);
        delete subArray;
        return result;
    }

    ImmutableArraySequence<T>* Append(T item) override {
        return dynamic_cast<ImmutableArraySequence<T>*>(ArraySequence<T>::Append(item));
    }

    ImmutableArraySequence<T>* Prepend(T item) override {
        return dynamic_cast<ImmutableArraySequence<T>*>(ArraySequence<T>::Prepend(item));
    }

    ImmutableArraySequence<T>* InsertAt(T item, int index) override {
        return dynamic_cast<ImmutableArraySequence<T>*>(ArraySequence<T>::InsertAt(item, index));
    }

    ImmutableArraySequence<T>* Concat(Sequence<T>* other) override {
        return dynamic_cast<ImmutableArraySequence<T>*>(ArraySequence<T>::Concat(other));
    }

    //map-reduce
    ImmutableArraySequence<T>* Map(std::function<T(T)> f) override {
        return dynamic_cast<ImmutableArraySequence<T>*>(ArraySequence<T>::Map(f));
    }

    ImmutableArraySequence<T>* Where(std::function<bool(T)> predicate) override {
        return dynamic_cast<ImmutableArraySequence<T>*>(ArraySequence<T>::Where(predicate));
    }

    T Reduce(std::function<T(T, T)> f, T initial) const override {
        return ArraySequence<T>::Reduce(f, initial);
    }

    bool ContainsSubsequence(Sequence<T>* sub) const override {
        ImmutableArraySequence<T>* subArray = dynamic_cast<ImmutableArraySequence<T>*>(sub);
        if (subArray) {
            return this->arraySeq->ContainsSubsequence(subArray->arraySeq);
        }
        DynamicArray<T>* temp = new DynamicArray<T>();
        for (int i = 0; i < sub->GetLength(); i++) {
            temp->Append(sub->Get(i));
        }
        bool result = this->arraySeq->ContainsSubsequence(temp);
        delete temp;
        return result;
    }

    ImmutableArraySequence<T>* Instance() override {
        return new ImmutableArraySequence<T>(*this);
    }
};
#endif