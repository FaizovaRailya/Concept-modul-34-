#include <iostream>
#include <string>

template <typename T> concept ComplexConcept = requires(const T v) {
    {v.hash()} -> std::convertible_to<long>;
    {v.toString()} -> std::same_as<std::string>;
} && !std::has_virtual_destructor<T>::value;

class Empty {};

class With_destructor {
    int _v;
public:
    With_destructor(const int v) :_v(v) {}
    virtual ~With_destructor() {}
    int hash() const {
        return _v;
    }
    std::string toString() const {
        return std::to_string(_v);
    }
};

class Correct {
    int _v;
public:
    Correct(const int v) :_v(v) {}

    int hash() const {
        return _v;
    }
    std::string toString() const {
        return std::to_string(_v);
    }
};

template <ComplexConcept T> void concept_method(T val) {
    std::cout << "Hash: " << val.hash() << std::endl;
    std::cout << "String: " << val.toString() << std::endl;
}

int main() {
    //Empty e();
    //concept_method<Empty>(e); // ошибка т.к. в классе нет методов hash() и toString()
    //With_destructor d(5);
    //concept_method<With_destructor>(d); // ошибка т.к. в классе есть деструктор

    Correct c(10);
    concept_method<Correct>(c);
    return 0;
}
