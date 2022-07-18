#include "Preprocess.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <json/json.h>
#include <map>
#include "Recipe.hpp"
#include "Calculator.hpp"
#include <vector>
using namespace std;


string ITEMS_JSON_PATH = "local/item_map.json";
map<string, list<Recipe>> Reader::ReadItem() {
    ifstream f{ITEMS_JSON_PATH};
    string pre_data;
    string line;
    while (getline(f, line)) {
        pre_data += line;
    }
    
    Json::Value root;
    Json::Reader reader;
    reader.parse(pre_data, root);
    map<string, list<Recipe>> item_map;
    for (auto name : root.getMemberNames()) {
        auto item = root[name];
        list<Recipe> recipes; 
        for (auto r : item) {
            Put ingredient;
            for (auto i : r["ingredients"]) {
                ingredient.insert({i["name"].asString(), i["amount"].asFloat()});
            }
            Put result;
            for (auto i : r["result"]) {
                result.insert({i["name"].asString(), i["amount"].asFloat()});
            }
            Recipe recipe{r["name"].asString(), result, ingredient};
            recipes.push_back(recipe);        
            }
        item_map.insert({name, recipes});
    }
    return item_map;
}
