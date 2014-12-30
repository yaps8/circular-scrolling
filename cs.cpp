#include "cs.hpp"

char* Color_Off= (char*) "\e[0m"; // Text Reset

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
}

int main (int argc, char *argv[]) {
	// getting number of rows and columns of the terminal
	struct winsize w;
	int nCol;
	int nRow;
	int maxCol = 1000;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	nCol = w.ws_col;
	nRow = w.ws_row;

	bool firstpass = true;
	clearPage();
	placeTerm(0, 0);
	char line[maxCol];
	int curRow = 0;
	while(fgets(line, std::min(nCol, maxCol), stdin)!=NULL){
		placeTerm(0, curRow+1);
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		nCol = w.ws_col;
		nRow = w.ws_row;
		
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
		fflush(stdout);
		
		curRow++;
		if (curRow > nRow - 1){
			curRow=0;
			placeTerm(0, 0);
			firstpass = false;
		}
	}
	if (not firstpass){
		clearLine(nRow, curRow, nRow, nCol);
		placeTerm(0, nRow);
	}
	else {
		placeTerm(0, curRow+1);
	}
}
