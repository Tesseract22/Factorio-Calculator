#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "Recipe.hpp"
#include "ItemGraph.hpp"
#include "ItemNode.hpp"
#include <map>
#include <string>
#include <list>
#include <fstream>
#include <vector>


class Calculator {
    public:
        Calculator(map<string, list<Recipe>> data): data_(data) {}
        Put ProduceToRaw(const string& name, float amount) const;
        ItemGraph ProduceWithGraph(const string& name, float amount) const;
        void PrintItems() const;
        static void PrintAns(Put ans);
        static void PrintAns(shared_ptr<ItemNode> root);
        static void GraphToCSV(shared_ptr<ItemNode> root);
    private:
        map<string, list<Recipe>> data_;
        void ProduceToRawHelper(const string& name, float amount, Put& ans) const;
        void ProduceWithGraphHelper(const string& name, float amount, shared_ptr<ItemNode> root) const;
        static int GraphToCSVHelper(shared_ptr<ItemNode> root, vector<vector<string>>& chart, int depth, int height);
};

#endif