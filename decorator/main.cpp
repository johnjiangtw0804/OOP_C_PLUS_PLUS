#include <iostream>

using namespace std;

// Builder Pattern 是為了建立物件，而 Decorator Pattern 是為了擴充物件的功能，而且不修改原始物件結構。


class IBeverage {
public:
    virtual int getCost()  = 0;
    virtual string getDescription() = 0;
    virtual ~IBeverage() = default;
};

class Espresso : public IBeverage{
public:
    int getCost() override{
        return 1;
    }
    string getDescription() override{
        return "The beverage contains a Espresso";
    }
};

// Decorator 是一個 abstract class 去包
class BeverageDecorator: public IBeverage {
protected:
    shared_ptr<IBeverage> base_drink;
public:
    BeverageDecorator(shared_ptr<IBeverage>base): base_drink(base){};
    virtual ~BeverageDecorator() = default;
};

class MilkDecorator : public BeverageDecorator {
public:
    MilkDecorator(shared_ptr<IBeverage> base) : BeverageDecorator(base) {};
    int getCost() override{
        return base_drink->getCost() + 10;
    }
    string getDescription() override{
        return base_drink->getDescription() + " added milk";
    }
};

class SugarDecorator : public BeverageDecorator {
public:
    SugarDecorator(shared_ptr<IBeverage> base) : BeverageDecorator(base) {};
    int getCost() override {
        return base_drink->getCost() + 20;
    }
    string getDescription() override
    {
        return base_drink->getDescription() + " added sugar";
    }
};


int main() {
    shared_ptr<IBeverage> espresso = shared_ptr<Espresso>(new Espresso());
    shared_ptr<IBeverage> milkEspresso = make_shared<MilkDecorator>(espresso);
    cout << milkEspresso->getDescription() << endl;
    cout << "Cost: " << milkEspresso->getCost() << endl;
    shared_ptr<IBeverage> sugarMilkEspresso = make_unique<SugarDecorator>(milkEspresso);
    cout << "Description: " << sugarMilkEspresso->getDescription() << endl;
}
