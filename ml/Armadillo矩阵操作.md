# Armadillo矩阵操作

http://arma.sourceforge.net/docs.html#stats_fns

* 基本矩阵操作

| **Matlab/Octave**          | **Armadillo**                    | Notes      |
| -------------------------- | -------------------------------- | ---------- |
| A(1, 1); A(k, k)           | A(0, 0); A(k-1, k-1)             | 索引操作   |
| size(A, 1); size(A, n)     | A.n_rows A.ncols A.n_slices      | 维度的size |
| numel(A)                   | A.n_elem                         | A的元素数  |
| A(:, k)  A(k, :) A(:, p:q) | A.col(k)  A.row(k) A.cols(p, q)  | 切片操作   |
| A(p:q, r:s)                | A( span(p,q), span(r,s) )        | 切片操作   |
| Q(:, :, k)                 | Q.slice(k)                       | 三维切片   |
| A‘                         | A.t()  trans(A)                  | 转置       |
| A                          | A.print("A=")  cout << A << endl | 打印       |

* 常用矩阵

| **Matlab/Octave**  | **Armadillo**             | Notes    |
| ------------------ | ------------------------- | -------- |
| `A=zeros(size(A))` | `A.zeros()`               | 0矩阵    |
| `A=ones(size(A))`  | `A.ones()`                | 1矩阵    |
| `A = zeros(k)`     | `A=zeros<mat>(k,k)`       |          |
| `A = onns(k)`      | `A=ones<mat>(k,k)`        |          |
| C = complex(A, B)  | cx_mat c = cx_mat(A, B)   | 复数矩阵 |
| A = randn(2,3);    | mat A = randn(2, 3)       | 随机矩阵 |
|                    | mat A(4, 5, fill::randu); | 随机矩阵 |

* randu 均匀分布[0, 1]
* 运算

| **Matlab/Octave**  | **Armadillo**                | Notes        |
| ------------------ | ---------------------------- | ------------ |
| A .* B             | A % B                        | 点乘         |
| A ./ B             | A / B                        | 点除         |
| A \ B              | solve(A, B) inv(A)*B         | 求方程解     |
| A = A + 1; A = A-1 | A++; A--                     | 每个元素+- 1 |
| A = [1 2; 3 4]     | A = {{1, 2}, {3, 4}}         | 赋值         |
| X = A(:)           | X = vectorise(A)             | 矩阵生成向量 |
| X = [ A B ]        | X = join_horiz(A, B)         | 行连接       |
| A = [A ; B]        | X = join_vert(A, B)          | 列连接       |
| F = {A ; B}        | field<mat> F(2,1); F(0,0)=A; | 元胞         |

*   X = vectorise(A, dim=0) 
  * dim=0则列方向复制，相当于连接*X的*所有列
  * dim=1行方向，相当于连接*X 的*所有行
  * **列向量化比行向量化更快**
  * 对于稀疏矩阵，不推荐行向量化

* 保存、加载

| **Matlab/Octave**   | **Armadillo**               | Notes |
| ------------------- | --------------------------- | ----- |
| save ‑ascii 'A.txt' | A.save("A.txt", raw_ascii); | 保存  |
| load ‑ascii 'A.txt' | A.load("A.txt", raw_ascii)  | 加载  |



## 矩阵

* 基本矩阵类
  * `Mat<type>, mat, cx_mat`
  * `mat = Mat<double>`, `fmat =Mat<float>`
  * umat, imat
* 构造函数

| Constructors                                                 | description          |
| ------------------------------------------------------------ | -------------------- |
| mat()  mat(*n_rows*, *n_cols*) mat(mat)                      |                      |
| mat(*n_rows*, *n_cols*, *fill_type*)                         | 初始化根据fill       |
| mat(vec) mat(rowvec)                                         |                      |
| mat(initializer_list) mat(std::vector)                       |                      |
| `mat::fixed<n_rows, n_cols>`                                 | 矩阵的大小固定       |
| `mat(ptr_aux_mem, n_rows, n_cols, copy_aux_mem = true, strict = false)` | 高级构造函数，见下文 |

* fill_type
  * fill::zeros
  * fill::ones
  * fill::eye  单位矩阵，主对角线初始化为1
  * fill::randu [0,1]均匀分布随机数
  * fill::randn 标准正态分布随机数
  * fill::none 不初始化
*  `double aux_mem[24]; mat H(&aux_mem[0], 4, 6, false);`   
  * *ptr_aux_mem*是指向内存的指针
  * 如果*copy_aux_mem*设置为*false*，则矩阵将直接使用辅助内存（即不复制） 
  * 当*strict*设置为*false 时*，矩阵将使用辅助内存直到大小发生变化
  *  当*strict*设置为*true 时*，绑定辅助内存，元素数量不能改变
* 10.4版本及之前默认不会初始化，可能带来NAN值；10.5版本默认初始化0
* `vec, Col<type>`,`Row<type>,rowvec`
  * 列向量

| `vec`     | `colvec`     | `Col<double>`    |
| --------- | ------------ | ---------------- |
| `dvec`     | `dcolvec`    | `Col<double>`    |
| `fvec`    | `fcolvec`    | `Col<float>`     |
|        |           |               |

```c++

vec a(5);  a = 123.0;
# instead above line
vec a(5);  a.fill(123.0);
```



* 稀疏矩阵 sp_mat
  * 默认情况下，所有元素都被视为零（即矩阵初始化为包含零）
  * 非零元素以[压缩稀疏列 (CSC) 格式存储](http://en.wikipedia.org/wiki/Sparse_matrix)（即列优先排序）；从不存储零值元素
  * 



## 运算符

```c++
 +  −  *  %  /  ==  !=  <=  >=  <  >  &&  ||
```

| `+`  | 两个对象的相加                                               |
| ---- | ------------------------------------------------------------ |
| `−`  | 从另一个对象中减去对象                                       |
| `*`  | 两个对象的矩阵乘法；不适用于*Cube*类，除非乘以标量           |
| `%`  | 两个对象的元素乘法（Schur 乘积）                             |
| `/`  | 一个对象被另一个对象或标量按元素划分                         |
| `==` | 两个对象的逐元素相等性评估；生成*umat* / *ucube*类型的矩阵/立方体 |
| `!=` | 两个对象的元素不等式评估；生成*umat* / *ucube*类型的矩阵/立方体 |
| `>=` | 对两个对象的逐元素“大于或等于”评估；生成*umat* / *ucube*类型的矩阵/立方体 |
| `<=` | 两个对象的逐元素“小于或等于”评估；生成*umat* / *ucube*类型的矩阵/立方体 |
| `>`  | 两个对象的逐元素“大于”评估；生成*umat* / *ucube*类型的矩阵/立方体 |
| `<`  | 两个对象的逐元素“小于”评估；生成*umat* / *ucube*类型的矩阵/立方体 |
| `&&` | 两个对象的逐元素逻辑 AND 评估；生成*umat* / *ucube*类型的矩阵/立方体 |
| `||` | 两个对象的逐元素逻辑 OR 评估；生成*umat* / *ucube*类型的矩阵/立方体 |

* 不建议将涉及相等比较的运算符（即`**==**`, `**!=**`, `**>=**`, `**<=**`）用于*mat*或*fmat*类型的矩阵，因为基础元素类型的[精度](https://en.wikipedia.org/wiki/Floating_point)必然[有限](https://en.wikipedia.org/wiki/Floating_point)；考虑使用[approx_equal()](http://arma.sourceforge.net/docs.html#approx_equal)代替
* 如果`**+**`,`**−**`和`**%**`操作符被链接起来，Armadillo 的目的是避免产生临时变量；如果所有给定的对象都具有相同的类型和大小，则不会生成临时对象
* 如果`*`运算符是链式的，Armadillo 的目标是找到矩阵乘法的有效排序
* 如果使用不兼容的对象大小抛出异常std :: logic_error

```c++
// 如果A和B中的所有对应元素近似相等， 则返回true
// 如果A和B中的任何相应元素不近似相等，或者A和B的维度不同 ，则返回false
approx_equal( A, B, method, tol )
approx_equal( A, B, method, abs_tol, rel_tol )

//method 控制如何确定近似相等,它是以下之一
// absdiff |x-y|<= tol
// reldiff  |x − y| / max( |x|, |y| ) ≤ tol
// both 前两者都满足
```

* () [] .at() 访问元素

  * （）不会做边界检查
  * 可以通过在包含*armadillo*头文件（例如）之前定义[ARMA_NO_DEBUG](http://arma.sourceforge.net/docs.html#config_hpp_arma_no_debug)宏来禁用`(n)`,`(i,j)`和`(i,j,k)`元素访问表单 使用的边界检查
  * 边界检查抛出*std::* *out_of_range*



## 随机数

* rng 随机数种子： 
  * `arma_rng::set_seed(value)`
  * `arma_rng::set_seed_random()`
* randu randn randi   均匀分布[0,1] 正态分布(0, 1)  
* `randi( )  randi( distr_param(a,b) )`  生成 a,b 之间的整数 矩阵或立方
  * 默认分布参数为*a=0*和*b=maximum_int*
* 其他随机分布: 压缩坐标轴推到
  * linspace，logspace，regspace

## 赋值

* fill  imbue
* 一个生成泊松分布矩阵的例子

```c++
mat A(5, 5);
std::mt19937 mt(20);
std::poisson_distribution<int> p(10);
A.imbue([&](){ return p(mt); });                             
A.print("A=");
```



### 特殊赋值

* **.clean(** threshold **)**：元素如果小于阈值，则设置为0

* **.replace( old_value, new_value )**: 每一个元素=old，替换成new

* diag()  diag(k)  对角线

* **.clamp( min_value, max_value)** : 大于最大值的替换成最大值，小于同理

* **.transform(** functor **)** ，**.transform( lambda_function)**

  * 使用函数或 lambda 函数转换每个元素
  * 对于密集矩阵，对所有元素逐列进行转换
  * 对于稀疏矩阵，对非零元素逐列进行转换
  
 * **.for_each(** functor **)**,  **.for_each( lambda_function )**

    * 对于每个元素，将其引用传递给函子或 lambda 函数

   ```c++
   A.for_each([](mat::elem_type& val) { val += 123.0;}); // 切记引用
   ```

   

##  修改size

| func     | notes           |
| -------- | --------------- |
| set_size | 不保留值,速度快 |
| reshape  | 保留值，列填充  |
| resize   | 保留布局        |



| **.set_size( n_elem )**                   | (member function of *Col*, *Row*, *field*)                   |
| ----------------------------------------- | ------------------------------------------------------------ |
| **.set_size( n_rows, n_cols )**           | (member function of *Mat*, *SpMat*, *field*)                 |
| **.set_size( n_rows, n_cols, n_slices )** | (member function of *Cube* and *field*)                      |
| **.set_size( size(X) )**                  | (member function of *Mat*, *Col*, *Row*, *Cube*, *SpMat*, *field*) |

- **注意**：*.reshape()*和*.resize()*比*.set_size()*慢得多
- 更改对象的大小，而不显式保留数据和初始化元素（即元素可能包含垃圾值，包括 NaN）
- 初始化的元素为零，同时改变大小，使用[.zeros（）](http://arma.sourceforge.net/docs.html#zeros_member)代替



| **.reshape( n_rows, n_cols )**           | （*Mat*和*SpMat 的*成员函数）          |
| ---------------------------------------- | -------------------------------------- |
| **.reshape( n_rows, n_cols, n_slices )** | ( *Cube 的*成员函数)                   |
| **.reshape( 大小(X) )**                  | ( *Mat* , *Cube* , *SpMat 的*成员函数) |

- 注意
  - 根据给定的大小规格重新创建对象，并以列方式从对象的先前版本中获取元素；生成的对象中的元素按列放置（即在填充第二列之前填充第一列）
  - 重新创建的对象中元素的布局将与对象的先前版本中的布局不同
  - 如果对象的上一版本中的元素总数小于指定的大小，则重新创建的对象中的额外元素将设置为零
  - 如果对象的上一版本中的元素总数大于指定的大小，则只取元素的一个子集

- **.copy_size(A)**
  - 设置大小与对象*A*相同
  - 对象*A*必须与正在修改的对象具有相同的根类型（例如，您不能通过提供立方体来设置矩阵的大小）
- reset()
  - 将大小重置为零（对象将没有元素）

## 子视图

- 连续视图,非连续视图

```c++
// sub matrix view
//

#include <iostream>
#include <armadillo>

using namespace arma;

int main(int argc, char* argv[])
{
	mat A(5, 6, fill::zeros);
	A.submat(0, 1, 2,3) = randu<mat>(3,3);
	A.print("A=");

	auto B = A(span(0,2), span(1,3));
	B.print("B=");

	auto C =A(0, 1, size(3, 3));
	C.print("C=");

	mat D(C);
	D.print("D=");
	// A的前2列
	std::cout << A.head_cols(2) << std::endl;

	// A的倒数2行
	std::cout << A.tail_rows(2) << std::endl;

	A.col(2).head(3) += 123;
	std::cout << A.col(2).head(3) << endl;

	//非连续
	uvec ind = {1,2, 5};
	A.elem(ind) = ones<vec>(3);
	std::cout << A(ind) << endl;
	return 0;
}

```

对角线



## 插入，删除，交换

```c++
// sub matrix view
//

#include <iostream>
#include <armadillo>

using namespace arma;

int main(int argc, char* argv[])
{
	mat A(5, 6, fill::zeros);
	//insert
	mat F(5, 2, fill::ones);
	A.insert_cols(2, F);
	A.print("A=");
	//delete col 2-
	A.shed_cols(2, 4);
	A.print("delete 2-4 cols\nA=");
	//swap 1 3 col
	A.swap_cols(1, 3);
	A.print("Swap 1,3col A=");

	//swap 
	mat G = A * 2; 
	A.swap(G);
	A.print("swap A, 2*A");
	return 0;
    
    //each_col row
    mat H(6, 5, fill::ones);
	vec v = linspace(10, 15, 6);
	H.each_col() += v;
	mat I = H.each_col() + v;

	std::cout << "I=" << std::endl;
	I.each_col([](const vec& b){b.t().print();});
	return 0;
}


```

## 迭代器

* memptr
  * 获取指向用于存储元素的内存的原始指针
  * 矩阵的数据按列顺序存储
  * 多维数据集的数据以逐个切片（matrix-by-matrix）的顺序存储
  * **警告：**在任何涉及大小更改或别名的操作后，指针将变为无效
  * **警告：**除非您知道自己在做什么，否则不建议使用此功能
* colptr
  * 获取指向指定列使用的内存的原始指针
  * 其他同 memptr
* 成员函数
  * begin， end
  * begin_col, end_col 引用指定列的第一个/最后一个元素的迭代器
  * begin_row, end_row
* 迭代器类型

| **mat::iterator**；**vec::iterator**； **rowvec::iterator**  | 随机访问迭代器，用于对元素的读/写访问（逐列存储） |
| ------------------------------------------------------------ | ------------------------------------------------- |
| **mat::const_iterator** ；**vec::const_iterator** ；**rowvec::const_iterator**； | 随机访问迭代器，用于对元素的只读访问（逐列存储）  |
| **mat::col_iterator** ；**vec::col_iterator** ；**rowvec::col_iterator**； | 随机访问迭代器，用于对指定列的元素进行读/写访问   |
| **mat::const_col_iterator** ；**vec::const_col_iterator** ；**rowvec::const_col_iterator**； | 随机访问迭代器，用于对指定列的元素进行只读访问    |
| **mat::row_iterator**；                                      | 双向迭代器，用于对指定行的元素进行读/写访问       |
| **mat::const_row_iterator**；                                | 双向迭代器，用于对指定行的元素进行只读访问        |
| **vec::row_iterator** ；**rowvec::row_iterator**；           | 随机访问迭代器，用于对指定行的元素进行读/写访问   |
| **vec::const_row_iterator** ；**rowvec::const_row_iterator**； | 随机访问迭代器，用于对指定行的元素进行只读访问    |

* 迭代器有*.row()*和*.col()*函数，它们返回当前元素的行和列；返回值的类型为（uword）
* front() 访问向量中的第一个元素
* back() 访问最后一个元素

## 生成器

| func                              | notes                                        |
| --------------------------------- | -------------------------------------------- |
| linspace(st, ed, N=100)           | 线性增长，n为阶数                            |
| logspace(A,B,N=50)                | 元素的值以对数间隔从*10^A*到（并包括）*10^B* |
| **regspace( start, delta, end )** | delta等差数列                                |
| **randperm( N, M=1 )**            | 放回的抽样随机整数，整数范围 0-N-1           |
| **eye( n_rows, n_cols )**         | 单位矩阵                                     |
| **ones( n_rows, n_cols )**        | 元素全为1矩阵                                |
| **zeros( n_rows, n_cols )**       | 0矩阵                                        |
| **randu( n_rows, n_cols )** randn | 均匀分布，正态分布                           |
| **randg( )** randi                | 伽马分布 均匀分布整数                        |

* **repmat(A, num_copies_per_row, num_copies_per_col )**
  * 通过以块状方式复制矩阵*A*来生成矩阵
  * 2，3参数为复制的倍数

## 矩阵常用函数

### 转换，行列式，cumsum

* **conv_to< type >::from( X )**

* det：行列式
* cumsum: 向量累积矩阵

### find,rank

- find(x); find(x, k); find(X, k, s)
  - 返回包含*X*非零或满足关系条件的元素的索引的列向量
  - *X*被解释为向量，对*X*的元素进行逐列排序
  - 可以使用关系运算符代替*X*，例如。 *A > 0.5*
  - 如果*k=0*（默认），则返回所有非零元素的索引，否则最多返回其索引中的*k 个*
  - 如果*s="first"*（默认），最多返回非零元素的前*k 个*索引
  - 如果*s="last"*，则最多返回非零元素的最后*k 个*索引
- **find_finite( X )**: 
  - 返回包含*X*元素索引的列向量，这些元素是有限的（即不是 ±Inf 也不是 NaN)
- **find_nonfinite( X )**
  - 返回包含*X*非有限元素索引的列向量（即 ±Inf 或 NaN）
- **find_unique( X )， find_unique( X, Ascending_indices )** 
  - 返回包含*X*唯一元素索引的列向量
  - 该*ascending_indices*参数是可选的; 它是以下之一：
    - true = 返回索引是升序的（默认）
    - false= 返回的索引是随机的（速度快）
- rank 返回秩， 第二个参数接受一个容差，小于容差的视为0

### sort，sort_index

​	

```c++
sort( V )
sort( V, sort_direction )
    
sort( X )
sort( X, sort_direction )
sort( X, sort_direction, dim )
    
sort_index( X )
sort_index( X, sort_direction )

stable_sort_index( X )
stable_sort_index( X, sort_direction )
```

- **sort**
- 对于向量*V*，返回一个向量，它是输入向量的排序版本
- 对于矩阵*X*，返回一个矩阵，其中输入矩阵的元素按每列 ( *dim=0* ) 或每行 ( *dim=1* )排序
- dim是可选的; 默认*dim= 0*使用
-  *sort_direction*是`"ascend"`或`"descend"`；默认`"ascend"`使用

* **sort_index**
* 返回一个描述*X*元素排序顺序的向量 （即它包含*X*元素的索引）
* 输出向量必须具有[uvec](http://arma.sourceforge.net/docs.html#Col)类型 （即索引存储为[uword](http://arma.sourceforge.net/docs.html#uword)类型的无符号整数）
* *X*被解释为向量，对*X*的元素进行逐列排序
* 所述*stable_sort_index（）*的变体保留了与等效值的元素的相对顺序

### min,max

* 返回最值，有成员函数版和函数版
* index_min, 返回索引

### normalise, intersect

* **normalise( V )， normalise( V, p )**： vector版本, 默认p=2
* **normalise( X )，normalise( X, p )，normalise( X, p, dim )**：mat版本
  * 对于向量*V*，返回其归一化版本
  * 对于矩阵*X*，返回其标准化版本，其中每一列（*dim=0*）或行（*dim=1*）已标准化为具有单位
  * **向量的n范数：sqrt(sum(v^n)): 向量的n次方求和再开方，即距离**
  * **归一化：向量的每个元素除以n范数，n默认为2**



### shuffle，折叠

* **shuffle( V )，shuffle( X )，shuffle( X, dim )**
  * 对于向量*V*，生成一个元素打乱的向量副本
  * 对于矩阵*X*，生成矩阵的副本，其中元素在每列 ( *dim=0* ) 或每行 ( *dim=1* ) 中 混洗，默认dim=0

- .as_col：将矩阵的扁平版本作为列向量返回；展平是通过连接所有列来完成的
- *.as_row()*：将矩阵的扁平版本作为行向量返回；扁平化是通过连接所有行来完成的
- **警告：**连接列比连接行快
- **vectorise( X ), vectorise( X, dim )**
  - dim=0, 列方向复制
  - dim=1，行方向



## 矩阵运算操作



## 矩阵数学函数

| `exp(A)`       | 基数 e 指数：*e x*                                           |
| -------------- | ------------------------------------------------------------ |
| `exp2(A)`      | base-2 指数：*2 x*                                           |
| `exp10(A)`     | base-10 指数：*10 x*                                         |
| `expm1(A)`     | `exp(A)-1`准确 计算A 接近零的值  （仅适用于*float*和*double*元素） |
| `trunc_exp(A)` | base-e 指数，截断以避免无穷大  （仅适用于*float*和*double*元素） |
| `log(A)`       | 自然对数：*log e x*                                          |
| `log2(A)`      | base-2 对数                                                  |
| `log10(A)`     | base-10 对数                                                 |
| `log1p(A)`     | `log(1+A)`准确 计算A 接近零的值  （仅适用于*float*和*double*元素） |
| `trunc_log(A)` | 自然对数，截断以避免±无穷大  （仅适用于*浮点*和*双*元素）    |
| `pow(A, p)`    | 提高到 p 的幂：*x p*                                         |
| `square(A)`    | 正方形：*x 2*                                                |
| `sqrt(A)`      | 平方根：*x ½*                                                |
| `floor(A)`     | 不大于输入值的最大整数值                                     |
| `ceil(A)`      | 不小于输入值的最小积分值                                     |
| `round(A)`     | 舍入到最接近的整数，中途情况从零舍入                         |
| `trunc(A)`     | 四舍五入到最接近的整数，向零                                 |
| `erf(A)`       | 错误函数  （仅适用于*float*和*double*元素）                  |
| `erfc(A)`      | 互补误差函数  （仅适用于*float*和*double*元素）              |
| `tgamma(A)`    | gamma 函数  （仅用于*float*和*double*元素）                  |
| `lgamma(A)`    | gamma 函数绝对值的自然对数  （仅适用于*float*和*double*元素  |
|sign(A)|  符号函数，-1，0，1|
* 三角函数：sin，asin，sinh，asinh，sinc=sin（pi * x）
  * cos，tan
* abs

- 统计函数：sum，min，max，median，mean，stddev，var，cov，cor，hist，quantile（分位数），range（最大和最小之间的差）

## 检查操作

* in_range: 检查是否在范围内

```c++
mat A(4, 5, fill::randu); 

cout << A.in_range(0,0) << endl; // true 
cout << A.in_range(3,4) << endl; // true 
cout << A.in_range(4,5) << endl; // 错误的
```

| func                                                         | notes                  |
| ------------------------------------------------------------ | ---------------------- |
| **.is_empty()**                                              | 判断空                 |
| .is_vec is_colvec is_rowvec                                  | 判断是否为对应的向量   |
| is_sorted()；is_sorted( sort_direction )；is_sorted( sort_direction, dim ) | 判断是否有序           |
| .is_trimatu()；.is_trimatl()                                 | 上三角，下三角         |
| **.is_diagmat()**                                            | 对角矩阵               |
| **is_square()**                                              | 方阵                   |
| **.is_symmetric()**                                          | 对称矩阵               |
| **.is_zero(tor=0)**                                          | 0矩阵，tor可以设置阈值 |
| **.is_finite()**                                             | 所有元素都是有限的     |
| **.has_inf()**                                               | 至少一个元素是inf      |
| **.has_nan()**                                               | 至少一个是nan          |



## 科学计算常数

- 常量存储在*Datum<type>*类中，其中*type*是*float*或*double*；
- 为方便起见， *Datum<double>*被定义为*datum*， *Datum<float>*被定义为*fdatum*
- 常用的常数
  - pi, inf, nan, e, sqrt2. sqrt2pi  
  - G（牛顿万有引力常量）

## 计时器

**wall_clock**

```c++
wall_clock timer;

mat A(100, 100, fill::randu);
mat B(100, 100, fill::randu);
mat C;

timer.tic();

for(uword i=0; i<100000; ++i)
  {
  C = A + B + A + B;
  }

double n = timer.toc();

cout << "number of seconds: " << n << endl;
```

										  