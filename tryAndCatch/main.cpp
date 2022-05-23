/*
//Szeretnénk egy függvényt, ami automatikusan (és faék egyszerűséggel) lekezeli nekünk a kivételeket, hogy ne kelljen mindent try blokkba tenni.

Ehhez készítse el az alábbi tryAndCatch függvénysablont, ami 1. paraméterként egy visszatérési érték nélküli, egyparaméteres f függvényobjektumot vár,
2. paraméterben pedig egy tetszőleges típusú p paramétert, amit majd továbbít f-nek.

A függvény hívja meg a f-et a megadott p paraméterrel, és ha az kivételt dob, akkor kezelje le: írja ki az exception konstruktorában megadott hibaüzenetet!

Figyeljen rá, hogy f paraméterben bal- vagy jobbérték referenciát is várhat, így a megfelelő referenciaként kell továbbítani neki p-t!

RESULT:
        16
        0.25
        Division by zero
        After increment: 3
        1
        2
        3
        Vector is empty
        4
        3
        2
        1
        55

*/
#include <iostream>
#include <vector>
#include <functional>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<class Function, class Param>
void tryAndCatch( Function f, Param&& p)// ezt a sort modositsa, ahogy szukseges!
{
    try
    {
        f(p);
    }
    catch (const std::invalid_argument& ia)
    {
        std::cout << ia.what() << std::endl;
    }
    catch (const std::logic_error& le) {
        std::cout << le.what() << std::endl;
    }

    // adja meg az implementaciot!

}

template<class Function, class Param>
void tryAndCatch(Function f, std::vector<Param>&& p)// ezt a sort modositsa, ahogy szukseges!
{
    try
    {
        f(std::move(p));
    }
    catch (const std::invalid_argument& ia)
    {
        std::cout << ia.what() << std::endl;
    }
    catch (const std::logic_error& le) {
        std::cout << le.what() << std::endl;
    }

    // adja meg az implementaciot!

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() 
{
    
    auto printSquare = [](int n) { std::cout << n * n << '\n'; };
    auto oneOverX = [](double x) {
        if (x == 0.0) throw std::invalid_argument("Division by zero");
        std::cout << 1.0 / x << '\n';
    };
    auto increment = [](int& n) { ++n; };
    tryAndCatch(printSquare, 4);
    tryAndCatch(oneOverX, 4);
    tryAndCatch(oneOverX, 0);

    int num = 2;
    tryAndCatch(increment, num);
    std::cout << "After increment: " << num << '\n';
    
    
    auto printAndClear = [](std::vector<int>&& v) {
        if (v.empty()) throw std::logic_error("Vector is empty");
        for (const auto& i : v) std::cout << i << '\n';
        v.clear();
    };
    std::vector<int> vec = { 1, 2, 3 };
    
    tryAndCatch(printAndClear, std::move(vec));
    tryAndCatch(printAndClear, std::move(vec));
    tryAndCatch(printAndClear, std::vector<int>{4, 3, 2, 1});

    tryAndCatch([](int x) {std::cout << x / 2 << '\n';}, 111);
    
    return 0;
};
