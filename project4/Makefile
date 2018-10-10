################################################################################
## OS
################################################################################
#OS = LINUX
OS = OSX

################################################################################
## GCC
################################################################################
CC = g++ -std=c++14 -w
OPTS = -O3
#OPTS = -g
FLAGS = -Wall -Werror
ifeq "$(OS)" "LINUX"
  DEFS = -DLINUX
else
  ifeq "$(OS)" "OSX"
  DEFS = -DOSX
endif
endif

################################################################################
## GL and QT
################################################################################
# Open gl
ifeq "$(OS)" "LINUX"
  GL_LIBS = -lglut -lGLU -lGL -lSOIL
else
  ifeq "$(OS)" "OSX"
  GL_LIBS = -framework GLUT -framework OpenGL
endif
endif

#-L/Utilities/SOIL/lib -lSOIL -framework CoreFoundation  -arch i386 -arch x86_64
################################################################################
## Rules
################################################################################
INCL = $(GL_INCL)
LIBS = $(GL_LIBS)

OBJS = \
	   Utilities/Camera.o \
	   Models/Face.o \
	   Models/MaterialInfo.o \
	   Models/Model.o \
	   Simulation/Attractor.o \
	   Simulation/Light.o \
	   Simulation/Obstacle.o \
	   Simulation/Particle.o \
	   Simulation/ParticleGenerator.o \
	   Simulation/Repeller.o \
	   Simulation/Simulator.o \
       main.o

EXECUTABLE = spiderling

default: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(OBJMOC)
	$(CC) $(OPTS) $(FLAGS) $(DEFS) $(OBJS) $(LIBS) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE) Dependencies $(OBJS)

.cpp.o:
	$(CC) $(OPTS) $(DEFS) -MMD $(INCL) -c $< -o $@
	cat $*.d >> Dependencies
	rm -f $*.d

-include Dependencies
