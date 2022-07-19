#include "Recipe.hpp"
#include "Calculator.hpp"
#include "Preprocess.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;



int main() {
    string item;
    float amount;
    cin >> item;
    cin >> amount;

    map<string, list<Recipe>> item_map = Reader::ReadItem();
    
    Calculator cal{item_map};
    ItemGraph graph;
    try {
        graph = cal.ProduceWithGraph(item, amount);
    } catch(out_of_range& e) {
        cout << "Error: No Item named " << item;
    }
    cout << graph.GraphToString();
    
}