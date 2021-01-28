
OPTIMIZATION_FLAG =
DEBUG_SYMBOL = -g
#CXXFLAG1 = -Wall -Wextra -Weffc++ -Werror -std=c++17
CXXFLAG1 = -Wall -Wextra -std=c++17
CXXFLAG2 = `wx-config --cxxflags`
CXXFLAG = $(OPTIMIZATION_FLAG) $(DEBUG_SYMBOL) $(CXXFLAG1) $(CXXFLAG2) 

INCLUDE_DIR = 
LINK_DIR = 

LIBS = `wx-config --libs` -pthread

CXXFLAGS ?= $(CXXFLAG) $(INCLUDE_DIR)
LDFLAGS ?= $(LINK_DIR) $(LIBS)

CXX = g++

CLIENT_FILES = client_gui.cpp client_main_frame.cpp \
         wxFormBuilder/gui_widgets_base.cpp
SERVER_FILES = server_gui.cpp server_main_frame.cpp \

all: system_message_queue.o
	$(CXX) $(CLIENT_FILES) system_message_queue.o $(CXXFLAGS) $(LDFLAGS) -o client_gui
#	$(CXX) $(SERVER_FILES) system_message_queue.o $(CXXFLAGS) $(LDFLAGS) -o server_gui

system_message_queue.o: ../system_message_queue.cpp ../system_message_queue.hpp
	$(CXX) ../system_message_queue.cpp $(CXXFLAGS) $(LDFLAGS) -c	


clean:
	rm *.o 
	rm client_gui
	rm server_gui

