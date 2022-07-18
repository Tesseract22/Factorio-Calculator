#ifndef RECIPE_HPP
#define RECIPE_HPP
#include <string>
#include <map>
#include <list>
using namespace std;
#define Put map<string, float>
class Recipe {
    public:
    Recipe(string name, Put result, Put ingredient): name_(name), result_(result), ingredient_(ingredient) {
    }
    const Put& GetIngredient() const { return ingredient_; }
    const Put& GetResult() const { return result_; }
    private:
    string name_;
    Put result_;
    Put ingredient_;
    
};

#endif