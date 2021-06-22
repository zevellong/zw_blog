# c++入门到入土

### 2020-4-4

## 头文件

* 类的声明放在头文件
* 在cpp文件放定义

## 定义和声明

* 一个cpp文件是一个编译单元
* 定义放在头文件
  * extern
  * 函数原型
  * 类声明

```c++
//防止多次被include
#ifndef HEADER_FLAG
#define HEADER_FLAG
//some declaration
#endif
```

* 一个头文件放一个声明
* 源代码文件使用.cpp

## 抽象

* 在某种程度不去思考内部细节，在某一个层面上考虑
* 一个对象分成几个部分看待
* 符合大多数人的思路

## 成员变量(Fields)



## 构造和析构

* 构造器：和类的名字一样，无返回类型，对象创建自动被调用
* 析构函数：对象删除的时候调用
* 初始化：构造函数调用，定义的时候才会调用
* default构造器：没有参数

## new & delete

```c++
new int;
new int[10];
delete p;
delete[] p;
```

* new会分配空间，调用构造函数，返回分配的地址
* 用new [],使用delete []
* delete调用析构，再回收空间
* 使用new[],调用delete，只会析构第一个，空间都会收回
* inch table：记录地址和内存大小
* 如果delete与table内容找不到，运行出错
* tips：
  * 不要用delete收回不是new的空间
  * 不要delete两次同一块空间
  * 可以delete null
  * new []和dlete[]一起调用，new和delete

### 2020-4-2 15:59

## 拷贝构造

```c++
T::T(const T&);
```

* 成员级别的拷贝
* 默认的拷贝构造，会将成员一个一个拷贝，指针也会拷贝， 而不是分配内存
* Constructions vs. assignment
  * 初始化只会做一次
  * 构造一次也会被析构一次
  * 一个对象construction一次，assignment多次
* 如果是私有的，别人不能拷贝
* 

## template

* 重用代码，类型成为参数

* 两种template，function template，class template

```c++
template <class T>
void swap(T& x, T& y){
	T temp = x;
	x = y;
	y = temp;
}	

int i = 3;
int j = 1;
swap(i,j);
```

```c++
//Interactions
swap(int, int) //yes
swap(float, float)//yes
swap(int, float)//no
swap<int> (a, b);
```

```c++
//vector members 类函数每一个函数都是模板
template <class T>
Vector<T>::Vector(int size) : m_size(size){
	m_elements = new T[m_size];
}
template <class T>
T& Vector<T>::operator[] (int index){
    if (index < m_size && indx > 0){
        return m_elements[index];
    }else {
        ...
    }
}

```

* template 可以多个参数

```c++
template< class Key, class Value>
template< class Key, int bounds = 100 >
```

* template 和 inheritance
```c++
// non-template classes
template< class A>
class Derived : public Base{ ... }

//
template< class A>
class Derived : public List<A> { ... }

class Derived : public Employee<A> { ... }
```



## exception

* 由于外界的条件，程序可能不正常运行

### Example

```txt
// read a file
open the file
determine its size
allocate that much memory
read the file into memory
close the file
```

```c++
try{
    open the file
	determine its size
	allocate that much memory
	read the file into memory
	close the file
}catch (fileOpenFailed) {
    doSomething
}catch (sizeDeterminationFailed) {
    doSomething
}catch (memoryAlloctionFailed) {
    doSomething
}catch (readFailed) {
    doSomething
}catch (fileColseFailed) {
    doSomething
}

throw <something>
```



## stream

* in c, printf, scanf
* Advantages of steams
  * safety
  * Extensible
  * More obkect-oriented
* Disadvantage
  * more verbose
  * Often slower

* what is a stream
  * 一维单方向

|                   | Input         | Output        | Headr       |
| ----------------- | ------------- | ------------- | ----------- |
| Generic           | istream       | ostream       | <iostream>  |
| File              | ifstream      | ofstream      | <fstream>   |
| C string <legacy> | istrstream    | ostrstream    | <strstream> |
| C string          | istringstream | ostringstream | <sstream>   |

* stream operations
  * Extractors (>>)
  * inserters (<<)
  * Manipulators: change the stream state
  * function
* kinds of streams
  * text streams : ASCLL text
  * Binart streams
* Predefined stream
  * cin
  * cout
  * cerr
  * clog

```c++
	istream& operator>> (istream& is, T& obj){
        // 特殊的格式读流
        return is;
    }
```

* chaining  `cin >> a >> b >> c`
* `istream& get(char& ch)`
* `get(char *buf, int limit, char delim = '\n')`
  * limit限制读入长度
  * 追加null在字符串后
  * 不消耗delim符号

* `getline(char* buf, int limit, char delim ='\n')`
  * 追加null
  * 消耗delim
* `ignore(int limit=1, int delim = EOF)`
  * 跳过limit个字符
  * 遇到delim结束
* `int gcount()`
  * 读入多少字节
* `int putback(char)`
  * 放回去一个字节
* `char peek()`
  * 偷窥
* `flush`
  * `cout << "something" << flush;`

* xx

| manipulator        | effect       | type |
| ------------------ | ------------ | ---- |
| dec, hex,oct       | 10,16,8进制  | I/O  |
| endl               | 换行         | O    |
| flush              | 刷新流       | O    |
| setw(int)          | 设置格式宽度 | I/O  |
| setfill(ch)        | 填充         | I O  |
| setbase()          | 进制         | O    |
| ws                 | 跳过空格     | I    |
| setprecision(int)  | 精度         | O    |
| setioflags(long)   | 设置ioflag   | IO   |
| resetioflags(long) | 复位         | IO   |

* ioflag

| flag                 | purpose              |
| -------------------- | -------------------- |
| ios::skipws          | 跳过空格             |
| ios::left   or right | justofocation        |
| intenal              | 符号和值之间填充     |
| dec oct hex          | 10 16 8              |
| showbase             | 进制                 |
| showpoint            | 小数点               |
| uppercase            | 大写                 |
| showpos              | 加上+在正数前        |
| scientific fixed     | 格式化浮点           |
| unitbuf              | 任何时候都使用刷新写 |

## auto_prt

* 该类主要用于管理动态内存分配。
* 当 auto_ptr 对象过期时，析构函数将使用 delete 来释放内存。如果将 new 返回的地址赋值给 auto_ptr 对象，无须记住还需要释放这些内存。在 auto_ptr 对象过期时，内存将自动被释放。
* auto_ptr 构造函数是显式的，不存在从指针到 auto_ptr 对象的隐式类型转换

```c++
	auto_ptr<double> pd;
	double *p_reg = new double;
	*p_reg = 3.1415;
	//pd = p_reg; // 不允许
	pd = auto_ptr <double> (p_reg); //允许
	//auto_ptr <double> panto =p_reg; //不允许
	auto_ptr <double> pauto (p_reg); //允许
```



## STL

[文档1](http://c.biancheng.net/stl/)          

[文档2](http://www.cplusplus.com/reference/)

* sort函数
  * #include algorithm

```C++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int arr[10] = {1, 3, -3, -9 ,6 ,9 ,11};
    sort(arr, arr+7);
    for (int i = 0; i < 7; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}
```

### string 

* 相当于char *的封装
* 获取一行字符串   `string s = NULL;  getline(cin,s);`

| 函数名称                          | 功能                         |
| --------------------------------- | ---------------------------- |
| 构造函数                          | 产生或复制字符串             |
| 析构函数                          | 销毁字符串                   |
| =，assign                         | 赋以新值                     |
| Swap                              | 交换两个字符串的内容         |
| + =，append( )，push_back()       | 添加字符                     |
| insert ()                         | 插入字符                     |
| erase()                           | 删除字符                     |
| clear ()                          | 移除全部字符                 |
| resize ()                         | 改变字符数量                 |
| replace()                         | 替换字符                     |
| +                                 | 串联字符串                   |
| ==，！ =，<，<=，>，>=，compare() | 比较字符串内容               |
| size()，length()                  | 返回字符数量                 |
| max_size ()                       | 返回字符的最大可能个数       |
| empty ()                          | 判断字符串是否为空           |
| capacity ()                       | 返回重新分配之前的字符容量   |
| reserve()                         | 保留内存以存储一定数量的字符 |
| [],at()                           | 存取单一字符                 |
| >>，getline()                     | 从 stream 中读取某值         |
| <<                                | 将值写入 stream              |
| copy()                            | 将内容复制为一个 C - string  |
| c_str()                           | 将内容以 C - string 形式返回 |
| data()                            | 将内容以字符数组形式返回     |
| substr()                          | 返回子字符串                 |
| find()                            | 搜寻某子字符串或字符         |
| begin( )，end()                   | 提供正向迭代器支持           |
| rbegin()，rend()                  | 提供逆向迭代器支持           |
| get_allocator()                   | 返回配置器                   |

```c++
    //切记不能初始化NULL
    std::string s;//执行默认构造函数
    std::string s = "";//执行拷贝构造函数
	string s(str, strbegin, strlen) //将字符串str中始于strbegin、长度为strlen的部分作为字符串初值
	strings(num, c) //生成一个字符串，包含num个c字符
	strings(strs, beg, end)    //以区间[beg, end]内的字符作为字符串s的初值
    

    s+ = "hello";
    s+ = '5'
    s+ = 65;//对应大写A
    cout << s << endl;//打印结果 hello5A


	std::string s('x');    //错误
	std::string s(1, 'x');    //正确
	std::string s("x"); // 正确

```

* 获取字符串长度

```c++
	s.size()
    s.length()
    s.max_size()//返回最大包含字符数，超出后抛出length_error
```

* 字符串的比较

```c++
    cout << A.compare (B)  << endl;
    cout << A.compare(2,2,B,2,2) << endl;
    cout << (ss == s2) << endl;
    cout << (stoi(ss) < stoi(s2) )<< endl;
    cout << "ss:" << ss << "  s2" << s2 << endl;
```

* 字符串的修改

```c++
	A.swap(B);
	
	//insert
	string str = "meihao";
	cout << str.insert(0,2,'A') << endl;//AAmeihao
	
	str = "meihao"; 
	cout << str.insert(1,"AA") << endl;//mAAeihao
	
	str = "meihao";
	cout << str.insert(1,"AAAAAA", 3) << endl; //mAAAeihao
	
	str = "meihao";
	str.insert(++str.begin(),2,'A');//不返回 
	cout << str << endl;

	//append
	string str = "meihao";
	cout << str.append("~live") << endl; //meihao~live
	
	str = "meihao";
	cout << str.append("~live", 2) << endl; //meihao~l
	
	str = "meihao";
	cout << str.append("~live", 2, 3) << endl; //meihaoive
	
	str = "meihao";
	cout << str.append(10, 'A') << endl; //meihaoAAAAAAAAAA
	
	str = "meihao";
	string str2 = "live";	
	cout << str.append(str2.begin(), str2.end()) << endl;
	//meihaolive



	//replace
	string var = "ABCDEFG";
	const string dest1 = "1234";
	string dest2 = "5678";
	var = "ABCDEFG";
	cout << var.replace(3,1, dest1) << endl;//ABC1234EFG (1234 rep D)
	
	var = "ABCDEFG";
	cout << var.replace (3, 1, 5, 'x')  << endl;//ABCxxxxxEFG
	
	var = "ABCDEFG";
	cout << var.replace(3, 1, dest1, 2, 2) << endl;//ABC34EFG
	
	var = "ABCDEFG";
	cout << var.replace(var.begin(), var.end(), dest2) << endl;//5678
```

* 字符串查找

```c++
	string source = "ABCDEFG";
	cout << (source.find("H") == -1) << endl;//return true;not find
	
	cout << source.find("FG") << endl;//5
	
	cout << (source.find("FG",6) == -1) << endl;//return true;not find
	
	cout << source.find("FG",0,1) << endl; // only find 'F', return 5
	
	cout << source.find_first_of("CDE", 0 , 4);//return 2
	cout << source.find_last_of("CDE") << endl;//return 4
```

* 迭代器

```c++
string str("abcdefg");
string::iterator ite;

```

* 对字符串排序

```c++
string = "5418345";
sort(s.begin(), s.end());
cout << s << endl;
```

* erase() 删除某字符
  * `s.erase(s.begin())`
* `substr(index, size);//`子字符串，size 正数取size个，size 负数倒取

### string转数字

```c++
//通过stream,sstream的转换

	#include <iostream>
	#include <string>
	#include <sstream>
	string line;
	getline(cin, line);
	stringstream ss(line);
	int a, b;
	ss >> a >> b;
```

```c
// c中通过多次调用strtol,跳出条件为 *p1 != '\0'

while ( *p1 != '\0'){
		a = (int )strtol(p1, &p2, 10);
		p1 = p2;	
		b = (int) strtol(p1 ,&p2, 10);
		p1 = p2;
}
```



### 迭代器失效

* vector
  * 当插入（push_back）一个元素后，end操作返回的迭代器肯定失效
  * 当插入(push_back)一个元素后，capacity返回值与没有插入元素之前相比有改变，则需要重新加载整个容器，此时first和end操作返回的迭代器都会失效
  * 当进行删除操作（erase，pop_back）后，指向删除点的迭代器全部失效；指向删除点后面的元素的迭代器也将全部失效。
* list
  * 插入操作（insert）和接合操作（splice）不会造成原有的list迭代器失效，这在vector中是不成立的，因为vector的插入操作可能造成记忆体重新配置，导致所有的迭代器全部失效
  * list的删除操作（erase）也只有指向被删除元素的那个迭代器失效，其他迭代器不受影响。（list目前只发现这一种失效的情况）
* deque
  * 在deque容器首部或者尾部插入元素不会使得任何迭代器失效。
  * 在其首部或尾部删除元素则只会使指向被删除元素的迭代器失效。 
  * 在deque容器的任何其他位置的插入和删除操作将使指向该容器元素的所有迭代器失效。
* set & map
  * 与list相同，当对它进行insert和erase操作时，操作之前的所有迭代器，在操作完成之后都依然有效，但被删除的元素的迭代器失效。





### 容器中的常见成员函数

| 函数成员         | 函数功能                                                     | array<T,N> | vector<T> | deque<T> |
| ---------------- | ------------------------------------------------------------ | ---------- | --------- | -------- |
| begin()          | 返回指向容器中第一个元素的迭代器。                           | 是         | 是        | 是       |
| end()            | 返回指向容器最后一个元素所在位置后一个位置的迭代器，通常和 begin() 结合使用。 | 是         | 是        | 是       |
| rbegin()         | 返回指向最后一个元素的迭代器。                               | 是         | 是        | 是       |
| rend()           | 返回指向第一个元素所在位置前一个位置的迭代器。               | 是         | 是        | 是       |
| cbegin()         | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是         | 是        | 是       |
| cend()           | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是         | 是        | 是       |
| crbegin()        | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是         | 是        | 是       |
| crend()          | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是         | 是        | 是       |
| assign()         | 用新元素替换原有内容。                                       | -          | 是        | 是       |
| operator=()      | 复制同类型容器的元素，或者用初始化列表替换现有内容。         | 是         | 是        | 是       |
| size()           | 返回实际元素个数。                                           | 是         | 是        | 是       |
| max_size()       | 返回元素个数的最大值。这通常是一个很大的值，一般是 2^32-1，所以我们很少会用到这个函数。 | 是         | 是        | 是       |
| capacity()       | 返回当前容量。                                               | -          | 是        | -        |
| empty()          | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 | 是         | 是        | 是       |
| resize()         | 改变实际元素的个数。                                         | -          | 是        | 是       |
| shrink _to_fit() | 将内存减少到等于当前元素实际所使用的大小。                   | -          | 是        | 是       |
| front()          | 返回第一个元素的引用。                                       | 是         | 是        | 是       |
| back()           | 返回最后一个元素的引用。                                     | 是         | 是        | 是       |
| operator[]()     | 使用索引访问元素。                                           | 是         | 是        | 是       |
| at()             | 使用经过边界检査的索引访问元素。                             | 是         | 是        | 是       |
| push_back()      | 在序列的尾部添加一个元素。                                   | -          | 是        | 是       |
| insert()         | 在指定的位置插入一个或多个元素。                             | -          | 是        | 是       |
| emplace()        | 在指定的位置直接生成一个元素。                               | -          | 是        | 是       |
| emplace_back()   | 在序列尾部生成一个元素。                                     | -          | 是        | 是       |
| pop_back()       | 移出序列尾部的元素。                                         | -          | 是        | 是       |
| erase()          | 移出一个元素或一段元素。                                     | -          | 是        | 是       |
| clear()          | 移出所有的元素，容器大小变为 0。                             | -          | 是        | 是       |
| swap()           | 交换两个容器的所有元素。                                     | 是         | 是        | 是       |
| data()           | 返回指向容器中第一个元素的[指针](http://c.biancheng.net/c/80/)。 | 是         | 是        | -        |

| 函数成员        | 函数功能                                                     | list<T> | forward_list<T> |
| --------------- | ------------------------------------------------------------ | ------- | --------------- |
| begin()         | 返回指向容器中第一个元素的迭代器。                           | 是      | 是              |
| end()           | 返回指向容器最后一个元素所在位置后一个位置的迭代器。         | 是      | 是              |
| rbegin()        | 返回指向最后一个元素的迭代器。                               | 是      | -               |
| rend()          | 返回指向第一个元素所在位置前一个位置的迭代器。               | 是      | -               |
| cbegin()        | 和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是      | 是              |
| before_begin()  | 返回指向第一个元素前一个位置的迭代器。                       | -       | 是              |
| cbefore_begin() | 和 before_begin() 功能相同，只不过在其基础上，增加了 const 属性，即不能用该指针修改元素的值。 | -       | 是              |
| cend()          | 和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是      | 是              |
| crbegin()       | 和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是      | -               |
| crend()         | 和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。 | 是      | -               |
| assign()        | 用新元素替换原有内容。                                       | 是      | 是              |
| operator=()     | 复制同类型容器的元素，或者用初始化列表替换现有内容。         | 是      | 是              |
| size()          | 返回实际元素个数。                                           | 是      | -               |
| max_size()      | 返回元素个数的最大值，这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。 | 是      | 是              |
| resize()        | 改变实际元素的个数。                                         | 是      | 是              |
| empty()         | 判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。 | 是      | 是              |
| front()         | 返回容器中第一个元素的引用。                                 | 是      | 是              |
| back()          | 返回容器中最后一个元素的引用。                               | 是      | -               |
| push_back()     | 在序列的尾部添加一个元素。                                   | 是      | -               |
| push_front()    | 在序列的起始位置添加一个元素。                               | 是      | 是              |
| emplace()       | 在指定位置直接生成一个元素。                                 | 是      | -               |
| emplace_after() | 在指定位置的后面直接生成一个元素。                           | -       | 是              |
| emplace_back()  | 在序列尾部生成一个元素。                                     | 是      | -               |
| cmplacc_front() | 在序列的起始位生成一个元索。                                 | 是      | 是              |
| insert()        | 在指定的位置插入一个或多个元素。                             | 是      | -               |
| insert_after()  | 在指定位置的后面插入一个或多个元素。                         | -       | 是              |
| pop_back()      | 移除序列尾部的元素。                                         | 是      | -               |
| pop_front()     | 移除序列头部的元素。                                         | 是      | 是              |
| reverse()       | 反转容器中某一段的元素。                                     | 是      | 是              |
| erase()         | 移除指定位置的一个元素或一段元素。                           | 是      | -               |
| erase_after()   | 移除指定位置后面的一个元素或一段元素。                       | -       | 是              |
| remove()        | 移除所有和参数匹配的元素。                                   | 是      | 是              |
| remove_if()     | 移除满足一元函数条件的所有元素。                             | 是      | 是              |
| unique()        | 移除所有连续重复的元素。                                     | 是      | 是              |
| clear()         | 移除所有的元素，容器大小变为 0。                             | 是      | 是              |
| swap()          | 交换两个容器的所有元素。                                     | 是      | 是              |
| sort()          | 对元素进行排序。                                             | 是      | 是              |
| merge()         | 合并两个有序容器。                                           | 是      | 是              |
| splice()        | 移动指定位置前面的所有元素到另一个同类型的 list 中。         | 是      | -               |
| splice_after()  | 移动指定位置后面的所有元素到另一个同类型的 list 中。         | -       | 是              |

### array

```c++
std::array<double,100> data; //
std::array<double,100> data {};//初始化为0
std::array<double, 10> values {0.5, 1.0, 1.5, 2.0};//前4个为。。，其余为0
values.fill(3.1415926);//所有元素初始化为3.14

```



### vector

```c++
vector<int> v;//空
vector<int> v2(4);//4个初始化0
vector<int> v3(4, 6);// 初始为6

vector<int> v(9, 10);
for (auto i:v)  cout << i << " ";
cout << v[1];//索引1
cout << v.at(2);//索引2
v.push_back(5);// 5放进v的末端
v.resize(10); //默认为0
v.erase(10);//删除元素10,复杂度O(n)
cout << v.front();//头
cout << v.back(); //尾
sort(v.begin(), v.end());
sort(v.begin(), v.end(), greater<int>());//从大到小


```

### stack

```c++
#include <stack>

stack<int> s;//构造器
s.push();
s.top();//不弹出
s.pop();
s.size();
s.empty();
//方便用栈进制转换
```

### queue

```
#include <queue>

queue<int> q;
q.push(5);
q.front();
q.pop();
q.size();

```

### map

```c++
#include <map>
//有序的，树状结构
map<int, int> m;
//unorderd_map无序的，哈希结构

```

### set

```c++
set<int> s;//树状结构
s.insert(3);
s.size();

```

### deque

```c++
deque<int> d;
d.push_back(3);
d.push_front(4);
d.pop_back();
d.pop_front();
```

### list

```c++
list<int> li;//
li.push_back(6);
li.emplace_front(5);
li.insert(++li.begin(),2);

```





# C语言回忆

## 函数指针

* 每一个函数都有地址

```c
void f(int i)
{
    printf("in f()  i=%d\n", i);
}
void g(int j)
{
    
}
int main()
{
    int i = 0;
    void (*pf)(int) = f;
    f(3);
    (*pf)(4);
    
    //不推荐
    switch(i)
    {
        case 0:f(0);break;
        case 1:g(2);break;
    }
    
    //推荐
    void (*pff[])(int) = {f, g};
    scanf("%d", &i);
    if (i>=0 i<sizeof(fa)/sizeof(fa[0])){
        (*pff[i])(0);
    }
    return 0;
}
```

```c
int plus(int a, int b)
{
    return a + b;
}
int minus(int a, int b)
{
    return a - b;
}
int cal(int (*f)(int, int), int a, int b)
{
    printf("%d\n",(*f)(a,b));
}
```

