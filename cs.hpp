#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h> //pour sleep et usleep
#include <algorithm>

void placeTerm(int x, int y);
void clearPos(int x, int y);
void clearLine(int row, int curRow, int nRow, int nCol);
int main(int argc, char* argv[]);
void clear();