#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Soyia
{
    public:
    void make()
    {
        cout << "---------" <<endl;
        select();
        if (customerWantCondiments())
            add();
        soak();
        beat();
        cout << "---------" <<endl;
    }
    virtual void add() = 0;
    private:
    void select()
    {
        cout << "step1:选择原材料"<<endl;
    }
    
    void soak()
    {
        cout << "step3:黄豆和配料开始浸泡3h" <<endl;
    }
    void beat()
    {
        cout << "step4:黄豆和配料放到豆浆机去打碎"<<endl;
    }
    bool customerWantCondiments() //钩子函数
    {
        return true;
    }
};
class ReadBeanSoy:public Soyia
{
    public:
    virtual void add()
    {
        cout << "step2:加入上好的红豆"<<endl;
    }
};
class PeanutSoy:public Soyia
{
    public:
    virtual void add()
    {
        cout << "step2:加入上好的花生"<<endl;
    }
};
class PureSoy : public Soyia
{
    public:
    virtual void add() override
    {

    }
    private:
    bool customerWantCondiments() //钩子函数
    {
        return false;
    }
};
int main(int argc, char const *argv[])
{
    ReadBeanSoy rbs;
    rbs.make();
    PeanutSoy ps;
    ps.make();
    PureSoy pus;
    pus.make();
    return 0;
}
