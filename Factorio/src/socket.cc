#include "Recipe.hpp"
#include "Calculator.hpp"
#include "Preprocess.hpp"
#include <iostream>
#include <string>


using namespace std;



int main() {
    string item;
    float amount;
    cin >> item;
    cin >> amount;

    map<string, list<Recipe>> item_map = Reader::ReadItem();
    
    Calculator cal{item_map};

    auto graph = cal.ProduceWithGraph(item, amount);
    cout << graph.GraphToString();
    
}