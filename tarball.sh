#!/bin/sh

mkdir othello-gbk
for FILE in *.cpp *.h Makefile
do
	iconv $FILE -f UTF-8 -t GBK > ./othello-gbk/$FILE
done
rm ./othello-gbk/heibaiqi_utf8.cpp
tar zcvf othello-gbk-`date -I`.tar.gz othello-gbk
rm -rf othello-gbk

