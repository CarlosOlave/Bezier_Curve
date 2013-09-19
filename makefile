# Makefile

CPP = g++
LDFLAGS = -lglut -lGLU -lGL -lX11
OBJS = main_t05m01.o Camera.o SceneReader.o Point.o BezierType.o
INCLUDE = Utility.h Camera.h SceneReader.h Point.h BezierType.h

# Compile the program.
main_t05m01 : $(OBJS)
	$(CPP) -o main_t05m01 $(OBJS) $(LDFLAGS)

main_t05m01.o: main_t05m01.cpp $(INCLUDE)
	$(CPP) -c main_t05m01.cpp

Camera.o: Camera.cpp $(INCLUDE)
	$(CPP) -c Camera.cpp

SceneReader.o: SceneReader.cpp $(INCLUDE)
	$(CPP) -c SceneReader.cpp
	
Point.o: Point.cpp $(INCLUDE)
	$(CPP) -c Point.cpp

BezierType.o: BezierType.cpp $(INCLUDE)
	$(CPP) -c BezierType.cpp

# command to be executed.
clean:
	rm -f main_t05m01 $(OBJS)
