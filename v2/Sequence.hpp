#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP
#include <functional>
template<typename T>
class Sequence {
    public:
        virtual T GetFirst() const = 0;
        virtual T GetLast() const = 0;
        virtual T Get(int index) const = 0;
        virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
        virtual int GetLength() const = 0;
        virtual Sequence<T>* Append(T item) =  0;
        virtual Sequence<T>* Prepend(T item) = 0;
        virtual Sequence<T>*InsertAt(T item, int index) = 0;
        virtual Sequence <T>* Concat(Sequence <T> *list) = 0;
        virtual Sequence<T>* Map(std::function<T(T)> f) = 0;
        virtual Sequence<T>* Where(std::function<bool(T)> f) = 0;
        virtual T Reduce(std::function<T(T, T)> f, T c) const = 0;
        virtual bool ContainsSubsequence(Sequence<T>* sub) const = 0;

        virtual ~Sequence()  = default;
};

#endif // SEQUENCE_HPP