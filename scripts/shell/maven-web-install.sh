#!/bin/bash
echo "开始部署"
webdir=/home/liushaohui/softwares/resin-3.0.21/webapps/analysis-0.0.1/
echo "依赖目录：${webdir}"
#回到maven工程根目录
cd ..
#删除原来的web目录
rm -rf ${webdir}/*
#拷贝webapp目录
cp -r src/main/webapp/* ${webdir}
#maven 编译打jar包
mvn clean compile package
#插件依赖包目录
mkdir ${webdir}/WEB-INF/lib
#部署jar包
cp target/analysis-0.0.1-SNAPSHOT.jar ${webdir}/WEB-INF/lib/
#部署依赖jar包
mvn dependency:copy-dependencies -DoutputDirectory=${webdir}/WEB-INF/lib/
echo "部署完成！"

