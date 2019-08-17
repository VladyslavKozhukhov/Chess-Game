#include "Parser.h"
bool parserIsInt(const char* str){
	if (*str == '-')
			++str;
		if (!*str)
			return false;

		while (((*str)!='\0')&&((*str)!='\n')) {
			if (!isdigit(*str))
				return false;
			else
				++str;
		}
		return true;
	}

Command parserPraseLine(const char* str){
	int num=0;
	int j,y;
	char x,i;
	FILE *inp,*op;
	Command command;
	char* string_arg;
	char str2[MAX_LEN]={0};
	strcpy(str2,str);
	char* ch=strtok(str2," \t\r\n");
	setMovePiece(&(command.move),0,0,0,1);
	command.move.dead=false;
	command.validArg=false;
	command.cmd=INVALID_LINE;
	command.arg=-1;
	if(!ch){
		command.cmd=INVALID_LINE;
		return command;
	}
	else if(strcmp(ch,"move")==0){
		string_arg=strtok(NULL," \t\r\n");
		if(string_arg==NULL){
			command.cmd=INVALID_LINE;
			return command;
		}
		else if(sscanf(string_arg,"<%d,%c>",&y,&x)!=2){
			command.cmd=INVALID_LINE;
			return command;
		}
		string_arg=strtok(NULL," \t\r\n");
		if(string_arg==NULL){
			command.cmd=INVALID_LINE;
			return command;
		}
		else if(strcmp(string_arg,"to")!=0){
			command.cmd=INVALID_LINE;
			return command;
		}
		string_arg=strtok(NULL," \t\r\n");
		if(string_arg==NULL){
			command.cmd=INVALID_LINE;
			return command;
		}
		else if(sscanf(string_arg,"<%d,%c>",&j,&i)!=2){
			command.cmd=INVALID_LINE;
			return command;
		}
		command.move.yf=ROWS-y;
		command.move.xf=(int)(x-'A');
		command.move.jt=ROWS-j;
		command.move.it=(int)(i-'A');
		command.cmd=MOVE;
	}


	else if(strcmp(ch,"game_mode")==0){//game mode
		string_arg=strtok(NULL," \t\r\n");
		command.cmd=GAME_MODE;
		if(parserIsInt(string_arg)){
			num=atoi(string_arg);
			command.arg=num;
		}
		command.validArg=true;
	}
	else if(strcmp(ch,"difficulty")==0){//difficulty
		string_arg=strtok(NULL," \t\r\n");
		command.cmd=DIFFICULTY;
		if(parserIsInt(string_arg)){
			num=atoi(string_arg);
			command.arg=num;
		}
		command.validArg=true;
	}
	else if(strcmp(ch,"user_color")==0){
		string_arg=strtok(NULL," \t\r\n");
		command.cmd=USER_COLOR;
		if(parserIsInt(string_arg)){
			num=atoi(string_arg);
			command.arg=num;
		}
		command.validArg=true;
	}
	else if(strcmp(ch,"load")==0){
		string_arg=strtok(NULL," \t\r\n");
		command.cmd=LOAD;
		inp=fopen(string_arg,"r");
		if(inp!=NULL){
			command.str=(char*)malloc(sizeof(char)*(strlen(string_arg)+1));
			if(!command.str){
				free(command.str);
				fclose(inp);
				return command;
			}
			strcpy(command.str,string_arg);
			command.validArg=true;
		}
		fclose(inp);
	}
	else if(strcmp(ch,"save")==0){
		string_arg=strtok(NULL," \t\r\n");
		command.cmd=SAVE;
		op=fopen(string_arg,"w");
		if(op!=NULL){
			command.str=(char*)malloc(sizeof(char)*(strlen(string_arg)+1));
			if(!command.str){
				free(command.str);
				fclose(op);
				return command;
			}
			strcpy(command.str,string_arg);
			command.validArg=true;
		}
		fclose(op);
	}
	else if(strtok(NULL," \t\r\n")==NULL){//no second parameter
		if(strcmp(ch,"undo")==0){
			command.cmd=UNDO_MOVE;
			command.validArg=true;
		}
		else if(strcmp(ch,"default")==0){
			command.cmd=DEFAULT;
			command.validArg=true;
		}
		else if(strcmp(ch,"reset")==0){
			command.cmd=RESTART;
			command.validArg=true;
		}
		else if(strcmp(ch,"print_setting")==0){
			command.cmd=PRINT_SETTINGS;
			command.validArg=true;
		}
		else if(strcmp(ch,"quit")==0){
			command.cmd=QUIT;
			command.validArg=true;
		}
		else if(strcmp(ch,"start")==0){
			command.cmd=START;
			command.validArg=true;
		}
	}
	else{
		command.cmd=INVALID_LINE;
	}
	return command;
	}






Command userInput(Game* game){
	setbuf(stdout,NULL);
	char str[1024];
	fgets(str,1024,stdin);
	Command command;
	ArrayList* moves;
	command=parserPraseLine(str);
	switch(command.cmd)
	{
		case(MOVE):{
			if(indexIsValid(command.move.xf,command.move.yf)==false||
					indexIsValid(command.move.it,command.move.jt)==false){
				printf("Invalid position on the board\n");
				command.cmd=INVALID_LINE;
			}
			else if(game->gameBoard[command.move.yf][command.move.xf]==NULL||
					game->gameBoard[command.move.yf][command.move.xf]->player!=game->curPlayer){
				printf("The specified position does not contain you piece\n");
				command.cmd=INVALID_LINE;
			}
			else if(gameIsValidMove(game,&command.move)==false){
				printf("Illegal move\n");
				command.cmd=INVALID_LINE;
			}
			else{//move is fine
				moveGame(command.move,game);
			}
			break;
		}
		case(SAVE):{
			command.cmd=INVALID_LINE;
			saveGame(game,command.str);
			break;
		}
		case(UNDO_MOVE):{
			if(game->set.gameMode==2){
				printf("Undo command not available in 2 players mode\n");
				command.cmd=INVALID_LINE;
				break;
			}
			int message=undoGame(game);
			if(message==1){
				printGameBoard(game);
			}
			command.cmd=INVALID_LINE;
			break;
		}
		case(RESTART):
				restartGame(game);
		break;
		case(QUIT):
				quitGame(game);
		break;
		default:command.cmd=INVALID_LINE;
		break;
	}
	return command;
}
Command gameSetting(Settings* settings){
	setbuf(stdout,NULL);
	char str[1024];
    fgets(str,1024,stdin);
    Command command;
    command=parserPraseLine(str);
    switch(command.cmd){
    	case(GAME_MODE):{
    		if(command.arg!=1&&command.arg!=2){
				printf("Wrong game mode\n");
				command.cmd=INVALID_LINE;
			}
    		else{
    			printf("Game mode is set to %d player",command.arg);
    			if(command.arg==2){
    				printf("s");
    				settings->userColor=1;
    				settings->gameMode=2;
    				settings->difficulty=2;
    			}
    			printf("\n");
    			settings->gameMode=command.arg;
    		}
    	};break;
    	case(DIFFICULTY):{
    		if(settings->gameMode!=1){
    			printf("Invalid command!\n");
    			command.cmd=INVALID_LINE;
    		}
    		else{
    			if(command.arg>5||command.arg<1){
    				printf("Wrong difficulty level. The value should be between 1 to 5\n");
    				command.cmd=INVALID_LINE;
    			}
    			else if(command.arg==5){
    				printf("Expert level not supported, please choose a value between 1 to 4:\n");
    				command.cmd=INVALID_LINE;
    			}
    			else{
    				settings->difficulty=command.arg;
    			}
		}
	};break;
    	case(USER_COLOR):{
    		if(settings->gameMode!=1){
    			printf("Invalid command!\n");
    			command.cmd=INVALID_LINE;
    		}
    		else{
    			if(command.arg==-1){
    				command.arg=settings->userColor;
    			}
    			else if(command.arg!=1&&command.arg!=0){
    				printf("Invalid command!\n");
    				command.cmd=INVALID_LINE;
    			}
    			else{
    				settings->userColor=command.arg;
    			}
    		}
	};break;
    	case(LOAD):{
    		if(command.validArg==false){
    			command.cmd=INVALID_LINE;
    		}
    	};break;
    	case(DEFAULT):{
    		settings->gameMode=ONE_PLAYER_MODE;
    		settings->difficulty=2;
    		settings->userColor=1;
    	};break;
    	case(PRINT_SETTINGS):{
    		if(settings->gameMode==2){
    			printf("SETTINGS:\nGAME_MODE: 2\n");
    		}
    		else{
    			if( settings->userColor){
        	printf("SETTINGS:\nGAME_MODE: 1\nDIFFICULTY_LVL: %d\nUSER_CLR: %s\n",
					settings->difficulty,"WHITE");
          			}
    			else

    			printf("SETTINGS:\nGAME_MODE: 1\nDIFFICULTY_LVL: %d\nUSER_CLR: %s\n",
    					settings->difficulty,"BLACK");
    			}
	};break;
    	case(QUIT):{
    		printf("Exiting...\n");
    		exit(0);
    	};break;
    	case(START):{
    		command.cmd=START;
    	};break;
    	default:command.cmd=INVALID_LINE;printf("Invalid command!\n");break;
    }
	return command;
}

