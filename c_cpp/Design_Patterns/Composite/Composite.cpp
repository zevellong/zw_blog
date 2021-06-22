#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;


class Org
{
public:
    Org(string de, string na) : des(de), name(na) { }
    void printThis(int ct)
    {
        for (int a=0; a < ct; a++)
            cout <<"\t";
        cout << getName() << ": " << getDes() << endl; 
    }
    virtual void add(Org* po) {}
    virtual void remove(Org* po){}
    virtual void print() {}
    virtual ~Org() = 0;
private:
    string des;
    string name;

protected:
    string getName()
    {
        return this->name;
    }
    void setName(string name)
    {
        this->name = name;
    }

    string getDes()
    {
        return this->des;
    }
    void setDes(string des)
    {
        this->des = des;
    }
};
Org::~Org() {}
class Department : public Org
{
    public:
    Department(string de, string na) : Org(de, na) { }
    void print() override
    {
        printThis(1);
    }
};
class College : public Org
{
    public:
    College(string de, string na) : Org(de, na) { }
    void print() override
    {
        printThis(0);
        for (auto x : pDpt)
            x->print();
    }
    void add(Org* po) override
    {
        pDpt.push_back(po);
    }
    void remove(Org* po) override
    {
        pDpt.pop_back();
    }
    private:
    vector<Org*> pDpt; 
};

int main(int argc, char const *argv[])
{
    College pku("国内顶级大学", "北京大学");
    College cs3("本部","交叉前沿学院");
    College cs1("本部","信科");
    College cs2("大兴","软微");
    Department d1("学硕","软件工程");
    Department d2("专硕","软件工程");
    Department d3("学硕","计算机与科学");
    Department d4("专硕","计算机与科学");
    Department d5("学硕","网络安全");
    Department d6("专硕","网络安全");
    Department d7("学硕","计算机辅助翻译");
    Department d8("专硕","计算机辅助翻译");
    Department d9("学硕","数据科学");
    Department d10("专硕","数据科学");
    Department d11("学硕","智能科学");
    Department d12("专硕","智能科学");

    cs1.add(&d1); cs1.add(&d3);
    cs1.add(&d2); cs1.add(&d4);
    cs2.add(&d5); cs2.add(&d6);
    cs2.add(&d7); cs2.add(&d8);
    cs3.add(&d9); cs3.add(&d10);
    cs3.add(&d12); cs3.add(&d11);
    pku.add(&cs1);pku.add(&cs2);pku.add(&cs3);
    pku.print();

    return 0;
}
