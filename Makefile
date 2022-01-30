CC = g++
SRC_DIR = src
SRC_FILES = ${shell where /R src *.cpp}
COMPILER_FLAGS = -c -std=c++14 -m64 -g -Wall
INCLUDE_PATHS = -I include
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
BUILD_DIR = bin

clear:
	del .\bin\*.o
	del .\bin\*.exe

all: clear
	${CC} -c ${SRC_FILES} ${COMPILER_FLAGS} ${INCLUDE_PATHS}
	move *.o ${BUILD_DIR}
	${CC} ${BUILD_DIR}/*.o -o ${BUILD_DIR}/main ${LINKER_FLAGS}

run:
	bin/main.exe