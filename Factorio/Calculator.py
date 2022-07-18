import pickle

from DataPreprocess import Recipe


RECIPE_PATH = "local/recipe.json"
ITEMS_PATH = "local/item_map"
ITEMS_JSON_PATH = "local/item_map.json"
with open(ITEMS_PATH, "rb") as f:
    items = pickle.load(file=f)

raw_items = []
for k, v in items.items():
    if v == []:
        raw_items .append(k)

# Produce 
class ItemNode:
        def __init__(self, name:str, amount) -> None:
            
            self.name = name
            self.amount = amount
            self.parents = {}
            self.children = {}
class ItemGraph:
    def __init__(self, name:str, amount:float) -> None:
        self.root = ItemNode(name, amount)
        pass
class Calculator:

    def __init__(self, items) -> None:
        self.items = items

    def ProduceToRaw(self,item: str, amount: float, default_choice=True) -> dict:
        ingredients = {}
        def recur(item: str, amount: float):
            # print(item)
            if self.items[item] == []:
                # print("Ingredients: %s, Amount: %f"%(item, amount))
                if item not in ingredients.keys():
                    ingredients[item] = amount
                else:
                    ingredients[item] += amount
                return
            if default_choice:
                choice = 0
            recipe = self.items[item][choice]

            multi = amount / recipe.ResultCount(item)

            for item in recipe.ingredients:
                name = item["name"]
                num = multi * item["amount"]
                recur(name, num)
        recur(item, amount)
        return ingredients

    def ProduceWithGraph(self,item:str, amount:float, default_choice=True) -> dict:
        graph = ItemGraph(item, amount)
        root = graph.root
        def recur(item: str, amount: float, root: ItemNode):
            # print(item)
            if self.items[item] == []:
                # print("Ingredients: %s, Amount: %f"%(item, amount))
                return

            if default_choice:
                choice = 0
            recipe = self.items[item][choice]
            multi = amount / recipe.ResultCount(item)

            for item in recipe.ingredients:
                name = item["name"]
                num = multi * item["amount"]

                child = ItemNode(name, num)
                root.children[child] = amount
                child.parents[root] = num

                recur(name, num, child)
        recur(item, amount, root)
        return graph
    def ShowItems(self):
        print(self.items.keys())
        
    
c = Calculator(items)

# ingre = c.ProduceToRaw("fast-inserter", 10)
# print(ingre)
graph = c.ProduceWithGraph("fast-inserter", 10)