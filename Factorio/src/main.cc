
#include <iostream>
#include <fstream>
#include <string>
#include "Recipe.hpp"
#include "Calculator.hpp"
#include "Preprocess.hpp"
#include <list>

using namespace std;


int main(int argc, char** argv) {

    map<string, list<Recipe>> item_map = Reader::ReadItem();
    
    Calculator cal{item_map};
    if (argc != 3) {
        cal.PrintItems();
        return 0;
    }
    string target_name = string(argv[1]);
    float target_amount = stof(string(argv[2]));

    // auto ans = cal.ProduceToRaw(target_name, target_amount);

    auto ans = cal.ProduceWithGraph(target_name, target_amount);
    // ans.GraphToCSV();
    cout << ans.GraphToString();
    return 0;
}