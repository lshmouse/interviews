#!/bin/bash
make clean &&
make &&
./friend_finder testdata/vocab.txt testdata/friends.txt testdata/query.txt > myresult.txt

#echo "diff result!:"
diff myresult.txt testdata/ans.txt

#rm -rf myresult.txt 
