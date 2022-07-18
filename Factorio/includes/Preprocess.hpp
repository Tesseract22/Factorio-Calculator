#ifndef PREPROCESS_HPP
#define PREPROCESS_HPP
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
namespace Reader {
    map<string, list<Recipe>> ReadItem();

    void SetEnd(map<string, list<Recipe>>& item_map);
}


#endif