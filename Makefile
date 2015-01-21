CC = g++
CFLAGS = -c

EXECUTABLE = plotter

all : $(EXECUTABLE)

$(EXECUTABLE) : plotter.o math_lib.o
	$(CC) plotter.o math_lib.o -o $(EXECUTABLE) -lglut -lGL

plotter.o : plotter.cpp
	$(CC) $(CFLAGS) plotter.cpp -lglut -lGL

math_lib.o : math_lib.cpp
	$(CC) $(CFLAGS) math_lib.cpp

clean : 
	rm -rf *o plotter
