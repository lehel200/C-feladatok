/*Készítse el a findLargestInt függvény alábbi két változatának implementációját!

Az egyik egy std::variant<int, double> elemeket,
a másik pedig egy std::any típusú elemeket tartalmazó listát (std::list) vár paraméterként.

Ezt leszámítva azonos módon működjenek: egy std::optional<int> objektumban adják vissza a lista legnagyobb,
int típusú értéket tároló elemét, vagy üres objektumot, ha nincs ilyen elem a listában!
*/
#include <iostream>
#include <list>
#include <optional>
#include <variant>
#include <any>

// adhat hozzá további include-okat
#include <algorithm>
#include <typeinfo>
#include <typeindex>

std::optional<int> findLargestInt(const std::list< std::variant<int, double> >& numbers) {

    std::list<int> sorted_list;
    
    for (auto it = numbers.begin(); it != numbers.end(); it++) {
        auto actual_element = *it;
        if (std::get_if<int>(&actual_element)) {
            int temp = *std::get_if<int>(&actual_element);
            sorted_list.push_back(temp);

        }
    }

    if (sorted_list.size() > 0) {
        sorted_list.sort();
        int largest_int = sorted_list.back();
        return std::optional<int>{largest_int};    
    }else
        return {};
}

bool isGoodCast(std::any& actual_element) {
    try {
        int akt = std::any_cast<int>(actual_element);
    }
    catch (std::bad_any_cast e) {
        return false;
    }
    return true;
}


std::optional<int> findLargestInt(const std::list<std::any>& numbers) {    
    
    std::list<int> sorted_list;    

    for (auto it = numbers.begin(); it != numbers.end(); it++) {
        auto actual_element= *it;
        if (isGoodCast(actual_element)) {
            sorted_list.push_back(std::any_cast<int>(actual_element));
        }
    }

    if (sorted_list.size() > 0) {
        sorted_list.sort();
        int largest_int = sorted_list.back();
        return std::optional<int>{largest_int};
    }
    else
        return {};
}


int main()
{
    std::list<std::variant<int, double>> numbers = { 1, 2, 3.14 };
    std::optional<int> expected = 2;
    std::cout << (expected == findLargestInt(numbers)) << std::endl;

    numbers.pop_front();
    expected = 2;
    std::cout << (expected == findLargestInt(numbers)) << std::endl;

    numbers.pop_front();
    expected = std::optional<int>{};
    std::cout << (expected == findLargestInt(numbers)) << std::endl;

    numbers = { 0.5, 6.66 };
    expected = std::optional<int>{};
    std::cout << (expected == findLargestInt(numbers)) << std::endl;
    
    std::list<std::any> things = { 3.1416, -20, 10 };
    expected = 10;
    std::cout << (expected == findLargestInt(things)) << std::endl;

    things.pop_back();
    expected = -20;
    std::cout << (expected == findLargestInt(things)) << std::endl;

    things = { -42, numbers, "something" };
    expected = -42;
    std::cout << (expected == findLargestInt(things)) << std::endl;

    things.pop_front();
    expected = std::optional<int>{};
    std::cout << (expected == findLargestInt(things)) << std::endl;
    return 0;
}
