# pattern : target output name: PREREQUISITE is a file used as input to create the target
raycaster: main.cpp
	g++ *.cpp -lSDL -l json-c -O3 -o ./bin/raycaster
	# Must have pkg-config to make json-c lib link work
	# CFLAGS += $(shell pkg-config --cflags json-c)
	# LDFLAGS += $(shell pkg-config --libs json-c)
	# without pkg-config use this
	# on my machine
	JSON_C_DIR=/usr/local
	CPPFLAGS=-I$(JSON_C_DIR)/include/json-c
	LDFLAGS=-L$(JSON_C_DIR)/lib
	#on other machine, pkg-config

clean:
	# no prerequisite here
	rm ./bin/*
	
# Phony target : instead of target compiled file name describe action by simple word
#
# We can define executable file relying on object .o files as prerequisites
# object .o files can themselves depend on source files as prerequisites.
# running gcc with -c flag compiles sources without linking
#
# The final executable to obtain is called the goal
# We put this rule first / "make" alone processes the default goal
# Prerequisites are themselves processed automatically if needed
#
# If object files are newer than executables, make decides to relink it
# By convention we have a variable listing all object .o files, names OBJECTS for example
# Then we call variables with $(variable)
#
# Implicit rules is when object files have same names as source files.
# Implicit rules have just target and prerequisite
#
# Entries in makefile can be grouped by a same prerequisites set / When makefiles consists only of implicit rules
# Like this :
# $(objects) : prerequisite.h
#
# Makefiles can read other makefiles
# Preceding a Makefile instruction with '-' makes it ignore errors (without even warnings)
#
