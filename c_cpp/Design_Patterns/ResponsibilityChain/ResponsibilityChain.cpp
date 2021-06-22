#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
class Requst
{
public:
    int id;
    float price;
    Requst(int i, float p) : id(i), price(p) {}
};
class Handler
{
public:
    virtual void process(const Requst &rq) = 0;
    void set_phd(Handler *_phd)
    {
        this->_phd = _phd;
    }
    Handler(string n) : name(n) {}

protected:
    Handler *_phd;
    string name;
};
class Lv1Handler : public Handler
{
public:
    virtual void process(const Requst &rq)
    {
        if (rq.price <= 5000)
        {
            cout << name << "\t" << rq.id << ": " << rq.price << endl;
        }
        else
        {
            _phd->process(rq);
        }
    }
    Lv1Handler(string n) : Handler(n) {}
};
class Lv2Handler : public Handler
{
public:
    virtual void process(const Requst &rq)
    {
        if (rq.price <= 10000)
        {
            cout << name << "\t" << rq.id << ": " << rq.price << endl;
        }
        else
        {
            _phd->process(rq);
        }
    }
    Lv2Handler(string n) : Handler(n) {}
};
class Lv3Handler : public Handler
{
public:
    virtual void process(const Requst &rq)
    {
        if (rq.price <= 30000)
        {
            cout << name << "\t" << rq.id << ": " << rq.price << endl;
        }
        else
        {
            _phd->process(rq);
        }
    }
    Lv3Handler(string n) : Handler(n) {}
};
class Lv4Handler : public Handler
{
public:
    virtual void process(const Requst &rq)
    {
        if (rq.price > 30000)
        {
            cout << name << "\t" << rq.id << ": " << rq.price << endl;
        }
        else
        {
            _phd->process(rq);
        }
    }
    Lv4Handler(string n) : Handler(n) {}
};
class HandlerFactory
{
public:
    HandlerFactory() : lv1(new Lv1Handler("张主任")),
                       lv2(new Lv2Handler("王主管")),
                       lv3(new Lv3Handler("李副校长")),
                       lv4(new Lv4Handler("候校长"))
    {
        lv1->set_phd(lv2);
        lv2->set_phd(lv3);
        lv3->set_phd(lv4);
        lv4->set_phd(lv1);
    }
    ~HandlerFactory()
    {
        delete lv1;
        delete lv2;
        delete lv3;
        delete lv4;
    }
    void process(const Requst &re)
    {
        lv4->process(re);
    }

private:
    Handler *lv1, *lv2, *lv3, *lv4;
};
int main(int argc, char const *argv[])
{
    HandlerFactory hf;
    Requst re(1, 1000);
    hf.process(re);
    return 0;
}
