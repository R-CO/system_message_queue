
OPTIMIZATION_FLAG =
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

all: 
	$(CXX) $(FILES) $(CXXFLAGS) $(LDFLAGS) -o test.out 


clean:
	rm *.out

