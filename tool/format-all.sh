cd "$(dirname "$0")"/..

clang-format -i include/utl/*.hpp \
                include/utl/__graph/*.hpp \
                include/utl/dispatch/*.hpp \
                src/*.cpp \
                test/utl/**.hpp \
                test/utl/**.cpp
