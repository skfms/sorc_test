.SUFFIXES:.cpp .o

PLATFORM=$(shell uname)
MODULE=jsoncpp_test

CXX=g++
LINK=g++

CFLAGS=-g -I ./../../../include
LFLAGS=-g -L ./../../../lib -ljsoncpp

EXEC=$(MODULE)

OBJS=jsoncpp_test.o ./../../../comm_cpp/sutil.o ./../../../comm_cpp/exception.o

all : build

build : $(OBJS)
	$(LINK) -o $(EXEC) $(OBJS) $(LFLAGS)

%.o : %.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJS) $(EXEC) core
