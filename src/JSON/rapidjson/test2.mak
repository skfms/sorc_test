.SUFFIXES:.cpp .o

PLATFORM=$(shell uname)
MODULE=test2

ifeq ($(PLATFORM), AIX)
	CXX=xlc_r
	LINK=xlc_r
else ifeq ($(PLATFORM), HP-UX)
	PLATFORM=HPXX
	CXX=aCC
	LINK=aCC
else ifeq ($(PLATFORM), SunOS)
	CXX=CC
	LINK=CC
else
	CXX=g++
	LINK=g++
endif

ifeq ($(PLATFORM), AIX)
	CFLAGS=-q64 -O3 
	LFLAGS=-q64 -lC
else ifeq ($(PLATFORM), HPXX)
#	HP-UX IA
	CFLAGS=+DD64 -AA -ext -mt -g0
	LFLAGS=+DD64 -AA
#	HP-UX PA-RISC
#	CFLAGS=+DA2.0W -AA -ext -mt -g0
#	LFLAGS=+DA2.0W -AA
else ifeq ($(PLATFORM), SunOS)
	CFLAGS=-xarch=v9 -mt
	LFLAGS=-xarch=v9
else
	CFLAGS=-I ../../include
endif

EXEC=$(MODULE)

OBJS=test2.o
     

all : build

build : $(OBJS)
	$(LINK) -o $(EXEC) $(OBJS) $(LFLAGS)

%.o : %.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJS) $(EXEC) core