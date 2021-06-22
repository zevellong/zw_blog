#include <iostream>
#include <string>
#include <memory>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class House
{
public:
    string getRoof()
    {
        return this->roof;
    }
    void setRoof(string roof)
    {
        this->roof = roof;
    }

    string getWalls()
    {
        return this->walls;
    }
    void setWalls(string walls)
    {
        this->walls = walls;
    }
    string getBasic()
    {
        return this->basic;
    }
    void setBasic(string basic)
    {
        this->basic = basic;
    }
    void print()
    {
        cout << "Info:" << endl
             << "Basic: " << basic
             << "\tWalls: " << walls
             << "\tRoof: " << roof << endl;
    }

private:
    string basic;
    string walls;
    string roof;
};
class HouseBuilder
{
public:
    virtual ~HouseBuilder() = 0;
    House *build()
    {
        buildBasic();
        buildWalls();
        roofed();
        return pHouse;
    }
    virtual void buildBasic() {}
    virtual void buildWalls() {}
    virtual void roofed() {}

protected:
    House *pHouse = new House();
};
HouseBuilder::~HouseBuilder()
{
    delete pHouse;
    cout << "call ~HouseBuilder" << endl;
}
class CommonHouse : public HouseBuilder
{
public:
    void buildBasic() override
    {
        pHouse->setBasic("commonBasic");
    }
    void buildWalls() override
    {
        pHouse->setWalls("Common Walls");
    }
    void roofed() override
    {
        pHouse->setRoof("Common Roof");
    }
};
class HighHouse : public HouseBuilder
{
public:
    void buildBasic() override
    {
        pHouse->setBasic("High Basic");
    }
    void buildWalls() override
    {
        pHouse->setWalls("High Walls");
    }
    void roofed() override
    {
        pHouse->setRoof("High Roof");
    }
};

class Director
{
public:
    Director() = default;
    Director(HouseBuilder *phb) : hb(phb) {}
    void setHb(HouseBuilder *phb)
    {
        hb = phb;
    }
    House *construct()
    {
        return hb->build();
    }

private:
    HouseBuilder *hb;
};

int main(int argc, const char **argv)
{
    CommonHouse ch = CommonHouse();
    HighHouse* phh = new HighHouse();
    Director boss(&ch);
    auto x = boss.construct();
    x->print();
    boss.setHb(phh);
    x = boss.construct();
    x->print();

    return 0;
}