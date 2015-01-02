SRC_DIR=src
BIN_DIR=bin
INCLUDE_DIR=$(SRC_DIR)/include

CC=g++
RM=rm -rf
MKDIR=mkdir -p
CFLAGS=-Wall -std=c++11 -I$(INCLUDE_DIR)
LDFLAGS=-lgmpxx -lgmp
INCLUDES=$(wildcard $(INCLUDE_DIR)/*.h)
COMMON=$(wildcard $(SRC_DIR)/*.cpp)

TARGETS=power matrix_power linear_rec iter num egcd poly

define DEF_TARGET

$(1): $(SRC_DIR)/$(1)/$(1).cpp $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/$(1)/$(1).cpp $(COMMON) -o $(BIN_DIR)/$(1) $(LDFLAGS)

endef

all: $(BIN_DIR) $(TARGETS)

$(foreach TARGET,$(TARGETS),$(eval $(call DEF_TARGET,$(TARGET))))

$(BIN_DIR):
	$(MKDIR) $@

clean:
	$(RM) $(BIN_DIR)/*
	find . -name "*.o" -type f -delete 
