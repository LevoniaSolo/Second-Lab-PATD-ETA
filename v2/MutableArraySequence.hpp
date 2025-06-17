#ifndef MUTABLE_ARRAY_SEQUENCE_HPP
#define MUTABLE_ARRAY_SEQUENCE_HPP
#include <functional>
#include "ArraySequence.hpp"
#include "Sequence.hpp"


template<typename T>
class MutableArraySequence : public ArraySequence<T> {
public:
    MutableArraySequence(const T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(int size) : ArraySequence<T>(size) {}
    MutableArraySequence(const MutableArraySequence<T>& other) : ArraySequence<T>(other) {}
    MutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {}

    // MutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) override {
    //     return dynamic_cast<MutableArraySequence<T>*>(ArraySequence<T>::GetSubsequence(startIndex, endIndex));
    // }
    
    MutableArraySequence<T>* GetSubsequence(int startIndex, int endIndex) override {
        DynamicArray<T>* subArray = this->arraySeq->GetSubArray(startIndex, endIndex);
        MutableArraySequence<T>* result = new MutableArraySequence<T>(*subArray);
        delete subArray;
        return result;
    }

    MutableArraySequence<T>* Append(T item) override {
        return dynamic_cast<MutableArraySequence<T>*>(ArraySequence<T>::Append(item));
    }

    MutableArraySequence<T>* Prepend(T item) override {
        return dynamic_cast<MutableArraySequence<T>*>(ArraySequence<T>::Prepend(item));
    }

    MutableArraySequence<T>* InsertAt(T item, int index) override {
        return dynamic_cast<MutableArraySequence<T>*>(ArraySequence<T>::InsertAt(item, index));
    }

    MutableArraySequence<T>* Concat(Sequence<T>* other) override {
        return dynamic_cast<MutableArraySequence<T>*>(ArraySequence<T>::Concat(other));
    }

    //map-reduce
    MutableArraySequence<T>* Map(std::function<T(T)> f) override {
        return dynamic_cast<MutableArraySequence<T>*>(ArraySequence<T>::Map(f));
    }

    MutableArraySequence<T>* Where(std::function<bool(T)> predicate) override {
        return dynamic_cast<MutableArraySequence<T>*>(ArraySequence<T>::Where(predicate));
    }

    T Reduce(std::function<T(T, T)> f, T initial) const override {
        return ArraySequence<T>::Reduce(f, initial);
    }

    bool ContainsSubsequence(Sequence<T>* sub) const override {
        MutableArraySequence<T>* subArray = dynamic_cast<MutableArraySequence<T>*>(sub);
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

    MutableArraySequence<T>* Instance() override {
        return this;
    }
};
#endif