# 学习c++ primer 5th edition

[Primer c++ 第5版.pdf](..\..\pdf\c_cpp\Primer c++ 第5版.pdf) 

 [codes](..\..\C_C++_Code\新建文件夹\) 



## ch2

### 2.1 类型转换

* bool <- 其他 , 0为false，其他值为true
* bool-> 其他，false 0，true 1
* float -> int，保留整数
* int -> float，小数部分为0
* 无符号数超过取值，取模
* 带符号数超过取值，编译器行为不确定

warn: 初始化不是赋值，初始化是创建时赋予一个初始值；赋值是把当前对象的值擦去再用一个新值代替

### 2.2 变量

* 列表初始化：如果存在丢数据，会报警告

### 2.3 复合类型

* char* const q & const char* p (顶层const)

```c++
Person p1("Fred", 200);
const Person* p = &p1;//对象const
person const* p = &p1;//对象const
person *const p = &p1;//指针const
```

* 识别技巧，从右往左读，p先和左边的符号结合，即*p or const p
  * *p指对象，对象const
  * const p 指指针，指针const

* constexpr和常量表达式
* 初始化空指针，`int *p1=nullptr`区别于`int *p1=NULL`

### 2.5 类的别名

* typedef
* decltype(fun())
  * 返回变量的类型
  * decltype((i))返回的为引用，双层括号必返回引用
* auto
  * 会忽略const，如需要const，应显示的定义`const auto`



## 3 string & vector

### 3.1 string

string 初始化

```c++
    string s1;
    string s2(s1);
    string s3("value");
    string s4(50, 'c');
```

string 的操作

| 操作             |                      |
| ---------------- | -------------------- |
| os << s, is >> s | 输入，输出           |
| getline(is, s)   | 读取一行到s          |
| s.empty()        | 判断空               |
| s.size()         | size                 |
| s[n]             | 索引到s的n个字符     |
| s1+s2            | 字符串连接           |
| s1=s2            | 赋值                 |
| s1==s2           | 判断相等，大小写敏感 |
| s1!=s2           | 不相等               |
| < , <=, >, >=    | 判断大于，小于       |

###  vector

```c++
#include <iostream>
#include <vector>

//初始化
	vector<string> v1;
    vector<string> v2(v1);
    vector<string> v3(10, "hello");
    vector<string> v4(10);
    vector<string> v5 {"hello", "world", "cpp"};
//添加元素
	v1.push_back(3);
	

```

* 在for each循环中，不要使用`push_back()`
* vector的操作

| vector              | 操作                |
| ------------------- | ------------------- |
| v.empty()           |                     |
| v.size()            |                     |
| v.push_back         |                     |
| v[n]                | 返回第n个元素的引用 |
| v1 = v2             |                     |
| v1 = {a, b, c, ...} | 列表初始化          |
| v1 == v2            |                     |
| v1 != v2            |                     |
| <, >, <=, >=        |                     |

* `vector<int>::size_type` 而不是 `vector::size_type` ，
* 不能用下标的形式添加元素

### 3.3 迭代器

* 迭代器运算符

| 迭代器    | 作用                         |
| --------- | ---------------------------- |
| *iter     | 返回迭代器iter指向元素的引用 |
| iter->num | 获取num                      |
| _         |                              |
| --iter    |                              |
| ==        |                              |
| !=        |                              |

* 迭代器的失效，一些有副作用的操作，使得迭代器失效
* 在C++中迭代器使用!=，而不是<,>,因为大多数类库都实现了!=
* 迭代器的类型

```c++
vector<int>::iterator it;
string::iterator it2;
//const 只能读，不能写
vector<int>::const_iterator it3;
string::const_iterator it4;

```

* begin，end，会识别是不是const
* (*it).empty() 而不是 *it.empty(),或者it->empty()
* iterator::difference_type，带符号整数

## 4 表达式

| 结合律        | 功能               | 用法            |
| ------------- | ------------------ | --------------- |
| 左 ::         | 全局作用域         | ::name          |
| 左 ::         | 类作用域           | class::name     |
| 左 ::         | 命名空间作用域     | namespace::name |
|               |                    |                 |
| 左 .          | 成员               |                 |
| 左 ->         | 成员               |                 |
| 左 []         | 下标               |                 |
| 左 ()         | 函数调用           |                 |
| 左 ()         | 类型构造           | type(expr_list) |
|               |                    |                 |
| ++            |                    |                 |
| --            |                    |                 |
| typeid        |                    |                 |
| typeid        |                    |                 |
| explicit cast |                    |                 |
| 逻辑运算      | != < >             |                 |
| ~             | 位取反             |                 |
| -             | 一元负号           |                 |
| +             | 一元正号           |                 |
| *             | 解引用             |                 |
| &             | 取地址             |                 |
| ()            | 类型转换           |                 |
| sizeof        |                    |                 |
| new           |                    |                 |
| delete        |                    |                 |
| noexcept      |                    |                 |
|               |                    |                 |
| ->*           | 指向成员选择的指针 |                 |
| .*            | 指向成员选择的指针 |                 |
|               |                    |                 |
| + -           |                    |                 |
|               |                    |                 |
| << >>         | 位移位             |                 |
|               |                    |                 |
|               |                    |                 |

* 太多了，见cpp primer， 147



## 5 语句

* 不能在while ()的条件定义,循环条件中的定义的变量，在循环体中不能直接引用的

```c++
	//[Error] expected initializer before '!=' token
	while (auto iter != str1.end()) 
	{
		*iter = toupper(*iter);
	}
```

* 悬垂else，else总是找在他上方离他最近的if

* switch内部定义变量

```c++
	
	switch(a)
	{
		case 1:
			string file3;//控制流跳过了一个隐式的初始化
			string file_name = "file1";//控制流跳过了一个显式的初始化
			int i;//正确，没有初始化
			break;
		case 2:
			i = 30;
			break; 
	}

	//可以定义在块内
	
	switch(a)
	{
		case 1:
            {
                string str("hello");
            }
	}
```

* case语句不要使用变量

```c++
	unsigned i = 512, j = 1024, k = 4096;
	unsigned bufsize;
	unsigned swt = 512;
	switch (swt){
		case i:
			bufsize = i * sizeof(int);
		case j:
			bufsize = j * sizeof(int);
		case k:
			bufsize = k * sizeof(int);
	}
//[Error] the value of 'i' is not usable in a constant expression
```

* for循环的条件为空语句，这默认为true

## 6 函数

* 函数是一个命名的代码块

* const 形参和实参

```c++
void fcn(const int i)//形参的顶层const会被忽略
void fcn(int i)//error:重复定义
```

* 尽量使用常量引用

```c++
void print(string &sr)
{
	cout << sr << endl;
}

print("hello"); //hello子字符串字面值，应该为const string &
//[Error] invalid initialization of non-const reference of type 
//'std::string& {aka std::basic_string<char>&}' from an rvalue of type //'const char*'
```

* 更加隐讳的错误

```c++
string::size_type print(string &sr,char c)
{
	
}
bool is_sentence(const string& s)
{
	string::size_type ctr = 0;
	return find_char(s, '.') == s.size();
    //s的类型与size_type()定义的类型不匹配
}
```

* 数组三种遍历方法：

  * 标记：C的字符串最后有一个空字符
  * 标准库规范：begin和end，end指向最后一个元素的下一块
  * 显式传递数组大小：`void print(const int a[], size_t size)`
* 数组引用形参

```c++
void print(int (&arr)[10])
{
	for (auto ele : arr)
		cout << ele << " ";
	cout << endl;
}
//切记括号不能少
f(int &arr[10])//一个含有10个int 引用的数组
f(int (&arr)[10]) //数组的引用
    
//传递二维数组
void print(int (*matrix)[10]);
```

* 可变形参 `initializar_list<T> lst;`

```c++
void lst_msg(const string &send_name,initializer_list<string> lst)
{	
    cout << "To " << send_name << ":"<< endl;
	for (auto beg=lst.begin(); beg != lst.end() ; ++beg)
	{
		cout << *beg << " ";
	}
}

lst_msg({"hello", "world"});
```

* 列表初始化返回值

```c++
vector<string> rtn_hello_str()
{
	return {"hello", "world"};
}
```

* 返回函数指针的函数

```c++
int (*func(int i))[10];
//func(int i)表示函数
//(*func(int i)) 表示对函数的结果解引用
//(*func(int i))[10] 表示func返回的是一个大小为10的数组

//使用尾置返回类型 -std=C++11
//更直观
auto fun2(int i) -> int (*)[10]
{
	
}

//使用decltype
int odd[] = {1, 2, 3, 4, 5};
decltype(odd) *fun3(int i)
{
}
//decltype不负责把数组类型转换为指针，要加一个*
```

* 函数重载，函数名相同，参数不相同

```c++
//错误，不能只有返回类型不同
int f1(int i);
bool f1(int i);


Record lookup(Phone);
Record lookup(const Phone);//重复声明了上一行

Record lookup(Phone* );
Record lookup(Phone* const);//重复声明了上一行

Record lookup(Account& );
Record lookup(const Account&);//新函数

Record lookup(Account* );
Record lookup(const Account* );//新函数
```



* 在局部块声明函数会隐藏包含此名的函数，不是一个好的选择
* 内联函数和constexpr函数放在头文件中



* 函数匹配
  * 最佳匹配
  * 无匹配
  * 二义性

```c++
f(int, int);
f(double, double);

//call f
f(40, 3.14);//二义性
//f(int, int)精确匹配, f(double, double)也精确匹配，编译器拒绝

```

* 参数转换等级(上方的等级高)
  *  精确匹配
    * 完全相同
    * 数组类型和函数类型转换为指针类型
    * 顶层const
  * const转换的匹配
  * 类型提升，char -> int
  * 算术类型转换或者指针类型转换
  * 类类型转换

## 7 类

* class 与 struct唯一区别就是默认访问权限
* 友元
  * 一般来说，最好在类的开始或结束处集中声明友元
* 声明和定义的地方都可以说明`inline`，但是最好只在类的外部定义的地方说明`inline`，比较好理解

```c++
struct X{
	friend void f(){};
    x() {f();}//错误
    void g();
    void h();
}
void X::g() { return f();}//错误
void f();
void X::h() { return f();}//正确
```

* 友元的声明影响访问权限，不是普通意义的声明
* 名字查找
  * 普通情况
    * 首先在当前块中
    * 外层作用域
    * 还没有找到，报错
  * 类成员函数
    * 首先找成员声明
    * 直到类全部可见才编译函数体

* 类的初始化顺序，最好与成员声明的顺序保持一致；并且尽量避免用其他的成员初始化其他成员
* 委托构造函数

* 使用默认的构造函数

```c++
Sales_data obj(); //定义了一个函数
Sales_data obj2; //一个对象，调用默认构造器
```

* 隐式的类型转换
  * 只允许一次类类型转换

```c++
Sales_data& Sales_data::combine (const Sales_data&);

Sales_data item;
//"9-999-99999" -> string -> Sales_data
item.combine("9-999-99999");//错误，只能转换一次
item.combine(string("9-999-99999"));//显示转为string，隐式转sales
item.combine(Sales_data("9-999-99999"));//隐式转为string，显式转sales
```

* 在构造器加入 `explicit` 可以拟制隐式转换

```
Sales_data item1(null_book);//正确直接初始化
Sales_data item2 = null_book;//错误，explicit禁止拷贝构造
```

* 标准库中的explicit

```
//接受一个单参数的const char* string
//vector单参数，圆括号
```

* static
  * 静态成员函数不能使用this，也不能在后面加const
  * 可以用类名访问静态成员，也可以用对象名
  * 可以在类的内部和外部定义static函数。在外部定义时，不要重复定义static，这个关键字只出现在类的内部

## 8 I/O

* 不能拷贝流对象进行赋值

| strm::iostate |            |
| ------------- | ---------- |
| strm::badbit  | 流崩溃     |
| strm::failbit | IO操作失败 |
| strm::eofbit  | 文件结束   |
| strm::godbit  | 流未出错   |

* unitbuf操作符：在每次操作后都刷新缓冲区

```c++
cout << unitbuf;
cout << nounitbuf;//回到正常模式
```

* 文件流

| mode   |                          |
| ------ | ------------------------ |
| in     | 读                       |
| out    | 写                       |
| app    | append，写操作定位到末尾 |
| ate    | 打开后立即定位到末尾     |
| trunc  | 截断文件                 |
| binary | 二进制IO                 |

* ofsteam，fstream，可设定写
* ifsteam，fstream，可设定读
* out设定，才能设定trunc或者app
* 默认情况out，trunc模式，会舍弃文件的原有内容，要追加内容，显示的加上app



* string流
  * istringstream
  * ostringstream

## 9 顺序容器

* `vector` 可变大小的数组
* `deque` 双端队列
* `list` 双向链表
* `forward_list` 单向链表
* `array` 固定大小的数组
* `string`



* 选择标准：一般用vector
* 小元素和对空间要求高不要用list
* vector和deque支持随机访问



| 类型别名        |                            |
| --------------- | -------------------------- |
| iterator        | 迭代器                     |
| const_iterator  | 只读迭代器                 |
| size_type       | 无符号整数，容器的最大大小 |
| difference_type | 带符号整数，容器之间距离   |
| value_type      | 元素类型                   |
| reference       | 引用                       |
| const_reference | 只读引用                   |

| 构造函数        |                      |
| --------------- | -------------------- |
| C c             | 默认构造器           |
| C c1(c2);       | 拷贝构造             |
| c c(b,e)        | 拷贝b,e之间的元素到c |
| C c{a,b,c,....} | 列表初始化           |

| 赋值与swap         |          |
| ------------------ | -------- |
| c1 = c2            | 赋值     |
| c1 = {a, b, c,...} | 列表替换 |
| a.swap(b)          |          |
| swap(a,b)          |          |

| 大小         |      |
| ------------ | ---- |
| c.size()     |      |
| c.max_size() |      |
| c.empty()    |      |

| 添加和删除      |      |
| --------------- | ---- |
| c.insert()      |      |
| c.emplace(args) |      |
| c.erase         |      |
| c.clear         |      |

| 关系运算符 |      |
| ---------- | ---- |
| ==， !=    |      |
| <,<=,>=,>  |      |

* 迭代器范围[begin,end),是一个左闭合区间，我们可以得到一些假定：
  * 如果begin等于end，那么区间为空
  * 如果不为空，那么至少有一个元素
  * 通过有限次递增，可以使得begin==end

* array具有固定大小,声明时也需要指定其大小

```c++
array<int, 42>
```

* 内置数组不能拷贝，array可以拷贝构造

* assign的三种重载
  * s.assign(bengin,end) 迭代器之间
  * s.assign(n,t) n个t
  * s.assign({3,2,1}) 替换为初始化列表

* 添加元素，insert，push_back,push_front,emplace



* insert返回值返回当前位置的迭代器，用insert的返回值可以在当前位置反复插入元素
* emplace调用构造函数

* 访问元素返回的是引用

| 访问元素  |                                     |
| --------- | ----------------------------------- |
| c.back()  | 返回尾元素的引用，c为空，行为未定义 |
| c.front() |                                     |
| c[n]      | 越界无out_of_range异常              |
| c.at(n)   | 若越界，抛出out_of_range异常        |

* 删除元素

| 函数        |                                           |
| ----------- | ----------------------------------------- |
| pop_back()  | 若为空，行为未定义；                      |
| pop_front() |                                           |
| erase(p)    | 删除迭代器p指向的元素，返回被删后的迭代器 |
| erase(b,e)  | 可用于删除多个元素                        |
| clear()     |                                           |

* forward_list有自己版本的erase
* erase若删除end迭代器，返回尾后迭代器，若删除尾后迭代器，行为未定义

### forward_list

* 未定义insert、erase、emplace
* 定义了begin、end、before_begin(返回首前迭代器)
* 定义了insert_arfter,erase_after,emplace_after
* 添加和删除元素时，多需要关注两个迭代器，当前处理的和前驱



* resize函数
  * resize(n)
  * resize(n,t)
  * array不支持
  * 如果增大将会初始化，减小会删除后面的元素
* 编写改变容器的循环

```c++
while (begin != v.end())//用这个代替下一行
end = v.end(); while (begin != end//不要使用这个
```

* vector 的增长
  * size(),capacity()
  * reserve(n)分配至少n
  * shrink_to_fit()回收一部分

### string

* 其他的构造函数

| 函数                   |                                  |
| ---------------------- | -------------------------------- |
| string s(cp, n)        | cp是c风格字符串，拷贝cp前n个字符 |
| string s(s2, pos2)     | 从下标尾pos2开始拷贝             |
| string s(s2,pos2,len2) | 从下标尾pos2开始拷贝len2个元素   |

* substr

  * s.substr(pos,n)

  * 返回子字符串

* 假定你希望每次读取一个字符存入一个string中，而且知道最少需要读取100个字符，应该如何提高程序的性能？

  * 大致的思路就是每次写一个字符，string都会去扩充内存，还不如一次就让内存扩大一点

* append replace

| 函数                  |                               |
| --------------------- | ----------------------------- |
| s.insert(pos,args)    |                               |
| s.erase(pos,len)      |                               |
| s.assign(args)        |                               |
| s.replace(range,args) | range是一对迭代器或者一组下标 |
| s.append(args)        |                               |

* find

| 函数                    | args            |
| ----------------------- | --------------- |
| find()                  | c，pos          |
| cfind()                 | s2,pos          |
| find_first_of(args)     | cp,pos          |
| find_last_of(args)      | cp,pos,n        |
| find_first_not_of(args) | cp是c风格字符串 |
| find_last_not_of(args)  | c是字符         |

* compare

| args               |      |
| ------------------ | ---- |
| s2                 |      |
| pos1,n1,s2         |      |
| pos1,n1,s2,pos2,n2 |      |
| cp                 |      |
| pos1,n1,cp         |      |
| pos1,n1,cp,n2      |      |

* 数值转换

| 函数                         |      |
| ---------------------------- | ---- |
| to_string()                  |      |
| stoi,stol,stoul,stoull,stoll |      |
| stof,stod,stold              |      |



## 10 泛型算法

* 初识泛型算法

```c++
find(begin, end, val);
```

* 迭代器让算法不依赖于容器，返回迭代器，可以通过返回的是否是尾后迭代器判断find成功还是失败；
* 算法依赖元素的类型，find使用==，也有其他的可能用><

* 只读算法：只读取输入的内容，不改变元素

```c++
string sum = accumulate(v.begin(), v.end(), string(""));
string sum = accumulate(v.begin(), v.end(), "");//错误
```

* ""为const char * 类型，没有+操作；string则有；accumulate第三个参数是求和的起点

* equal(v1.begin(), v1.end(), v2.begin());
  * v2只接受begin，默认v2等于或长于v1



### 泛型算法结构

| 迭代器         |                                |
| -------------- | ------------------------------ |
| 输入迭代器     | 只读，不写；单遍扫描，只能递增 |
| 输出迭代器     | 写，不读；单，递增             |
| 前向迭代器     | 读写， 多，递增                |
| 双向迭代器     | 读写，多，可增可减             |
| 随机访问迭代器 | 读写，多，支持全部迭代器操作   |

* 算法的形参

```c++
alg(beg,end, other args);
alg(beg,end,dest, other args);
alg(beg,end, beg2,other args);
alg(beg,end, beg2, end2, other args);
```

* 命名规范

```c++
//反向操作
reverse(beg, end);
reverse_copy(beg, end, dest);
//删除操作
remove_if(beg ,end, arg);
remove_copy_if();
```

### 迭代器

* 插入迭代器
  * back_insertor,调用push_back
  * front_insertor,调用push_front
  * insertor(lst, lst.begin()); 
* istream_iterator

```c++
//构造vector
istream_iterator<int> in_iter(cin), eof;
while (in_iter != eof)
{
    vec.push_back(*in_iter++);
}
//or
istream_iterator<int> in_iter(cin), eof;
vector<int> vec(in_iter, eof);

//用算法操作流迭代器
cout << accumulate(in_iter, eof, 0) << endl;
```

* 流迭代器允许使用懒惰赋值，在你第一次调用时，保证已经读取数据

* ostream_iterator

```c++
ostream_iterator<int> out_iter(cout, " ");
for (auto e : vec)
    *out_iter++ = e;//写入到cout
cout << endl;

//也可以忽略* ++,也是同样的效果
for (auto e : vec)
    out_iter = e;//写入到cout
cout << endl;

//使用copy写元素
copy(v.begin(), v.end(), out_iter);
```

* 反向迭代器

```c++
//用反向迭代器找到最后一个单词
//line = "first, mid, last"
auto rcomma = find(line.crbegin(), line.crend(), ',');
cout << string(line.crbegin(), rcomma) << endl;//将打印tsal

//使用reverse_iterator的base成员完成正向转换
cout << string(rcomma.base(), line.end()) << endl;//打印last
```

* 反向迭代器base生成的是相邻的位置，由于左开右闭合的性质

### 常见泛型算法

* fill

```c++
//v需要有足够空间可写
fill(v.begin(),v.end(), 10);
fill_n(v.begin(), v.size(), 10);
```

* copy

```c++
auto ret = copy(beg, end, beg2);//ret为beg2拷贝之后的迭代器
```

* replace

```c++
replace(beg, end, 10);//10替换
replace(beg, end, 0, 10);//0改为10
//原容器不变，替换后的结果写入dest
replace_copy(beg, end, dest, 0, 42);
```

* sort, unique，sort排序，unique消除相邻的相同元素

```c++
sort(wd.begin(), wd.end());//字典序排序
auto uni = unique(wd.begin(), wd.end());
wd.erase(uni, wd.end());
```

* for_each

```c++
//打印v的元素
for_each(v.begin(), ve.end(),
		[](const int i)
		{cout << i << " ";});
```



### lambda

```c++
//sort还接受第三个参数，用来定制排序
bool isShortor(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}
sort(wd.begin(), wd.end(), isShorter);
```

* lambda

```c++
[捕获列表](参数)->返回类型{语句};
```

* 可以忽略参数和返回类型，返回类型根据最后一句return判断，如果最后一句不是return，则为void

```c++
//lambda版本的按字符个数sort
sort(wd.begin(), wd.end(),
	[](const string &s1, const string &s2)
	{return s1.size() < s2.size();});
```

* 捕获列表

```c++
string::size_type sz = 6;
//找到长度大于6的首个单词
find_if(vc.begin(), vs.end(),
       [sz](const string &s)
        {return s.size() >= 6;});
```

* 值捕获和引用捕获

```c++
int i = 10;
auto f1 = [i] {return i};
auto f2 = [&i] {return i};
```

* 流对象不能拷贝，使用引用
* 隐式捕获

```c++
int i,j;
auto f = [=] {return i+j;};//值捕获
auto f2 = [&] {return i+j};//引用捕获

auto f3 = [&,i]{return i+j};//i为值捕获，j为引用捕获
auto f4 = [i,=]{return i+j};//错误，隐式捕获在前面
```

* 可变lambda

```c++
size_t v1 = 42;
auto f = [v1] ()mutable {return ++v1; };
v1 = 0;
auto j = f();//j=43,不加mutable则不会改变，
```

* 返回类型

```c++
//transform将容器替换为可调用对象返回的值
transform(vi.begin(), vi.end(),
			[](int i) 
			{if (i < 0) return -i;else return i;});
//错误，不能推测返回类型

//指定返回类型
transform(vi.begin(), vi.end(),
			[](int i) ->int 
			{if (i < 0) return -i;else return i;});

```

* bind
  * functional头文件

```c++
using std::placeholders::_1;
//将lambda改写函数，check_size
bool check_size(const string &s1, string::size_type sz)
{
    return s1.size() >= sz;
}

auto wc = find_if(v.begin(), v.end(),
                 bind(check_size, _1, 6));
```

* 重排参数

```c++
sort(v.begin(), v.end(), isShortor);按单词长度排序
sort(v.begin(), v.end(), bind(), bind(isShortor,_2,_1));//反向
```

* list,forword_list,vector等有特定版本的容器算法



## 11 关联容器

* map,set,multimap,multiset
* unordered_map,unordered_set,unordered_multimap,unordered_multiset

* 构造

```c++
map<string, size_t> word_cont;
set<string> st;

map<string, size_t> word_cont = {{"str1", 10}
                                 {"str2", 20}};
```

* 关键字：map第一个为关键字
* 严格弱序：元素之间可比较，小于等于

* pair

```c++
pair<T1, T2> p;
pair<T1, T2> p(v1, v2);
pair<T1, T2> p = {v1, v2};

make_pair(v1, v2);
p.fisrt
p.second
#符号运算
< > >= <=
p1 == p2
p1 != p2
```



* 关联容器操作

| 类型别名    |                                 |
| ----------- | ------------------------------- |
| key_type    | 关键字类型                      |
| mapped_type | 关键字关联的类型；map           |
| value_type  | set:key_type 相同；map:返回pair |

* 迭代器begin，end
* map迭代器返回的是pair的引用，但是pair的first不能改变
* set迭代器是const的



* insert

```c++
m.insert({word, 1});
m.insert(make_pair(word, 1));
m.insert(pair<string, int> (word, 1));
m.insert(map<string, int>::value_type (word, 1) );

m.insert(b, e);
m.insert(il); //列表
```

* insert返回pair,fisrt为插入后的迭代器，second为bool，插入成功为true
* multimap,multiset, 插入后必成功，返回迭代器



* erase,返回0，1，0为删除的元素不在容器，如果有多个元素，则删除多个元素

* map的下标，下标操作是一种副作用操作，先搜索关键字，元素存在，则赋值，不存在则插入
* 下标操作返回值为mapped_type



* 访问元素,find不产生副作用

```c++
set = {0,1,2,3,4,5,6,7,8,9}
set.find(1);//return 1的迭代器
set.find(11);//尾后迭代器
set.count(1);//1
set.count(11);//0

```

* multi迭代器
  * lower_bound() ----> upper_bound()
  * equal_range.fisrt -----> equal_range.second

* 无序的关联容器



## 12 动态内存

### 动态内存和智能指针

* new和delete，new []和delete[]

* shard_ptr,允许多个指针指向一个对象
* unique_ptr，独占一个对象
* weak_ptr，伴随shared



* shared_ptr

| share和unique都支持的操作 | 作用                      |
| ------------------------- | ------------------------- |
| _ptr<T> sp                | 空指针，可指向类型T的对象 |
| p                         | 条件判断                  |
| *p                        | 解引用                    |
| p->mem                    |                           |
| p.get()                   | 返回p保存的指针           |
| swap(p, q)                |                           |
| p.swap(q)                 |                           |

| shared独有操作       | 作用                                      |
| -------------------- | ----------------------------------------- |
| make_shared<T>(args) | 返回一个shared_ptr,指向动态内存分配的对象 |
| shared_ptr<T> p(q)   | 拷贝，增加q计数                           |
| p=q                  | q加计数，p减                              |
| p.unique()           | p.use_count()=1,返回true；否则返回false   |
| p.use_count()        | 返回计数，可能很慢                        |

* 拷贝和赋值都会增加shared计数，赋新值或离开作用域会减少计数，计数等于0，指向的对象被释放
* 被释放是通过析构函数
* 通常使用动态内存的原因：
  * 程序不知道自己需要使用多少对象
  * 不知道对象的准确类型
  * 需要多个对象共享数据



* new，返回对象指针，new会调用相应的构造函数
* const new,const对象必须被初始化

```c++
const in *pci = new const int(1024);
```

* new内存耗尽

```c++
int *p1 = new int;//分配失败，抛出std::bad_alloc
int *p2 = new (nothrow) int;//返回nullptr
```

* new的定位

* delete，删除一个指向动态内存的一个区域

```c++
int i, *pil = &i, *pil2 = nullptr;
double *pd = new double(33), *pd2 = pd;
delete i;//错误，i不是指针
delete pil;//未定义，指向局部变量
delete pil2;//正确，删除空指针总正确
delete pd;//正确
delete pd2;//未定义，指向的内存已经被释放了
```

* const 动态内存可以被释放

```c++
const int* p = new const int(1024);
delete p;//正确
```

* 动态内存的生命周期，直到显式被释放

* delete删除后指针变成了空悬指针，保留了地址，数据已经被释放；一种好的做法是，delete后显式赋值nullptr



* shared_pte和new结合

```c++
//错误，必须使用直接初始化
shared_ptr<int> p1 = new int(1024);
shared_ptr<int> p1(new int(1024));
```

| 定义和改变shared的其他操作 | 作用                 |
| -------------------------- | -------------------- |
| shared_ptr<T>p(q)          | q内置指针            |
| shared_ptr<T>p(u)          | 接管unique_ptr,u置空 |
| shared_ptr<T>p(q,d)        | d删除器              |
| shared_ptr<T>p(p2, q)      |                      |
| shared_ptr<T>p.reset()     | p置空                |
| shared_ptr<T>p.reset(q)    | 内置指针q，p指向q    |
| shared_ptr<T>p.reset(q,d)  |                      |

* 不要混合使用普通指针和智能指针
* 不要用get初始化另外一个智能指针或赋值智能指针



### 智能指针和异常

```c++
void f()
{
	shared_ptr<int> sp(new int(1024));
	//抛出一个异常，且f未捕获
}//函数结束自动释放内存

//若函数f外无指针指向这块内存，这块内存不能被释放了
void f2()
{
    int *ip = new int(42);
    //抛出一个异常，且f未捕获
    delete ip;
}
```

### uniqe_ptr

| 函数                   | 作用              |
| ---------------------- | ----------------- |
| unique_ptr<T> u1       | 空指针            |
| unique_ptr<T，D> u1    | 调用类型为D删除器 |
| unique_ptr<T，D> u1(d) |                   |
| u = nullptr            | 释放，u置空       |
| u.release()            | 释放，置空        |
| u.reset()              |                   |
| u.reset(q)             |                   |
| u.reset(nullptr)       |                   |

* 不能拷贝和赋值unique

```c++
uniqe_ptr<int> p1(10);
uniqe_ptr<int> p2(p1.release());
uniqe_ptr<int> p3;
p3.reset(p2.release());

p2.release();//错误，p2不会释放内存，并且我们丢失了指针
```

### weak_ptr

| 函数              | 作用                                                   |
| ----------------- | ------------------------------------------------------ |
| weak_ptr<T> w     | 空                                                     |
| weak_ptr<T> w(sp) | shared                                                 |
| w = p             |                                                        |
| w.reset()         | w置空                                                  |
| w.use_count()     |                                                        |
| w.expired()       | use=0，返回false；否则返回true                         |
| w.lock()          | expired=true,返回空的shared；否则返回指向w对象的shared |

### 动态数组

```c++
typedef int arrT[42];
int *p = new arrT;//new []
```

* 分配空数组是合法的

```c++
size_t n = 0;
int arr[n];//非法
int *p = new int[n];//合法,new返回一个与其他new的指针都不相同
for (int *q = p; q != p + n; ++q)
    ;
```

* delete
* 智能指针和动态数组

```c++
unique_ptr<int[]> up(new int[10]);
up.release();//自动调用delete[]
for (size_t i = 0; i != 10; i++)
    up[i] = i;
```

* 不能使用.和->，可以使用[],因为up指向的是数组

* allocator

```c++
    allocator<string> alloc;
    size_t n = 10;
    auto const p = alloc.allocate(n);
    auto q = p;
    alloc.construct(q++);
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++, "hi");
    
    for(size_t si=0; p + si != q; si++)
        cout << *(p+si) << endl;
    while (q != p)
        alloc.destroy(--q);
    
   alloc.deallocate(p, n);//收回内存

```

* allocator拷贝和fill

```c++
vector<int> vi {1,2,3,5};
auto p = alloc.allocate(vi.size() * 2);
auto q = uninitialized_copy(vi.begin(), vi.end(), p);
uninitialized_fill_n(q, vi.size(), 42);
```









类键盘输入模板

```c++
#include <iostream>
#include <vector>

using namespace std;

class Student{
    public:
        friend istream &operator>>(istream &is, Student &s);        
        void print()
        {
            cout << this->name << " " << this->ID << endl;
        }
    private:
        string name, ID;
        char gender;
        int grade;  
};
istream & operator>>(istream &is, Student &s)
{
    is >> s.name;
    is >> s.gender;
    is >> s.ID;#include <iostream>
#include <vector>

using namespace std;

class Student{
    public:
        friend istream &operator>>(istream &is, Student &s);        
        void print()
        {
            cout << this->name << " " << this->ID << endl;
        }
    private:
        string name, ID;
        char gender;
        int grade;  
};
istream & operator>>(istream &is, Student &s)
{
    is >> s.name;
    is >> s.gender;
    is >> s.ID;
    is >> s.grade;

    return is;
}
int main()
{
    int i;
    Student tmp;
    vector<Student> vstd;
    cin >> i;
    for (;i>0; i--)
    {
        cin >> tmp;
        vstd.push_back(tmp);
    }
    for (auto st : vstd)
        st.print();
    
    return 0;
}
    is >> s.grade;

    return is;
}
int main()
{
    int i;
    Student tmp;
    vector<Student> vstd;
    cin >> i;
    for (;i>0; i--)
    {
        cin >> tmp;
        vstd.push_back(tmp);
    }
    for (auto st : vstd)
        st.print();
    
    return 0;
}

3
Joe M Math990112 89
Mike M CS991301 100
Mary F EE990830 95
```

