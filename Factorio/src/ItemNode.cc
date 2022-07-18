#include "ItemNode.hpp"
#include "Calculator.hpp"
#include "ItemGraph.hpp"

bool operator==(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b) { return a->GetName() == b->GetName(); }
bool operator!=(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b) { return a->GetName() != b->GetName(); }
bool operator<(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b) { return a->GetName() < b->GetName(); }
bool operator>(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b) { return a->GetName() > b->GetName(); }
bool operator<=(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b) { return a->GetName() <= b->GetName(); }
bool operator>=(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b) { return a->GetName() >= b->GetName(); }

// shared_ptr<ItemNode> ItemNode::MergeNode(shared_ptr<ItemNode> a, shared_ptr<ItemNode> b, const Calculator& c) {
//     if (a->name_ != b->name_) {
//         throw "Can't merge node of different items!";
//     }
//     // auto new_node = make_shared<ItemNode>(a->name_, a->amount_ + b->amount_);
//     float new_amount = a->amount_ + b->amount_;
//     auto new_node = c.ProduceWithGraph(a->name_, new_amount).root_;

//     for (auto parent : a->parents_) {
        
//         new_node->AddParent(parent.first, parent.second);
//         parent.first->children_.erase(a);
//         parent.first->AddChild(new_node, parent.first->amount_);
//     }
//     a->parents_.clear();
//     a->children_.clear();

//     for (auto parent : b->parents_) {
//         new_node->AddParent(parent.first, parent.second);
//         parent.first->children_.erase(b);
//         parent.first->AddChild(new_node, parent.first->amount_);
//     }
//     b->parents_.clear();
//     b->children_.clear();

//     return new_node;

// }