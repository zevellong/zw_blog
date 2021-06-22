#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class stock
{
public:
    stock() : name("StockA"), quanity(10) {}
    void buy()
    {
        cout << "Stock:buy()\t|\tname: " + name + "\tquanity: " << quanity << endl;
    }
    void sell()
    {
        cout << "Stock:sell()\t|\tname: " + name + "\tquanity: " << quanity << endl;
    }

private:
    string name;
    int quanity;
};
class Order
{
public:
    virtual void execute(){};
    virtual ~Order() = 0;

private:
};
Order::~Order() {}
class BuyStock : public Order
{
public:
    BuyStock() : pstk(new stock) {}
    virtual ~BuyStock()
    {
        delete pstk;
    }
    virtual void execute() override
    {
        pstk->buy();
    }

private:
    stock *pstk;
};
class SellStock : public Order
{
public:
    SellStock() : pstk(new stock) {}
    virtual ~SellStock()
    {
        delete pstk;
    }
    virtual void execute() override
    {
        pstk->sell();
    }

private:
    stock *pstk;
};
class Broket
{
public:
    void putOrder(Order *po)
    {
        ordVec.push_back(po);
    }
    void exeOrder()
    {
        for (auto x : ordVec)
        {
            if (x != nullptr)
                x->execute();
        }
    }

private:
    vector<Order *> ordVec;
};
int main(int argc, char const *argv[])
{
    BuyStock bs1, bs2;
    SellStock ss1, ss2;
    Broket btk;
    btk.putOrder(&bs1);
    btk.putOrder(&bs2);
    btk.putOrder(&ss2);
    btk.putOrder(&ss1);
    btk.exeOrder();
    return 0;
}
