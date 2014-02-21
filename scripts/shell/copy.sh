#!/bin/sh
ip=`/sbin/ifconfig | grep 'inet addr:'| grep -v '127.0.0.1' | cut -d: -f2 | awk '{ print $1}'`

#./fu64 ls /xfs/tjd2-websearch/home/xcube/url_import --role=xcube --identity=xcube --ca_server=mock.soso.oa.com
xfs=/xfs/tjd2-websearch/home/xcube/url_import/${ip}/
args=" --role=xcube --identity=xcube --ca_server=mock.soso.oa.com"
retry=3

# create dir
./fu64 mkdir $xfs $args

while read filename
do
    if [ -f $filename ]; then
        success=0
        data=`echo $$filename | cut -d "/" -f 2`
        id=`echo $$filename | cut -d "/" -f 5`
        name=`echo $$filename | cut -d "/" -f 6`
        ./fu64 mkdir "$xfs/$data" $args
        ./fu64 mkdir "$xfs/$data/$id" $args
        dst_xfs="$xfs/$data/$id"

        for ((i =0 ; i < $retry; i++)); do
            local_size=`ls -al copy.sh | awk '{print $5}'`
            # copy file
            ./fu64 cp $filename $dst_xfs/ $args
            if [ $? != 0 ]; then
                #echo "copy file $filename to xfs: $xfs failed!"
                continue
            fi
            # remotw size
            remote_size=`./fu64 ls $dst_xfs/$name $args -al | grep $name | awk '{print $8}'`

            echo "$local_size $remote_size"
            if [ "$local_size" != "$remote_size" ]; then
                #echo "copy file $filename to xfs: $xfs failed! file size not equal!"
                continue;
            fi
            success=1
            break;
        done

        if [ "$success" != "1" ]; then
            echo "copy file $filename to xfs: $xfs failed!"
        fi
    fi
done
