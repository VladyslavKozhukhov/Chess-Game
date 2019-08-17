CC = gcc
OBJS = main.o Widget.o Player.o GUI_SimpleButton.o Validation.o Get_MoveP.o GUI_SettingsWin.o settings.o GUI_PieceButton.o Piece.o Parser.o move.o GUI_MainWin.o maingui.o  mainAux.o GUI_LoadWin.o GUI_Manager.o GUI_GameWin.o Game.o ErrFails.o GUI_Common.o ArrayList.o AlphaBetaMinimax.o
 
EXEC = Chess
CC_COMP_FLAG = -std=c99 -Wall -Wextra -Werror -pedantic-errors
SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
GUI_Common.o: gui/GUI_Common.c gui/GUI_Common.h mainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c
GUI_GameWin.o: gui/GUI_GameWin.c gui/GUI_GameWin.h gui/GUI_SimpleButton.h gui/GUI_PieceButton.h mainAux.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c
GUI_Manager.o: gui/GUI_Manager.c gui/GUI_Manager.h gui/GUI_SettingsWin.h gui/GUI_LoadWin.h gui/GUI_MainWin.h gui/GUI_Common.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c	
GUI_MainWin.o: gui/GUI_MainWin.c gui/GUI_MainWin.h gui/GUI_SimpleButton.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c
GUI_LoadWin.o: gui/GUI_LoadWin.c gui/GUI_LoadWin.h gui/GUI_SimpleButton.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c		
GUI_PieceButton.o: gui/GUI_PieceButton.c gui/GUI_PieceButton.h gui/Widget.h gui/GUI_Common.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c	
GUI_SettingsWin.o: gui/GUI_SettingsWin.c gui/GUI_SettingsWin.h settings.h gui/GUI_SimpleButton.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c
GUI_SimpleButton.o: gui/GUI_SimpleButton.c gui/GUI_SimpleButton.h gui/GUI_Common.h gui/Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c	
Widget.o: gui/Widget.c gui/Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c gui/$*.c
main.o: main.c mainAux.h maingui.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
AlphaBetaMinimax.o: AlphaBetaMinimax.c AlphaBetaMinimax.h Game.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ArrayList.o: ArrayList.c ArrayList.h move.h ErrFails.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Get_MoveP.o: Get_MoveP.c Get_MoveP.h Game.h 
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
ErrFails.o: ErrFails.c ErrFails.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
game.o: Game.c Game.h ArrayList.h settings.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
mainAux.o: mainAux.c mainAux.h Parser.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Validation.o: Validation.c Validation.h Game.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
settings.o: settings.c settings.h Piece.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Player.o: Player.c Player.h Piece.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
maingui.o: maingui.c maingui.h gui/GUI_Manager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
move.o: move.c move.h Player.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h AlphaBetaMinimax.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Piece.o: Piece.c Piece.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c

clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
