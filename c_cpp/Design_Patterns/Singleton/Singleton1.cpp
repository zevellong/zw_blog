#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <pthread.h>

using namespace std;
#define barrier() __asm__ __volatile__("" ::: "memory")
//内存屏障， 运行时，防止多cpu交互导致内存乱序访问
//保证对象的构造一定在barrier执行之前完成，因此pInstance被赋值时，对象总是完好的
//在x86_64架构中内核barrier的实现 #define barrier() __asm__ __volatile__("" ::: "memory")


// 饿汉，静态变量
class Singleton{
    private:
    Singleton() { }
    static Singleton* instance;
    static int a;

    public:
    int cc = 10;
    static Singleton* getInstance()
    {
        return instance;
    }
};
 
int Singleton::a = 1;
Singleton* Singleton::instance = new Singleton();

// 懒汉式，线程不安全
class Singleton_lh{
    private:
    Singleton_lh() { }
    static Singleton_lh* instance;

    public:
    void print() {cout << "懒汉式，线程不安全" << endl ;};
    static Singleton_lh* getInstance()
    {
        if (instance == nullptr)
            instance = new Singleton_lh();
        return instance;
    }
};
Singleton_lh* Singleton_lh::instance = nullptr;


// 懒汉，线程安全
class Singleton3
{
    private:
    Singleton3() { };
    static Singleton3* instance;
    public:
    static pthread_mutex_t mutex;
    static Singleton3* getInstance()
    {
        if (instance == nullptr)
        {
            pthread_mutex_lock(&mutex);
            if (instance == nullptr)
            {
                Singleton3* tmp = new Singleton3;

                barrier();
                instance = tmp;
            }
            pthread_mutex_unlock(&mutex);
        }
        return instance;
    }
};
Singleton3* Singleton3::instance = nullptr;
pthread_mutex_t Singleton3::mutex;


// 懒汉，双重检查
class Singleton4
{
    private:
    Singleton4() { };
    static volatile Singleton4* instance;
    public:
    static pthread_mutex_t mutex;
    static volatile Singleton4* getInstance()
    {
        if (instance == nullptr)
        {
            pthread_mutex_lock(&mutex);
                Singleton4* tmp = new Singleton4;
                barrier();
                instance = tmp;
            pthread_mutex_unlock(&mutex);
        }
        return instance;
    }
};
volatile Singleton4* Singleton4::instance = nullptr;
pthread_mutex_t Singleton4::mutex;


//c++ 11 standard
class Singleton5{
    private:
    Singleton5() {}
    public:
    static Singleton5& getInstance() 
    {
        static Singleton5 instance;
        return instance;
    }
};


int main(int argc, const char** argv) {
    Singleton* sp = Singleton::getInstance();
    Singleton* sp2 = Singleton::getInstance();
    cout << sp << endl;
    cout << sp2 << endl;

    Singleton_lh* lh1 = Singleton_lh::getInstance();
    Singleton_lh* lh2 = Singleton_lh::getInstance();
    cout << lh1 << endl << lh2 << endl;
    lh1->print();

    Singleton5 s5 = Singleton5::getInstance();
    return 0;
}

