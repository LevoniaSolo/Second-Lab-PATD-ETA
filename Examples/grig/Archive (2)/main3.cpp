#include <functional>
#include <iostream>

void print_some(int num) {
    std::cout << "some " << num << std::endl;
}

class PrintableClass {
public:
    PrintableClass(double v)
        : value(v) {}

    void operator()(int n) {
        std::cout << "PrintableClass " << value << " " << n << std::endl;
    }

private:
    double value;
    (void *f)(int);
};

int main() {
    PrintableClass printable(123.456);

    std::function<void(int)> f(printable);

    f(1);
    f(2);
    f(3);

    printable(432);

    return 0;
}