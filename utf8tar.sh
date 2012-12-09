#!/bin/sh

mkdir othello-utf8
cp *.cpp *.h Makefile othello-utf8/
tar zcvf othello-utf8-`date -I`.tar.gz othello-utf8
rm -rf othello-utf8

