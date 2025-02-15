CC = g++
CFLAGS = -Wall
INCDIR = .
LIBDIR = .
INCLUDEOPTS = -I$(INCDIR) -I/opt/homebrew/include/SDL2
LDOPTS = -L$(LIBDIR) -L/opt/homebrew/lib -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

SRCS = main.cpp game.cpp paddle.cpp ball.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = SDLPong

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDOPTS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDEOPTS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)