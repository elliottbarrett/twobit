LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++
	
all: twobit

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.hpp
	$(CXX) -c $< -o $@

twobit: main.o
	@echo "** Building twobit"
	$(CXX) -o twobit main.o $(LIBS)

clean:
	@echo "** Removing object files and executable..."
	rm -f twobit *.o

install:
	@echo '** Installing...'
	cp twobit /usr/bin/

uninstall:
	@echo '** Uninstalling...'
	$(RM) /usr/bin/twobit
