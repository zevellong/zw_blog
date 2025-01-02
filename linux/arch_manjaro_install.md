# manjaro gnome install

- pacman

```shell
sudo pacman-mirrors -i -c China -m rank
sudo pacman -Syy
#在 /etc/pacman.conf 文件末尾添加以下两行

[archlinuxcn]
#SigLevel = TrustAll
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
[antergos]
#SigLevel = TrustAll
Server = https://mirrors.tuna.tsinghua.edu.cn/antergos/$repo/$arch

#安装 archlinuxcn-keyring 包导入GPG key
sudo pacman -Sy archlinuxcn-keyring
sudo pacman -S yaourt
```

- speaker

```shell
#adding next code to /etc/modprobe.d/alsa-base.conf
options snd-hda-intel dmic_detect=0 

#reboot
```

- 

```shell
sudo pacman -S vscode vim gcc typora bochs make cmake figlet screenfetch gdb chromium netease-cloud-music vlc inkscape clang ccls llvm
```

* keyboard 



* vim

```c++
vim plugin
sudo python3 get-pip.py             
sudo npm install -g neovim
pip3 install --user --upgrade pynvim

```

* 输入法

```
sudo pacman -S ibus ibus-rime
#adding in ~/.xprofile or ~/.bashrc
export GTK_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export QT_IM_MODULE=ibus
ibus-daemon -d -x

# seting find input medtod
```



* anaconda

```shell
#download anaconda64.sh
chmod a+x

echo 'export PATH="~/anaconda3/bin:$PATH"'>>~/.bashrc  
source ~/.bashrc    
conda config --set auto_activate_base false 

conda config --add channels https://mirrors.ustc.edu.cn/anaconda/pkgs/free/
conda config --add channels https://mirrors.ustc.edu.cn/anaconda/pkgs/main/
conda config --set show_channel_urls yes
conda config --add channels https://mirrors.ustc.edu.cn/anaconda/cloud/bioconda/

sudo conda update anaconda 
sudo conda install spyder=5.0.3

```

* latex

```shell
# download iso
sudo pacman -S perl-tk tcl tk
sudo mount -o loop texlive.iso /mnt
sudo mount -o loop -t iso9660 texlive2021.iso /mnt/loop
cd /mnt
sudo  perl ./install-tl -gui 
sudo pacman -S texstudio
sudo umount
# 选择添加符号链接

#更新
tlmgr option repository ctan #选择镜像
tlmgr update --self --all #更新
tlmgr update --reinstall-forcibly-removed --all #强制更新
```

* vscode

```shell
#插件 c code runner
#setting->zoom level:1  text font:18
```

* 

```shell
amule # 下载软件
woeusb #制作win10 u盘
blast
debtap #安装deb包   https://blog.csdn.net/weixin_43968923/article/details/100170418
xclip

```

* vm

```
https://blog.csdn.net/lpwmm/article/details/80304637
https://blog.csdn.net/c123728529/article/details/50825417
```

- sorfware

```sh
sudo pacman -S pdftk jre-openjdk mysql rstudio-desktop-bin
yaourt cppman
sudo chmod +rw /usr/lib/R/library
sudo vim /etc/pacman.conf 
#忽略r更新

sudo pacman -S libreoffice **zh_cn
```

- proxy

```zsh
# https://shuttle.onl/clientarea.php
# https://iochen.com/post/v2gen-usage/   v2gen
./v2gen_amd64_linux -u https://sub.shuttle.mobi/app/qv2ray/1601/X3FCL1PS8Anu -o shuttle.json
yaourt qv2ray

git config --global http.sslVerify true
git config --global https.sslVerify true
git config --global http.proxy 'http://127.0.0.1:8889'
git config --global https.proxy 'http://127.0.0.1:8889'
 
# ~/.gitconfig 
[http]
	sslVerify = true
	proxy = http://127.0.0.1:8889
[https]
	sslVerify = true
	proxy = http://127.0.0.1:8889
vim /etc/profile
# export http_proxy=http://127.0.0.1:8889               # export https_proxy=http://127.0.0.1:8889


#terminal使用代理
#修改/etc/profile
export http_proxy=http://127.0.0.1:8889
export https_proxy=http://127.0.0.1:8889
```

- zsh

```zsh

git clone https://gitee.com/mirrors/oh-my-zsh.git ~/.oh-my-zsh
cat ~/.oh-my-zsh/templates/zshrc.zsh-template >> ~/.zshrc

git clone https://gitee.com/pankla/zsh-syntax-highlighting.git ~/.oh-my-zsh/plugins
git clone https://gitee.com/pankla/zsh-syntax-highlighting.git ~/.oh-my-zsh/plugins/zsh-syntax-highlighting
git clone https://gitee.com/fatbadfrog/zsh-autosuggestions.git ~/.oh-my-zsh/plugins/zsh-autosuggestions
#set .zshrc
plugins=(git history history-substring-search zsh-syntax-highlighting sudo zsh-autosuggestions)
ZSH_THEME="ys"
```

* web

```zsh
# chrome
spring

# firefox
# kimi no 
# https://addons.mozilla.org/zh-CN/firefox/addon/animated-kimi-no-na-wa/?utm_source=addons.mozilla.org&utm_medium=referral&utm_content=search
```

* fonts

```lua
sudo pacman -S ttf-fira-code
vscode: Fira Code, Mircosoft Yahei
使用kfontinst 安装字体
系统设置：见图片
```

