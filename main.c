
#include "maingui.h"
#include "mainAux.h"
#include "SPBufferset.h"
#include <assert.h>

int main(int argc, char** argv){

	if(argc == 2 && strcmp(argv[1], "-c") == 0) {
		NewGame();
		return 1;
	}

	else if(argc == 2 && strcmp(argv[1], "-g") == 0) {
		return maingui();
	}
	else {

		NewGame();

	return 1;

}
}
