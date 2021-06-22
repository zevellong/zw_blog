# 安装WSL

1. 打开wsl选项，打开开发者模式，重启

2. 设置密码

   ```bash
   sudo passwd root
   ```

3. 跟换apt源

   ```bash
   sudo vi /etc/apt/source.list
   
   按照 https://mirror.tuna.tsinghua.edu.cn/help/ubuntu/
   ```

4. 禁用bash提示音(windows 上太烦人)

   ```bash
   sudo vi /etc/inputrc
   取消注释 set bell-style none
   重启
   ```

5. 安装软件

   gcc、gdb、g++、make、bochs、nasm、lua5.2

