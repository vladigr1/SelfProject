#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//table is the number of games you play in one launch board size is password length
#define BOARDSIZE 4
#define TABLESIZE 12
#define SCOREFILE "GameScore.txt"

typedef struct {
	int *pass, BlackeScore, WhiteScore;
} Game,*PGame;


// 0 isnt part of the game ment not active 
void get_lost(char *string);
void free_pass(int *pass);
void PrintPass(int pass[]);
int *GenratePass();
void RandPass(int *pass);
void EnterPass(int *pass);
void ScoreGame(PGame Match,int *generate, int *enter);
void PrintGame(Game Match,int index);
void RunGame(Game Table[], int PreMade[], int NumGame);
int launchApp();
void TutorialApp();
int PrintScore();
void AddScore(int res);
void ResetScore();

int main()
{
	int EndMenuFlag = 1,avg,game;
	char button;
	while (EndMenuFlag) {
		int EndInputFlag = 1;
		printf("\n\t\tMENU:\n\n");
		printf("\tPress the button for:\n");
		printf("\t1. Start game\n");
		printf("\t2. Reset results\n");
		printf("\t3. Tutorial\n");
		printf("\t4. Exit\n");
		while (EndInputFlag) {
			EndInputFlag = 0;
			button = getch();
			switch (button) {
				case '3':
					TutorialApp();
					break;
				case '1':
					avg = PrintScore();
					game = launchApp();
					if (avg != 0) {
						if (avg > game) {
							printf("\tYou did better this game.\n\tavg: %d\n\tres: %d\n\n",avg,game);
						} else {
							printf("\tDidn't improve nab.\n\t avg: %d\n\tres: %d\n\n", avg, game);
						}
					}
					AddScore(game);
					break;
				case '2':
					ResetScore();
					break;
				case '4':
					EndMenuFlag = 0;
					break;
				default:
					printf("You press an illigal button\n");
					EndInputFlag = 1;
			}
		}
	}	
	return 0;
}


void get_lost(char *string)
{
	printf(string);
	exit(1);
}

void free_pass(int *pass)
{
	int i;
	for (i = 0; i < BOARDSIZE; ++i) {
		printf("%d ", pass[i]);
	}
	putch('\n');
	free(pass);
	pass = NULL;
}

void PrintPass(int pass[])
{
	int i;
	for (i = 0; i < BOARDSIZE; ++i) {
		printf("%d ", pass[i]);
	}
	putch('\n');
}


int *GenratePass()
{
	int *arr,i;
	srand(time(NULL));
	arr = (int *)malloc(sizeof(int) * BOARDSIZE);
	if (arr == NULL) get_lost("Malloc failed in GenratePass\n");
	return arr;
}

void RandPass(int *pass)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < BOARDSIZE; ++i) {
		pass[i] = rand() % 4 + 1;
	}
}

void EnterPass(int *pass)
{
	int i;
	printf("Please enter Pass (4 numbers 1-4 each enter one by one):\n");
	for (i = 0; i < BOARDSIZE; ++i) {
		printf("%d. ", i+1);
		scanf("%d", (pass + i) );
		if (pass[i] < 1 || pass[i] > 4) {
			printf("Number you enter is out of range.\n");
			--i;
		}
	}
	rewind(stdin);
}

// 0 isn't part of the game meant not active 
void ScoreGame(PGame Match, int *premade, int *enter)
{
	int MissMatchP[BOARDSIZE] = { 0 },MissMatchE[BOARDSIZE] = { 0 },i,j,missP=0,missE=0;
	Match->BlackeScore = 0;
	Match->WhiteScore = 0;
	Match->pass = enter;
	for(i = 0; i < BOARDSIZE; ++i)
	{
		if (premade[i] == enter[i]) {
			++(Match->BlackeScore);
		} else {
			for (j = 0; j < missP; ++j) {
				if (MissMatchP[j] == premade[i]) break;
			}
			if (missP == j) {
				++missP;
				MissMatchP[j] = premade[i];
			}
			//same for enter
			for (j = 0; j < missE; ++j) {
				if (MissMatchE[j] == enter[i]) break;
			}
			if (missE == j) {
				++missE;
				MissMatchE[j] = enter[i];
			}
		}
	}

	for (i = 0; i < missP; ++i) {
		for (j = 0; j < missE; ++j) {
			if (MissMatchP[i] == MissMatchE[j]) ++(Match->WhiteScore);
		}
	}
}

void PrintGame(Game Match, int index)
{
	int i;
	printf("\t %d. Pass: ",index+1);
	for (i = 0; i < BOARDSIZE; ++i) {
		printf("%d ",Match.pass[i]);
	}
	printf("\tBlackScore: %d\n\t\t\t  \tWhiteScore: %d\n\n", Match.BlackeScore, Match.WhiteScore);
}
void RunGame(Game Table[],int PreMade[], int NumGame)
{
	int i,*enter;
	for (i = 0; i < NumGame; ++i) {
		PrintGame(Table[i], i);
	}
	enter = GenratePass();
	EnterPass(enter);
	ScoreGame((Table + NumGame), PreMade, enter);
}

int launchApp()
{
	Game Table[TABLESIZE];
	int RandArr[BOARDSIZE],i;
	RandPass(RandArr);
	//PrintPass(RandArr);		//for dubuging seeing RandArr
	for (i = 0; i < TABLESIZE; ++i) {
		RunGame(Table, RandArr, i);
		if (Table[i].BlackeScore == 4) {
			int j;
			printf("You won with %d attempts ! the password was ",i+1);
			for (j = 0; j < BOARDSIZE; ++j) {
				printf("%d ", RandArr[j]);
			}
			printf("\n\n\t The passwords you tried:\n");
			for (j = 0; j < i+1; ++j) {
				printf("\t %d.\t", j+1);
				free_pass(Table[j].pass);
			}
			putch('\n');

			return i+1;		//at the end of the if ++i
		}
	}
	PrintGame(Table[i-1], i);
	printf("You LOST ! the password was ", i + 1);
	for (i = 0; i < BOARDSIZE; ++i) {
		printf("%d ", RandArr[i]);
	}
	printf("\n\n\t The passwords you tried:\n");
	for (i = 0; i < TABLESIZE; ++i) {
		printf("\t %d.\t", i);
		free_pass(Table[i].pass);
	}
	return TABLESIZE;
}

void TutorialApp()
{
	int RandomArr[] = { 1,4,2,2 }, enter[] = { 1,2,1,3 };
	Game Match;
	printf("\nThank you for playing,\nthe purpose of the game is to guess the password\n");
	printf("The password randomly generate the length of the password %d and you %d tries\n", BOARDSIZE, TABLESIZE);
	printf("the password contain numbers 1-4\n");
	printf("for each try you will get clues,\nblack point mean you places one number correctly\n");
	printf("White point mean you guess a number that didn't score black point but he appear in the password\n");
	printf("for exmaple let say the password is 1 4 2 2 and we guess 1 2 3 3\n\n");
	ScoreGame(&Match, RandomArr, enter);
	PrintGame(Match, 0);
	printf("\n\nIn the example we got black point because 1 and white point 2\n");
}

int PrintScore()
{
	FILE *score;
	int sum = 0, amount = 0,game,avg;
	score = fopen(SCOREFILE, "r");
	if (score == NULL) {
		printf("You never played a game\nLets make a NICE score\n\n");
		return 0;
	}
	while (feof(score) == 0) {
		fscanf(score, "%d", &game);
		sum += game;
		++amount;
	}
	avg = (sum % amount != 0 ? 1 + sum / amount : sum / amount);
	printf("Your average score is %d\nLets BEAT it\n\n",avg);
	fclose(score);
	return avg;
}

void AddScore(int res)
{
	FILE *score;
	score = fopen(SCOREFILE, "a+");
	if (score == NULL) {
		get_lost("error has accrued\n");
	}
	fprintf(score, " %d", res);
	fclose(score);
}
void ResetScore()
{
	remove(SCOREFILE);
}