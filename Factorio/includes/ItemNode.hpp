#ifndef ITEM_NODE_HPP
#define ITEM_NODE_HPP
#include <string>
#include <memory>
#include <list>
#include <map>

// #include "Calculator.hpp"

using namespace std;
class ItemNode {
    public:
        
        ItemNode(string name, float amount): name_(name), amount_(amount) {}
        void AddParent(shared_ptr<ItemNode> node, float amount) { parents_.insert({node, amount}); }
        void AddChild(shared_ptr<ItemNode> node, float amount) { children_.insert({node, amount}); }
        map<shared_ptr<ItemNode>, float> GetParents() const { return parents_; }
        map<shared_ptr<ItemNode>, float> GetChildren() const { return children_; }
        
        string GetName() const { return name_; }
        float GetAmount() const { return amount_; }
        // static shared_ptr<ItemNode> MergeNode(shared_ptr<ItemNode> a, shared_ptr<ItemNode> b, Calculator& c);
        // static bool name_comp(shared_ptr<ItemNode> a, shared_ptr<ItemNode> b) { return a->GetName() > b->GetName();}
    private:
        string name_;
        float amount_;
        map<shared_ptr<ItemNode>, float> parents_;
        map<shared_ptr<ItemNode>, float> children_;
};
bool operator==(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b);
bool operator!=(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b);
bool operator<(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b);
bool operator>(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b);
bool operator<=(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b);
bool operator>=(const shared_ptr<ItemNode>& a, const shared_ptr<ItemNode>& b);



#endif