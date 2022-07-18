

#include "Calculator.hpp"
#include <iostream>
#include "ItemGraph.hpp"
#include <fstream>
#include <vector>
string CSV_PATH = "local/graph.csv";
int MAX_SIZE = 30;

Put Calculator::ProduceToRaw(const string& name, float amount) const {
    Put ans;
    ProduceToRawHelper(name, amount, ans);
    return ans;
}

ItemGraph Calculator::ProduceWithGraph(const string& name, float amount) const  {
    ItemGraph graph{name, amount};
    ProduceWithGraphHelper(name, amount, graph.root_);
    return graph;
}
void Calculator::ProduceWithGraphHelper(const string& name, float amount, shared_ptr<ItemNode> root) const  {
    if (data_.at(name).empty()) {
        return;
    }
    Recipe recipe = *(data_.at(name).cbegin());
    float multi = amount / recipe.GetResult().at(name);
    for (auto iter : recipe.GetIngredient()) {
        auto next = make_shared<ItemNode>(iter.first, multi * iter.second);
        next->AddParent(root, multi * iter.second);
        root->AddChild(next, amount);
        ProduceWithGraphHelper(iter.first, multi * iter.second, next);

    }
}
void Calculator::ProduceToRawHelper(const string& name, float amount, Put& ans) const  {
    // cout << name << endl;
    if (data_.at(name).empty()) {
        if (ans.find(name) == ans.cend()) {
            ans.insert({name, amount});
        } else {
            ans.at(name) += amount;
        }
        return;
    };
    
    Recipe recipe = *(data_.at(name).cbegin());
    float multi = amount / recipe.GetResult().at(name);
    for (auto iter : recipe.GetIngredient()) {
        ProduceToRawHelper(iter.first, multi * iter.second, ans);
    }
}

void Calculator::PrintItems() const  {
    for (auto iter : data_) {
        cout << iter.first << endl;
    }
}
void Calculator::PrintAns(Put ans) {
    for (auto iter : ans) {
        cout << iter.first << ": " << iter.second << endl;
    }
}

void Calculator::PrintAns(shared_ptr<ItemNode> root) {
    for (auto iter : root->GetChildren()) {
        PrintAns(iter.first);
    }
    cout << root->GetName() << ": " << root->GetAmount() << endl;
}

// void Calculator::GraphToCSV(shared_ptr<ItemNode> root) {
//     // stack<shared_ptr<ItemNode>> stk;
//     // stk.push(root);

//     // while (!stk.empty()) {
//     //     auto node = stk.top();
//     //     stk.pop();
//     //     for (auto iter : node->GetChildren()) {
//     //         stk.push(iter.first);
//     //     }
//     // }
//     auto chart = vector<vector<string>>(MAX_SIZE, vector<string>(MAX_SIZE, ""));
//     ofstream f{CSV_PATH};
//     if (!f.is_open()) {
//         cout << "failed" << endl;
//     }
//     GraphToCSVHelper(root, chart, 0, 0);
//     for (int i = 0; i < MAX_SIZE; i++) {
//         for (int j = 0; j < MAX_SIZE; j++) {
//             f << chart[i][j];
//             f << ',';
//         }
//         f << '\n';
//     }
//     f.close(); 
// }

//  int Calculator::GraphToCSVHelper(shared_ptr<ItemNode> root, vector<vector<string>>& chart, int depth, int height) {
//     int size = 0;
//     vector<string> word_vec = {"ore"};
//     for (auto iter : root->GetChildren()) {
//         for (auto word : word_vec) {
//             if (iter.first->GetName().find(word) == string::npos) {
//                 size += GraphToCSVHelper(iter.first, chart, depth + 2, height + size);
//             }
//         }
//     }
//     while (height >= chart.size()) { 
//         chart.push_back(vector<string>());
//         // cout << height << " " << chart.size() << endl;
//     }
//     while (depth + 1 >= chart[height].size()) {
//         chart[height].push_back("");
//         cout << "push depth" << endl;
//     }
//     chart[height][depth] = root->GetName();
//     chart[height][depth + 1] = to_string(root->GetAmount());
    
    

//     return max(size, 1);

//  }  