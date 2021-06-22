# 学习ATT汇编

## Makefile

```makefile
SOURCE = linkstdio.s
TARGET = $(SOURCE:.s=)
OBJ = $(SOURCE:.s=.o)

ASFLAG = -gstabs
CODE64 = 0 #default 32 bits code
LDFLAG = 

ifeq ($(CODE64), 0)
	LDFLAG += -m elf_i386
	ASFLAG += --32
else
	LDFLAG += -dynamic-linker /lib/ld-linux-x86-64.so.2 -lc  
endif

everything : $(TARGET)	
	@if (( $(CODE64) == 0 )); \
	then \
		echo 'Output:$(TARGET) [32 Bits]'; \
	else \
		echo 'Output:$(TARGET) [64 Bits]'; \
	fi
$(TARGET) : $(OBJ)
	ld $(LDFLAG) -o $@ $<

$(OBJ) : $(SOURCE)
	as $(ASFLAG) -o $@ $<

clean :
	rm -rf $(TARGET) $(OBJ)
all :	clean everything

# if注意使用双括号 [[]] (())
#  语句如 echo 后加上 ;\ 防止出错

```



## 编译 调试

```bash
# 32 bits
rm -rf test test.o
as -gstabs --32 -o test.o test.s
ld -m elf_i386 -o test test.o


# 64 bits
rm -rf test test.o
as -gstabs -o test.o test.s
ld  -o test test.ovim

# link glibc 64
ld  -dynamic-linker /lib/ld-linux-x86-64.so.2 -o test -lc  test.o  

```

| GDB  查看内存                |                                                       |
| ---------------------------- | ----------------------------------------------------- |
| info r                       | 寄存器b                                               |
| info $rax                    | rax寄存器                                             |
| x 0xfffffff                  | 直接访问wwd                                           |
| x / num [b h w g] [c d f x]  | 数字 [字节 半字 字 giant] [字符 10进制 浮点数 16进制] |
| **反汇编**                   |                                                       |
| disas                        | 反汇编当前函数                                        |
| disas foo                    | 反汇编foo函数                                         |
| disas 0x5655619d             | 反汇编xx地址处函数                                    |
| disas 0x5655619d, 0x565561b3 | 反汇编xx到xx                                          |
| print /x $rip                | 输出当前pc 16进制                                     |



### 汇编语言的构成

* .section .data -- 变量
* .section .bss -- 常量，0初始化的，缓冲区
* .section .text -- 代码段
* 

### 打印字符串

* 64位下，.long 和 .int 都是4字节，**可能导致错误**
* .quad 为8字节
* printf 使用普通寄存器传递浮点数会发生错误
* 测试代码如下

```asm
# int 0x80
# call printf


.section .data
# 变量
Len:
	.quad 10, 20 ,30 , 40, 50
Flt:
	.double 3.14, 2.77, 0.618, 102.4
Str1:
	.asciz "long %ld %ld \n float %lf %lf \n equ %ld\n"  #c风格字符串，末尾为0
Str2:
	.ascii "hello, world \n"
Str3:
	.asciz "Long %ld \n"
# 常量
Def:
	.equ LINUX_SYSCALL, 0x80
	.equ factor, 3
.section .bss
# 缓冲区 .comm .lcomm
.lcomm buffer, 16

.section .text
.global _start

_start:
   	movq	$LINUX_SYSCALL , %r9
   	movq	Flt + 8, %r8
   	movq	Flt, %rcx	
   	movq	Len + 8, %rdx
   	movq	Len, %rsi
   	movq	$Str1, %rdi	
	call	printf
	movq	$0, %rax
	call	exit

```

```bash
# manjaro复制到剪贴板
ls | xclip -selection clipboard

```



## 函数传递参数

| arg  | 1    | 2    | 3    | 4    | 5    | 6    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 64   | rdi  | rsi  | rdx  | rcx  | r8   | r9   |
| 32   | edi  | esi  | edx  | ecx  | r8d  | r9d  |
| 16   | di   | si   | dx   | cx   | r8w  | r9w  |
| 8    | dil  | sil  | dl   | cl   | r8b  | r9b  |

* 浮点数使用上述寄存器传递参数会报错
* 大于六个参数时，使用栈传递参数
* rbx, rbp, r12~r15为被调用者保持寄存器，使用这些寄存器需要先保护这些寄存器的值，通常使用压栈

```asm
#64 bit, use function
.section .data
	str1:
		.asciz "In func a=%ld  b=%ld\n"
	str2:
		.asciz "In main return=%ld \n"
	value:
		.quad 0
.section .text
.globl _start
_start:
	movq	$5, %rsi
	movq	$6, %rdi
	call	func
	movq	value, %rsi
	movq	$str2, %rdi
	call	printf
	movq	$0, %rdi
	call	exit

func:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, %rax
	imulq	%rsi, %rax
	movq	%rax, value
	movq	%rsi, %rdx
	movq	%rdi, %rsi
	movq	$str1, %rdi
	call	printf
	
	movq	%rbp, %rsp	b 
	popq	%rbp传送数据
	ret
	
```



```asm
#32 bit

.section .data
	str1:
		.ascii "In func\n"
	str2:
		.ascii "In main\n"
	value:
		.quad 0
.section .text
.globl _start
_start:
	pushl	$6
	pushl	$5
	call	func

	#print str2
	movl	$4, %eax
	movl	$1, %ebx
	movl	$str2, %ecx
	int	$0x80
	#print value

	movl	$1, %eax
	movl	$0, %ebx
	int	$0x80
func:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	imull	12(%ebp), %eax
	movl	%eax, value
	movl	%ebp, %esp(%ebp)
	popl	%ebp
	ret
	
```



## 函数栈

* 32 位函数栈帧

|            |           |
| ---------- | --------- |
| 函数参数3  | 16(%ebp)  |
| 函数参数2  | 12(%ebp)  |
| 函数参数1  | 8(%ebp)   |
| 返回地址   | 4(%ebp)   |
| 旧ebp      | (%ebp)    |
| 局部变量1  | -4(%ebp)  |
| 局部变量2  | -8(%ebp)  |
| 局部变量3h | -12(%ebp) |
|            |           |
|            |           |
|            |           |

- main 函数栈  32bit

```shell
gdb> set args AAA BBB CCC
gdb> b _start
gdb> r
gdb> x /20x $esp
----------------
(gdb) x /20x $esp
0xffffd5e0:	0x00000004	0xffffd7d7	0xffffd803	0xffffd807
0xffffd5f0:	0xffffd80b	0x00000000	0xffffd80f	0xffffd82a
0xffffd600:	0xffffd853	0xffffd8a7	0xffffd8fd	0xffffd90e
0xffffd610:	0xffffd928	0xffffd952	0xffffd964	0xffffd96c
0xffffd620:	0xffffd987	0xffffd99e	0xffffd9c1	0xffffd9d7
---------------
# 0x000004 为argc

#第二个为 文件名字符串的地址
(gdb) x /40cb 0xffffd7d7
0xffffd7d7:	47 '/'	104 'h'	111 'o'	109 'm'	101 'e'	47 '/'	122 'z'	119 'w'
0xffffd7df:	47 '/'	108 'l'	101 'e'	97 'a'	114 'r'	110 'n'	47 '/'	118 'v'
0xffffd7e7:	115 's'	99 'c'	111 'o'	100 'd'	101 'e'	95 '_'	119 'w'	111 'o'
0xffffd7ef:	114 'r'	107 'k'	115 's'	112 'p'	97 'a'	99 'c'	101 'e'	47 '/'
0xffffd7f7:	99 'c'	115 's'	97 'a'	112 'p'	112 'p'	47 '/'	102 'f'	117 'u'

#后三个为argv的地址
(gdb) x /16cb 0xffffd803
0xffffd803:	65 'A'	65 'A'	65 'A'	0 '\000'	66 'B'	66 'B'	66 'B'	0 '\000'
0xffffd80b:	67 'C'	67 'C'	67 'C'	0 '\000'	81 'Q'	84 'T'	95 '_'	81 'Q'

#argv后则为 一串空字符

#后面的字符串则为 指向环境变量的指针 环境变量命令行参数
(gdb) x /16cb 0xffffd9d7
0xffffd9d7:	71 'G'	78 'N'	79 'O'	77 'M'	69 'E'	95 '_'	84 'T'	69 'E'
0xffffd9df:	82 'R'	77 'M'	73 'I'	78 'N'	65 'A'	76 'L'	95 '_'	83 'S'

```

* 64bit

```bash
(gdb) set args AAA BBB CCC
(gdb) b _start 
(gdb) r
(gdb) x /20xg $rsp
0x7fffffffe420:	0x0000000000000004	0x00007fffffffe7d7
0x7fffffffe430:	0x00007fffffffe803	0x00007fffffffe807
0x7fffffffe440:	0x00007fffffffe80b	0x0000000000000000
0x7fffffffe450:	0x00007fffffffe80f	0x00007fffffffe82a
0x7fffffffe460:	0x00007fffffffe853	0x00007fffffffe8a7
0x7fffffffe470:	0x00007fffffffe8fd	0x00007fffffffe90e
0x7fffffffe480:	0x00007fffffffe928	0x00007fffffffe952
0x7fffffffe490:	0x00007fffffffe964	0x00007fffffffe96c
0x7fffffffe4a0:	0x00007fffffffe987	0x00007fffffffe99e
0x7fffffffe4b0:	0x00007fffffffe9c1	0x00007fffffffe9d7
# 可见，64bit也有相似的结构

(gdb) x /20cb 0x00007fffffffe7d7
0x7fffffffe7d7:	47 '/'	104 'h'	111 'o'	109 'm'	101 'e'	47 '/'	122 'z'	119 'w'
0x7fffffffe7df:	47 '/'	108 'l'	101 'e'	97 'a'	114 'r'	110 'n'	47 '/'	118 'v'
0x7fffffffe7e7:	115 's'	99 'c'	111 'o'	100 'd'

```



* 可以总结出main函数栈为

|                    |      |
| ------------------ | ---- |
| 环境变量命令行参数 |      |
| 指向环境变量的指针 |      |
| 0x00               |      |
| argv[n]            |      |
| ....               |      |
| argv[2]            |      |
| argv[1]            |      |
| 函数名             |      |
| argc               | %rsp |

## 函数模板

```asm
function:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp  #分配2个局部变量
	...
	
	movl	%ebp, %esp
	popl	%ebp
	ret
	
	
# 传递参数， 调用
	pushl %eax
	pushl %ebx
	call function
	addl $8, %esp #恢复栈
```

## 字符串

* esi: 源
* edi: 目标
* DF: 方向标志
* 两种取地址的方法

```asm
leal output, %edi
movl $output, %esi
```

* cld将DF清零，std设置DF标志
* movsb movsw movsl %esi --> %edi 执行后无需操作si di，自动增加
* rep指令  重复的执行一条指令，直到ecx为0
* lodsb lodsw lodsl 把esi处加载到 eax
* stosb stosw stosl 把eax加载到edi
* cmpsb cmpsw cmpsl 与eax比较
* scasb w l 比较内存的4字节和eax