#include <iostream>
#include <string>
#include <memory>
using std::shared_ptr;
class Thing : public std::enable_shared_from_this<Thing>
{
public:
    void foo1();
    void foo2() { std::cout << " foo2()" <<std::endl;}
    ~Thing()
    {
        std::cout << "~thing()" <<std::endl;
    }
};
void trans(shared_ptr<Thing> t)
{
    std::cout << "trans()" <<std::endl;
    t->foo2();
}

void Thing::foo1()
{
    //shared_ptr<Thing> sp_for_this(this);
     shared_ptr<Thing> sp_for_this = shared_ptr<Thing>(this);
    trans(sp_for_this);
}
using std::string;
int main(int argc, char const *argv[])
{
    // shared_ptr<Thing> t1(new Thing);
    // t1->foo1();
    // std::cout << "sadsadsa" <<std::endl;
    
    shared_ptr<string> sps = shared_ptr<string>( new string("hellp"));
    std::cout << *sps <<std::endl;
    return 0;
}
