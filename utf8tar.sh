#!/bin/sh

mkdir othello-utf8
cp *.c *.cpp *.h Makefile othello-utf8/
rm othello-utf8/heibaiqi_utf8.cpp
tar zcvf othello-utf8-`date +%F-%H`.tar.gz othello-utf8
rm -rf othello-utf8

