#!/bin/bash
make clean

rm -rf ./CMakeFiles ./CMakeCache.txt ./Makefile ./cmake_install.cmake CTestTestfile.cmake ./xml ./html ./latex  ./Testing/Binary ./Testing/Coverage ./Testing/Temporary

find . -maxdepth 10 -name "*.aux" -exec rm -r {} \;
find . -maxdepth 10 -name "*.bbl" -exec rm -r {} \;
find . -maxdepth 10 -name "*.blg" -exec rm -r {} \;
find . -maxdepth 10 -name "*.lof" -exec rm -r {} \;
find . -maxdepth 10 -name "*.log" -exec rm -r {} \;
find . -maxdepth 10 -name "*.lol" -exec rm -r {} \;
find . -maxdepth 10 -name "*.lot" -exec rm -r {} \;
find . -maxdepth 10 -name "*.nav" -exec rm -r {} \;
find . -maxdepth 10 -name "*.out" -exec rm -r {} \;
find . -maxdepth 10 -name "*.snm" -exec rm -r {} \;
find . -maxdepth 10 -name "*.synctex.gz" -exec rm -r {} \;
find . -maxdepth 10 -name "*.toc" -exec rm -r {} \;
find . -maxdepth 10 -name "*.vrb" -exec rm -r {} \;

find . -maxdepth 10 -empty -type f -exec rm -r {} \;

find . -maxdepth 10 -name "*.c"   -print0 | xargs -0 clang-format -i -sort-includes
find . -maxdepth 10 -name "*.cpp" -print0 | xargs -0 clang-format -i -sort-includes
find . -maxdepth 10 -name "*.hpp" -print0 | xargs -0 clang-format -i -sort-includes
echo "clean-up done"
