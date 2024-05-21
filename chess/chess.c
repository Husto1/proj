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
void swap(int x1, int x2, int y1, int y2, int board[8][8]);
int rules(int x1, int x2, int y1, int y2, int board[8][8]);
void promo(int x2, int y2, int board[8][8]);

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
			printf("ERROR");
	}

	if (value<=6 && value!=0) {
		fg=whiteFG;	
	} else {
		fg=blackFG;
	}

	if (square%2==0) {
		printf(whiteBG "%s%lc " defaultBG, fg, peace);
	} else {
		printf(blackBG "%s%lc " defaultBG, fg, peace);
	}
}

void move(int board[8][8]) {
	while (1) {
		switch (turn%2) {
			case 0:
				printf("===White's move!===\n");
				break;
			case 1:
				printf("===Black's move!===\n");
				break;
		}

		printBoard(board);
		char move[5];

		printf("Enter your move(e.g. e2-e4): ");
		scanf("%5s", move);
		printf(clear);

		if (move[0]>='a' && move[0]<='h' && move[1]>='1' && move[1]<='8' && move[3]>='a' && move[3]<='h' && move[4]>='1' && move[4]<='8' ) {
			int x1 = move[1]-'1';
			int x2 = move[4]-'1';
			int y1 = move[0]-'a';
			int y2 = move[3]-'a';
			if(rules(x1, x2, y1, y2, board) == 0) {
				swap(x1, x2, y1, y2, board);
				turn++;
				validMove();
			} else {
				invalidMove();
			}
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

void swap(int x1, int x2, int y1, int y2, int board[8][8]) {
	board[x2][y2] = board[x1][y1];
	board[x1][y1] = 0;
}

int rules(int x1, int x2, int y1, int y2, int board[8][8]) {
	int wb=turn%2;
	int from=board[x1][y1];
	int to=board[x2][y2];
	printf("from: %d\n", from);
	printf("to: %d\n", to);
	printf("wb: %d\n", wb);
	printf("from location:%d|%d\n",x1,y1);
	printf("to location:%d|%d\n",x2,y2);
	/* If not your turn */
	if(wb==0 && from>=7) {
		/* for white */
		return 1;
	} else if(wb!=0 && from<=6  && from!=0) {
		/* for black */
		return 1;
	}
	/* If square is empty */
	if(from==0) {
		return 1;
	}
	/* If same square */
	if(from==to) {
		return 1;
	}
	/* If same color */
	if(wb==0 && to<=6 && to!=0) {
		/* for white */
		return 1;	
	} else if(wb!=0 && to>=7) {
		/* for black */
		return 1;
	}
	
	switch (from) {
		/* Pawns moves */
		case 1:
			/* for white */
			if(x2==0) {
				promo(x1, y1, board);
			}
			if(to==0 && x1==6 && x2==4 && y1==y2 && board[5][y1]==0) {
				break;
			}
			if(x1!=x2+1){
				return 1;
			}
			if(y1==y2 && to!=0) {
				return 1;
			}
			if((to>0 && x1==x2+1 && (y1==y2+1 || y1==y2-1))) {
				break;
			}
			if(y1!=y2) {
				return 1;
			}
			break;
		case 7:
			/* for black */
			if(x2==7) {
				promo(x1, y1, board);	
			}
			if(to==0 && x1==1 && x2==3 && y1==y2 && board[2][y1]==0) {
				break;
			}
			if(x1!=x2-1) {
				return 1;
			}
			if(y1==y2 && to!=0) {
				return 1;
			}		
			if((to<7 && to!=0 && x1==x2-1 && (y1==y2-1 || y1==y2+1))) {
				break;
			}
			if(y1!=y2) {
				return 1;
			}
			break;
	}
	return 0;
}

void promo(int x, int y, int board[8][8]) {
	printf(clear);
	int invalidChoice;
	int promo = 0;
	char input[2];	
	if(turn%2!=0) {
		promo=6;
	}
	do {
		printf(correctBG whiteFG "===--Promotion--===\n" defaultBG);
		printBoard(board);
		printf("1. Knight\n");
		printf("2. Bishop\n");
		printf("3. Rook\n");
		printf("4. Queen\n");
		printf("Enter peace to promote(e.g. 1): ");
		scanf("%1s", &input);
		int digit = input[0]-'0';
		invalidChoice = 0;
		switch (digit) {
			case 1:
				board[x][y]=promo+3;
				break;
			case 2:
				board[x][y]=promo+2;
				break;
			case 3:
				board[x][y]=promo+4;
				break;
			case 4:
				board[x][y]=promo+5;
				break;
			default:
				printf(clear);
				invalidChoice = 1;
				invalidMove();
		}
	} while (invalidChoice);
	printf(clear);
}
