#include "ItemGraph.hpp"
#include "ItemNode.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
using namespace std;
void ItemGraph::GraphToCSV() {
    // stack<shared_ptr<ItemNode>> stk;
    // stk.push(root);

    // while (!stk.empty()) {
    //     auto node = stk.top();
    //     stk.pop();
    //     for (auto iter : node->GetChildren()) {
    //         stk.push(iter.first);
    //     }
    // }
    auto chart = vector<vector<string>>();
    ofstream f{"local/" + root_->GetName() + ".csv"};
    if (!f.is_open()) {
        cout << "failed to open file" << endl;
        return;
    }
    GraphToCSVHelper(root_, chart, 0, 0);
    for (int i = 0; i < chart.size(); i++) {
        for (int j = 0; j < chart[i].size(); j++) {
            f << chart[i][j];
            f << ',';
        }
        f << '\n';
    }
    cout << "chart sucessfull written" << endl;
    f.close(); 
}
string ItemGraph::GraphToString() {
    auto chart = vector<vector<string>>();
    GraphToCSVHelper(root_, chart, 0, 0);
    string res;
    for (int i = 0; i < chart.size(); i++) {
        for (int j = 0; j < chart[i].size(); j++) {
            res += chart[i][j];
            res += ',';
        }
        res += '\n';
    }
    return res;
}
 int ItemGraph::GraphToCSVHelper(shared_ptr<ItemNode> root, vector<vector<string>>& chart, int depth, int height) {
    int size = 0;
    vector<string> word_vec = {"ore"};
    for (auto iter : root->GetChildren()) {
        for (auto word : word_vec) {
            if (iter.first->GetName().find(word) == string::npos) {
                size += GraphToCSVHelper(iter.first, chart, depth + 2, height + size);
            }
        }
    }
    while (height >= chart.size()) { 
        chart.push_back(vector<string>());
        // cout << height << " " << chart.size() << endl;
    }
    while (depth + 1 >= chart[height].size()) {
        chart[height].push_back("");
        // cout << "push depth" << endl;
    }
    chart[height][depth] = root->GetName();
    chart[height][depth + 1] = to_string(root->GetAmount());
    
    

    return max(size, 1);

}

// ItemGraph ItemGraph::MergeGraph(const Calculator& c) {
//     map<string, reference_wrapper<shared_ptr<ItemNode>>> refer_list;
//     // ItemGraph new_graph{root_->GetName(), root_->GetAmount()};
//     MergeGraphHelper(root_, refer_list, c);
// }

// void ItemGraph::MergeGraphHelper(shared_ptr<ItemNode> root, map<string, reference_wrapper<shared_ptr<ItemNode>>>& refer_list, const Calculator& c) {
//     auto find_res = refer_list.find(root->GetName());
//     if (find_res == refer_list.cend()) {
//         refer_list.insert({root->GetName(), root});
//     } else {
//         auto new_node = ItemNode::MergeNode(root, refer_list.at(root->GetName()), c);
//         refer_list.at(root->GetName()) = new_node;
//         root = new_node;
//     }
//     for (auto iter : root->GetChildren()) {
//        MergeGraphHelper(iter.first, refer_list, c);
//     }
// }

