# auto

## 条款五：优先考虑`auto`而非显式类型声明

- `typename std::iterator_traits<It>::value_type`，一个局部变量，类型是一个闭包，闭包的类型只有编译器知道，因此我们写不出来
- 避免语法冗长，重复写很多形参类型

```cpp
std::function<bool(const std::unique_ptr<Widget> &,
                   const std::unique_ptr<Widget> &)>
derefUPLess = [](const std::unique_ptr<Widget> &p1,
                 const std::unique_ptr<Widget> &p2)
                { return *p1 < *p2; };
```

-  可移植性

```cpp
//Windows 32-bit上std::vector<int>::size_type和unsigned是一样的大小，但是在Windows 64-bit上std::vector<int>::size_type是64位，unsigned是32位。
std::vector<int> v;
…
unsigned sz = v.size();
```

- 在没有`auto`的版本中`p`会指向一个临时变量，这个临时变量在每次迭代完成时会被销毁。

```cpp
std::unordered_map<std::string, int> m;
…

for(const std::pair<std::string, int>& p : m)
{
    …                                   //用p做一些事
}

for(const auto& p : m)
{
    …                                   //如之前一样
}
```

- auto是可选项，不是命令，在某些情况下如果你的专业判断告诉你使用显式类型声明比auto要更清晰更易维护，那你就不必再坚持使用auto



## 条款六：`auto`推导若非己愿，使用显式类型初始化惯用法



- 一些代理类被设计于用以对客户可见。比如`std::shared_ptr`和`std::unique_ptr`。其他的代理类则或多或少不可见，比如`std::vector<bool>::reference`就是不可见代理类的一个例子，还有它在`std::bitset`的胞弟`std::bitset::reference`。
- `std::vector<bool>::reference`是一个代理类（*proxy class*）的例子：所谓代理类就是以模仿和增强一些类型的行为为目的而存在的类

```cpp
std::vector<bool> features(const Widget& w);

Widget w;
…
bool highPriority = features(w)[5];     //w高优先级吗？
…
processWidget(w, highPriority);         //根据它的优先级处理w

//使用auto后highPriority不再是bool类型。虽然从概念上来说std::vector<bool>意味着存放bool，但是std::vector<bool>的operator[]不会返回容器中元素的引用（这就是std::vector::operator[]可返回除了bool以外的任何类型），取而代之它返回一个std::vector<bool>::reference的对象（一个嵌套于std::vector<bool>中的类）。
auto highPriority = features(w)[5];     //w高优先级吗？
processWidget(w,highPriority);          //未定义行为！
```



- 作为一个通则，不可见的代理类通常不适用于`auto`
- 显式类型初始器惯用法强制`auto`推导出你想要的结果

```cpp
auto sum = static_cast<Matrix>(m1 + m2 + m3 + m4);
```

