#############################################################################
# Pong Game Makefile 
# Author: Vasileios Filippos Skarleas - All rights reserved.
#############################################################################

CCplus = g++
DIR = .
LIBS = .
INCLUDEOPTS = -I$(DIR) -I/opt/homebrew/include/SDL2
LDOPTS = -L$(LIBS) -L/opt/homebrew/lib -fsanitize=address -lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread
COMPILOPTSplus = -Wall -std=c++20 -g $(INCLUDEOPTS)

SRCS = main.cpp \
    game.cpp \
    paddle.cpp \
    ball_base.cpp \
    classic_ball.cpp \
    square_ball.cpp \
    triangle_ball.cpp \
    menu.cpp \
    pause_menu.cpp \
    game_save.cpp \
	notices.cpp \
	middle_menu.cpp \
	renderers.cpp

OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = game

all: $(EXECUTABLE)

paddle.o: paddle.cpp paddle.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

renderers.o: renderers.cpp renderers.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

ball_base.o: ball_base.cpp ball_base.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

classic_ball.o: classic_ball.cpp classic_ball.hpp ball_base.hpp renderers.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

square_ball.o: square_ball.cpp square_ball.hpp ball_base.hpp renderers.hpp
	@echo ""@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

triangle_ball.o: triangle_ball.cpp triangle_ball.hpp ball_base.hpp renderers.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

menu.o: menu.cpp menu.hpp game_save.hpp macros.hpp renderers.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

notices.o : notices.cpp notices.hpp macros.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

pause_menu.o: pause_menu.cpp pause_menu.hpp renderers.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

game_save.o: game_save.cpp game_save.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

middle_menu.o: middle_menu.cpp middle_menu.hpp renderers.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

game.o: game.cpp game.hpp paddle.hpp ball_base.hpp menu.hpp pause_menu.hpp game_save.hpp macros.hpp notices.hpp middle_menu.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

main.o: main.cpp game.hpp
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CCplus) -c $(COMPILOPTSplus) $< -o $@

$(EXECUTABLE): $(OBJS)
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CCplus) $^ $(LDOPTS) -o $@

assets:
	mkdir -p assets
	@echo "Add the following sound files to assets directory:"
	@echo "- background.wav"
	@echo "- paddle_hit.wav"
	@echo "- wall_hit.wav"
	@echo "- score.wav"

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean run assets