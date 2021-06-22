#include <iostream>
#include <string>
#include <list>
#include <memory>
using std::shared_ptr;
using std::cout;
using std::endl;
using std::string;
using std::list;

class Memento
{
public:
    int atk, def, vit;
    Memento() = default;
    Memento(int a, int d, int v) : atk(a),def(d),vit(v) {}
};
class Originator
{
public:
    Originator(int a, int d, int v) : atk(a),def(d),vit(v) {}
    void setState(int a, int d, int v)
    {
        atk  = a; def = d; vit = v;
    }
    void setState(Memento* m)
    {
        setState(m->atk, m->def, m->vit);
    }
    shared_ptr<Memento> ctMemento()
    {
        return std::make_shared<Memento>(atk, def, vit);
    }
    void restore(Memento* m)
    {
        setState(m);
    }
    void display()
    {
        cout << "atk: " << atk << "\tdef: " << def
             << "\tvit:" << vit << endl;
    }
private:
    int atk, def, vit;
};
class Caretaker
{
private:
    list<shared_ptr<Memento>> lst;
public:
    void addMem(shared_ptr<Memento> spm)
    {
        lst.push_back(spm);
    }
    void rmMem(shared_ptr<Memento> spm)
    {
        lst.remove(spm);
    }
    shared_ptr<Memento> getMem(int x)
    {
        auto bg = lst.begin(), ed = lst.end();
        auto ret = *bg;
        for (int i = 0; i < x+1; i++)
        {
            if (bg == ed)
                throw std::out_of_range("List out range");
            ret = *bg;
            bg++;
            
        }
        return ret;
    }
};
int main(int argc, char const *argv[])
{
    Originator o1(10, 10, 9);
    Caretaker busket;
    o1.display();
    auto x = o1.ctMemento();
    busket.addMem(x);
    o1.setState(80, 90, 100);
    o1.display();
    auto y= o1.ctMemento();
    busket.addMem(y);
    o1.setState(8, 9, 100);
    o1.display();
    
    o1.restore(busket.getMem(2).get());
    o1.display();
    return 0;
}
