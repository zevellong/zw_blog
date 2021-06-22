## pat1007 basic

* 在函数里面不适合定义很大的临时数组变量。应该使用堆动态分配

* 大数组应该定义在全局数据区，而不要定义在局部栈，默认栈为1mb



## pat1011 advanced

```c++
//c++ 保留n位小数
    double value = (value * 0.65 - 1) * 2;

    cout << fixed << setprecision(2);
    cout << value << endl;
//求三个值的最大值，需要两条判断语句

```

