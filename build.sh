CC=gcc
CFLAGS="-Wall -Wextra -O0 -g -Ilib"
POSTFIX=""
if [[ `uname` == "Windows_NT" ]]; then
    POSTFIX=".exe"
fi

mkdir -p out/test

if [ $# -eq 1 ]; then
    if [[ "$1" == "clean" ]]; then
        rm -rf out
        exit
    fi
    src="src/${1}.c"
    lib_names=`cat $src | grep "\"*\.h\"" | cut -d'"' -f2 | cut -d'.' -f1`
    lib=`echo $lib_names | awk '{ for (i = 1; i <= NF; i++) print "lib/" $i ".c" }'`
    echo "Compiling: $src"
    $CC $src $lib $CFLAGS -o "out/${1}${POSTFIX}"
elif [ $# -eq 2 ]; then
    if [[ "$1" != "test" ]]; then
        echo "Invalid arguments"
        exit
    fi
    if [[ "$2" == "all" ]]; then
      for src in test/*.c; do
          lib_names=`cat $src | grep "\"*\.h\"" | cut -d'"' -f2 | cut -d'.' -f1`
          lib=`echo $lib_names | awk '{ for (i = 1; i <= NF; i++) print "lib/" $i ".c" }'`
          echo "Compiling: $src"
          $CC $src $lib $CFLAGS -o "out/${src%.c}${POSTFIX}"
      done
      echo ""
      for test_out in out/test/*; do
          echo "$test_out"
          $test_out
          echo ""
      done
      exit
    fi

    src="test/${2}.c"
    lib_names=`cat $src | grep "\"*\.h\"" | cut -d'"' -f2 | cut -d'.' -f1`
    lib=`echo $lib_names | awk '{ for (i = 1; i <= NF; i++) print "lib/" $i ".c" }'`
    echo "Compiling: $src"
    $CC $src $lib $CFLAGS -o "out/test/${2}${POSTFIX}"
else
    for src in src/*.c; do
        lib_names=`cat $src | grep "\"*\.h\"" | cut -d'"' -f2 | cut -d'.' -f1`
        lib=`echo $lib_names | awk '{ for (i = 1; i <= NF; i++) print "lib/" $i ".c" }'`
        echo "Compiling: $src"
        src="${src##*/}"
        $CC $src $lib $CFLAGS -o "out/${src%.c}${POSTFIX}"
    done
fi
