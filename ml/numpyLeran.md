# 学习numpy

## MATLAB和numpy的一些差异

| MATLAB®                                                      | NumPy                                                        |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 在MATLAB®中，基本数据类型是**双精度浮点数的多维数组**。大多数表达式采用这样的数组并且也返回这样的数据类型，操作这些数组的2-D实例的的方式被设计成或多或少地像线性代数中的矩阵运算一样。 | 在NumPy中，基本类型是**多维`数组(array)`**。在所有维度(包括2D)上对这些数组的操作都是元素级的操作。对于线性代数，需要使用特定的函数（尽管对于矩阵乘法，可以在python 3.5及以上版本中使用`@`运算符）。 |
| MATLAB®是使用**基于1的索引**。 使用`a(1)`下标作为元素的初始位置。请参阅[备注](#备注) | Python使用**基于0的索引**。序列的初始元素使用`a[0]`来查找。  |
| MATLAB的脚本语言是为做线性代数而创建的。基本矩阵操作的语法很好也很简洁，但是用于添加GUI和制作成熟应用程序的API或多或少是事后才想到的。 | NumPy基于Python，它从一开始就被设计为一种优秀的通用编程语言。 虽然Matlab的一些数组操作的语法比NumPy更紧凑，但NumPy（由于是Python的附加组件）可以做许多Matlab所不能做的事情，例如正确处理矩阵的堆叠操作。 |
| 在 MATLAB® 中，数组具有按值传递的语义，采用延迟的“写时复制”(copy-on-write)模式，以防止在实际需要时创建副本。 |                                                              |
| 使用切片操作是复制数组的部分。                               | 在NumPy数组，在NumPy数组中按引用传递语义。切片操作是数组的视图。 |

## “array” 还是 “matrix”? 我应该选谁?

**使用 arrays.**

- 它们是numpy的标准向量/矩阵/张量类型。许多numpy函数返回的是数组，而不是矩阵。
- 元素级运算和线性代数运算之间有着明确的区别。
- 如果你愿意，可以使用标准向量或行/列向量。

| MATLAB                          | NumPy                                                        | 注释                                                         |
| ------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| ndims(a)                        | ndim(a) 或 a.ndim                                            | 获取数组的维数。                                             |
| numel(a)                        | size(a) 或 a.size                                            | 获取数组的元素个数。                                         |
| size(a)                         | shape(a) 或 a.shape                                          | 求矩阵的“大小”                                               |
| size(a,n)                       | a.shape[n-1]                                                 | 获取数组a的n维元素数量。(请注意，MATLAB使用基于1的索引，而Python使用基于0的索引，请参见注释索引)。 |
| [ 1 2 3; 4 5 6 ]                | array([[1.,2.,3.], [4.,5.,6.]])                              | 一个 2x3 矩阵的字面量。                                      |
| [ a b; c d ]                    | vstack([hstack([a,b]), hstack([c,d])]) 或 bmat('a b; c d').A | 从快a、b、c和d构造矩阵。                                     |
| a(end)                          | a[-1]                                                        | 访问1xn矩阵a中的最后一个元素。                               |
| a(2,5)                          | a[1,4]                                                       | 访问第二行，第五列中的元素。                                 |
| a(2,:)                          | a[1] 或 a[1,:]                                               | 取得a数组第二个元素全部（译者注：第二个元素如果是数组，则返回这个数组） |
| a(1:5,:)                        | a[0:5] 或 a[:5] 或 a[0:5,:]                                  | 取得a数组的前五行。                                          |
| a(end-4:end,:)                  | a[-5:]                                                       | 取得a数组的后五行。                                          |
| a(1:3,5:9)                      | a[0:3][:,4:9]                                                | a数组的第1行到第3行和第5到第9列，这种方式只允许读取。        |
| a([2,4,5],[1,3])                | a[ix_([1,3,4],[0,2])]                                        | 行2,4和5以及第1列和第3列。这允许修改矩阵，并且不需要常规切片方式。 |
| a(3:2:21,:)                     | a[ 2:21:2,:]                                                 | a数组每隔一行，从第三行开始，一直到第二十一行。              |
| a(1:2:end,:)                    | a[ ::2,:]                                                    | a数组从第一行开始，每隔一行。                                |
| a(end: -1:1,:) 或 flipud(a)     | a[ ::-1,:]                                                   | 反转a数组的顺序。                                            |
| a([1:end 1],:)                  | a[r_[:len(a),0]]                                             | 将a数组的第一行的副本添加到数组末尾。                        |
| a.'                             | a.transpose() 或 a.T                                         | a数组的转置。                                                |
| a'                              | a.conj().transpose() 或 a.conj().T                           | a数组的共轭转置。                                            |
| a * b                           | a.dot(b)                                                     | 矩阵乘法。                                                   |
| a .* b                          | a * b                                                        | 元素相乘。                                                   |
| a./b                            | a/b                                                          | 元素相除。                                                   |
| a.^3                            | a**3                                                         | 元素指数运算。                                               |
| (a>0.5)                         | (a>0.5)                                                      | 其i, th元素为(a_ij > 0.5)的矩阵。Matlab的结果是一个0和1的数组。NumPy结果是一个布尔值false和True的数组。 |
| find(a>0.5)                     | nonzero(a>0.5)                                               | 找到条件满足 (a > 0.5) 的索引。                              |
| a(:,find(v>0.5))                | a[:,nonzero(v>0.5)[0]]                                       | 找到满足条件 向量v > 0.5 的列。                              |
| a(:,find(v>0.5))                | a[:,v.T>0.5]                                                 | 找到满足条件 列向量v > 0.5 的列。                            |
| a(a<0.5)=0                      | a[a<0.5]=0                                                   | 元素小于0.5 赋为 0。                                         |
| a .* (a>0.5)                    | a * (a>0.5)                                                  | （译者注：应该是a乘上a中大于0.5的值的矩阵）                  |
| a(:) = 3                        | a[:] = 3                                                     | 将所有值设置为相同的标量值                                   |
| y=x                             | y = x.copy()                                                 | numpy 通过拷贝引用来赋值。                                   |
| y=x(2,:)                        | y = x[1,:].copy()                                            | numpy 通过拷贝引用来切片操作。                               |
| y=x(:)                          | y = x.flatten()                                              | 将数组转换为向量(请注意，这将强制拷贝)。                     |
| 1:10                            | arange(1.,11.) 或 r_[1.:11.] 或 r_[1:10:10j]                 | 创建一个可增长的向量 (参见下面的[备注](#备注)章节)           |
| 0:9                             | arange(10.) 或 r_[:10.] 或 r_[:9:10j]                        | 创建一个可增长的向量 (参见下面的[备注](#备注)章节)           |
| [1:10]'                         | arange(1.,11.)[:, newaxis]                                   | 创建一个列向量。                                             |
| zeros(3,4)                      | zeros((3,4))                                                 | 创建一个全是0的填充的 3x4 的64位浮点类型的二维数组。         |
| zeros(3,4,5)                    | zeros((3,4,5))                                               | 创建一个全是0的填充的 3x4x5 的64位浮点类型的三维数组。       |
| ones(3,4)                       | ones((3,4))                                                  | 创建一个全是 1 的填充的 3x4 的64位浮点类型的二维数组。       |
| eye(3)                          | eye(3)                                                       | 创建一个3x3恒等矩阵。                                        |
| diag(a)                         | diag(a)                                                      | 创建a数组的对角元素向量。                                    |
| diag(a,0)                       | diag(a,0)                                                    | 创建方形对角矩阵，其非零值是a的所有元素。                    |
| rand(3,4)                       | random.rand(3,4)                                             | 创建一个随机的 3x4 矩阵                                      |
| linspace(1,3,4)                 | linspace(1,3,4)                                              | 创建4个等间距的样本，介于1和3之间。                          |
| [x,y]=meshgrid(0:8,0:5)         | mgrid[0:9.,0:6.] 或 meshgrid(r_[0:9.],r_[0:6.]               | 两个2维数组：一个是x值，另一个是y值。                        |
| -                               | ogrid[0:9.,0:6.] 或 ix_(r_[0:9.],r_[0:6.]                    | 最好的方法是在一个网格上执行函数。                           |
| [x,y]=meshgrid([1,2,4],[2,4,5]) | meshgrid([1,2,4],[2,4,5])                                    | -                                                            |
| -                               | ix_([1,2,4],[2,4,5])                                         | 最好的方法是在网格上执行函数。                               |
| repmat(a, m, n)                 | tile(a, (m, n))                                              | 通过n份a的拷贝创建m。                                        |
| [a b]                           | concatenate((a,b),1) 或 hstack((a,b)) 或 column_stack((a,b)) or c_[a,b] | 连接a和b的列。                                               |
| [a; b]                          | concatenate((a,b)) 或 vstack((a,b)) 或 r_[a,b]               | 连接a和b的行。                                               |
| max(max(a))                     | a.max()                                                      | 取a数组的中的最大元素（对于matlab来说，ndims(a) <= 2）       |
| max(a)                          | a.max(0)                                                     | 求各列的最大值。                                             |
| max(a,[],2)                     | a.max(1)                                                     | 求各行最大值。                                               |
| max(a,b)                        | maximum(a, b)                                                | 比较a和b元素，并返回每对中的最大值。                         |
| norm(v)                         | sqrt(dot(v,v)) 或 np.linalg.norm(v)                          | 向量v的L2范数                                                |
| a & b                           | logical_and(a,b)                                             | 逐元素使用 AND 运算符 (NumPy ufunc) (参见下面的[注释](#note)章节) |
| a                               | b                                                            | logical_or(a,b)                                              |
| bitand(a,b)                     | a & b                                                        | 按位AND运算符 (Python原生 和 NumPy ufunc)                    |
| bitor(a,b)                      | a                                                            | b                                                            |
| inv(a)                          | linalg.inv(a)                                                | 矩阵a的逆运算                                                |
| pinv(a)                         | linalg.pinv(a)                                               | 矩阵a的反逆运算                                              |
| rank(a)                         | linalg.matrix_rank(a)                                        | 二维数组或者矩阵的矩阵rank。                                 |
| a\b                             | 如果a是方形矩阵 linalg.solve(a,b) ，否则：linalg.lstsq(a,b)  | 对于x，x = b的解                                             |
| b/a                             | Solve a.T x.T = b.T instead                                  | 对于x，x a = b的解                                           |
| [U,S,V]=svd(a)                  | U, S, Vh = linalg.svd(a), V = Vh.T                           | a数组的奇值分解                                              |
| chol(a)                         | linalg.cholesky(a).T                                         | 矩阵的cholesky分解（matlab中的chol(a)返回一个上三角矩阵，但linalg.cholesky(a)返回一个下三角矩阵） |
| [V,D]=eig(a)                    | D,V = linalg.eig(a)                                          | a数组的特征值和特征向量                                      |
| [V,D]=eig(a,b)                  | V,D = np.linalg.eig(a,b)                                     | a，b数组的特征值和特征向量                                   |
| [V,D]=eigs(a,k)                 | -                                                            | 找到a的k个最大特征值和特征向量                               |
| [Q,R,P]=qr(a,0)                 | Q,R = scipy.linalg.qr(a)                                     | Q，R 的分解                                                  |
| [L,U,P]=lu(a)                   | L,U = scipy.linalg.lu(a) or LU,P=scipy.linalg.lu_factor(a)   | LU 分解 (注意: P(Matlab) == transpose(P(numpy)) )            |
| conjgrad                        | scipy.sparse.linalg.cg                                       | 共轭渐变求解器                                               |
| fft(a)                          | fft(a)                                                       | a数组的傅立叶变换                                            |
| ifft(a)                         | ifft(a)                                                      | a的逆逆傅里叶变换                                            |
| sort(a)                         | sort(a) or a.sort()                                          | 对矩阵或者数组进行排序                                       |
| [b,I] = sortrows(a,i)           | I = argsort(a[:,i]), b=a[I,:]                                | 对矩阵或数组的行进行排序                                     |
| regress(y,X)                    | linalg.lstsq(X,y)                                            | 多线性回归                                                   |
| decimate(x, q)                  | scipy.signal.resample(x, len(x)/q)                           | 采用低通滤波的下采样                                         |
| unique(a)                       | unique(a)                                                    | -                                                            |
| squeeze(a)                      | a.squeeze()                                                  | -                                                            |



### 读写文本文件

1. `np.savetxt(fname,array,fmt='%.18e',delimiter=None)`

frame : 文件、字符串或产生器,可以是.gz 或.bz2的压缩文件

array : 存入文件的数组

fmt : 写入文件的格式,例如：%d %.2f %.18e

delimiter :分割字符串,默认是任何空格。

```
 a = np.arange(100).reshape(5,20)
np.savetxt('a.csv',a,fmt='%d',delimiter=',')
```

1. `np.loadtxt(fname,dtype=np.float,delimiter=None,unpack=False)`

frame : 文件、字符串或产生器,可以是.gz 或.bz2的压缩文件

dtype : 数据类型,可选

delimiter :分割字符串,默认是任何空格。

unpack :读入数据写入一个数组 如果是True,读入属性将分别写入不同变量

例如

```
b = np.loadtxt('a.csv',delimiter=',')
b = np.loadtxt('a.csv',dtype = np.int,delimiter=',')
```