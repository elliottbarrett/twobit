rm = rm -f

LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lGL
CC := g++
CFLAGS = -g
LINKER = g++

TARGET = twobit

SRCDIR = src
INCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) -o $@ $(LIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"
