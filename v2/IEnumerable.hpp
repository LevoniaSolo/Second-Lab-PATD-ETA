#ifndef IENUMERABLE_HPP
#define IENUMERABLE_HPP

template<typename T>
class IEnumerator {
public:
    virtual ~IEnumerator() = default;
    virtual bool MoveNext() = 0;
    virtual T Current() const = 0;
    virtual void Reset() = 0;
};

template<typename T>
class IEnumerable {
public:
    virtual ~IEnumerable() = default;
    virtual IEnumerator<T>* GetEnumerator() = 0;
};

#endif