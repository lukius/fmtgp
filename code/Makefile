SRC_DIR=src
BIN_DIR=bin
INCLUDE_DIR=$(SRC_DIR)/include

CC=g++
RM=rm -rf
MKDIR=mkdir -p
CFLAGS=-Wall -std=c++11 -I$(INCLUDE_DIR)
INCLUDES=$(wildcard $(INCLUDE_DIR)/*.h)


all: $(BIN_DIR) power linear_rec

power: $(SRC_DIR)/power/power.o $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $(BIN_DIR)/$@

linear_rec: $(SRC_DIR)/linear_rec/linear_rec.o $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $(BIN_DIR)/$@

$(BIN_DIR):
	$(MKDIR) $@

$(BIN_DIR)/%: $(SRC_DIR)/%/%.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp $(INCLUDES)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(BIN_DIR)/*
	find . -name "*.o" -type f -delete 
