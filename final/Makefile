OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw3
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN=transformer 
SRCS=main.cpp transformer.cpp image.cpp background.cpp gl_framework.cpp
INCLUDES=gl_framework.hpp image.hpp transformer.hpp background.hpp

all: $(BIN)


$(BIN): $(SRCS) $(INCLUDES)
	g++ -stdlib=libstdc++ -lstdc++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS) -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
clean:
	rm -f *~ *.o $(BIN)
