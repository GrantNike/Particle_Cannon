LIBS = -lglut -lGLU -lGL
load: particle_cannon.cpp
	g++ -o cannon particle_cannon.cpp $(LIBS)