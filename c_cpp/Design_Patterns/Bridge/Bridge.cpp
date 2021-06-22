#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::string;
using std::endl;

class Brand
{
    public:
    virtual void call() = 0;
    virtual void open() {}
    virtual void close() {}
    private:

};
void Brand::call()
{

}
class Phone
{
private:
    Brand* pbrd;
protected:
    void popen()
    {
        pbrd->open();
    }
    void pclose()
    {
        pbrd->close();
    }
    void pcall()
    {
        pbrd->call();
    }
public:
    Phone(Brand* pb) : pbrd(pb) {}
    virtual ~Phone() = 0;
    virtual void open() {}
    virtual void close() {}
    virtual void call() {}

};
Phone::~Phone()
{
    cout << "calling ~Phone()" << endl;
    if (pbrd != nullptr)
        delete pbrd;
}

class FoldedPhone : public Phone
{
    public:
    FoldedPhone(Brand* pb) : Phone(pb) {}
    void prt()
    {
        cout << "FoldedPhone";
    }
    void close()
    {
        prt();
        Phone::pclose();
    }
    void open()
    {
        prt();
        Phone::popen();
    }
    void call()
    {
        prt();
        Phone::pcall();
    }
};
class Mi : public Brand
{
    private:
    string info = "Mi";
    public:
    void open() override
    {
        cout << info << ":open phone ~" << endl;
    }
     void close() override
    {
        cout << info << ":close phone ~" << endl;
    }
     void call() override
    {
        cout << info << ":calling phone ~" << endl;
    }
};
class Vivo : public Brand
{
    private:
    string info = "Vivo";
    public:
    void open() override
    {
        cout << info << ":open phone ~" << endl;
    }
     void close() override
    {
        cout << info << ":close phone ~" << endl;
    }
     void call() override
    {
        cout << info << ":calling phone ~" << endl;
    }
};
class UprightPhone : public Phone
{
    public:
    UprightPhone(Brand* pb) : Phone(pb) {}
    void prt()
    {
        cout << "UprightPhone";
    }
    void close()
    {
        prt();
        Phone::pclose();
    }
    void open()
    {
        prt();
        Phone::popen();
    }
    void call()
    {
        prt();
        Phone::pcall();
    }
};
int main(int argc, char const *argv[])
{
    Brand* pb1 = new Mi();
    Phone* miFold = new FoldedPhone(pb1);
    miFold->open();
    miFold->call();
    miFold->close();

    delete miFold;

    cout << "--------------" << endl;

    Brand* pb2 = new Vivo();
    Phone* pvivo = new UprightPhone(pb2);
    pvivo->open();
    pvivo->close();
    pvivo->call();
    delete pvivo;
    return 0;
}
