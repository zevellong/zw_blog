#  Linux Programing Interface

## file IO

```bash
	# 测试文件写入剪贴板
	cat xx.cpp.new | xclip -selection cclipboard
	# 
	alias cattest=" cat test.c | xclip -selection cclipboard" 
```



```
#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif

// Source file copy to dest file
int main(int argc, char *argv[])
{
	int inputFd, outPutFd, openFlags;
	mode_t filePerms;
	ssize_t numRead;
	char buf[BUF_SIZE_];
	
	if (argc != 3 || (strcmp(argv[1], "--help")) == 0 )
		usageErr("%s old-file new-file\n", argv[0]);
	inputFd = open(argv[1], O_RDONLY);
	if (inputFd <= 0)
		usageErr("%s open error\n", argv[1]);
	openFlags = O_CREAT | O_WRONLY | O_TRUNC;
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP
			| S_IWGRP | S_IROTH | S_IWOTH;
	outPutFd = open(argv[2], openFlags, filePerms);
	if (outPutFd <= 0)
		usageErr("%s open error\n", argv[2]);
	
	while ((numRead = read(inputFd, buf, BUF_SIZE_)) > 0)
	{
		if (write(outPutFd, buf, numRead) != numRead)
			fatal("coundn't write buffer");
	}
	if (numRead == -1)
		errExit("read");
	if (close(inputFd) == -1)
		errExit("close input");
	if (close(outPutFd) == -1)
		errExit("close outPut");

	exit(0);
}
```



* open(filename, flags, ... mode)
  * 打开一个文件

| flags       | describe                               |
| ----------- | -------------------------------------- |
| O_RDONLY    | 只读                                   |
| O_WRONLY    | 写                                     |
| O_RDWR      | 读写                                   |
| O_CREAT     | 不存在则创建                           |
| O_DIRECTORY | 不是目录返回-1（errno=ENOTDIR）        |
| O_NOATIME   | 不修改访问时间，需要权限               |
| O_NOFOLLOW  | 不进行软链接解引用                     |
| O_SYNC      | 同步IO打开文件                         |
| O_TRUNC     | 已存在且为普通文件，清空文件，需写权限 |
| O_NONBLOCK  | 非阻塞方式打开                         |
|             |                                        |
|             |                                        |
|             |                                        |
|             |                                        |

* 返回值， 成功返回文件描述符， 失败返回-1
* 错误

| error   |                                                              |
| ------- | ------------------------------------------------------------ |
| EACCES  | flags参数不允许进程调用，可能是权限问题，文件不存在且无法创建 |
| EISDIR  | 打开文件属于目录                                             |
| EMFILE  | 进程打开的文件描述符达上限                                   |
| ENOENT  | 不存在且为指定creat，或者目录不存在，或者符号链接指向的不存在 |
| EROFS   | 只读文件系统，企图写方式打开                                 |
| ETXTBSY | 指定的文件为可执行文件，不允许修改正在执行的文件             |
|         |                                                              |

* read
* write
  * write可以在文件末尾的任意处写数据，导致文件空洞
  * 文件空洞在编程角度存在字节，读取文件空洞返回0到缓冲区，但不占磁盘空间

```c
#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif

int main(int argc, char *argv[])
{
	off_t oft = 10000;
	int sourceFile = open(argv[1], O_WRONLY | O_CREAT);
	printf("set seek %d Bytes\n", oft);
	if (lseek(sourceFile, oft, SEEK_CUR) == -1)
		errExit("lseek");
	if (write(sourceFile, argv[2], strlen(argv[2])) < 0)
		errExit("write");
	if (close(sourceFile) == -1)
		errExit("close");

	exit(EXIT_SUCCESS);
}


//运行 ./test xx.cpp.new abc
//ls -al 逻辑字节为10003
//du xx.cpp.new 实际字节为 8
```

* lseek

| seek     |        |
| -------- | ------ |
| seek_set | 开头   |
| seek_cur | 当前   |
| seek_end | 文件尾 |

### 原子操作和竞争

```c
int fd = open(argv[1], O_WRONLY);
if (fd != -1){
    printf("File exits\n");
    close(fd);
}else{
    if (errno != ENOENT)
        errExit("open"); //unexpected error
    else{
        fd = open(argv[1], O_CREAT | O_WRONLY, );
    }
}
```

* 上述进程试图独占的使用文件
* 但是可能存在打开文件判断不存在后， 另一进程时间开始，创建了此文件
* 使用 `flags = O_EXCL | O_CREAT`,原子操作，可以独占的创建文件
* 两个进程使用lseek在文件尾写数据，也可能引起竞争，导致一个进程的数据被覆盖，使用`flags=O_APPEND`原子操作，总在文件末尾添加

### 文件控制符操作 fcntl

```c
// 添加文件控制符O_APPEND的例子
int flags;
flags = fcntl(fd, F_GETFL);
flags |= O_APPEND;
fcntl(fd, F_SETFL, flags);
```

* 常用场景
  * 文件不是由该进程创建的，如标准输入，在进程运行前就打开了
  * pipe(), socket()

### 文件描述符和打开文件的关系

* 进程的文件描述符表
* 系统的打开文件表（所以进程共享）
  * 文件偏移
  * 状态标志（flags）
  * 文件的访问模式
  * 信号IO设置
  * inode对象
* 文件的inode表（共享）
  * 文件类型
  * 文件的锁
  * 文件的属性，文件大小，时间等信息

### 复制文件描述符

`int dup(int oldfd)`

`bint dup2(int oldfd, int newfd)`

```c
int newfd = dup(1); // newfd复制为标准输出
int xx = dup2(1, 2); //相当于先关闭标准错误，然后将2复制为标准输出
int newfd = fcntl(oldfd, F_DUPFD, startfd); // 返回一个大于等于startfd的文件描述符
```

* dup2调用如果newfd已经打开，则关闭它，此时忽略关闭错误；因此最好在调用dup2时，显示的关闭（调用close）



```c
pread(fd, buf, size, offset);
pwrite(fd, buf, size, offset);
//和read write相同， 但不会改变文件的偏移量， 偏移量由offset决定
```

### /dev/fd 目录

* 每个进程，内核都虚拟的一个文件目录

### 临时文件

fd = mkstemp(char * tem)

### 非局部跳转

```c
#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <setjmp.h> 
#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif

static jmp_buf jbuf;
static void f2()
{
	longjmp(jbuf, 2);
}
static void f1(int argc)
{
	if (argc == 1)
		longjmp(jbuf, 1);
	f2();
}
extern char** environ;
int main(int argc, char *argv[])
{
	switch(setjmp(jbuf)){
		case 0:
			printf("init and call f1() \n");
			f1(argc);
			break;
		case 1: 
			printf("jump bacj from f1()\n");
			break;
		case 2:
			printf("jumo back from f2()\n");
	}
	return 0;
}

```

* 从不同的函数返回
* 与goto不同， goto只能存在与相同的函数间
* setjmp() 一般只用于， if， switch， while的控制表达式
  * 以及 == < 等逻辑关系符
* 滥用longjmp
  * 调用 f1(), 使用setjmp，返回
  * 然后调用f2(), 使用全局的buf调用 longjmp
  * 行为是未定义的，因为f1调用后栈帧可能消失
* 优化可能导致 longjmp出错
  * 调用longjmp的函数尽量使用volatile

```c
#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <setjmp.h> 
#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif

extern char** environ;

static jmp_buf jbuf;
void doJmp(int nvar, int rvar, int vvar)
{
	
	printf("After longjmp: navr=%d  rvar=%d, vvar=%d \n",
					nvar, rvar, vvar);
	longjmp(jbuf, 1);
}

int main(int argc, char *argv[])
{
	int nvar = 111;
	register int rvar = 222;
	volatile int vvar = 333;

	if (setjmp(jbuf) == 0)
	{
		nvar = 777;
		rvar = 888;
		vvar = 999;
		doJmp(nvar, rvar, vvar);

	}else
	{
		printf("After longjmp: navr=%d  rvar=%d, vvar=%d \n",
					nvar, rvar, vvar);
	}
}


/*
#  运行结果	
test.c  -o test                                         
~/.../vscode_workspace/csapp >>> ./test                                                      
After longjmp: navr=777  rvar=888, vvar=999 
After longjmp: navr=777  rvar=222, vvar=999 
~/.../vscode_workspace/csapp >>> gcc test.c  -o test -O                                      
~/.../vscode_workspace/csapp >>> ./test                                                      
After longjmp: navr=777  rvar=888, vvar=999 
After longjmp: navr=111  rvar=222, vvar=999 
~/.../vscode_workspace/csapp >>> cattest      


*/
```



* alloca(size)
  * 在栈上分配内存
  * 不能在函数调用中使用 alloca，比如 `fun(a, alloca(10), c);`
  * alloca分配的数组会随栈的释放而释放，相比malloc速度更快
  * 配合longjmp而不会导致内存泄漏

### 用户和组

**/etc/passwd**

用户名 x表示加密的密码 用户ID 组ID 注释 主目录 shell

```bashh
zw:x:1000:1000:zw:/home/zw:/bin/zsh
```

**/etc/group**

组名 密码 组ID 用户列表

```bash
zw:x:1000:
```

### 进程凭证

* 实际用户ID 组ID
* 有效 
* set-user-id set-group-id
* 保存的set＊id

* 系统和进程信息
  * /proc/pid/* 文件
  * 记录了进程的信息，进程开始时创建，结束时删除

| file    |                                          |
| ------- | ---------------------------------------- |
| cmdline | 命令行参数                               |
| cwd     | 指向当前目录的符号链接                   |
| environ | 环境列表                                 |
| exe     | 正在执行的文件的符号链接                 |
| fd      | 文件目录，包含了进程打开的文件的符号链接 |
| maps    | 内存映射                                 |
| mem     | 进程虚拟内存                             |
| mounts  | 进程安装点                               |
| root    | 指向根目录的符号链接                     |
| status  | 各种信息 进程ID 凭证 内存 信号           |
| task    | 线程                                     |
|         |                                          |

uname

* 主机系统标识信息

```c
#define _GNU_SOURCE
#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <setjmp.h> 
#include <stdlib.h>
#include <sys/utsname.h>


#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif



int main(int argc, char *argv[])
{
	struct utsname um;
	if (uname(&um) == -1)
		errExit("uname");

	printf("Node name: %s\n", um.nodename);
	printf("sys name: %s\n", um.sysname);
	printf("release name: %s\n", um.release);
	printf("version name: %s\n", um.version);
	printf("Machine name: %s\n", um.machine);
#ifdef _GNU_SOURCE
	printf("Domain name: %s\n", um.domainname);
#endif
}

```



### 文件IO缓冲

- 出于速度考虑，read和write系统调用在操作磁盘文件不会直接发起磁盘访问，仅在用户空间缓冲区和内核缓冲区高速缓存之间复制
- write(fd, "adc", 3)执行后立即返回，在后续的某个时刻，内核才将数据写入磁盘；read同理；
- 加速了系统调用的速度
- Linux内核对缓冲区的大小没有固定上限，内核会尽可能的分配多的缓冲区，但受限于两个因素
  - 可用的物理内存总量
  - 其他目的对物理内存的需求

* setvbuf, setbuf, fflush

```c
// 例子
#define BUFSIZE 1024
static buf[BUFSIZE];

setvbuf(FILE* F, buf, mode, BUFSIZE);
setbuf(F, buf); //与下行相当
setvbuf(F, buf, (buf != NULL) ? _IOFBF : _IONBF, BUFSIZ);
//BUFSIZ 定义在stdio头文件，通常为 8192
```

| mode   |        |
| ------ | ------ |
| _IONBF | 无缓冲 |
| _IOLBF | 行缓冲 |
| _IOFBF | 全缓冲 |

* 如果无缓冲， 将忽略buf和size参数
* setvbuf返回非0值



### 同步IO

* 文件的元数据： 文件数据的信息数据， 即属主， 组， 时间戳等

| IO                                        |                                                              |
| ----------------------------------------- | ------------------------------------------------------------ |
| synchronized IO data integrity completion | 文件读需要 从磁盘已经传递到进程；文件写需要进程指定的数据传递完毕, 即元数据和数据都要传送完毕 |
| synchronized IO file integrity completion | 与上述的区别在于只需要更新文件的元数据                       |

* 同步IO对性能的影响很大，要比普通的时候慢很多（几十倍到几千倍）
* open函数的 O_SYNC标志， 写入数据同步



```c
int fileno(FILE *stream);
FILE* fdopen(int fd, mode_t mode);
// 文件描述符和文件流指针的转换
```

### 设备

* 字符设备，基于字符处理， 鼠标和键盘
* 块设备， 基于块（通常512B的倍数）， 磁盘
* 设备ID， 每个设备都有主 辅设备ID，由主ID建立起设备和驱动程序的关系（内核不会用文件名查找设备驱动）

### ext2 文件系统和 i-node节点

磁盘 --> 分区 --> 文件系统

文件系统

* 引导块
* 超级块
* i-node表
* 数据块

i-node

* 文件类型： 常规文件， 目录，符号链接，字符设备
* 文件属主（pid）和组（gid）
* 三类用户的访问权限 rwx-rwx-rwx
* 三个时间戳
  * 文件的最后修改时间， 最后访问时间， 文件状态的最后修改时间
* 硬链接数量
* 文件大小
* 块数量
* 指向数据的指针

### ext2中的inode

* 每个inode包含15个指针
* 前12个指向在文件系统的位置， 第13个指向后面的其他指针的位置
* 13为一级，14为二级，15为三级，这些对大文件指向
* 文件空洞中的一些只需做上标记，无需分配实际的磁盘

### 文件属性

`stat` `lstat` `fstat` 系统调用，`struct stat *statbuf`

* 设备ID，主ID和辅ID，使用majar()和minor()可提取主辅ID
* 文件属主，uid，gid
* 文件类型和权限，
* 文件大小，分配块数（512B），最优IO块大小
* 时间戳，`atime`上次访问时间，`mtime`上次修改时间，`ctime`上次发生改变的时间

```c
/* Listing 15-1 */
/* t_stat.c

   A program that displays the information returned by the stat()/lstat()
   system calls.

   Usage: t_stat [-l] file

   The '-l' option indicates that lstat() rather than stat() should be used.
*/
#include <sys/sysmacros.h>
#if defined(_AIX)
#define _BSD
#endif
#if defined(__sgi) || defined(__sun)            /* Some systems need this */
#include <sys/mkdev.h>                          /* To get major() and minor() */
#endif
#if defined(__hpux)                             /* Other systems need this */
#include <sys/mknod.h>
#endif
#include <sys/stat.h>
#include <time.h>
#include "file_perms.h"
#include "tlpi_hdr.h"

static void
displayStatInfo(const struct stat *sb)
{
    printf("File type:                ");

    switch (sb->st_mode & S_IFMT) {
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFLNK:  printf("symbolic (soft) link\n");    break;
    case S_IFIFO:  printf("FIFO or pipe\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown file type?\n");      break;
    }

    printf("Device containing i-node: major=%ld   minor=%ld\n",
                (long) major(sb->st_dev), (long) minor(sb->st_dev));

    printf("I-node number:            %ld\n", (long) sb->st_ino);

    printf("Mode:                     %lo (%s)\n",
            (unsigned long) sb->st_mode, filePermStr(sb->st_mode, 0));

    if (sb->st_mode & (S_ISUID | S_ISGID | S_ISVTX))
        printf("    special bits set:     %s%s%s\n",
                (sb->st_mode & S_ISUID) ? "set-UID " : "",
                (sb->st_mode & S_ISGID) ? "set-GID " : "",
                (sb->st_mode & S_ISVTX) ? "sticky " : "");

    printf("Number of (hard) links:   %ld\n", (long) sb->st_nlink);

    printf("Ownership:                UID=%ld   GID=%ld\n",
            (long) sb->st_uid, (long) sb->st_gid);

    if (S_ISCHR(sb->st_mode) || S_ISBLK(sb->st_mode))
        printf("Device number (st_rdev):  major=%ld; minor=%ld\n",
                (long) major(sb->st_rdev), (long) minor(sb->st_rdev));

    printf("File size:                %lld bytes\n", (long long) sb->st_size);
    printf("Optimal I/O block size:   %ld bytes\n", (long) sb->st_blksize);
    printf("512B blocks allocated:    %lld\n", (long long) sb->st_blocks);

    printf("Last file access:         %s", ctime(&sb->st_atime));
    printf("Last file modification:   %s", ctime(&sb->st_mtime));
    printf("Last status change:       %s", ctime(&sb->st_ctime));
}

int
main(int argc, char *argv[])
{
    struct stat sb;
    Boolean statLink;           /* True if "-l" specified (i.e., use lstat) */
    int fname;                  /* Location of filename argument in argv[] */

    statLink = (argc > 1) && strcmp(argv[1], "-l") == 0;
                                /* Simple parsing for "-l" */
    fname = statLink ? 2 : 1;

    if (fname >= argc || (argc > 1 && strcmp(argv[1], "--help") == 0))
        usageErr("%s [-l] file\n"
                "        -l = use lstat() instead of stat()\n", argv[0]);

    if (statLink) {
        if (lstat(argv[fname], &sb) == -1)
            errExit("lstat");
    } else {
        if (stat(argv[fname], &sb) == -1)
            errExit("stat");
    }

    displayStatInfo(&sb);

    exit(EXIT_SUCCESS);
}

```

* `utime`和`utimes`，显式的修改atime和mtime，futimes和lutimes功能相同，参数为文件描述符和软链接
* utime第二个参数为时间(utimebuf)，若为null则以当前时间
* 成功返回0，失败返回1



* 改变文件的属主，`chown`及 f， l



### 文件权限

* 目录权限
  * 读权限，列出文件
  * 写权限，创建及删除文件;**注意：要删除文件，与文件本身的权限没有要求，示例：使用root用户创建了一个普通文件，exit，然后使用用户1000删除这个文件，提示是否删除此文件，按y，文件删除**
  * 执行权限，访问目录中的文件，也称搜索权限
  * 示例：要想读`/home/zw/x`文件，需要 `/、/home、/home/zw/ `三个目录的执行权限；若当前目录为`/home/zw/sub1`,访问 `../sub2/x`，需要`zw`和`sbu2`的执行权限，无需home的权限
  * 使用open调用打开了文件，对后续的调用read，write等无需检查权限
* 权限检查算法
  * 指定文件目录后，内核会检查相应的文件权限；带有文件目录前缀时，会检查相应目录的执行权限；根据有效用户组ID；
  * 1， 特权用户，所有权限
  * 2， 若有效用户ID和文件属主id相同，给予其相应的权限
  * 3， 有效用户组ID和文件属组id相同，给予相应组权限
  * 4， 按照other用户权限
* sticky位
  * 老式unix系统中，sticky位让常用的程序运行更快，首次执行程序时，系统将其文本拷贝至交换区
  * 现在unix中，若目录设置了sticky位，则其他用户对此目录具有写权限，但是只能删除当前目录下属于自己的文件
* umask， 设置掩码，返回上一次的掩码



### 扩展属性EA

* 名称-值 对将元数据和文件节点i相联系的技术
* user ea，trusted ed, system ea，security ea
* shell ea示例

```shell
touch tfile
setfattr -n user.x -v "hello" tfile
setfattr -n user.y -v "yyy" tfile
getfattr -d tfile
```

* ea只能设置普通文件和目录，软链接设置毫无意义，其他文件设置难以对其控制
* 若一目录设置了sticky位，且为其他用户所有，不能对齐设置ea
* 系统调用 setattr getattr removeattr

### 访问控制列表ACL

*  acl由acl记录组成，acl记录记录了单个用户和单个组的权限
* acl三个类型：
  * 标记类型：acl_user_obj(文件属主)，acl_user(特定用户)
  * 标记限定符: 指定用户的ID或gid
  * 权限：读写执行权限
  * acl_mask：特定用户和组访问时将按照掩码&运算
* acl权限检查算法
  * 与文件的权限检查算法相似
  * 顺序为，特权用户--文件属主--特定用户--文件属组--特定组--其他用户
* acl格式，见书上
* 如果acl由acl_user acl_group的记录，那么一定含有acl_mask
* shell: setfacl getfacl
* 新建的目录总是倾向最小acl

### 目录和链接

* 目录和硬链接存储方式相似
  * inode条目中，标记不同，目录为d
  * 目录是特殊组织的文件，本质是inode和文件名组成的表格
  * 硬链接若计数为0，则删除文件
* inode编号开始于2，0记录未使用，1表示坏块
* 符号链接（软链接），指代一个文件
  * 符号链接引用有解引用次数限制
  * 可以指代一个不存在的目录文件
  * 不计入inode引用次数
  * 符号链接有通常所有权限，一般权限和指代的文件相关；当目录设置stiky位才重视符号链接的权限

```shell
# ln命令
ln abc xyz #创建一个xyz文件指向abc文件的inode节点
ln -s abc sss #符号链接
ls -li #查看文件的inode和链接计数（硬链接）
```

* link 和 unlink调用， 创建和删除一个链接；
  * 当所有的链接删除时，如果还有文件描述符指向此，不会执行删除，在进程结束后，然后在删除文件；如果计数为0，文件还存在时，此时已经不能在别的进程用open打开，因为不能建立inode和文件名的对应关系
* `rename(oldnmae, newname)` 系统调用
  * newpath已经存在，则覆盖
  * 若指向同一文件，则什么都不做；这是为了保证rename(x, x)的正确语义
  * rename不进行解引用
  * 如果oldname为文件而非目录，则newname不能为一个目录名
  * `rename(/sub1/x, /sub2/y)`此调用即修改文件路径，又修改文件名
  * 如果old为目录名，则new不能为已经存在的目录名
  * new不能包含old为前缀
* 符号链接系统调用  symlink()，readlink
* 创建和移除目录 mkdir和rmdir
* 移除一个目录或文件，remove，如果文件调用unlink，如果目录，调用rmdir
* 访问目录， opendir，closedir，rewinddir， DIR流和struct dirent
* int dirfd(DIR* dirp)，返回dirp的文件描述符
*  

```c
#define _BSD_SOURCE
#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <setjmp.h> 
#include <stdlib.h>
#include <sys/utsname.h>
#include <time.h>
#include <dirent.h>



#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif

static void listDir(const char *pathname)
{
	DIR* dirp;
	struct dirent *drtp;
	int imCurr;
	imCurr = !strcmp(pathname, ".");
	dirp = opendir(pathname);
	if (dirp == NULL)
	{
		errExit("opendir err\n");
		return;
	}
	for ( ; ; )
	{
		drtp = readdir(dirp);
		if (drtp == NULL)
			break;
		if (!strcmp(drtp->d_name, ".")| !strcmp(drtp->d_name, ".."))
			continue;
		if (!imCurr)
			printf("%s/", pathname);
		printf("%s \n", drtp->d_name);
	}
	if (errno != 0)
		errExit("readdir");
	if (closedir(dirp) == -1)
		errExit("closedir");
}


int main(int argc, char *argv[])
{
	if (argc == 1)
		listDir(".");
	else
		for (int i = 1; i < argc; i++)
			listDir(argv[i]);

	exit(EXIT_SUCCESS);
}


```

* nftw系统调用，提供一个函数参数指定操作

* getcwd 获取当前目录，chdir改变当前目录，
* chroot将当前进程的根目录替换
* 解析路径名 redlpath
* 解析路径 dirname， basename获取当前的目录，文件名
* 

## process

* fork、exit、wait、execve

### fork

* 调用后，存在2个进程，每个进程都从fork返回处继续执行
* 两个进程都执行相同的代码段，但是有自己独立的栈，堆，和数据段
* 返回0子进程，进程id为父进程，子进程可以通过getgpid获取pid，这样的设计方便父进程管理子进程
* fork失败可能是超过了进程上限
* 调用和两个进程共享一份文件描述符表，一个进程改变了，将影响另一进程
* **内存语义**
  * 早期的unix设计**老实**的复制所有信息
  * 现代的unix运用了一些技术减少这些浪费
  * 内核将代码段标记为只读，两个进程的代码段均指向同一物理页页帧
  * 写时复制
* vfork， 尽量避免使用
  * 无需复制内存和页表；父子直接共享内存
  * 父进程先挂起，子进程执行
* fork会导致父子进程的调动竞争，不能准确的预测谁先执行
* 可以使用信号进程父子进程的同步，sigsuspend

### exit

```c
int exit(int status);
int _exit(int status);
```

* 调用退出处理程序（atexit()和on_exit()）,与注册的顺序相反
* 刷新stdio流
* 使用status调用_exit()

### 进程终止的细节

* 关闭所有文件描述符，目录流，信息目录描述符
* 释放所有文件锁
* 分离所有的system v共享内存段，段的shm_battach减一
* 如果是一个终端进程，会向前台的所有程序发送一个sighup
* 关闭posix信号量
* 关闭消息队列
* 取消内存锁和mmap调用的内存映射
* 进程退出，如果进程组成为孤儿，且存在停止的进程，所有的进程先收到sighup然后sigcont

- 退出处理程序：on_exit(), atexit() ， 略

fork，stdio缓冲区，_exit之间的交互

```c
#include <tlpi_hdr.h>
#include <sys/utsname.h>
#include <time.h>
#include <signal.h>
#define _GNU_SOURCE
#include <string.h>
#include <setjmp.h>
#define _BSD_SOURCE

int main(int argc, char* argv[])
{
	printf("Print 2 times\n");
	write(STDOUT_FILENO, "cao\n", 5);
	
	if (fork() == -1)
		errExit("fork");
	exit(EXIT_SUCCESS);
}
/*
~/.../vscode_workspace/csapp >>> make; ./test         
gcc -o test test.c -ltlpi
Print 2 times
cao
~/.../vscode_workspace/csapp >>> ./test > a                                                        
~/.../vscode_workspace/csapp >>> cat a                                                             
cao
Print 2 times
Print 2 times


~/.../vscode_workspace/csapp >>> make; ./test                                                      
gcc -o test test.c -ltlpi
Print 2 times
cao
~/.../vscode_workspace/csapp >>> ./test > a                                                        
~/.../vscode_workspace/csapp >>> cat a                                                             
cao
Print 2 times
Print 2 times
*/

```

* 终端中和重定向到a输出不同
  * 终端行缓冲，文件为块缓冲
  * fork调用后，write的高速缓冲也被复制了，而调用exit会显式的刷新一次stdio
* 因此可以使用两个原则避免上述：
  * 显式的刷新缓冲区，fflush，setvbuf
  * 父子进程只有一个函数调用exit其他的调用_exit

### wait

* 等待子进程
  * 如果没有子进程返回，一直阻塞到子进程返回；如果有子进程返回，则立即返回
  * 根据status返回一些信息
  * 追加资源和时间
  * 返回子进程的pid
* waitpid
  * wait存在限制
  * 如果有多个子进程，不能等特定的那个进程
  * 如果没有子进程退出，一直阻塞；有时候希望执行非阻塞的等待
  * 只能发现已经终止的进程，对于sigkill stop的进程无能为力
  * 根据pid参数执行不同的等待
  * 等待的状态值：见tlpi，略

### 孤儿进程和僵死进程

**孤儿进程：一个父进程退出，而它的一个或多个子进程还在运行，那么那些子进程将成为孤儿进程。孤儿进程将被init进程(进程号为1)所收养，并由init进程对它们完成状态收集工作。**

**僵尸进程：一个进程使用fork创建子进程，如果子进程退出，而父进程并没有调用wait或waitpid获取子进程的状态信息，那么子进程的进程控制块(PCB)仍然保存在系统中。这种进程称之为僵死进程**

- sigkill无法杀死僵死进程

- 子进程终止后，父进程有可能执行wait来确定子进程如何终止的，因此内核将子进程释放大量的资源，仅仅保留一条记录

- 僵尸进程危害场景：

  　　例如有个进程，它定期的产 生一个子进程，这个子进程需要做的事情很少，做完它该做的事情之后就退出了，因此这个子进程的生命周期很短，但是，父进程只管生成新的子进程，至于子进程 退出之后的事情，则一概不闻不问，这样，系统运行上一段时间之后，系统中就会存在很多的僵死进程，倘若用ps命令查看的话，就会看到很多状态为Z的进程。 严格地来说，僵死进程并不是问题的根源，罪魁祸首是产生出大量僵死进程的那个父进程。因此，当我们寻求如何消灭系统中大量的僵死进程时，答案就是把产生大量僵死进程的那个元凶枪毙掉（也就是通过kill发送SIGTERM或者SIGKILL信号啦）。枪毙了元凶进程之后，**它产生的僵死进程就变成了孤儿进 程，这些孤儿进程会被init进程接管**，init进程会wait()这些孤儿进程，释放它们占用的系统进程表中的资源，这样，这些已经僵死的孤儿进程 就能瞑目而去了。

### sigchld信号

* 子进程退出将发送一个sigchld信号到父进程
* 保证移植性，应该创建子进程前就设置好信号处理函数

- SIGCHLD信号的含义：
  简单的说，子进程退出时父进程会收到一个SIGCHLD信号，默认的处理是忽略这个信号，而常规的做法是在这个信号处理函数中调用wait函数获取子进程的退出状态。 

- 既然在SIGCHLD信号的处理函数中要调用wait函数族，为什么有了wait函数族还需要使用SIGCHLD信号?

我们知道，unix中信号是采用异步处理某事的机制，好比说你准备去做某事，去之前跟邻居张三说如果李四来找你的话就通知他一声，这让你可以抽身出来去做这件事，而李四真正来访时会有人通知你，这个就是异步信号一个较为形象的比喻。
一般的，父进程在生成子进程之后会有两种情况：一是父进程继续去做别的事情，类似上面举的例子；另一是父进程啥都不做，一直在wait子进程退出。 
**SIGCHLD信号就是为这第一种情况准备的，它让父进程去做别的事情，而只要父进程注册了处理该信号的函数，在子进程退出时就会调用该函数，在函数中wait子进程得到终止状态之后再继续做父进程的事情。** 
最后，我们来明确以下二点： 
1)凡父进程不调用wait函数族获得子进程终止状态的子进程在退出时都会变成僵尸进程。 
2)SIGCHLD信号可以异步的通知父进程有子进程退出。

## signal

* 信号即对进程的通知机制，也称软件中断
* 信号与硬件中断相似，但大多数情况，无法准确的预测到信号的到达时间
* 产生信号的事件有
  * 硬件异常；硬件检测到一个错误，然后内核发信号给进程
  * 用户的终端特殊字符（contral+z contral+c）
  * 软件事件，定时器
* 信号都定义了从1开始的数字
* 信号分两大类：内核向进程通知，即传统的标准信号，linux以1到31表示；
  * 第二类为实时信号
* 信号的默认操作：
  * 忽略信号
  * 终止进程
  * 产生核心转储文件
  * 从暂停恢复
  * 采取默认行为
  * 执行信号处理程序
  * **注意：无法将信号的处置设置为核心转储或终止进程，除非是默认设置**
* 一些信号

| sig              | num   | 描述                                      |
| ---------------- | ----- | ----------------------------------------- |
| SIGABRT          | 6     | 默认情况，终止进程，核心转储，abort()调用 |
| SIGALRM          | 14    | 定时器到期                                |
| SIGBUS           | 7     | 内存访问错误                              |
| SIGCLD (SIGCHLD) | 17    | 终止或停止子进程                          |
| SIGCONT          | 18    | 继续执行 （continue）                     |
| SIGEMT           | undef | 硬件错误                                  |
| SIGFPE           | 8     | 算术错误                                  |
| SIGHUP           | 1     | 挂起                                      |
| SIGILL           | 4     | 非法指令                                  |
| SIGINFO          |       | linux等价SIGPWER                          |
| SIGIO            |       | fcntl()                                   |
| SIGIOT           |       |                                           |
| SIGKILL          | 9     | 杀死进程，不能被屏蔽                      |
| SIGLOST          |       |                                           |
| SIGPIPE          | 13    | 管道断开，试图往管道写东西，但无目标      |
| SIGPOLL          |       |                                           |
| SIGPROF          | 27    | 设置的性能分析器时间到期                  |
| SIGPWR           | 30    | 电量将耗尽                                |
| SIGQUIT          | 3     | 终端退出                                  |
| SIGSEGV          | 11    | 无效的内存引用                            |
| SIGSTKFLT        |       |                                           |
| SIGSTOP          | 19    | 确保停止                                  |
| SIGSYS           | 31    | 无效的系统调用                            |
| SIGTRAP          | 5     | 跟踪陷阱                                  |
| SIGTSTP          | 20    | 终端停止                                  |
| SIGTTIN          | 21    | BG后台读                                  |
| SIGTTOU          | 22    | BG写                                      |
| SIGUNUSED        |       |                                           |
| SIGURG           |       | 套接字带有紧急数据                        |
| SIGUSER1         |       | 用户定义1                                 |
| SIGUSER2         |       | 用户定义2                                 |
| SIGVTALRM        |       | 虚拟定时器过期                            |
| SIGWINCH         |       | 终端窗口发生变化                          |
| SIGXCPU          |       | cpu时间到期                               |
| SIGXFSZ          |       | 突破对文件大小的限制                      |

* singal函数

```c
void (*singal(int sig, void (*handler(int))) (int));
//也可定义
typedef void (*handler)(int);
hander* signal(int sig, handler);

```

* 返回值
  * SIG_DFL
  * SIG_IGN
  * SIG_ERR

```c
#include <stdio.h>
#include <tlpi_hdr.h>
#include <signal.h>

#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif

static void listDir(const char *pathname)
{
}
static int a;
static void sigHandler(int sig)
{
	printf("receive sig, a=%d\n", a++);
}

int main(int argc, char *argv[])
{
	if (signal(SIGINT, sigHandler) == SIG_ERR)
		errExit("signal");
	for (int i =0; ; i++)
		sleep(3);
}


```

* 信号处理中尽量使用可重入的函数

```c
#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <setjmp.h> 
#include <stdlib.h>
#include <sys/utsname.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>

#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif

static int a;
static void sigHandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("Receive SIGINT %d times\n", a++);
		return;
	}
	printf("receive SIGQUIT \n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	if (signal(SIGINT, sigHandler) == SIG_ERR)
		errExit("signal");
	if (signal(SIGQUIT, sigHandler) == SIG_ERR)
		errExit("signal");
	for (int i =0; ; i++)
		sleep(3);
}


```

```c
#include <stdio.h>
#include <tlpi_hdr.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <setjmp.h> 
#include <stdlib.h>
#include <sys/utsname.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>

#ifndef BUF_SIZE_
#define BUF_SIZE_ 1024
#endif

static int a;
static void sigHandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("Receive SIGINT %d times\n", a++);
		return;
	}
	printf("receive SIGQUIT \n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	int sig, s;
	sig = getInt(argv[2], 0, "signum");
	s = kill(getLong(argv[1], 0, "pid"), sig);
	if (sig != 0)
	{
		if (s !=0 )
			printf("err\n");
		printf("send success\n");
	}else
	{
		if (s == 0)
			printf("we can send sig %d\n", sig);
		else
			if (errno == EPERM)
			{
				printf("Perm err\n");
			}
			else if (errno == ESRCH)
				printf("%d don't exit\n", argv[1]);
	}
	
	exit(EXIT_SUCCESS);
}


```

### 发送信号

- `int kill(pid_t pid, int sig)` 
- 如果pid大于0，发送进程信号
- 如果pid=0，向此进程的进程组发送信号
- pid=-1,广播信号，除了init和自己本身
- pid<-1, pid绝对值的进程组发送信号
- 如果进程组找不到，发送失败，返回-1
- 发送信号的权限
  - 特权用户可以向所有进程发送信号
  - init进程是个例外（只能接受自己安装处理函数的信号），防止被意外杀死
  - 有效用户id的可以向保存用户id和真实id相匹配的进程发送信号
    - 而将有效id排除在外，原因见tlpi 333页
  - sigcont例外，任何非特权的进程可以向同一会话的任何其他进程发送这一个信号；利用这一个规则，shell可以重启停止的作业
- 发送失败，若权限不足，errno设置EPERM，若无此进程，设置为ESRCH
- 发送0信号可以探测进程是否存在
  - wait调用也可以
  - 管道和fifo
  - /proc/PID接口
- `int raise(int sig)` == `kill(getpid(), sig)`
- int killpg(int sig)

* 显示信号的描述
  * sys_siglist数组
  * char* strsignal(int sig)

```c
#include <tlpi_hdr.h>
#include <sys/utsname.h>
#include <time.h>
#include <signal.h>
#define _GNU_SOURCE
#include <string.h>
#define _BSD_SOURCE
int main(int argc, char *argv[])
{
	int i;
	for (i = 0; i < 32; i++)
		printf("%d: %s\n", i, strsignal(i));
}

/*
0: Unknown signal 0
1: Hangup
2: Interrupt
3: Quit
4: Illegal instruction
5: Trace/breakpoint trap
6: Aborted
7: Bus error
8: Floating point exception
9: Killed
10: User defined signal 1
11: Segmentation fault
12: User defined signal 2
13: Broken pipe
14: Alarm clock
15: Terminated
16: Stack fault
17: Child exited
18: Continued
19: Stopped (signal)
20: Stopped
21: Stopped (tty input)
22: Stopped (tty output)
23: Urgent I/O condition
24: CPU time limit exceeded
25: File size limit exceeded
26: Virtual timer expired
27: Profiling timer expired
28: Window changed
29: I/O possible
30: Power failure
31: Bad system call
*/
```

### 信号集

* 由一组型号组成的集合

```c
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set;
int sigaddset(sigset_t *set, int sig);
int sigdeleteset(sigset_t *set, int sig);
int sigorset(sigset_t *set, sigset_t *left, sigset_t *right);
int sigisemptyset(const sigset *set);
int sigismember(const sigset_t *set, int sig);
```



```c
#include <tlpi_hdr.h>
#include <sys/utsname.h>
#include <time.h>
#include <signal.h>
#define _GNU_SOURCE
#include <string.h>
#define _BSD_SOURCE

void printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
	int cnt, sig;
	for (sig = 1, cnt = 0; sig < NSIG; sig++)
		if (sigismember(sigset, sig) == 1){
			cnt++;
			fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
		}
	if (cnt == 0)
		fprintf(of, "%s<emputy set>\n", prefix);
}
int printSigmask(FILE *of, const char *msg)
{
	sigset_t set;
	if  (msg != NULL)
		fprintf(of, "%s \n", msg);
	if (sigprocmask(SIG_BLOCK, NULL, &set) == -1)
		return -1;
	printSigset(of, "\t\t", &set);
	return 0;
}
int printPendingsig(FILE *of, const char *msg)
{
	sigset_t set;
	if (msg != NULL)
		fprintf(of, "%s \n", msg);
	if (sigsuspend(&set) == -1)
		return -1;
	printSigset(of, "\t\t", &set);

	return 0;
}
int main(int argc, char *argv[])
{
	sigset_t set;
	sigfillset(&set);
	printSigset(stdout, "\t\t", &set);

	return 0;
}


```



### 信号掩码

* 内核对进程维护一组信号掩码，并阻塞对该进程的传递
* 若阻塞的信号传递给进程，对该信号的传递靠后，直到进程解除阻塞
* 阻塞的系统调用
  * sigprocmask(),显式的阻塞
  * sigaction()信号安装函数
  * **行为**
  * SIG_BLOCK
  * SIG_UNBLOCK
  * SIG_SETMASK
* 解除后，如果由等待信号，将至少立即传送一个信号
* 阻塞sigkill和sigstop不会报错，也不能阻塞

### 等待状态的信号

* 如果一个进程正在阻塞信号，那么该信号将会添加到等待集合中，可以使用sigpending检测



```c
#include <tlpi_hdr.h>
#include <sys/utsname.h>
#include <time.h>
#include <signal.h>
#define _GNU_SOURCE
#include <string.h>
#define _BSD_SOURCE

void printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
	int cnt, sig;
	for (sig = 1, cnt = 0; sig < NSIG; sig++)
		if (sigismember(sigset, sig) == 1){
			cnt++;
			fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
		}
	if (cnt == 0)
		fprintf(of, "%s<emputy set>\n", prefix);
}
int printSigmask(FILE *of, const char *msg)
{
	sigset_t set;
	if  (msg != NULL)
		fprintf(of, "%s \n", msg);
	if (sigprocmask(SIG_BLOCK, NULL, &set) == -1)
		return -1;
	printSigset(of, "\t\t", &set);
	return 0;
}
int printPendingsig(FILE *of, const char *msg)
{
	sigset_t set;
	if (msg != NULL)
		fprintf(of, "%s \n", msg);
	if (sigsuspend(&set) == -1)
		return -1;
	printSigset(of, "\t\t", &set);

	return 0;
}
static int sigcnt[NSIG];
static volatile sig_atomic_t gotSigint = 0;
void sigHandler(int sig)
{
	if (sig == SIGINT)
		gotSigint++;
	else
		sigcnt[sig]++;
}
int main(int argc, char *argv[])
{
	int n, numSecs;
	sigset_t emptySet, pendingSet, blockSet;

	printf("%s prococess id is %ld\n", argv[0], getpid());

	for (int i = 0; i < NSIG; i++)
		(void) signal(i, sigHandler);
	if (argc > 1)		
	{
		numSecs = getInt(argv[1], 0, NULL);
		if (sigfillset(&blockSet) == -1)
			errExit("sigfillset");
		if (sigprocmask(SIG_SETMASK, &blockSet, NULL) == -1)
			errExit("sigprocmask");
		sleep(numSecs);
		
		if (sigpending(&pendingSet) == -1)
			errExit("sigpending");
		printf("Pending Sig set:\n");
		printSigset(stdout, "\t\t", &pendingSet);
		sigemptyset(&emptySet);
		if (sigprocmask(SIG_SETMASK, &emptySet, NULL) == -1)
			errExit("sigprocmask");
	}
	while (!gotSigint)
		pause();
	for (int i =0; i < NSIG; i++)
		if (sigcnt[i] != 0)
			printf("%s: singal %d receive %d times\n", argv[0], i, sigcnt[i]);
	exit(EXIT_SUCCESS);
}


```

```c
#include <signal.h>
#include "tlpi_hdr.h"

int main(int argc, char* argv[])
{
	int numsig, sig, j;
	pid_t pid;
	if (argc < 4)
		errExit("At least 4 argc");
	pid = getLong(argv[1], 0, "PID");
	numsig = getInt(argv[2], 0, "NUMSIG");
	sig = getInt(argv[3], 0, "SIG NO");
	printf("%s: sending singal %d to process %ld %d times\n", argv[0], sig, pid, numsig);

	for (j=0; j < numsig; j++)
		if (kill(pid, sig) == -1)
			errExit("kill");
	if (argc == 5)
		if (kill(pid, getInt(argv[4], 0, "SigINT")) == -1)
			errExit("kill");
	printf("process %ld end\n ", pid);
	exit(EXIT_SUCCESS);
}

```

```shell
上述程序运行
~/.../vscode_workspace/csapp >>> ./test 20&                                                       
[3] 85504
./test prococess id is 85504                                                                       
~/.../vscode_workspace/csapp >>> ./a.out 85504 100000 10 2                                        
./a.out: sending singal 10 to process 85504 100000 times
process 85504 end
 %                                                                                                 ~/.../vscode_workspace/csapp >>> Pending Sig set:                                                 
		2 (Interrupt)
		10 (User defined signal 1)
./test: singal 10 receive 1 times

[3]  + done       ./test 20
~/.../vscode_workspace/csapp >>> ./test &                                                         
[3] 85532
./test prococess id is 85532                                                                       
~/.../vscode_workspace/csapp >>> ./a.out 85532 1000000 10 2                                       
./a.out: sending singal 10 to process 85532 1000000 times
process 85532 end
./test: singal 10 receive 249096 times
 [3]  + done       ./test
~/.../vscode_workspace/csapp >>>    
```

* 当设置阻塞，只能收到1次信号
* 没有设置阻塞，发信号的数量也小于收到信号的数量，大约为1/4
* 更具灵活性的sigaction

```c
int sigaction(int sig, const struct sigaction *act, const struct sigaction *oldact);
struct sigaction{
    void (*handler),
    sigset_t set;
    int sa_flags;
    void (*sa_restorer)(void);
}
```

* sigaction 函数
  * 每次进入信号处理函数时，自动将set中的信号设置阻塞，退出时解除，除非设置了SA_NODEFER
  * 使用longjump函数在进入的时候设置掩码，但是跳出时，不会解除阻塞

### 信号处理函数

* 信号设计的原则：应该尽量简单，可以降低竞争的风险
  * 两种常见的设计：
    * 信号处理函数设置全局变量并退出
    * 信号完成某种清理动作，非本地跳转
* 可重入函数：即在多逻辑流中结果是预期的
  * 更新全局变量或静态的数据结构一般不是可重入，而使用本地变量的是可重入
* 确保信号处理器代码本身是可重入的，只调用可重入函数
* 当执行不安全的函数操作信号时，尽量的阻塞信号，结束后恢复
* errno在函数开始保存，退出时恢复

* sig_atomic_t 变量，总是使用volatile，保证流读写的原子性

### 终止信号的其他方法

* _exit()系统调用，可重入的，因为退出前总是显式的刷新stdio流
* kill -9
* 非本地跳转
* abort函数，核心转储

* siglongjmp sigsetjmp, 返回时会更具set的第二个参数：
  * 0，不设置掩码
  * 非0，将当前的掩码记录在envbuf中，返回设置掩码

```c
#include <tlpi_hdr.h>
#include <sys/utsname.h>
#include <time.h>
#include <signal.h>
#define _GNU_SOURCE
#include <string.h>
#include <setjmp.h>
#define _BSD_SOURCE

void printSigset(FILE *of, const char *prefix, const sigset_t *sigset)
{
	int cnt, sig;
	for (sig = 1, cnt = 0; sig < NSIG; sig++)
		if (sigismember(sigset, sig) == 1){
			cnt++;
			fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
		}
	if (cnt == 0)
		fprintf(of, "%s<emputy set>\n", prefix);
}
int printSigmask(FILE *of, const char *msg)
{
	sigset_t set;
	if  (msg != NULL)
		fprintf(of, "%s \n", msg);
	if (sigprocmask(SIG_BLOCK, NULL, &set) == -1)
		return -1;
	printSigset(of, "\t\t", &set);
	return 0;
}
int printPendingsig(FILE *of, const char *msg)
{
	sigset_t set;
	if (msg != NULL)
		fprintf(of, "%s \n", msg);
	if (sigsuspend(&set) == -1)
		return -1;
	printSigset(of, "\t\t", &set);

	return 0;
}

static volatile sig_atomic_t canJump = 0;
#ifdef USE_SIGSETJMP
static sigjmp_buf senv;
#else
static jmp_buf env;
#endif
void sigHandler(int sig)
{
	printf("In sigHandler:Receive sig %d (%s)\n", sig, strsignal(sig));
	printSigmask(stdout, NULL);
	if (!canJump)
	{
		printf("not set jump buf\n");
		return;
	}
#ifdef USE_SIGSETJMP
	siglongjmp(senv, 1);
#else
	longjmp(env, 1);
#endif
}
int main(int argc, char *argv[])
{
	struct sigaction sa;
	printSigmask(stdout, NULL);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigHandler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		errExit("sigaction");

#ifdef USE_SIGSETJMP
	printf("Call siglongjmp\n");
	if (sigsetjmp(senv, 1) == 0)
#else
	printf("call setJmp\n");
	if (setjmp(env) == 0)
#endif
		canJump = 1;
	else
		printSigmask(stdout, "After jump, sig mask is:\n");
	printf("Set suc\n");
	for (;;)
		pause();


}


```

### 系统调用和重启

* SA_RESTART标志
* 系统调用失败，将errno设置为EINTR, 信号处理函数返回后，可以手动的重启系统调用

```c
while((cnt = read(fd, buf, bufsize)) != cnt && errno == EINRE)
	contine;
if (cnt == -1)
	errExit("read");
```

* 启用sa_restart标志后，调用失败，内核代替进程自动重启，而无需判断errno

* sigsuspend(const sigset_t set)， 将set的信号集替换进程的信号掩码，然后挂起进程，直到捕获到此信号

