

# 类型推导

- 模板推导
- auto
- decltype

## 条款一：理解模板类型推导

如果你不介意浏览少许伪代码，我们可以考虑像这样一个函数模板：

```cpp
template<typename T>
void f(ParamType param);
f(expr);                        //使用表达式调用f
```



`T`的类型推导不仅取决于`expr`的类型，也取决于`ParamType`的类型。这里有三种情况：

- `ParamType`是一个指针或引用，但不是通用引用

  - 保存const性
  - 忽略引用性

  ```cpp
  template<typename T>
  void f(T& param);               //param是一个引用
  ```

  

  我们声明这些变量，

  ``` cpp
  int x=27;                       //x是int
  const int cx=x;                 //cx是const int
  const int& rx=x;                //rx是指向作为const int的x的引用
  ```

  在不同的调用中，对`param`和`T`推导的类型会是这样：

  ```cpp
  f(x);                           //T是int，param的类型是int&
  f(cx);                          //T是const int，param的类型是const int&
  f(rx);                          //T是const int，param的类型是const int&
  ```

- `ParamType`一个通用引用

  - 如果`expr`是左值，`T`和`ParamType`都会被推导为左值引用。这非常不寻常，第一，这是模板类型推导中唯一一种`T`被推导为引用的情况。第二，虽然`ParamType`被声明为右值引用类型，但是最后推导的结果是左值引用。
  - 如果`expr`是右值，就使用正常的（也就是**情景一**）推导规则

```cpp
template<typename T>
void f(T&& param);              //param现在是一个通用引用类型
		
int x=27;                       //如之前一样
const int cx=x;                 //如之前一样
const int & rx=cx;              //如之前一样

f(x);                           //x是左值，所以T是int&，
                                //param类型也是int&

f(cx);                          //cx是左值，所以T是const int&，
                                //param类型也是const int&

f(rx);                          //rx是左值，所以T是const int&，
                                //param类型也是const int&

f(27);                          //27是右值，所以T是int，
                                //param类型就是int&&
```



- `ParamType`既不是指针也不是引用
  - 和之前一样，如果`expr`的类型是一个引用，忽略这个引用部分
  - 如果忽略`expr`的引用性（reference-ness）之后，`expr`是一个`const`，那就再忽略`const`。如果它是`volatile`，也忽略`volatile`

```cpp
int x=27;                       //如之前一样
const int cx=x;                 //如之前一样
const int & rx=cx;              //如之前一样

f(x);                           //T和param的类型都是int
f(cx);                          //T和param的类型都是int
f(rx);                          //T和param的类型都是int
```

- 数组实参

在模板类型推导时，数组名或者函数名实参会退化为指针，除非它们被用于初始化引用

```cpp
const char name[] = "J. P. Briggs";     //name的类型是const char[13]

const char * ptrToName = name;          //数组退化为指针


template<typename T>
void f(T& param);                       //传引用形参的模板
f(name);                                //传数组给f

//T被推导为了真正的数组！这个类型包括了数组的大小，在这个例子中T被推导为const char[13]，f的形参（对这个数组的引用）的类型则为const char (&)[13]
```

- 函数

```cpp
void someFunc(int, double);         //someFunc是一个函数，
                                    //类型是void(int, double)

template<typename T>
void f1(T param);                   //传值给f1

template<typename T>
void f2(T & param);                 //传引用给f2

f1(someFunc);                       //param被推导为指向函数的指针，
                                    //类型是void(*)(int, double)
f2(someFunc);                       //param被推导为指向函数的引用，
                                    //类型是void(&)(int, double)
```



## 条款二：理解`auto`类型推导

- `auto`类型推导和模板类型推导几乎一样的工作
- 例外:`auto`类型推导假定花括号初始化代表`std::initializer_list`，而模板类型推导不这样做

```cpp
int x1 = 27;
int x2(27);

// C++11由于也添加了用于支持统一初始化（uniform initialization）的语法
int x3 = { 27 };
int x4{ 27 };
```

```cpp
auto x1 = 27;                   //类型是int，值是27
auto x2(27);                    //同上
auto x3 = { 27 };               //类型是std::initializer_list<int>，
                                //值是{ 27 }
auto x4{ 27 };                  //同上
```

* 在C++14中`auto`允许出现在函数返回值或者*lambda*函数形参中，但是它的工作机制是模板类型推导那一套方案，而不是`auto`类型推导

```cpp
auto x = { 11, 23, 9 };         //x的类型是std::initializer_list<int>

template<typename T>            //带有与x的声明等价的
void f(T param);                //形参声明的模板

f({ 11, 23, 9 });               //错误！不能推导出T

//c++14
auto createInitList()
{
    return { 1, 2, 3 };         //错误！不能推导{ 1, 2, 3 }的类型
}
std::vector<int> v;
…
auto resetV = 
    [&v](const auto& newValue){ v = newValue; };        //C++14
…
resetV({ 1, 2, 3 });            //错误！不能推导{ 1, 2, 3 }的类型
```

## 条款三：理解`decltype`

- `decltype`是一个奇怪的东西。给它一个名字或者表达式`decltype`就会告诉你这个名字或者表达式的类型。
- 相比模板类型推导和`auto`类型推导（参见[Item1](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/1.DeducingTypes/item1.md)和[Item2](https://github.com/kelthuzadx/EffectiveModernCppChinese/blob/master/1.DeducingTypes/item2.md)），`decltype`只是简单的返回名字或者表达式的类型：

```cpp
const int i = 0;                //decltype(i)是const int

bool f(const Widget& w);        //decltype(w)是const Widget&
                                //decltype(f)是bool(const Widget&)

struct Point{
    int x,y;                    //decltype(Point::x)是int
};                              //decltype(Point::y)是int

Widget w;                       //decltype(w)是Widget

if (f(w))…                      //decltype(f(w))是bool

template<typename T>            //std::vector的简化版本
class vector{
public:
    …
    T& operator[](std::size_t index);
    …
};

vector<int> v;                  //decltype(v)是vector<int>
…
if (v[0] == 0)…                 //decltype(v[0])是int&

```

- 在C++11中，`decltype`最主要的用途就是用于声明函数模板，而这个函数返回类型依赖于形参类型

```cpp
//函数名称前面的auto不会做任何的类型推导工作。相反的，他只是暗示使用了C++11的尾置返回类型语法，即在函数形参列表后面使用一个”->“符号指出函数的返回类型，尾置返回类型的好处是我们可以在函数返回类型中使用函数形参相关的信息。
template<typename Container, typename Index>    //可以工作，
auto authAndAccess(Container& c, Index i)       //但是需要改良
    ->decltype(c[i])
{
    authenticateUser();
    return c[i];
}

//operator[]对于大多数T类型的容器会返回一个T&,但是Item1解释了在模板类型推导期间，表达式的引用性会被忽略,
template<typename Container, typename Index>    //C++14版本，
auto authAndAccess(Container& c, Index i)       //不那么正确
{
    authenticateUser();
    return c[i];                                //从c[i]中推导返回类型
}

//函数返回的那个int是一个右值，上面的代码尝试把10赋值给右值int，C++11禁止这样做，所以代码无法编译。
std::deque<int> d;
authAndAccess(d, 5) = 10;      


//使用decltype(auto)，只支持左值，不支持右值
template<typename Container, typename Index>    //C++14版本，
decltype(auto)                                  //可以工作，
authAndAccess(Container& c, Index i)            //但是还需要
{                                               //改良
    authenticateUser();
    return c[i];
}

//std::forward实现通用引用
template<typename Container, typename Index>    //最终的C++14版本
decltype(auto)
authAndAccess(Container&& c, Index i)
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}

template<typename Container, typename Index>    //最终的C++11版本
auto
authAndAccess(Container&& c, Index i)
->decltype(std::forward<Container>(c)[i])
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}
```





## 条款四：学会查看类型推导结果

- 查看ide给出的结果：鼠标
- 运行时打印：typeid`和`std::type_info::name
  - ”`PK`“表示”pointer to ~~`konst`~~ `const`“
- 使用boost：**Boost.TypeIndex**