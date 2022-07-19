#ifndef ITEM_GRAPH_HPP
#define ITEM_GRAPH_HPP
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include "ItemNode.hpp"
#include <string>
using namespace std;


class ItemGraph {
    public:
        ItemGraph() {}
        ItemGraph(string name, float amount): root_(make_shared<ItemNode>(name, amount)) {}
        shared_ptr<ItemNode> root_;
        void GraphToCSV();
        string GraphToString();
        // ItemGraph MergeGraph(const Calculator& c);
    private:
        int GraphToCSVHelper(shared_ptr<ItemNode> root, vector<vector<string>>& chart, int depth, int height);
        // void MergeGraphHelper(shared_ptr<ItemNode> root, map<string, reference_wrapper<shared_ptr<ItemNode>>>& refer_list, const Calculator& c);
};
#endif