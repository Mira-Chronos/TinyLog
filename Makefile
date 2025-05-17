CXX=g++
CPPFLAGS=-g -Wall -Wextra -std=c++17
LDFLAGS=
LDLIBS=

SRCS=main.cpp TLog.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(CPPFLAGS) -g -o main $(OBJS) $(LDLIBS)

clean:
	rm *.o mainSDL
