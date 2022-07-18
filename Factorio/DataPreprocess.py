import json
import pickle


RECIPE_PATH = "local/recipe.json"
ITEMS_PATH = "local/item_map"
ITEMS_JSON_PATH = "local/item_map.json"
with open(RECIPE_PATH, "rb") as f:
    recipes = json.load(f)



class Recipe:

    def __init__(self, data: dict) -> None:
        self.name = data["name"]
        if "normal" in data.keys():
            data = data["normal"]
        self.ingredients = data["ingredients"]

        self.ingredients = []
        for item in data["ingredients"]:
            if type(item) is list:
                new_data = {"type": "item", "name": item[0], "amount": item[1]}
                self.ingredients.append(new_data)
            else:
                self.ingredients.append(item)

        self.result = []
        if "results" in data.keys():
            for item in data["results"]:
                if type(item) is list:
                    new_data = {"type": "item", "name": item[0], "amount": item[1]}
                    self.result.append(new_data)
                else:
                    self.result.append(item)
        elif type(data["result"]) is str:
            name = data["result"]
            amount = 1
            if "result_count" in data.keys():
                amount = data["result_count"]
            self.result = [ {"type": "item", "name": name, "amount": amount}, ]

    def ResultCount(self, item: str) -> int:
        for r in self.result:
            if r["name"] == item:
                return r["amount"]

def CreateItemList(recipes: list) -> dict:
    items = {}
    c = 0
    for data in recipes:
        print(c)
        recipe = Recipe(data)
        print(recipe.name)
        for item in recipe.result:
            # every item in items would store its child recipes
            name = item["name"]
            if name not in items.keys():
                items[name] = []
            items[name].append(recipe)
        for item in recipe.ingredients:
            name = item["name"]
            if name not in items.keys():
                items[name] = []
        c += 1
    return items


items_json = {}
for k, v in CreateItemList(recipes).items():
    new_recipes = []
    for recipe in v:
        json_recipe = {"name": recipe.name, "result": recipe.result, "ingredients": recipe.ingredients}
        new_recipes.append(json_recipe)
    items_json[k] = new_recipes

if __name__ == "__main__":
    items = CreateItemList(recipes)
    with open(ITEMS_JSON_PATH, "w") as f:
        json.dump(items_json, f)


    # with open(ITEMS_PATH, "rb") as f:
    #     items = pickle.load(file=f)

    print(items.keys())