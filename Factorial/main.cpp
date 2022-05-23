/*
Az alább megadott main függvényben lévő kódhoz készítse el a factorial függvényt,
ami visszaadja egy szám faktoriálisát, 

és a szükséges operátor függvény implementációját,
ami szóközökkel elválasztva továbbítja az std::array elemeit az std::ostreamre!

RESULT:
			5! = 120
			8! = 40320
			(3*3)! = 362880
			array contents: 1 1 2 6 24 120
*/

#include <array>
#include <iostream>
// adhat hozzá további include-okat

template<class T>
constexpr T factorial(T x) {
	if (x == 0)
	{
		return x = 1;
	}
	else {
		return x *= factorial(x-1);
	}
}

std::ostream& operator<<(std::ostream& o, std::array<int, factorial(2 * 1 + 1)> arr) {
	for (size_t i = 0; i < arr.size(); ++i) {
		o << arr[i] << " ";
	}
	return o;
}






int main() 
{
	std::cout << "5! = " << factorial(5) << '\n';
	std::cout << "8! = " << factorial(8) << '\n';
	std::cout << "(3*3)! = " << factorial(3 * 3) << '\n';
	
	std::array<int, factorial(2 * 1 + 1)> arr;
	
	for (size_t i = 0; i < arr.size(); ++i) {
		arr[i] = factorial(i);
	}
	std::cout << "array contents: " << arr << '\n';
	
	
	return 0;
}
