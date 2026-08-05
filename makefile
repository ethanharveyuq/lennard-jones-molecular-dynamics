# 1. Compiler and Flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# 2. Targets and Files
TARGET   := lennard-jones-mol-dyn
SOURCES  := main.cpp
OBJECTS  := $(SOURCES:.cpp=.o)

# 3. Default Rule
all: $(TARGET)

# 4. Linking Rule
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# 5. Compilation Rule (Pattern Rule)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 6. Housekeeping
.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)