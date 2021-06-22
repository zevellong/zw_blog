# OS

- 特权级模型

  - 一致代码段:简单理解，就是操作系统拿出来被共享的代码段,可以被低特权级的用户直接调用访问的代码。通常这些共享代码，是"不访问"受保护的资源和某些类型异常处理。
     比如一些数学计算函数库,为纯粹的数学运算计算，被作为一致代码段。
- 一致代码段的限制作用：
  
  - 特权级高的程序不允许访问特权级低的数据:核心态不允许调用用户态的数据.  
  -  特权级低的程序可以访问到特权级高的数据.但是特权级不会改变:用户态还是用户态.
  - 非一致代码段
  
      - 为了避免低特权级的访问而被操作系统保护起来的系统代码.
  - 非一致代码段的限制作用
      - 	只允许同级间访问.
      - 	绝对禁止不同级访问:核心态不用用户态.用户态也不使用核心态.
  - 特权级
    - CPL：是当前进程的权限级别(Current Privilege Level)，
    - 是当前正在执行的代码所在的段的特权级，存在于cs寄存器的低两位。
  - RPL:说明的是进程对段访问的请求权限(Request Privilege Level)，
    - DPL:存储在段描述符中，规定访问该段的权限级别(Descriptor Privilege Level)，
  - 每个段的DPL固定。当进程访问一个段时，需要进程特权级检查，一般要求DPL >= max {CPL, RPL}

## GDB


gcc -gstabs -o xxx xxx.c //-gstabs选项编译或者汇编可执行文件
gdb xxx

常用命令：
    list
    break main
    next
(1) 数据检查命令
info registers　打印寄存器信息
print/(dxt) $eax    打印10 16 2 进制寄存器信息
x/nyz &output  　　　n为整数，要显示的字符数    y可选　cdx　字符１０进制　１６　ｚ（bhw）(8bit字节　16bit半字　32bit字)



## 第五章disp_str() 函数bug

### 2020年 03月 21日 星期六 13:38:00 CST

1.	*描述*
   第一次使用正常，第二次使用乱码
2.	反汇编
   先进入kernel程序进入点--**0x30400** 
   反汇编

```borchs
u 0x30400 0x304A0#反汇编160字节
```

	反汇编代码如下:

```asm
u 0x30423 0x30483
00030423: (                    ): push ebp                  ; 55
00030424: (                    ): mov ebp, esp              ; 89e5
00030426: (                    ): push ebx                  ; 53
00030427: (                    ): sub esp, 0x00000014       ; 83ec14
0003042a: (                    ): call .+172                ; e8ac000000
0003042f: (                    ): add ebx, 0x00002bd1       ; 81c3d12b0000
00030435: (                    ): sub esp, 0x0000000c       ; 83ec0c
00030438: (                    ): lea eax, dword ptr ds:[ebx-8192] ; 8d8300e0ffff
0003043e: (                    ): push eax                  ; 50
0003043f: (                    ): call .+364                ; e86c010000
00030444: (                    ): add esp, 0x00000010       ; 83c410
00030447: (                    ): sub esp, 0x0000000c       ; 83ec0c
0003044a: (                    ): lea eax, dword ptr ds:[ebx-8170] ; 8d8316e0ffff
00030450: (                    ): push eax                  ; 50
00030451: (                    ): call .+346                ; e85a010000
00030456: (                    ): add esp, 0x00000010       ; 83c410
00030459: (                    ): sub esp, 0x0000000c       ; 83ec0c
0003045c: (                    ): lea eax, dword ptr ds:[ebx-8163] ; 8d831de0ffff
00030462: (                    ): push eax                  ; 50
00030463: (                    ): call .+328                ; e848010000
00030468: (                    ): add esp, 0x00000010       ; 83c410
0003046b: (                    ): sub esp, 0x0000000c       ; 83ec0c
0003046e: (                    ): lea eax, dword ptr ds:[ebx-8157] ; 8d8323e0ffff
00030474: (                    ): push eax                  ; 50
00030475: (                    ): call .+310                ; e836010000
0003047a: (                    ): add esp, 0x00000010       ; 83c410
0003047d: (                    ): mov eax, 0x00033c20       ; c7c0203c0300
```

	disp_str汇编代码如下：

```asm
disp_str:
	push	ebp
	push	esi
	push	edi
	push	ebx
	mov	ebp, esp

	mov	esi, [ebp + 20]	; pszInfo
	mov	edi, [disp_pos]
	mov	ah, 0Fh
.1:
	lodsb
	test	al, al
	jz	.2
	cmp	al, 0Ah	; 是回车吗?
	jnz	.3
	push	eax
	mov	eax, edi
	mov	bl, 160
	div	bl
	and	eax, 0FFh
	inc	eax
	mov	bl, 160
	mul	bl
	mov	edi, eax
	pop	eax
	jmp	.1
.3:
	mov	[gs:edi], ax
	add	edi, 2
	jmp	.1

.2:
	mov	[disp_pos], edi
	pop	ebx
	pop	edi
	pop	esi
	pop	ebp
	ret
```

3.	分析
   第一次调用disp_str后,C代码里面会使用ebx寄存器,但是ebx在disp_str里面使用过,
   而且没有保持原始值
   导致第二次调用时使用的值有错误

4.	解决方法
   在disp_str 加入两行保存可能使用的寄存器

```asm
push	reg1
push	reg2
...
pop	reg2
pop	reg1
```



