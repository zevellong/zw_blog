# 机器学习-Andrew Ng

## 导论

- 机器学习：

  - 计算机从经验E学习，解决某一项任务P，进行某一性能度量P，通过P测定在T的表现**因经验E**而提高

- 监督学习

  - 回归问题、分类问题
  - 对于数据集的每个样本，我们通过算法预测，得到“正确答案“

- 无监督学习

  - 事先不知道正确答案
  - 聚类问题，


## 线性回归

- 线性函数：(hypothesis)    引用请使用$\ref{func1}$
  $$
  h(x) = \theta_0 + \theta_1 *  x \label{func1}
  $$
  
- 代价函数：(cost function)  平方损失函数
  $$
  J({\theta_0,\theta_1}) = \frac{1}{2m}\sum_{i=1}^m((h(x^{(i)}) - y^{(i)})^2)
  $$

- 目标：（Goal）
  $$
  \min_{\theta0,\theta1}\, J(\theta_0, \theta_1)
  $$

- 梯度下降算法

  - 找出$J(\theta_0, \theta_1)$的最小值
  - **step：**
  - 给$\theta_0,\theta_1$初值，通常设置为0
  - 改变$\theta_0,\theta_1$的值，来减少$J$
  - 直到找到一个最小的值
  - 梯度下降描述:($\alpha$是学习率，控制梯度下降的步长)

$$
\theta_j := \theta_j-\alpha\dfrac{\partial}{\partial \theta_J}J(\theta_0,\theta_1) \qquad (for j=0\; and\;j=1)
$$

   上述相当于：（错误的：没有同步）
$$
temp0 := \theta_0 -\alpha\dfrac{\partial}{\partial \theta_0}J(\theta_0,\theta_1) \\
temp1 := \theta_1 -\alpha\dfrac{\partial}{\partial \theta_1}J(\theta_0,\theta_1) \\
\theta_0 := temp0  \\
\theta_1 := temp1
$$
上述相当于：（正确的）
$$
temp0 := \theta_0 -\alpha\dfrac{\partial}{\partial \theta_0}J(\theta_0,\theta_1) \\
\theta_0 := temp0  \\
temp1 := \theta_1 -\alpha\dfrac{\partial}{\partial \theta_1}J(\theta_0,\theta_1) \\
\theta_1 := temp1
$$
推导：
$$
\theta_0:=\theta_0-\alpha\frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)} \\
\theta_1:=\theta_1-\alpha\frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)}).x^{(i)} \\
$$

### typora矩阵和向量

$$
\begin{pmatrix}
	a & b \\
	c & d \\
	e & f
\end{pmatrix}  \quad
\begin{bmatrix}
	a & b \\
	c & d
\end{bmatrix}
$$

### 多元情况

Hypothesis:
$$
h_\theta(x)=\theta_0+\theta_1 * x_1 + \theta_2 * x_2 + \theta_3 * x_3 + \theta_4 * x_4
$$
向量形式：
$$
h_\theta(x)=\theta^T.X \\
X = \begin{bmatrix}
	x_0 \\
	x_1 \\
	\dots \\
	x_n
\end{bmatrix} \qquad
\theta = \begin{bmatrix}
	\theta_0 \\
	\theta_1 \\
	\dots \\
	\theta_n
\end{bmatrix}
$$
代价函数：
$$
J(\theta_0,\theta_1,\dots,\theta_n)=\frac{1}{2m}\sum_{i=1}^{m}(h_\theta(x_i) - y_i)^2
$$
梯度下降：
$$
\theta_j:=\theta_j-\alpha J(\theta_0,\theta_1,\dots,\theta_n) \qquad for(j=0,1,\dots,n)
$$

$$
\theta_j:=\theta_j-\alpha\frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)}x_{j}^{(i)})
$$

$$
\theta_0:=\theta_0-\alpha\frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)})x_{0}^{(i)}\quad (x_0^{(i)}=1)\\
\theta_1:=\theta_1-\alpha\frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)})x_{1}^{(i)} \\
\theta_2:=\theta_2-\alpha\frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)})x_{2}^{(i)} \\
\dots
$$

正规方程：
$$
\theta=(X^TX)^{-1}X^Ty \\
Octave: pinv(x'*x)*x'*y
$$

* 梯度下降法优点缺点：
  * 需要$\alpha$(学习率)
  * 需要多次迭代
  * 优点：n特别大，也能正常计算
* 正规方法：无上述缺点
  * 非常慢，如果n特别大
  * 矩阵运算时间接近复杂度n3
  * 矩阵小计算快，简洁



## Logistic 回归

* 问题的引入， 分类问题：
  * Email：是否是 垃圾邮件
  * 在线交易：是否是 诈骗
  * 肿瘤：良性阴性
* 二元分类描述

$$
y\in\{0, 1\}  \\
0: Negative\;Class \\
1: Positive\;Class
$$



* 多元分类 $y\in\{0, 1, 2, 3\}$
* output

$$
If \quad h_\theta(x) \geq 0.5, predict\quad"y=1" \\
If \quad h_\theta(x)<0.5, predict\quad"y=0"
$$



* logistic Regression: 

$$
0 \le h_\theta(x) \le 1
$$

*  Hypothesis

$$
h_\theta(x) = sigmoid(\theta^Tx) \\
sigmoid(z) = \frac{1}{1+e^{-z}} \\
h_\theta(x) = \frac{1}{1+e^{-\theta^Tx}}
$$

```gnuplot
plot (1/(1+exp(-x)))
```

- example:


$$
If\quad x = \begin{bmatrix}
x_0 \\
x_1
\end{bmatrix} = 
 \begin{bmatrix}
1 \\
tumorSize
\end{bmatrix} \\
h_\theta(x) = 0.7 \\
$$

* 这预示了70%的概率有恶性 $h_\theta(x)=P(y=1|x;\theta)=0.7$

### 决策界限

* 如果 $h_\theta(x)\ge 0.5$ ，预测y=1
* 反之，y = 0
* 又由sigmoid函数的性质
  * 只需判断 $\theta^Tx\ge0$ 

- set： $\{(x^{(1)}, y^{(1)}),(x^{(2)}, y^{(2)}), \dots, (x^{(m)}, y^{(m)})\}$

$$
x\in\begin{bmatrix}
x_0 \\
x_1 \\
\dots \\
x_m \\
\end{bmatrix},\qquad x_0=1,y\in\{0,1\} \\
h_\theta(x) = \frac{1}{1+e^{-\theta^Tx}}
$$

- cost函数

$$
J(\theta) = \frac{1}{m}\sum_{i=1}^{m}cost(h_\theta(x), y) \\

\begin{equation}
cost(h_\theta(x), y) =\left\{
\begin{aligned}
-log(h_\theta(x))\qquad if\;y=1 \\
-log(1 - h_\theta(x))\qquad if\;y=0
\end{aligned}
\right.
\end{equation}
$$

* 简化的cost

$$
cost(h_\theta(x), y) = -ylog(h_\theta(x))-(1-y)log(1 - h_\theta(x))
$$

- 优化目标

$$
\min_\theta\,J(\theta)
$$

- 梯度下降

$$
\theta_j:=\theta_j-\alpha\frac{\partial}{\partial\theta_j}J(\theta) \\
\theta_j:=\theta_j-\alpha\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)})x_j^{(i)}
$$

### 过拟合问题

* 减少维度
* 正则化
  * 高阶惩罚系数 加入cost
  * 梯度
  * 正规方程： 对角线第一个元素0，对角线其他元素1，其他元素全0

$$
J(\theta_0,\theta_1,\dots,\theta_n)=\frac{1}{2m}\left[\sum_{i=1}^{m}(h_\theta(x_i) - y_i)^2 + \lambda\sum_{j=1}^{n}\theta_j^2\right]
$$


$$
\theta_j:=\theta_j-\alpha\left[\frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)}x_{j}^{(i)}) + \frac{\lambda}{m}\theta_j\right] \\
\theta_j:=\theta_j(1-\alpha\frac{\lambda}{m})-\alpha\frac{1}{m}\sum_{i=1}^{m}(h_\theta(x^{(i)})-y^{(i)}x_{j}^{(i)}) \\
$$

$$
\theta = (X^TX +  \alpha\begin{bmatrix} 
0 & & & & \\
 & 1 & & & \\
 &  &  1& & \\
 &  & & \ddots&  \\
 &  & & &  1\\
\end{bmatrix})^{-1}X^Ty
$$



### 牛顿法

* 迭代公式即其矩阵形式

$$
\theta := \theta - \frac{J'(\theta)}{J''(\theta)} \\
\theta := \theta - H^{-1}\nabla
$$

* 梯度矩阵

$$
\nabla_i=\sum_{i=1}^{m}(y^{(i)} - h_\theta(x^{(i)}))x_j^{(i)}
$$

* Hessian Matrix

$$
\begin{align}
H_{ij}& = \frac{\partial^2l(\theta)}{\partial\theta_i\partial\theta_j}\\
& =\frac{1}{m} \frac{\partial}{\theta_j}\sum_{t=1}^m(y^{(t)}-h_\theta(x^{(t)}))x_i^{(t)}\\
& = \frac{1}{m} \sum_{t=1}^m \frac{\partial}{\theta_j} (y^{(t)}-h_\theta(x^{(t)}))x_i^{(t)}\\
& = \frac{1}{m} \sum_{t=1}^m -x_i^{(t)} \frac{\partial }{\partial \theta_j}h_\theta(x^{(t)})\\
& = \frac{1}{m} \sum_{t=1}^m -x_i^{(t)} h_\theta(x^{(i)}) (1-h_\theta(x^{(i)})) \frac{\partial}{\theta_j}(\theta^Tx^{(t)} )\\
&=\frac{1}{m} \sum_{t=1}^m h_\theta(x^{(t)})(h_\theta(x^{(t)})-1)x^{(t)}_ix^{(t)}_j\\
\end{align}
$$

* 正则化后

$$
cost(h_\theta(x), y) = -ylog(h_\theta(x))-(1-y)log(1 - h_\theta(x)) + \frac{\lambda}{2m}\sum_{j=1}{n}\theta_j^2
$$

$$
\nabla_i=\sum_{i=1}^{m}(y^{(i)} - h_\theta(x^{(i)}))x_j^{(i)}+\frac{\lambda}{m}\theta_j \quad for\; j\ge1
$$

$$
H_{ij}=\frac{1}{m} \sum_{t=1}^m h_\theta(x^{(t)})(h_\theta(x^{(t)})-1)x^{(t)}_ix^{(t)}_j + \frac{\lambda}{m}
$$



## 神经网络

* 引入，logistic回归当输入的特征n很大时，组合的多项式项讲爆炸式增长

* 起源：模仿人类大脑行为

* 结构

  * 输入层，输出层，隐藏层
  * $a_i^{(j)}$ :第j层的第i个神经元的激活函数
  * $\theta^{(j)}$: 第j层的权重矩阵

  $$
  \begin{align}
  a_1^{(2)} =& g(\theta_{10}^{(1)}x_0 + \theta_{11}^{(1)}x_1 + \theta_{12}^{(1)}x_2 + \theta_{13}^{(1)}x_3 ) \\
  a_2^{(2)} = &g(\theta_{20}^{(1)}x_0 + \theta_{21}^{(1)}x_1 + \theta_{22}^{(1)}x_2 + \theta_{23}^{(1)}x_3 ) \\
  a_3^{(2)} =&g(\theta_{30}^{(1)}x_0 + \theta_{31}^{(1)}x_1 + \theta_{32}^{(1)}x_2 + \theta_{33}^{(1)}x_3 ) \\
  h_\theta(x) =& a_1^{(3)} = g(\theta_{10}^{(2)}a_0^{(2)} + \theta_{11}^{(2)}a_1^{(2)} +\theta_{12}^{(2)}a_2^{(2)} + \theta_{13}^{(2)}a_3^{(2)})
  \end{align}
  $$

  

* 向量化

$$
z_i^{(j)} = \theta_{i0}^{(j-1)}x_0 + \theta_{i1}^{(j-1)}x_1 + \theta_{i2}^{(j-1)}x_2 + \theta_{i3}^{(j-1)}x_3 \\
a_i^{j} = g(z_i^{(j)}) \\
x = \begin{bmatrix}
x_0 \\ x_1 \\ x_2 \\ x_3
\end{bmatrix} \qquad
z^{(j)} =  \begin{bmatrix}
z_0^{(j)} \\ z_1^{(j)} \\ z_2^{(j)} \\ z_3^{(j)}
\end{bmatrix} \\

z^{(2)} = \theta^{(1)}a^{(1)} \\
a^{(2)} = g(z^{(2)})
$$

*  cost 函数

* L：表示总共的层数； $S_l$：第l层的神经元树

$$
h_\theta(x)\in R^k \qquad (h_\theta(x))_i=i^{(th)} \; output \\
J(\theta) = -\frac{1}{m}\left[\sum_{i=1}^{m}\sum_{k=1}^{K}y_k^{(i)}log(h_\theta(x^{(i)}))_k+(1-y_k^{(i)})log(1-(h_\theta(x^{(i)}))_k)\right] \\+ \frac{\lambda}{2m}\sum_{l=1}^{L-1}\sum_{i=1}^{s_l}\sum_{j=1}^{s_l+1}(\theta_{ji}^{(l)})^2
$$



* 梯度
  * $\delta_j^{(l)}$: 第l层的第j个神经元的"error"
  * $\delta_j^{(4)}=a_{j}^{(4)}-y_j$
  * $\delta_j^{(3)}=((\theta^{(3)})^T\delta^{(4)}).*g'(z^{(3)})$   $g' = a^{(3)}(1-a^{(3)})$
  * $\delta_j^{(2)}=((\theta^{(2)})^T\delta^{(3)}).*g'(z^{(2)})$   $g' = a^{(2)}(1-a^{(2)})$
  * 输入层无误差

* pipeline
  * 选择神经网络的结构
    * 输入，输出，隐藏神经元要大于输入层
  * 初始化权重theta
  * 前向传播 $h_\theta(x)$
  * cost function $J_\theta()$
  * 反向传播计算 $\frac{\partial}{\partial\theta}J(\theta)$
  * 数值方法计算梯度，与上一步的比较；验证没有问题后删除这一步
  * 用优化方法优化theta（梯度下降，牛顿法）



## 模型评价

* 数据分成两组，4/5用于训练
* 模型的选择问题
  * 训练集合，交叉验证，测试集合
  * 训练theta，交叉验证多项式阶数d，测试误差
* 学习曲线



| 高方差       | 高偏差     |
| ------------ | ---------- |
| 增加训练样本 | 增加特征   |
| 减少特征     | 多项式     |
| 增加lambda   | 减小lambda |
|              |            |



## SVM

- hypothesis

$$
\min_\theta C\sum_{i=1}^{m}\left[y^{(i)}cost_1(\theta^TX^{(i)}) + (1-y)cost_0(\theta^TX^{(i)}) \right] + \frac{1}{2}\sum_{i=1}^{n}\theta_j^2 \\
\begin{equation}
h_\theta(x)=\left\{
\begin{aligned}
1\quad if\,\theta^TX\ge0 \\
0\quad otherwise 
\end{aligned}
\right.
\end{equation}
$$







## K-means算法

- 算法步骤：
  - 随机生成K个聚类中心， $\mu_1, \mu_2, \dots, \mu_K \in R^n$​
  - 重复以下直到收敛：
  - for i = 1:m 
    - $c^{(u)}:=$最接近的聚类中心的下标
  - for k = 1:K
    - $\mu_k:=$​当前这个簇的中心点
  - 如果某个聚类中心没有任何点，移出这个中心
- 优化目标：

$$
J(c^{(1)},\dots,c^{(m)}, \mu_1,\dots,\mu_K)=\frac{1}{m}\sum_{i=1}^{m}||x^{(i)} - \mu_{c^{(i)}}||^2 \\
\min_{c^{(1)},\dots,c^{(m)}, \mu_1,\dots,\mu_K} J(c^{(1)},\dots,c^{(m)}, \mu_1,\dots,\mu_K)
$$

- 初始化：运行50到1000次算法，选取代价最小的
- 选取聚类的数量：肘部法则，结合实际需要





## PCA





## 随机梯度下降算法
