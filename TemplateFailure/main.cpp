#include <iostream>
#include <functional>

/*
öltse ki a program hiányzó részeit(a kommenteknél), hogy az alábbi kimenetet adja :

Result for 10 / 2: Result: 5
After dividing result by 0 and then by 2 again : Failed!
identity(5) should equal : Result: 5
throwException applied to 5 should result in : Failed!
*/

template <typename ValueType> class Failure {
    bool hasFailed; //ezt en irtam ide
    ValueType value;
public:
    Failure(ValueType v) : hasFailed{ false }, value{ v } {}
    // az alabbi fuggvenyben kell egy op nevu argumentum megfelelo tipussal (a pelda bemenetbol (test case) kiolvashato)
    Failure<ValueType>& bind(std::function<ValueType(ValueType)> op) {
        if (!hasFailed) {
            try {
                value = op(value);
            }
            catch (const std::exception& e) {
                hasFailed = true;
                return *this;
            }
            return *this;
        }
        else {
            return *this;
        }
    }
    template<typename T>
    friend std::ostream& operator<<(std::ostream& os, const Failure<T>& failure);
};

template <typename ValueType>
std::ostream& operator<<(std::ostream& os, const Failure<ValueType>& failure) {
    // ezt a fuggvenyt valositsa meg!
    if (failure.hasFailed)
    {
        os << "Failed!";
    }
    else 
    {
        os << "result: " << failure.value;
    }
    return os;
}

template <typename T>
class MockOperators {
public:
    // itt ket fuggvenyt meg kell valositani: identity es throwException
    // identity adja vissza a parametert valtoztatas nelkul!
    // throwException egy std::runtime_error tipusu kivetelt dobjon!

    inline static std::function<T(T)> identity = [](T x) -> T { return x; };
    inline static std::function<T(T)> throwException = [](T x) -> T {throw std::runtime_error("Failed!"); };

    
};

int main() {
	Failure<double> doubleResult(10.0);
	std::function<double(double)> divideBy2 = [](double x) -> double { return x / 2.0; };
	doubleResult.bind(divideBy2);
	std::cout << "Result for 10 / 2: " << doubleResult << std::endl;

	std::function<double(double)> divideBy0 = [](double x) -> double { throw std::runtime_error("divided by 0!"); };
	doubleResult.bind(divideBy0).bind(divideBy2);
	std::cout << "After dividing result by 0 and then by 2 again: " << doubleResult << std::endl;

    // divideBy2 - 

    
	Failure<int> intResult(5);
	std::cout << "identity(5) should equal: " << intResult.bind(MockOperators<int>::identity) << std::endl;
	std::cout << "throwException applied to 5 should result in: " << intResult.bind(MockOperators<int>::throwException) << std::endl;
    

	return 0;
}
