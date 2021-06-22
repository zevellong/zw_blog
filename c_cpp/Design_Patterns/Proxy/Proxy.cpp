#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class iTeacherDao
{
    public:
    virtual void teach() = 0;
};
// void iTeacherDao::teach()
// {

// }
class TeacherDao : public iTeacherDao
{
    public:
    virtual void teach() override
    {
        cout << "TeacherDao::teach()"<<endl;
    }
};
class TeacherDaoProxy : public iTeacherDao
{
    private:
    TeacherDao* pTD;
    public:
    TeacherDaoProxy() = default;
    TeacherDaoProxy(TeacherDao* p) : pTD(p) {}
    virtual void teach() override
    {
        cout << "Proxy: start~~"<<endl;
        pTD->teach();
        cout << "Proxy: end~~"<<endl;
    }
};
int main(int argc, char const *argv[])
{
    TeacherDao td;
    TeacherDaoProxy tdp(&td);
    tdp.teach();
    return 0;
}
