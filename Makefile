# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall

# Source files
SRC_FILES = drivercode.cpp entry.cpp evaluator.cpp exprtreenode.cpp symtable.cpp ulimitedint.cpp ulimitedrational.cpp

# Object files
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Executable name
EXECUTABLE = exp_evaluator

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^
	rm -f $(OBJ_FILES)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(EXECUTABLE)
