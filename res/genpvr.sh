#!/bin/bash

BASEDIR=$(dirname $0)
cd $BASEDIR
echo
ls
echo $BASEDIR
echo
read -p "警告：你确定要处理这个目录吗? (y/n) " RESP

if [ "$RESP" = "y" ]; then
rm -f *.pvr.ccz
rm -f *.plist

find . -name \*.png | sed 's/\.png//g' | \
xargs -I % -n 1 TexturePacker %.png \
--data %-hd.plist \
--sheet %.pvr.ccz \
--allow-free-size \
--disable-rotation \
--size-constraints POT \
--opt RGBA4444 \
--premultiply-alpha \
--dither-none-nn \
--border-padding 0 \
--main-extension -hd. \
--autosd-variant 0.5:.

rm -f *.plist
else
echo "请在正确目录执行此脚本"
fi
