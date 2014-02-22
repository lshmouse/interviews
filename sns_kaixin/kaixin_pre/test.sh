#!/bin/bash
rm -f myresult.txt

./ipfinder testdata/ipbase.txt testdata/ipcheck.txt > myresult.txt

echo "diff result!:"
diff myresult.txt testdata/result.txt

#rm -rf myresult.txt 
