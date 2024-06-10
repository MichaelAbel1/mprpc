#!/bin/bash

set -e

rm -rf `pwd`/build/*
cd `pwd`/build &&
    cmake .. &&
    make

cd ..
cp -r `pwd`/src/include `pwd`/lib

# 将动态库 libmymuduo.so 安装到 /usr/lib 目录:
# 这是为了让链接器能够找到这个静态库文件
# /usr/local/lib 目录用于存放用户自行安装的本地库文件，而 /usr/lib 目录用于存放系统级别的库文件。
cp $(pwd)/lib/libmprpc.a /usr/local/lib