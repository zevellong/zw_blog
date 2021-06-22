# MySql

[初始化见](https://blog.csdn.net/weixin_42413447/article/details/113233935)

```shell
mysqld --initialize --console #初始化
mysqld install #安装
net start mysql #启动
mysql -u root -p #登录
alter user root@localhost identified by '123'; #修改密码


# manjaro 下初始化
sudo pacman -S mysql 
sudo mysqld --initialize --user=mysql --basedir=/usr --datadir=/var/lib/mysql #初始化
sudo systemctl start mysqld
#or
sudo systemctl enable mysqld
```

- 创建数据库和表

```mysql
create database db_name;
create TABLE Student(sid char(8) not null, Sname char(10), Ssex char(2), Sage integer, Did char(2), Sclass char(6), PRIMARY key(SID)) ENGINE=InnoDB;

create TABLE Course(Cid char(3) not null, Cname char(12), Chours integer, Credit float(1),Tid char(3), PRIMARY key(Cid)) ENGINE=InnoDB;

create TABLE Dept(Did char(2) not null, Dname char(10), Dean char(10), PRIMARY key(Did)) ENGINE=InnoDB;

create TABLE Teacher(Tid char(3) not null, Tname char(10), Did char(2), Salary float(2), PRIMARY key(Tid)) ENGINE=InnoDB;

create TABLE Sc(Sid char(8) not null, Cid char(3), Score float(1)) ENGINE=InnoDB;
desc Student; #查看表结构
```

* 插入数据

```mysql
	insert into Student values(
        '98030101',
        '张三',
        '男', 
        20, 
        '03',
        '980301'
    	);
    insert into Student values(
        '98030102',
        '张四',
        '女', 
        20, 
        '03',
        '980301'
    	);
   insert into Student values(
        '98030103',
        '张五',
        '男', 
        19, 
        '03',
        '980301'
    	);
   	insert into Student values(
        '98040201',
        '王三',
        '男', 
        20, 
        '04',
        '980402'
    	);
    insert into Student values(
        '98040202',
        '王四',
        '男', 
        21, 
        '04',
        '980402'
    	);
   insert into Student values(
        '98040203',
        '王五',
        '女', 
        19, 
        '04',
        '980402'
    	);
    	
    insert into Course values(
    	'001',
        '数据库',
        40,
        6,
        '001'
    );
    insert into Course values(
    	'002',
        '数据结构',
        40,
        6,
        '003'
    );
    insert into Course values(
    	'003',
        '编译原理',
        40,
        6,
        '001'
    );
    insert into Course values(
    	'004',
        'C语言',
        30,
        4.5,
        '003'
    );
    insert into Course values(
    	'005',
        '高等数学',
        80,
        12,
        '004'
    );
    
    insert into Dept values(
    	'01',
        '机电',
    	'李三'
    );
    insert into Dept values(
    	'02',
        '能源',
    	'李四'
    );
    insert into Dept values(
    	'03',
        '计算机',
    	'李五'
    );
    insert into Dept values(
    	'04',
        '自动控制',
    	'李六'
    );
    
    insert into Teacher values(
    	'001',
        '赵三',
    	'01',
        1200.00
    );
    insert into Teacher values(
    	'002',
        '赵四',
    	'03',
        1400.00
    );
    insert into Teacher values(
    	'003',
        '赵五',
    	'03',
        1000.00
    );
    insert into Teacher values(
    	'004',
        '赵六',
    	'04',
        1100.00
    );
    
    insert into Sc values(
    	'98030101',
        '001',
    	92
    );
    insert into Sc values(
    	'98030101',
        '002',
    	85
    );
    insert into Sc values(
    	'98030101',
        '003',
    	88
    );
    insert into Sc values(
    	'98040202',
        '002',
    	90
    );
    insert into Sc values(
    	'98040202',
        '003',
    	80
    );
    insert into Sc values(
    	'98040202',
        '001',
    	55
    );
    insert into Sc values(
    	'98040203',
        '003',
    	56
    );
    insert into Sc values(
    	'98030102',
        '001',
    	54
    );
    insert into Sc values(
    	'98030102',
        '002',
    	85
    );
    insert into Sc values(
    	'98030102',
        '003',
    	48
    );
```

* select

```mysql
#select 列名 from 表名 [where 检索条件];
select * from Student;
select Sid, Sname from Student;

#年龄小于19
select Sage, Sname
From Student
where Sage <= 19;

#检索条件 and or not
Select Tname 
From Teacher
where (Salary<1500 or Salary > 2000) and Did = '03';

# distinct 去重复
 select distinct Sage from Student;
 
#排序 order by 列名 [asc | desc]
Select sid, sname from Student
Order By sid desc;

#模糊查询
# % 零个或多个字符
# _ 任意单个字符
# \ 转义
Select Sname, sid from Student
where sname Like '张%';
Select Sname, sid from Student
where sname not Like '%三';
```

- 连接

```mysql
#按‘001’号课程（排序高到低显示）所有学生的姓名
select sname from Student, sc where Student.Sid = Sc.sid and Sc.Cid='001' Order By Score Desc;
#数据库成绩排名
ect Student.sid,sname,sclass,score from Student, sc,course where cname='数据库'and Student.sid=sc.sid and sc.cid=course.cid order by Score desc;
#别名 from 表名 as 别名
#θ连接不等值连接
#薪水差的任意两位教师
select t1.tname as Teacher1,t1.salary, t2.tname as teacher2,t2.salary from teacher t1, teacher t2 where t1.salary > t2.salary;

#即学过001 又学过002的所有同学 
select sc1.sid from sc as sc1, sc as sc2 where sc1.cid='001' and sc2.cid='002';
select sc1.sid from sc as sc1, sc as sc2 where sc1.cid='001' and sc2.cid='002' and sc1.sid = sc2.sid;
select sc1.sid from sc as sc1, sc as sc2 where sc1.cid='001' and sc2.cid='002' and sc1.sid = sc2.sid and sc1.score >= sc2.score;
```

* 增删改

```mysql
# insert update delete

#批元组增
insert into st(sid, sname)
	select sid, sname from Student
	where sname like '%三'；
	
#及格同学表
 create table sct(sid char(8) not null, sname char(10), cid char(3), score float(1));
insert into sct(sid, cid, score)
select sid, sname, score from sc
where score >= 60;

insert into sct(sid, sname, cid, score)
select Student.sid,sname, cid, score from sc,Student
where score >= 60 and sc.sid=Student.sid;

# delete from 表名 [where con];

#update 表名 set 列名 = xx where con;
#计算机系教师工资上调10%
Update Teacher set Salary=salary*2
where Did in (select Did from Dept where Dname='计算机');
```

* 修正和撤销

```mysql
alter table tabename
[add {colname datatype, ...}]
[drop {完整性约束名}]
[modify {colname datatype, ...}]

#delete vs drop
#use vs close
```







