# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11

# Directories
SRCDIR = SRC
OBJDIR = OBJ

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Target executable
TARGET = tests

# Platform-specific commands
ifeq ($(OS),Windows_NT)
    RM = del /q
    MKDIR = mkdir
else
    RM = rm -rf
    MKDIR = mkdir -p
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJDIR) $(TARGET)

.PHONY: all clean