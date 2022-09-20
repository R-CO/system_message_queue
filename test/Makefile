
OPTIMIZATION_FLAG = -O2
DEBUG_SYMBOL = -g
#CXXFLAG1 = -Wall -Wextra -Weffc++ -Werror -std=c++17
CXXFLAG1 = -Wall -Wextra -Weffc++ -std=c++17
CXXFLAG2 = 
CXXFLAG = $(OPTIMIZATION_FLAG) $(DEBUG_SYMBOL) $(CXXFLAG1) $(CXXFLAG2) 

INCLUDE_DIR = -Igtest/include
LINK_DIR = -Lgtest/lib

LIBS = -lgtest -pthread

CXXFLAGS ?= $(CXXFLAG) $(INCLUDE_DIR)
LDFLAGS ?= $(LINK_DIR) $(LIBS)

CXX = g++

FILES = ../system_message_queue.cpp system_message_queue_test.cpp test.cpp

TARGETS = ../system_message_queue.o system_message_queue_test.o test.o

all: test.out
	@echo "Make done!"

test.out: $(TARGETS)
	$(CXX) $(TARGETS) $(CXXFLAGS) $(LDFLAGS) -o test.out

../system_message_queue.o: ../system_message_queue.cpp ../system_message_queue.hpp
	$(CXX) ../system_message_queue.cpp $(CXXFLAGS) $(LDFLAGS) -c -o ../system_message_queue.o

system_message_queue_test.o: system_message_queue_test.cpp
	$(CXX) system_message_queue_test.cpp $(CXXFLAGS) $(LDFLAGS) -c -o system_message_queue_test.o

test.o: test.cpp
	$(CXX) test.cpp $(CXXFLAGS) $(LDFLAGS) -c -o test.out

clean:
	rm ../system_message_queue.o
	rm *.out

