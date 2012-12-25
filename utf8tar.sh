#!/bin/sh

mkdir othello-utf8
cp $(cat filelist) othello-utf8/
tar zcvf othello-utf8-`date +%F-%H`.tar.gz othello-utf8
rm -rf othello-utf8

