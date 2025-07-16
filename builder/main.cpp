#include <iostream>

using namespace std;

class Ingredient {
    public:
    virtual string getName() const= 0;
    virtual ~Ingredient() = default;
};

class Cheese: public Ingredient {
    string getName() const
    {
        return "cheese";
    }
};
class Bacon : public Ingredient
{
    string getName() const
    {
        return "bacon";
    }
};

class Pepperoni : public Ingredient
{
    string getName() const
    {
        return "pepperoni";
    }
};

class Pizza {
public:
    enum class SIZE
    {
        SMALL,
        MEDIUM,
        LARGE
    };
    SIZE size;
    vector<unique_ptr<Ingredient>> ingredients;
    void printFlavor() {
        if (ingredients.empty())
        {
            cout << "This pizza has nothing" << endl;
            return;
        } else {
            cout << "This pizza contains \n";
            // unique pointer 不可以 copy
            for (const auto &i : ingredients)
            {
                cout << i->getName() << endl;
            }
        }
    }
private:
    friend class PizzaBuilder;
    Pizza() = default;
};

class PizzaBuilder {
    // no init => segfault
    unique_ptr<Pizza> base;
public:
    PizzaBuilder() {
        base = unique_ptr<Pizza>(new Pizza());
    }
    PizzaBuilder& addCheese() {
        base->ingredients.push_back(make_unique<Cheese>());
        return *this;
    }
    PizzaBuilder& addBacon() {
        base->ingredients.push_back(make_unique<Bacon>());
        return *this;
    }

    PizzaBuilder& addPepperoni() {
        base->ingredients.push_back(make_unique<Pepperoni>());
        return *this;
    }
    unique_ptr<Pizza> build() {
        return std::move(base);
    }
};


int main() {
    PizzaBuilder pb;
    unique_ptr<Pizza> my_pizza = pb.addCheese().addBacon().build();
    my_pizza->printFlavor();
}
