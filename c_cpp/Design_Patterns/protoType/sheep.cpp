#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class point2D{
    public:
        point2D(double xx, double yy) : x(xx), y(yy) {}
        void print()
        {
            cout << "point[x:" << x << ",y:"<<y << "]";
        }
    private:
        double x, y;
};
class BaseShape
{
    public:
    virtual ~BaseShape() {}
    virtual std::unique_ptr<BaseShape> deepClone() = 0;
    virtual void print() { cout << "A base shape" << endl;}
};

class triangle : public BaseShape{
    public:
    triangle(point2D aa, point2D bb, point2D cc) 
        : a(aa), b(bb), c(cc) { }
    std::unique_ptr<BaseShape> deepClone() override
    {
        return  std::make_unique<triangle>(*this);
    }
    private:
    point2D a,b,c;
};
class circle : public BaseShape{
    public:
    circle(point2D oo, double rr) 
        : o(oo), r(rr) { }

    std::unique_ptr<BaseShape> deepClone() override
    {
        return  std::make_unique<circle>(*this);
    }
    void print() override
    {
        cout << "circle:: ";
        o.print();
        cout << "\tr:" << r;
        cout << endl;
    }
    private:
    point2D o;
    double r;
};
class shapeFactory{
    public:
    shapeFactory()
    {
        triangle tri_sml(point2D(1,1), point2D(2,2), point2D(3,3));
        triangle tri_big(point2D(10,10), point2D(20,20), point2D(30,30));
        circle cir_sml(point2D(1,1), 1);
        circle cir_big(point2D(1,1), 10);

        shapeMap["tri_sml"] = std::make_unique<triangle>(tri_sml);
        shapeMap["tri_big"] = std::make_unique<triangle>(tri_big);
        shapeMap["cir_sml"] = std::make_unique<circle>(cir_sml);
        shapeMap["cir_big"] = std::make_unique<circle>(cir_big);
    }
    std::unique_ptr<BaseShape> getShape(string style)
    {
        return shapeMap[style]->deepClone();
    }
    private:
    std::unordered_map<string, std::unique_ptr<BaseShape>> shapeMap;
};
class fac2{
    public:
    vector<BaseShape*> shapeVec;
    fac2()
    {
        circle c1(point2D(1,1), 10);
        for (int i = 1; i < 10; i++)
            shapeVec.push_back(new circle(c1));
    }

};
void swap(int& a, int &b)
{
    cout << "use zw's swap()" << endl;
    std::swap(a,b);
}
int main(int argc, const char** argv) {

    // shapeFactory sf;
    // for (int i = 0; i < 5; i++)
    // {
    //     auto x = reinterpret_cast<circle*>(sf.getShape("cir_big").release());
    //     x->print();
    //     cout << "pointer x:"<<x << endl;
        
    // }
    fac2 f;
    cout << sizeof(double) <<  endl;
    cout << sizeof(circle) << " " << sizeof(BaseShape) << endl;
    for (auto bg = f.shapeVec.begin(); bg != f.shapeVec.end(); bg++)
        cout << *bg << endl;
    return 0;
}