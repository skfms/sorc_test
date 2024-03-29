.SUFFIXES:.cpp .o

PLATFORM=$(shell uname)
MODULE=test

CXX=g++
LINK=g++

CFLAGS=-g -m32 -I ./../../include
LFLAGS=-g -m32 -L ./../../lib -ljsoncpp

EXEC=$(MODULE)

OBJS=test.o ./../../common/sutil.o ./../../common/exception.o

all : build

build : $(OBJS)
	$(LINK) -o $(EXEC) $(OBJS) $(LFLAGS)

%.o : %.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJS) $(EXEC) core
