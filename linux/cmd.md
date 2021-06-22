### xxd

| 参数           | 描述                              |
| -------------- | --------------------------------- |
| -a             | 自动跳过空行，默认关闭            |
| -b             | 二进制代替16进制                  |
| -c cols        | 按cols byte每行显示,默认16        |
| -g bytes       | 按bytes字节隔开                   |
| -l num         | 显示num字节停止                   |
| -s [+][-] seek | 偏移seek字节                      |
| -u             | 使用大写字符显示输出信息,默认小写 |

### 1.4 格式化U盘

```shell
sudo fdisk /dev/sdb #删除卷，新建卷
~d
~n
~p
sudo mkfs.ntfs /dev/sdb1 #格式化文件系统
#or
sudo mkfs.ext4 /dev/sdb1 #格式化文件系统
sudo chown your_uname /run/media/your_uname/dev_name #设置权限
e2label /dev/sdb1 "rename dev" #重命名卷名

```

 

## 1. pacman 学习

### 1. 参数基本含义

| 参数        |      |
| ----------- | ---- |
| -R   (删除) |      |
| -Q  (查询)  |      |
| -S   (安装) |      |



```bash
pacman -S [filename]
pacman -Sy #更新软件库
pacman -Syy #强制
pacman -Su [filename] #更新一个软件
pacman -Syu #更新软件源并更新软件
pacman -Syyu #强制
pacman -Ss [filename] #查询一个软件
pacman -Sc #清除缓存软件包
pacman -R [filename] #删除
pacman -Rs [filename] #删除软件并删除依赖
pacman -Rns [filename] #并删除全局配置文件 检验使用
pacman -Q #查询本地软件
pacman -Q | wc -l #统计多少软件包
pacman -Qe #自己安装的软件包
pacman -Qeq #不显示版本号
pacman -Qdt #查询孤儿依赖软件
sudo pacman  -R $(pacman -Qdtq)
pacman -U #安装本地软件
pacman -Sw #只下载不安装 

pacman 配置文件 /etc/pacman.conf
Color #打开彩色
[archlinuxcn]#软件源
Server= 
```

* pacman手动安装一个例子

~~~bash
git clone https://aur.archlinux.org/ranger-git.git
makepkg
sudo pacman -U ranger-git
~~~

* pacman Key

```shell
#先拷贝一下
sudo rm -R  /etc/pacman.d/gnupg/      # 删除gnupg目录及其文件
sudo pacman-key --init
sudo pacman-key --populate archlinux
sudo pacman-key --populate archlinuxcn    # 启用了archlinux中文软件库的还要执行这个

```

## 2.xxd

## 2020年 03月 07日 星期六 13:24:05 CST** 

| 参数           | 描述                              |
| -------------- | --------------------------------- |
| -a             | 自动跳过空行，默认关闭            |
| -b             | 二进制代替16进制                  |
| -c cols        | 按cols byte每行显示,默认16        |
| -g bytes       | 按bytes字节隔开                   |
| -l num         | 显示num字节停止                   |
| -s [+][-] seek | 偏移seek字节                      |
| -u             | 使用大写字符显示输出信息,默认小写 |

## 3. fdisk 

### 格式化U盘

```bash
sudo fdisk /dev/sdb #删除卷，新建卷
~d
~n
~p
sudo mkfs.ntfs /dev/sdb1 #格式化文件系统
#or
sudo mkfs.ext4 /dev/sdb1 #格式化文件系统
sudo chown your_uname /run/media/your_uname/dev_name #设置权限
e2label /dev/sdb1 "rename dev" #重命名卷名

```

##  4. tar 压缩和解压

* 单个文件压缩打包 tar czvf my.tar file1
* 多个文件压缩打包 tar czvf my.tar file1 file2,...
* 单个目录压缩打包 tar czvf my.tar dir1
* 多个目录压缩打包 tar czvf my.tar dir1 dir2
* 解包至当前目录：tar xzvf my.tar



### data：2020-4-4

## 5. ln

*  软连接和硬链接

```bash
ln -s [source] [deter] #软链接
ln [source] [deter] #硬链接
```

## 6. find

* find path -option [ -print] [-exec ] {}\;

* 常用参数
  * -amin n:n分钟内被读过
  * -atime n:过去几天被读取过
  * -cmin n:过去几分钟被修改过
  * -ctime
  * -name :名字符合name的文件
  * -size n:文件大小
* 例子

```bash
find /home/zw/ -name "*.c" #在/home/zw下找到以.c结尾的文件
find /home/zw -name "*c" -type d #找目录
find /home/zw/learn/oslearn/5 -name "*.c" -atime +8
find /home/zw/learn/oslearn/5/i/ *.c -atime +3 -exec cp -r {} ./ \;
find /home/zw/learn/oslearn/5/i/ *.c -size +10k #文件大于10k
find /home/zw/learn/oslearn/5/i/ *.c -perm 644 #权限644

find -name "*.exe"  -type f -exec rm -rf {} \; #删除当前目录下所有exe文件
find c_cpp/Design_Patterns/ -regextype posix-egrep -regex ".*\.c(pp)?" #正则表达式
```

## 7. grep

* 语法  

```
  grep [-abcEFGhHilLnqrsvVwxy][-A<显示列数>][-B<显示列数>][-C<显示列数>][-d<进行动作>][-e<范本样式>][-f<范本文件>][--help][范本样式][文件或目录...]
```

  

* 参数

  * -a or --text ：不要忽略二进制数据
  * -c：显示找到的行数
  * -i：忽略大小写
  * -n：顺便输出行号
  * -v：反向选择
  * -h：查找多文件不显示文件名
  * -l：多文件只输出有匹配的文件名
  * -E：允许使用扩展

```bash
grep "[0-9]" fat12hdr.inc
grep -E "[0-9]{2}" fat12hdr.inc
```



## 8. awk

* [参考](https://awk.readthedocs.io/en/latest/chapter-one.html)

* emp.data

```txt
Beth    4.00    0
Dan     3.75    0
kathy   4.00    10
Mark    5.00    20
Mary    5.50    22
Susie   4.25    18
```

```bash
awk  '{print}' emp.data #打印每一行
awk '{print NF,$1,$3}' emp.data #每一行的条目数
awk '$3 > 0 {print $1,"\t" ,$2 * $3}' emp.data #计算并打印
awk '{print NR,$1}' emp.data #打印行号
awk '{print "total pay for",$1,"is",$2*$3}' emp.data #穿插你想要打印字符串
#使用printf格式化你的输出
awk '{ printf("total pay for %s is $%.2f\n", $1, $2 * $3) }' emp.data
#排序
awk '{ printf("%6.2f    %s\n", $2 * $3, $0) }' emp.data | sort
awk '$1 == "Susie" {print}' emp.data #匹配susie
awk ' $2 >= 4 || $3 >= 20 ' emp.data #或
#BEGIN输出一个表头，END，则表尾
wk 'BEGIN { print "Name    RATE    HOURS"; print ""}  {print}' emp.data
#计数
 awk '$3 > 15 {emp=emp+1} END {print "emp =",emp}' emp.data 
#平均值
awk ' {pay=pay+$2 * $3} END {print "average :", pay/NR}' emp.data 
#找到最大值
awk ' $2 > maxrate { maxrate = $2; maxemp = $1 } END { print "highest hourly rate:", maxrate, "for", maxemp }' emp.data 
awk '{name=name $1 " "} END{ print name}' emp.data #字符串拼接

awk `$2 > 6 { n = n + 1; pay = pay + $2 * $3 }\
END    { if (n > 0)\
            print n, "employees, total pay is", pay,\
                     "average pay is", pay/n\
         else\
             print "no employees are paid more than $6/hour"\
        }` emp.data
```
