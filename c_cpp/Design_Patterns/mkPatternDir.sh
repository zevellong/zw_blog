#!/bin/sh
# set +m  #通过关闭“监控模式”,使shell终止后台作业后不打印报告
if [[  $1 == "-h"  ]] || [ $# -ne 1 ]; then
	echo "mkPatternDir create a new dir for learn Design PatternDir~~"
	echo "Usage:mkPatternDir [-h] [name]"
	kill -9 $$
fi

if [ ! -d $1 ]; then
	mkdir $1
	mkdir $1/uml
	echo "#include <iostream>" >> $1/$1.cpp
	echo "#include <string>" >> $1/$1.cpp
	echo "using std::cout;" >> $1/$1.cpp
	echo "using std::endl;" >> $1/$1.cpp
	echo "using std::string;" >> $1/$1.cpp
	cp "./umlTmp.tex" $1/uml/$1.tex
	echo "Create Info:"
	du -h -a $1 | awk '{print "\t" $0}'

else
	echo "$1 existed"
fi
