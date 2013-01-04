#!/bin/sh

mkdir othello-gbk
for FILE in $(cat filelist)
do
	iconv $FILE -f UTF-8 -t GBK > ./othello-gbk/$FILE
done
tar zcvf othello-gbk-`date -I`.tar.gz othello-gbk
rm -rf othello-gbk

