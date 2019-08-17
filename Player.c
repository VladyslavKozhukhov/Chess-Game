#include "Player.h"
Player* creatPlayer(char symbol,int color){
	Player* player=(Player*)malloc(sizeof(Player));
	if(!player){
		free(player);
		exit(0);
	}
	player->color=color;
	player->symbol=symbol;
	player->nump=0;
	return player;
}
Player* initPlayer(Player* player){
	int j;
	player->nump=16;
	if(player->color==BLACK){
		player->pieces[0]=createPiece(4,0,player->symbol,'k',player->color);
		player->pieces[1]=createPiece(3,0,player->symbol,'q',player->color);
		player->pieces[2]=createPiece(0,0,player->symbol,'r',player->color);
		player->pieces[3]=createPiece(7,0,player->symbol,'r',player->color);
		player->pieces[4]=createPiece(2,0,player->symbol,'b',player->color);
		player->pieces[5]=createPiece(5,0,player->symbol,'b',player->color);
		player->pieces[6]=createPiece(1,0,player->symbol,'n',player->color);
		player->pieces[7]=createPiece(6,0,player->symbol,'n',player->color);
		for(j=8;j<player->nump;j++){
			player->pieces[j]=createPiece(j-8,1,player->symbol,'m',player->color);
		}
	}
	else if(player->color==WHITE){
		player->pieces[0]=createPiece(4,7,player->symbol,'k',player->color);
		player->pieces[1]=createPiece(3,7,player->symbol,'q',player->color);
		player->pieces[2]=createPiece(0,7,player->symbol,'r',player->color);
		player->pieces[3]=createPiece(7,7,player->symbol,'r',player->color);
		player->pieces[4]=createPiece(2,7,player->symbol,'b',player->color);
		player->pieces[5]=createPiece(5,7,player->symbol,'b',player->color);
		player->pieces[6]=createPiece(1,7,player->symbol,'n',player->color);
		player->pieces[7]=createPiece(6,7,player->symbol,'n',player->color);
		for(j=8;j<player->nump;j++){
			player->pieces[j]=createPiece(j-8,6,player->symbol,'m',player->color);
		}
	}
	player->king=player->pieces[0];
	return player;
}
Player* copyPlayer(Player* player){
	Player* copy=creatPlayer(player->symbol,player->color);
	int i;
	for(i=0;i<player->nump;i++){
		copy->pieces[i]=CopyPiece(player->pieces[i]);
		if(copy->pieces[i]->type=='k'){
			copy->king=copy->pieces[i];
		}
	}
	copy->nump=player->nump;
	return copy;
}
void destroyPlayer(Player* player){
	int i;
	for(i=0;i<player->nump;i++){
		destroyPiece(player->pieces[i]);
	}
	free(player);
}
int setColorPlayer(Player* player,int color){
	player->color=color;
	return 1;
}
int setSymbolPlayer(Player* player,char symbol){
	player->symbol=symbol;
	return 1;
}
int getColorPlayer(Player* player){
	return player->color;
}
char getSymbolPlayer(Player* player){
	return player->symbol;
}
void printPlayer(Player* player){
	int i;
	printf("the %s user has:\n",getColorPlayer(player)?"white":"black");
	for(i=0;i<player->nump;i++){
		printPiece(player->pieces[0]);

	}
}

Piece* getPiecelayer(Player* player,int index){
	return player->pieces[index];
}
Piece* getKingPlayer(Player* player){
	return player->king;
}
Piece* addPiecePlayer(Player* player,int x,int y,char type){
	player->pieces[player->nump]=createPiece(x,y,player->symbol,type,player->color);
	player->nump++;
	return player->pieces[player->nump-1];
}
