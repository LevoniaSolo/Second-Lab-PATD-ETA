class TestDeleteClass {
public:
    static int counter;

    TestDeleteClass() {
        incrementCounter();
    }
    TestDeleteClass(const TestDeleteClass& other) {
        incrementCounter();
    }
    TestDeleteClass& operator=(const TestDeleteClass& other) {
        return *this;
    }

    ~TestDeleteClass() {
        decrementCounter();
    }

    static int getCounter() {
        return counter;
    }

    static void resetCounter() {
        counter = 0;
    }
    
    static void incrementCounter() {
        counter += 1;
    }
    
    static void decrementCounter();
};
