#include <iostream>
#include <string>
#include <list>

using std::list;
using std::cout;
using std::endl;
using std::string;
class Observer
{
public:
    void update(float temp, float pres, float humi)
    {
        _temp = temp;
        _pres = pres;
        _humi = humi;
        display();
    }
    virtual void display() const = 0;
protected:
    float _temp, _pres, _humi;
};
class Sina : public Observer
{
public:
virtual void display() const override
{
    cout << "This is sina.com weather" <<endl;
    cout << "Temperature: " << _temp << endl;
    cout << "Pressure: " << _pres << endl;
    cout << "Humidity: " << _humi << endl; 
}
};
class Baidu : public Observer
{
public:
virtual void display() const override
{
    cout << "This is Baidu.com weather" <<endl;
    cout << "Temperature: " << _temp << endl;
    cout << "Pressure: " << _pres << endl;
    cout << "Humidity: " << _humi << endl; 
}
};
class Subject
{
public:
    Subject() : _temp(30),_pres(1000),_humi(20) {}
    void setData(float temp, float pres, float humi)
    {
        _temp = temp;
        _pres = pres;
        _humi = humi;
        datachange();
    }
    virtual void datachange() = 0;
    virtual void registerObs(Observer* po) = 0;
    virtual void removeObs(Observer* po) = 0;
    virtual void notifyAllObs() = 0;
protected:
    float _temp, _pres, _humi;
};
class Weather : public Subject
{
public:
    
    virtual void registerObs(Observer* po)
    {
        obsList.push_back(po);
        po->update(_temp,_pres,_humi);
    }
    virtual void removeObs(Observer* po)
    {
        obsList.remove(po);
    }
    virtual void notifyAllObs()
    {
        for (auto x : obsList)
        {
            x->update(_temp,_pres,_humi);
        }
    }
    virtual void datachange() override
    {
        notifyAllObs();
    }
private:
list<Observer*> obsList;
};
int main(int argc, char const *argv[])
{
    Sina sn;
    Baidu bd;
    Weather weatherStation;
    weatherStation.registerObs(&sn);
    weatherStation.registerObs(&bd);

    weatherStation.setData(15, 1200, 10);
    return 0;
}
