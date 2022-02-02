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
class BJCheesePizza : public Pizza
{
public:
    BJCheesePizza() : Pizza("BeiJing Cheese") { }
    virtual void papare()
    {
        cout << "Cheese Pizza papare:" << endl;
    }
};
class BJPepperPizza : public Pizza
{
public:
    BJPepperPizza() : Pizza("BeiJing Pepper") { }
    virtual void papare()
    {
        cout << "Pepper Pizza papare:" << endl;
    }
};
class LDCheesePizza : public Pizza
{
public:
    LDCheesePizza() : Pizza("Ledon Cheese") { }
    virtual void papare()
    {
        cout << "Cheese Pizza papare:" << endl;
    }
};
class LDPepperPizza : public Pizza
{
public:
    LDPepperPizza() : Pizza("Ledon Pepper") { }
    virtual void papare()
    {
        cout << "Pepper Pizza papare:" << endl;
    }
};

class AbsFactory{
    public:
    virtual std::shared_ptr<Pizza> createPizza(string type) = 0;
};
class BJFactory : public AbsFactory{
    public:
    virtual std::shared_ptr<Pizza> createPizza(string type)
    {
        if (type == "cheese")
        {
            return std::shared_ptr<Pizza>(new BJCheesePizza);
        }else if (type == "pepper")
        {
            return std::shared_ptr<Pizza>(new BJPepperPizza);
        }else
            return nullptr;
    }
};
class LDFactory : public AbsFactory{
    public:
    virtual std::shared_ptr<Pizza> createPizza(string type)
    {
        if (type == "cheese")
        {
            return std::shared_ptr<Pizza>(new LDCheesePizza);
        }else if (type == "pepper")
        {
            return std::shared_ptr<Pizza>(new LDPepperPizza);
        }else
            return nullptr;
    }
};
enum PizzaType{
    BEIJING_ = 0,
    LEDON_
};
class OrderStore
{
    friend std::istream &operator>>(std::istream &is, OrderStore& ord);

public:
    OrderStore() : factory(new BJFactory())
    {
        
    }
    OrderStore(PizzaType pt)
    {
        switch (pt)
        {
        case LEDON_:
            factory = new LDFactory();
            break;
        default:
            break;
        }
    }
    void OrderPizza()
    {
        cin >> *this;
        
        for (auto x : OrderList)
        {
            auto pz = factory->createPizza(x);
            if (pz)
                pz->make();
            else
                cout << x <<":Invaild pizza type~~" << endl;
        }
    }
private:
    vector<string> OrderList;
    AbsFactory* factory;
};
std::istream &operator>>(std::istream &is, OrderStore &ord)
{
    string buf;
    while (is >> buf)
    {
        ord.OrderList.push_back(buf);
    }
    return is;
}
class Order2
{
};
int main(int argc, const char **argv)
{
    OrderStore o1(LEDON_);
    o1.OrderPizza();
    return 0;
}