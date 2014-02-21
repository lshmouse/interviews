#!/bin/bash -ex
BLADE_ROOT=${WORKSPACE}/src
BLADE_ARGS="-pdebug -j4 --gcov"
cd  ${BLADE_ROOT}

if [ ! -f ${BLADE_ROOT}/BLADE_ROOT ]
then
    touch ${BLADE_ROOT}/BLADE_ROOT
fi

echo '###############Begin Compile###############'

# only run blade clean in the building between the 1am to 3am every day
# Because of blade clean and then build is a time-comsuming operation
if [ `date +%H` -lt 3 ] && [ `date +%H` -gt 1 ]
then
    ${BLADE_ROOT}/common/builder/blade/blade clean $BLADE_ARGS
    rm -rf ${BLADE_ROOT}/build64_*
fi

${BLADE_ROOT}/common/builder/blade/blade build ${BLADE_ARGS} ${BLADE_ROOT}/tborg/... --generate-dynamic
echo '###############End Compile Success###############'


echo '###############Begin Unittest###############'
#${BLADE_ROOT}/common/builder/blade/blade test ${BLADE_ARGS} ${BLADE_ROOT}/tborg/... --test-jobs 4
# no parallel test run
${BLADE_ROOT}/common/builder/blade/blade test ${BLADE_ARGS} ${BLADE_ROOT}/tborg/...

echo '###############End Unittest Success###############'

if [ ! -d ${WORKSPACE}/ci_report/ ]
then
    mkdir -p ${WORKSPACE}/ci_report/
fi

echo '###############Begin Coverage###############'
# temporarily exclude monitor module when calc coverage rate
cd ${BLADE_ROOT}
lcovrp --ignore-sourc -d build64_debug/tborg -b .  -e '/data/gcc*' -e '/usr/' -e 'build64_debug/' -e 'common/' -e 'thirdparty/' -e 'poppy/' -e 'tborg/' -e 'xfs/' -e 'xcube' -e 'ca/' -e 'longconn/' -e 'taas/ '-e '.*_test\.cc' -e '.*_unittest\.cc' -o ${WORKSPACE}/coverage_report
echo '###############End Coverage Success###############'

echo '###############Begin Cpplint###############'
echo '###############End Cpplint Success###############'
