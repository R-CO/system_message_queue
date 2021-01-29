#
# Author: R-CO
# E-mail: daniel1820kobe@gmail.com
# Date: 2021-01-29
#

OPTIMIZATION_FLAG = -O2
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

CLIENT_TARGETS = client_gui.o client_main_frame.o wxFormBuilder/gui_widgets_base.o \
                 ../system_message_queue.o

SERVER_TARGETS = wxFormBuilder/gui_widgets_base.o \
                 ../system_message_queue.o

all: client_gui server_gui
	@echo "Make done!"

client_gui: $(CLIENT_TARGETS)
	$(CXX) $(CLIENT_TARGETS) $(CXXFLAGS) $(LDFLAGS) -o client_gui

server_gui: $(SERVER_TARGETS)
	@echo
#	$(CXX) $(server_TARGETS) $(CXXFLAGS) $(LDFLAGS) -o server_gui

system_message_queue.o: ../system_message_queue.cpp ../system_message_queue.hpp
	$(CXX) ../system_message_queue.cpp $(CXXFLAGS) $(LDFLAGS) -c	

../system_message_queue.o: ../system_message_queue.cpp ../system_message_queue.hpp
	$(CXX) ../system_message_queue.cpp $(CXXFLAGS) $(LDFLAGS) -c -o ../system_message_queue.o

client_gui.o: client_gui.cpp client_gui.hpp
	$(CXX) client_gui.cpp $(CXXFLAGS) $(LDFLAGS) -c -o client_gui.o

client_main_frame.o: client_main_frame.cpp client_main_frame.hpp
	$(CXX) client_main_frame.cpp $(CXXFLAGS) $(LDFLAGS) -c -o client_main_frame.o

wxFormBuilder/gui_widgets_base.o: wxFormBuilder/gui_widgets_base.cpp wxFormBuilder/gui_widgets_base.h
	$(CXX) wxFormBuilder/gui_widgets_base.cpp $(CXXFLAGS) $(LDFLAGS) -c -o wxFormBuilder/gui_widgets_base.o




clean:
	rm ../system_message_queue.o
	rm wxFormBuilder/gui_widgets_base.o
	rm *.o 
	rm client_gui
#	rm server_gui

