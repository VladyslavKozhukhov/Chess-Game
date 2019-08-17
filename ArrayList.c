#include "ArrayList.h"
ArrayList* arrayListCreate(int maxSize){// init a new list
	if(maxSize<=0){
		PrintError(ERROR_COMMAND,NULL,0);
		return NULL;
	}
	ArrayList* arr =(ArrayList*) malloc(sizeof(ArrayList));
	if(!arr){
		free(arr);
		exit(0);
		return NULL;
	}
	arr->maxSize=maxSize;
	arr->actualSize=0;
	arr->elements=(Move*)calloc(maxSize,sizeof(Move));
	if(!arr->elements){

		arrayListDestroy(arr);
		exit(0);
		return NULL;
	}
	return arr;
}
ArrayList* arrayListCopy(ArrayList* src){
	int i;
	if(!src){

		return NULL;
	}
	ArrayList* arr= arrayListCreate(src->maxSize);
	if(!arr){
		exit(0);
		return NULL;
	}
	arr->actualSize=src->actualSize;
	for(i=0; i<arr->actualSize; i++){
		arr->elements[i]=src->elements[i];//copy all the elements that are in src to arr
	}
	if(!arr->elements){
		arrayListDestroy(arr);
		exit(0);
		return NULL;
	}
	return arr;
}
void arrayListDestroy(ArrayList* src){
	if(!src){
		return;
	}
	if(src->elements!=NULL){
		free(src->elements);
		src->elements=NULL;
	}
	free(src);
	return;
}
ARRAY_LIST_MESSAGE arrayListClear(ArrayList* src){
	if(!src){
		arrayListDestroy(src);
		exit(0);
		return ARRAY_LIST_INVALID_ARGUMENT;
	}
	src->actualSize=0;
	return ARRAY_LIST_SUCCESS;
}
ARRAY_LIST_MESSAGE arrayListAddAt(ArrayList* src, Move elem, int index){
	int i=0;
	if((!src)||(index<0)|| (index>(src->actualSize))){
		return ARRAY_LIST_INVALID_ARGUMENT;
	}
	if(arrayListIsFull(src)){
		return ARRAY_LIST_FULL;
	}
	for(i=(src->actualSize-1);i>=index;--i){
		src->elements[i+1]=src->elements[i];//shifts all the elements of src one side to the left so we can add a new one
	}
	src->elements[index]=elem;
	(src->actualSize)++;
	return ARRAY_LIST_SUCCESS;
}
ARRAY_LIST_MESSAGE arrayListAddFirst(ArrayList* src, Move elem){
	return arrayListAddAt(src,elem,0);
}
ARRAY_LIST_MESSAGE arrayListAddLast(ArrayList* src, Move elem){
	return arrayListAddAt(src,elem,src->actualSize);
}
int cmpfunc(const void * move1, const void * move2){
	if(((Move*)move1)->jt>((Move*)move2)->jt){
		return -1;
	}
	else if(((Move*)move1)->jt==((Move*)move2)->jt){
		if(((Move*)move1)->it>((Move*)move2)->it){
			return 1;
		}
			return -1;
	}
	else{
		return 1;
	}
}
ARRAY_LIST_MESSAGE arrayListRemoveAt(ArrayList* src, int index){
	int i;
	if(!src||index>src->actualSize||index<0){
		return ARRAY_LIST_INVALID_ARGUMENT;
	}
	if(src->actualSize==0){
		return ARRAY_LIST_EMPTY;
	}
	for(i=index;i<src->actualSize;i++){
		src->elements[i]=src->elements[i+1];
	}
	src->actualSize--;
	return ARRAY_LIST_SUCCESS;
}
ARRAY_LIST_MESSAGE arrayListRemoveFirst(ArrayList* src){
	return arrayListRemoveAt(src,0);
}
ARRAY_LIST_MESSAGE arrayListRemoveLast(ArrayList* src){
	return arrayListRemoveAt(src,src->actualSize-1);
}
Move arrayListGetAt(ArrayList* src, int index){
	Move move;
	if(!src){
		move.xf=-1;
		move.yf=-1;
		return move;
	}
	if(index<0||index>src->actualSize-1){
		move.xf=-1;
		move.yf=-1;
		return move;
	}
	return src->elements[index];
}
Move arrayListGetFirst(ArrayList* src){
	return arrayListGetAt(src,0);
}
Move arrayListGetLast(ArrayList* src){
	return arrayListGetAt(src,src->actualSize-1);
}
int arrayListMaxCapacity(ArrayList* src){
	if(!src){
		return -1;
	}
	return src->maxSize;
}
int arrayListSize(ArrayList* src){
	if(!src){
		return -1;
	}
	return src->actualSize;
}
bool arrayListIsFull(ArrayList* src){
	if(!src||(src->actualSize)<(src->maxSize)){
		return false;
	}
	if((src->actualSize)==(src->maxSize)){
		return true;
	}
	return false;
}
bool arrayListIsEmpty(ArrayList* src){
	if(!src||(src->actualSize)!=0){
		return false;
	}
	return true;
}

