// Библиотека с исключениями
#include <exception>
#include <iostream>

// throw - создать исключение
// try - попробовать выполнить код
// catch - в случае если в try произошла ошибка, то поймать её


void some_f() {
    std::cout << "init" << std::endl;

    int* buff = new int[100];

    //...
    // Нашёл ошибку
    bool err = true;
    if (err) {
        throw 6;
    }

    std::cout << "after throw" << std::endl;
    delete[] buff;
}

// Пример обработки одной ошибки
int main1() {
    try {
        some_f();

        std::cout << "After f" << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "Got exception" << std::endl;
    }
    return 0;
}


// std::exception
// * logic_error
//     * invalid_argument
//     * domain_error
//     * length_error
//     * out_of_range
//     * future_error (since C++11)
// * runtime_error
//     * range_error
//     * overflow_error
//     * underflow_error
//     * regex_error (since C++11)
//     * system_error (since C++11)
//         * ios_base::failure (since C++11)
//         * filesystem::filesystem_error (since C++17)
//     * tx_exception (TM TS)
//     * nonexistent_local_time (since C++20)
//     * ambiguous_local_time (since C++20)
//     * format_error (since C++20)
// * bad_typeid
// * bad_cast
//     * bad_any_cast (since C++17)
// * bad_optional_access (since C++17)
// * bad_expected_access (since C++23)
// * bad_weak_ptr (since C++11)
// * bad_function_call (since C++11)
// * bad_alloc
//     * bad_array_new_length (since C++11)
// * bad_exception
// * ios_base::failure (until C++11)
// * bad_variant_access (since C++17)

void f1() {
    throw std::out_of_range("out_of_range f1");
}

void f2() {
    throw std::invalid_argument("invalid_argument f2");
}

void f3() {
    throw std::overflow_error("overflow_error f3");
}

void some_f2() {
    try {
        std::cout << "some_f2" << std::endl;
        f2();
    }
    catch (std::out_of_range &err) {
        std::cout << "Got out_of_range: " << err.what() << std::endl;
    }
}

// Пример с вложенным блоком try и обработкой std исключений

int main2() {
    try {
        some_f2();
        std::cout << "main: No exceptions" << std::endl;
    }
    catch (std::logic_error &err) {
        std::cout << "Got logic error: " << err.what() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "Default exception: " << e.what() << std::endl;
    }

    // Пример с исключением std::bad_alloc
    // new double[1000000000000000];

    return 0;
}


template<typename T>
class LinkedList {
public:
    LinkedList(): head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        while(head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(const T& value) {
        if (!head) {
            head = new Node{value, nullptr};
            tail = head;
            return;
        }

        tail->next = new Node{value, nullptr};
        tail = tail->next;
    }
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
    Node* tail;
};

#include "TestClass.h"

void LinkedListTestDelete() {
    TestDeleteClass::resetCounter();

    LinkedList<TestDeleteClass> *list = new LinkedList<TestDeleteClass>();

    for (int i = 0; i < 10; ++i) {
        list->append(TestDeleteClass());
    }

    delete list;

    std::cout << "Counter: " << TestDeleteClass::getCounter() << std::endl;
}

int main() {
    LinkedListTestDelete();
    return 0;
}
