.SUFFIXES:.cpp .o

PLATFORM=$(shell uname)
MODULE=test

CXX=g++
LINK=g++

CFLAGS=-g -m32 -I $(O2MROOT)/src/include
LFLAGS=-g -m32 -L $(O2MROOT)/lib -ljsoncpp

#CFLAGS=-g -m64 -I $(O2MROOT)/src/include -I $(O2MROOT)/src/include/oracle
#LFLAGS=-g -m64 -L $(O2MROOT)/lib -lclntsh -lnnz19

EXEC=$(MODULE)

OBJS=test.o ./../../common/sutil.o ./../../common/exception.o

all : build

build : $(OBJS)
	$(LINK) -o $(EXEC) $(OBJS) $(LFLAGS)

%.o : %.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJS) $(EXEC) core
