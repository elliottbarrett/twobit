LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++
LINKER = g++

TARGET = twobit

SRCDIR = src
INCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) -o $@ $(LIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"


# all: twobit

# %.o: %.cpp
# 	$(CXX) -c $< -o $@

# %.o: %.hpp
# 	$(CXX) -c $< -o $@

# twobit: main.o
# 	@echo "** Building twobit"
# 	$(CXX) -o twobit main.o $(LIBS)

# clean:
# 	@echo "** Removing object files and executable..."
# 	rm -f twobit *.o

# install:
# 	@echo '** Installing...'
# 	cp twobit /usr/bin/

# uninstall:
# 	@echo '** Uninstalling...'
# 	$(RM) /usr/bin/twobit
