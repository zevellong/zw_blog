#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Drink
{
private:
    string des; 
    double price;

public:
    Drink(string d, double p) : des(d), price(p) {}

    double getPrice()
    {
        return this->price;
    }
    void setPrice(double price)
    {
        this->price = price;
    }

    string getDes()
    {
        return this->des;
    }
    void setDes(string des)
    {
        this->des = des;
    }
    virtual double calcCost() { return 0.0; }
    virtual string geneInfo() {
        return nullptr;}
    void print() {
        cout << geneInfo() << ": " << calcCost() << endl;
    }
};
class Coffee : public Drink
{
public:
    Coffee(string d, double p) : Drink(d + "Coffice", p) {}
    double calcCost() override
    {
        return getPrice();
    }
    string geneInfo() override
    {
        return getDes();
    }
};
class LongBlack : public Coffee
{
public:
    LongBlack() : Coffee("LongBlack", 6) {}
    double calcCost() override
    {
        return Coffee::calcCost();
    }
    string geneInfo() override
    {
        return Coffee::geneInfo();
    }
};

class Derector : public Drink
{
public:
    Derector(string d, double p, Drink *pD)
        : Drink(d, p), pDrk(pD) {}

protected:
    Drink *pDrk;
public:
    double calcCost() override
    {
        return getPrice() + pDrk-> calcCost();
    }
    string geneInfo() override
    {   
        return getDes() + "_" +  pDrk->geneInfo();
    }
};
class Soy : public Derector
{
    public:
    Soy(Drink* pD) : Derector("Soy", 2, pD) { }
};
class Chocolate : public Derector
{
    public:
    Chocolate(Drink* pD) : Derector("Chocolate", 4, pD) { }
};
class Milk : public Derector
{
    public:
    Milk(Drink* pD) : Derector("Milk", 3, pD) { }
};
int main(int argc, char const *argv[])
{
    LongBlack lb;
    Milk mk(&lb);
    mk.print();
    Chocolate cho1(&mk);
    cho1.print();
    Chocolate cho2(&cho1);
    cho2.print();
    Soy soy(&cho2);
    soy.print();
    return 0;
}
