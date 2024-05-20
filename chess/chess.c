#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#define whiteBG   "\x1b[46m"
#define blackBG   "\x1b[41m"
#define whiteFG   "\x1b[1;37m"
#define blackFG   "\x1b[30m"
#define errorBG   "\x1b[41m"
#define correctBG "\x1b[42m"
#define defaultBG "\x1b[0m"
#define clear "\e[1;1H\e[2J"
int turn = 0;

void newBoard(int board[8][8]);
void printBoard(int board[8][8]);
void printPeace(int value, int square);
void move(int board[8][8]);
void invalidMove();
void validMove();


int main() {
	printf(clear);
	int board[8][8];
	newBoard(board);
	move(board);
}

void newBoard(int board[8][8]) {
	int newBoard[8][8] = {
        	{10, 9, 8, 11, 12, 8, 9, 10},
        	{7, 7, 7, 7, 7, 7, 7, 7},
        	{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
        	{0, 0, 0, 0, 0, 0, 0, 0},
        	{0, 0, 0, 0, 0, 0, 0, 0},
        	{1, 1, 1, 1, 1, 1, 1, 1},
        	{4, 3, 2, 5, 6, 2, 3, 4}
	};

	for (int i = 0; i < 8; i++) {
        	for (int j = 0; j < 8; j++) {
           	board[i][j] = newBoard[i][j];
		}
	}
}

void printBoard(int board[8][8]) {
	for (int i = 0; i < 8; i++) {
		printf("%d ", i+1);
		for (int j = 0; j < 8; j++) {
			printPeace(board[i][j], i+j);	
	    	}
		printf(defaultBG);
		printf("\n");
	}
	printf("  A B C D E F G H\n");
}

void printPeace(int value, int square) {
	setlocale(LC_CTYPE, "");
	wchar_t peace;
	char *fg;
	switch (value) {
		case 0:
			peace=0x0020;
			break;
		case 1:
		case 7:
			peace=0x265F;
			break;
		case 2:
		case 8:
			peace=0x265D;
			break;
		case 3:
		case 9:
			peace=0x265E;
			break;
		case 4:
		case 10:
			peace=0x265C;
			break;
		case 5:
		case 11:
			peace=0x265B;
			break;
		case 6:
		case 12:
			peace=0x265A;
			break;
		default:
			printf("Error!");
	}

	if (value<=6 && value!=0) {
		fg=whiteFG;	
	} else {
		fg=blackFG;
	}

	if (square%2==0) {
		printf(whiteBG "%s%lc ", fg, peace);
	} else {
		printf(blackBG "%s%lc ", fg, peace);
	}
}

void move(int board[8][8]) {
	while (1) {
		switch (turn%2==0) {
			case 1:
				printf("===White's move!===\n");
				break;
			case 0:
				printf("===Black's move!===\n");
				break;
		}
		printBoard(board);		
		char move[5];
		printf("Enter your move(e.g. e2-e4): ");
		scanf("%s", move);
		printf(clear);
		if (move[0]>='a' && move[0]<='h' && move[1]>='1' && move[1]<='8' && move[3]>='a' && move[3]<='h' && move[4]>='1' && move[4]<='8' ) {
			validMove();
			int x1 = move[1]-'1';
			int x2 = move[4]-'1';
			int y1 = move[0]-'a';
			int y2 = move[3]-'a';
			board[x2][y2] = board[x1][y1];
			board[x1][y1] = 0;
			turn++;
			validMove;
		} else {
			invalidMove();
		}
	}
}
void invalidMove() {
	printf(errorBG whiteFG "==-INVALID MOVE!-==\n" defaultBG);
}

void validMove() {
	printf(correctBG whiteFG "===+VALID MOVE!+===\n" defaultBG);
}
/*void rules(int board[8][8], int move) {

}*/
