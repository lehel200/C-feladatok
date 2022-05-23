#include <iostream>
#include <memory>
#include <variant>
#include <list>
/*
Készítse el az alábbi main függvény működéséhez azt a << operátor függvényt (és esetleges segédfüggvényeket),
ami a weak_ptr-eket tartalmazó lista elemeiből kiírja az érvényes címre hivatkozó pointerek által mutatott értékeket,
szóközzel elválasztva!

Ahogy látható, a weak_ptr-ek std::variant értékekre mutatnak, ennek megfelelően a helyes típusú értéket írja ki a program!

RESULT:

				linkedList before x3 is freed: 4 a 55
				linkedList after x3 is freed: 4 a

*/
// adhat hozzá további include-okat
// adhat meg tetszőleges using aliasokat az átláthatóbb típusok érdekében

using VariantOfIntChar = std::variant<int, char>;
using WeakPtrList = std::list<std::weak_ptr<VariantOfIntChar>>;

std::ostream& operator<<(std::ostream& o, VariantOfIntChar var) {
	try
	{
		if(char* r = std::get_if<char>(&var)) {
			return o << *r;
		}
		else if (int* r = std::get_if<int>(&var)) {
			return o << *r;
		}
		else {
			return o;
		}
	}
	catch (const std::bad_variant_access b)
	{

	}
}

std::ostream& operator<<(std::ostream& o, std::weak_ptr<VariantOfIntChar> ptr) {
	if (std::shared_ptr<VariantOfIntChar> spt = ptr.lock())
	{
		o << *spt;
	}
	return o;
}


std::ostream& operator<<(std::ostream& o, WeakPtrList w) {
	for (auto i = w.begin(); i != w.end() ; ++i)
	{
		o << *i << " ";
	}
	return o;
}



int main() 
{
	using VariantOfIntChar = std::variant<int, char>;
	VariantOfIntChar x1(4);
	VariantOfIntChar x2('a');

	auto sp1 = std::make_shared<VariantOfIntChar>(x1);
	auto sp2 = std::make_shared<VariantOfIntChar>(x2);

	using WeakPtrList = std::list<std::weak_ptr<VariantOfIntChar>>;
	WeakPtrList myll;
	myll.push_back(sp1);
	myll.push_back(sp2);

	{
		VariantOfIntChar x3(55);
		auto sp3 = std::make_shared<VariantOfIntChar>(x3);
		myll.push_back(sp3);
		std::cout << "linkedList before x3 is freed: " << myll << std::endl;
	}
	std::cout << "linkedList after x3 is freed: " << myll << std::endl;
	return 0;
};
