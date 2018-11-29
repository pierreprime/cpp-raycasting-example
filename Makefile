raycaster: main.cpp
	g++ *.cpp -lSDL -O3 -o ./bin/raycaster
	# Must have pkg-config to make json-c lib link work
	# CFLAGS += $(shell pkg-config --cflags json-c)
	# LDFLAGS += $(shell pkg-config --libs json-c)
	# without pkg-config use this
	JSON_C_DIR=/usr/local
	CPPFLAGS=-I$(JSON_C_DIR)/include/json-c
	LDFLAGS=-L$(JSON_C_DIR)/lib
