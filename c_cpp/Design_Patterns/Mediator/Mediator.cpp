// 各个设备协同工作，流程：闹钟响起->咖啡机开始->窗帘落下->电视机开始播放

#include <iostream>
#include <string>
#include <unordered_map>
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
class Colleague;
enum class Country
{
    China = 0,
    USA,
    Tailand,
    None,
    AllCountry
};
static inline string getCName(Country c)
{
    static string info[] = {"China", "USA", "TaiLand", "None", "All"};
    return info[static_cast<int>(c)];
}
class Mediator
{
public:
    virtual void communicate(Country from, Country to, string msg) = 0;
    virtual void registerCountry(Country c, Colleague *pcl) = 0;
    virtual void removeCountry(Country c) = 0;

private:
};
class Colleague
{
public:
    Colleague(Mediator *med, Country c = Country::None)
        : pmed(med), id(c) {}
    virtual void sendMsg(Country id, string Msg) = 0;
    virtual void receiveMsg(Country id, string Msg) = 0;

protected:
    Country id;
    Mediator *pmed;
};
class C_Cn : public Colleague
{
public:
    C_Cn(Mediator *med) : Colleague(med, Country::China)
    {
        med->registerCountry(id, this);
    }
    virtual void sendMsg(Country id, string msg) override
    {
        cout << getCName(this->id) << "sendmsg:" << msg
             << "\t to:" << getCName(id) << endl;
        pmed->communicate(this->id, id, msg);
    }
    virtual void receiveMsg(Country id, string msg) override
    {
        cout << "China received: " << msg << "\tmsg from:"
             << getCName(id) << endl;
    }
};
class C_USA : public Colleague
{
public:
    C_USA(Mediator *med) : Colleague(med, Country::USA)
    {
        med->registerCountry(id, this);
    }
    virtual void sendMsg(Country id, string msg) override
    {
        cout << getCName(this->id) << "sendmsg:" << msg
             << "\t to:" << getCName(id) << endl;
        pmed->communicate(this->id, id, msg);
    }
    virtual void receiveMsg(Country id, string msg) override
    {
        cout << "USA received: " << msg << "\tmsg from:"
             << getCName(id) << endl;
    }
};
class C_TAI : public Colleague
{
public:
    C_TAI(Mediator *med) : Colleague(med, Country::Tailand)
    {
        med->registerCountry(id, this);
    }
    virtual void sendMsg(Country id, string msg) override
    {
        cout << getCName(this->id) << "sendmsg:" << msg
             << "\t to:" << getCName(id) << endl;
        pmed->communicate(this->id, id, msg);
    }
    virtual void receiveMsg(Country id, string msg) override
    {
        cout << "Tailand received: " << msg << "\tmsg from:"
             << getCName(id) << endl;
    }
};
class ConcreteMediator : public Mediator
{
public:
    virtual void registerCountry(Country c, Colleague *pcl)
    {
        mp[c] = pcl;
    }
    virtual void removeCountry(Country c)
    {
        mp.erase(c);
    }
    virtual void communicate(Country from, Country to, string msg) override
    {
        if (to == Country::None)
            return;
        if (to == Country::AllCountry)
        {
            for (auto bg = mp.begin(), ed = mp.end();
                 bg != ed; bg++)
            {
                bg->second->receiveMsg(from, msg);
            }
        }
        else
        {
            mp[to]->receiveMsg(from, msg);
        }
    }

private:
    unordered_map<Country, Colleague *> mp;
};
int main(int argc, char const *argv[])
{
    Mediator *pm = new ConcreteMediator;
    C_Cn cn(pm);
    C_USA usa(pm);
    C_TAI tai(pm);
    cn.sendMsg(Country::USA, "How are you?");
    usa.sendMsg(Country::AllCountry, "I'm fine!");

    delete  pm;
    return 0;
}
