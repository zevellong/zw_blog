#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
class QuackBehavor
{
public:
    virtual void quack() const = 0;
};
class FlyBehavor
{
public:
    virtual void fly() const = 0;
};
class GoodQuack : public QuackBehavor
{
public:
    virtual void quack() const override
    {
        cout << "Good quack behavor" << endl;
    }
};
class BadQuack : public QuackBehavor
{
public:
    virtual void quack() const override
    {
        cout << "Bad quack behavor" << endl;
    }
};
class GoodFly : public FlyBehavor
{
public:
    virtual void fly() const override
    {
        cout << "Good fly behavor" << endl;
    }
};
class BadFly : public FlyBehavor
{
public:
    virtual void fly() const override
    {
        cout << "Bad fly behavor" << endl;
    }
};
class duck
{
protected:
    string name;
    FlyBehavor *_fb;
    QuackBehavor *_qb;

public:
    duck(string nm, FlyBehavor *fb, QuackBehavor *qb)
        : name(nm), _fb(fb), _qb(qb) {}
    virtual ~duck() = 0;
    void display()
    {
        cout << "Duck type: " << name << endl;
        _fb->fly();
        _qb->quack();
    }
};
duck::~duck() {}
class WildDuck : public duck
{
public:
    WildDuck() : duck("野鸭",new GoodFly, new GoodQuack) {}
    virtual ~WildDuck()
    {
        delete _fb;
        delete _qb;
    }
};
class PekingDuck : public duck
{
public:
    PekingDuck() : duck("北京鸭",new BadFly, new BadQuack) {}
    virtual ~PekingDuck()
    {
        delete _fb;
        delete _qb;
    }
};

int main(int argc, char const *argv[])
{
    duck* pdk = new PekingDuck();
    duck* wdk = new WildDuck;
    pdk->display();
    wdk->display();
    return 0;
}
