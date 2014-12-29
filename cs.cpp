#include "cs.hpp"

char* Color_Off= (char*) "\e[0m";      // Text Reset

void placeTerm(int x, int y){
	printf("\033[%u;%uH", y, x);
}

void clearPos(int x, int y){
	placeTerm(x, y);
	printf("%s ", Color_Off);
}

void clearLine(int row, int curRow, int nRow, int nCol){
	if (row < nRow){
		placeTerm(0, row+1);
		for (int i=0; i<nCol; i++){
			printf("%s ", Color_Off);
		}
		placeTerm(0, curRow+1);
	}
}

void clearPage(){
	printf("\033[2J"); // clear the screen
	placeTerm(0, 0);
}

int main (int argc, char *argv[]) {
	// initialization
	// getting number of rows and columns of the terminal
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int nCol = w.ws_col;
    int nRow = w.ws_row;
// 	printf("nC: %d, nR: %d\n", nCol, nRow);

	bool firstpass = true;
	clearPage();
    char line[nCol];
	int curRow = 0;
    while(fgets(line, nCol, stdin)!=NULL){
		int l = strlen(line) - 1;
		if (line[l] == '\n'){
			line[l] = '\0';
		}
		
		if (not firstpass){
			clearLine(curRow, curRow, nRow, nCol);
			clearLine(curRow+1, curRow, nRow, nCol);
			clearLine(curRow+2, curRow, nRow, nCol);
		}
		
		printf("%s", line);
		if (curRow < nRow - 1){
			printf("\n");
		}
		
		usleep(100000);
		curRow++;
		if (curRow > nRow - 1){
			curRow=0;
			placeTerm(0, 0);
			firstpass = false;
		}
	}
	clearLine(nRow, curRow, nRow, nCol);
	placeTerm(0, nRow);
// 	clearPage();
}
