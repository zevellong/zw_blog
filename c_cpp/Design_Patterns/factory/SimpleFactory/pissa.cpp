#include <iostream>
#include <string>
#include <memory>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class Pizza
{
protected:
    string name;

public:
    virtual void papare() = 0;
    Pizza(string nm) : name(nm) { }
    void bake()
    {
        cout << name << " "
             << "baking" << endl;
    }
    void cut()
    {
        cout << name << " "
             << "cutting" << endl;
    }
    void box()
    {
        cout << name << " "
             << "boxing" << endl;
    }
    void setName(string nm)
    {
        name = nm;
    }
    void make()
    {
        this->papare();
        this->bake();
        this->cut();
        this->box();
    }
};
class CheesePizza : public Pizza
{
public:
    CheesePizza() : Pizza("Cheese") { }
    virtual void papare()
    {
        cout << "Cheese Pizza papare:" << endl;
    }
};
class GreezPizza : public Pizza
{
public:
    GreezPizza() : Pizza("Greez") { }
    virtual void papare()
    {
        cout << "Greez Pizza papare:" << endl;
    }
};
class PepperPizza : public Pizza
{
public:
    PepperPizza() : Pizza("Pepper") { }
    virtual void papare()
    {
        cout << "Pepper Pizza papare:" << endl;
    }
};

class SimpleFactory
{
public:
    std::shared_ptr<Pizza> createPizza(string orderType)
    {
        if (orderType == "Cheese")
            return std::shared_ptr<Pizza>(new CheesePizza());
        else if (orderType == "Greez")
            return std::shared_ptr<Pizza>(new GreezPizza());
        else if (orderType == "Pepper")
            return std::shared_ptr<Pizza>(new GreezPizza());
        else
            return nullptr;
    }
};

class Order1
{
    friend std::istream &operator>>(std::istream &is, Order1 &O1);

public:
    SimpleFactory sf;
    void OrderPizza()
    {
        cin >> *this;
        for (auto x : OrderList)
        {
            auto pp = sf.createPizza(x);
            if (pp)
                pp->make();
            else
                cout << "Invaild Pizza type" << endl;
        }
    }

private:
    vector<string> OrderList;
};
std::istream &operator>>(std::istream &is, Order1 &O1)
{
    string buf;
    while (is >> buf)
    {
        O1.OrderList.push_back(buf);
    }
    return is;
}
class Order2
{
};
int main(int argc, const char **argv)
{
    Order1 o1;
    o1.OrderPizza();
    return 0;
}