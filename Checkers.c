#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define SQRSIZE 6
#define BRDSIZE 9

//blocks 1 white blocks 2 black blocks 3 white block 4 black pieces
//type is for playing piece or not
typedef struct sqr
    {
    char image[SQRSIZE][SQRSIZE + 1];
    int type;
    }square;

void Printsqr(char arr[][SQRSIZE + 1], int size);//print image (for image test)
void PrintBoardLine(int arr[], square pieces[]);//print single line 1 * 9 
void PrintBoard(int arr[][BRDSIZE], square pieces[]);

int PieceMove(int *PBoard[], int turn);
int CheckSimpleEat(int *PBoard[], char sc, int sn, char dc, int dn);

void LiveGame(int *PBoard[], square pieces[]);

int main( )
    {
    int i, j, Board[][BRDSIZE] =
        {
                { 11,4,2,4,2,4,2,4,2 },
                { 12,2,4,2,4,2,4,2,4 },
                { 13,4,2,1,2,4,2,4,2 },
                { 14,2,4,2,1,2,1,2,1 },
                { 15,1,2,3,2,1,2,1,2 },
                { 16,2,3,2,1,2,3,2,3 },
                { 17,3,2,3,2,3,2,3,2 },
                { 18,2,3,2,3,2,3,2,3 },
                { 1,21,22,23,24,25,26,27,28 }
        };
    //blocks 1 white blocks 2 black blocks 3 white block 4 black pieces number 1-8 11-18 letter A-H 21-28
    //type 0 unplayable 1 white 2 black 3 white stone 4 black stone 5 white king 6 black king
    square pieces[29];

    pieces[1].type = 1;//	setting white
    strcpy(pieces[1].image[0], " ---- ");
    strcpy(pieces[1].image[1], "|    |");
    strcpy(pieces[1].image[2], "|    |");
    strcpy(pieces[1].image[3], "|    |");
    strcpy(pieces[1].image[4], "|    |");
    strcpy(pieces[1].image[5], " ---- ");

    pieces[2].type = 2;//	setting black
    strcpy(pieces[2].image[0], " ---- ");
    strcpy(pieces[2].image[1], "| - -|");
    strcpy(pieces[2].image[2], "|  - |");
    strcpy(pieces[2].image[3], "| -  |");
    strcpy(pieces[2].image[4], "|- - |");
    strcpy(pieces[2].image[5], " ---- ");

    pieces[1].type = 3;//	setting white stone
    strcpy(pieces[3].image[0], " ---- ");
    strcpy(pieces[3].image[1], "| -- |");
    strcpy(pieces[3].image[2], "||  ||");
    strcpy(pieces[3].image[3], "||  ||");
    strcpy(pieces[3].image[4], "| -- |");
    strcpy(pieces[3].image[5], " ---- ");
    pieces[2].type = 4;//	setting black stone
    strcpy(pieces[4].image[0], " ---- ");
    strcpy(pieces[4].image[1], "|    |");
    strcpy(pieces[4].image[2], "||--||");
    strcpy(pieces[4].image[3], "||--||");
    strcpy(pieces[4].image[4], "|    |");
    strcpy(pieces[4].image[5], " ---- ");

    pieces[11].type = 0;//	setting 1
    strcpy(pieces[11].image[0], " ---- ");
    strcpy(pieces[11].image[1], "|    |");
    strcpy(pieces[11].image[2], "| 1  |");
    strcpy(pieces[11].image[3], "|    |");
    strcpy(pieces[11].image[4], "|    |");
    strcpy(pieces[11].image[5], " ---- ");

    pieces[12].type = 0;//	setting 2
    strcpy(pieces[12].image[0], " ---- ");
    strcpy(pieces[12].image[1], "|    |");
    strcpy(pieces[12].image[2], "| 2  |");
    strcpy(pieces[12].image[3], "|    |");
    strcpy(pieces[12].image[4], "|    |");
    strcpy(pieces[12].image[5], " ---- ");

    pieces[13].type = 0;//	setting 3
    strcpy(pieces[13].image[0], " ---- ");
    strcpy(pieces[13].image[1], "|    |");
    strcpy(pieces[13].image[2], "| 3  |");
    strcpy(pieces[13].image[3], "|    |");
    strcpy(pieces[13].image[4], "|    |");
    strcpy(pieces[13].image[5], " ---- ");

    pieces[14].type = 0;//	setting 4
    strcpy(pieces[14].image[0], " ---- ");
    strcpy(pieces[14].image[1], "|    |");
    strcpy(pieces[14].image[2], "| 4  |");
    strcpy(pieces[14].image[3], "|    |");
    strcpy(pieces[14].image[4], "|    |");
    strcpy(pieces[14].image[5], " ---- ");

    pieces[15].type = 0;//	setting 5
    strcpy(pieces[15].image[0], " ---- ");
    strcpy(pieces[15].image[1], "|    |");
    strcpy(pieces[15].image[2], "| 5  |");
    strcpy(pieces[15].image[3], "|    |");
    strcpy(pieces[15].image[4], "|    |");
    strcpy(pieces[15].image[5], " ---- ");

    pieces[16].type = 0;//	setting 6
    strcpy(pieces[16].image[0], " ---- ");
    strcpy(pieces[16].image[1], "|    |");
    strcpy(pieces[16].image[2], "| 6  |");
    strcpy(pieces[16].image[3], "|    |");
    strcpy(pieces[16].image[4], "|    |");
    strcpy(pieces[16].image[5], " ---- ");

    pieces[17].type = 0;//	setting 7
    strcpy(pieces[17].image[0], " ---- ");
    strcpy(pieces[17].image[1], "|    |");
    strcpy(pieces[17].image[2], "| 7  |");
    strcpy(pieces[17].image[3], "|    |");
    strcpy(pieces[17].image[4], "|    |");
    strcpy(pieces[17].image[5], " ---- ");

    pieces[18].type = 0;//	setting 8
    strcpy(pieces[18].image[0], " ---- ");
    strcpy(pieces[18].image[1], "|    |");
    strcpy(pieces[18].image[2], "| 8  |");
    strcpy(pieces[18].image[3], "|    |");
    strcpy(pieces[18].image[4], "|    |");
    strcpy(pieces[18].image[5], " ---- ");

    pieces[21].type = 0;//	setting A
    strcpy(pieces[21].image[0], " ---- ");
    strcpy(pieces[21].image[1], "|    |");
    strcpy(pieces[21].image[2], "| A  |");
    strcpy(pieces[21].image[3], "|    |");
    strcpy(pieces[21].image[4], "|    |");
    strcpy(pieces[21].image[5], " ---- ");

    pieces[22].type = 0;//	setting B
    strcpy(pieces[22].image[0], " ---- ");
    strcpy(pieces[22].image[1], "|    |");
    strcpy(pieces[22].image[2], "| B  |");
    strcpy(pieces[22].image[3], "|    |");
    strcpy(pieces[22].image[4], "|    |");
    strcpy(pieces[22].image[5], " ---- ");

    pieces[23].type = 0;//	setting C
    strcpy(pieces[23].image[0], " ---- ");
    strcpy(pieces[23].image[1], "|    |");
    strcpy(pieces[23].image[2], "| C  |");
    strcpy(pieces[23].image[3], "|    |");
    strcpy(pieces[23].image[4], "|    |");
    strcpy(pieces[23].image[5], " ---- ");

    pieces[24].type = 0;//	setting D
    strcpy(pieces[24].image[0], " ---- ");
    strcpy(pieces[24].image[1], "|    |");
    strcpy(pieces[24].image[2], "| D  |");
    strcpy(pieces[24].image[3], "|    |");
    strcpy(pieces[24].image[4], "|    |");
    strcpy(pieces[24].image[5], " ---- ");

    pieces[25].type = 0;//	setting E
    strcpy(pieces[25].image[0], " ---- ");
    strcpy(pieces[25].image[1], "|    |");
    strcpy(pieces[25].image[2], "| E  |");
    strcpy(pieces[25].image[3], "|    |");
    strcpy(pieces[25].image[4], "|    |");
    strcpy(pieces[25].image[5], " ---- ");

    pieces[26].type = 0;//	setting F
    strcpy(pieces[26].image[0], " ---- ");
    strcpy(pieces[26].image[1], "|    |");
    strcpy(pieces[26].image[2], "| F  |");
    strcpy(pieces[26].image[3], "|    |");
    strcpy(pieces[26].image[4], "|    |");
    strcpy(pieces[26].image[5], " ---- ");

    pieces[27].type = 0;//	setting H
    strcpy(pieces[27].image[0], " ---- ");
    strcpy(pieces[27].image[1], "|    |");
    strcpy(pieces[27].image[2], "| G  |");
    strcpy(pieces[27].image[3], "|    |");
    strcpy(pieces[27].image[4], "|    |");
    strcpy(pieces[27].image[5], " ---- ");

    pieces[28].type = 0;//	setting G
    strcpy(pieces[28].image[0], " ---- ");
    strcpy(pieces[28].image[1], "|    |");
    strcpy(pieces[28].image[2], "| H  |");
    strcpy(pieces[28].image[3], "|    |");
    strcpy(pieces[28].image[4], "|    |");
    strcpy(pieces[28].image[5], " ---- ");

	LiveGame(&Board, pieces);
    _getch( );
    return 0;
    }


void Printsqr(char arr[][SQRSIZE + 1], int size)
    {
    int i, j;
    for(i = 0; i < size; ++i){
        for(j = 0; j < size; ++j)printf("%c", *(*(arr + i) + j));
        putch('\n');
        }
    }

//blocks 1 white blocks 2 black blocks 3 white block 4 black pieces
void PrintBoardLine(int arr[], square pieces[])
    {
    int i, j;
    square currnet_pieace;
    char Printline[SQRSIZE*BRDSIZE + 1];
    for(i = 0; i < SQRSIZE; ++i){
        for(j = 0; j < BRDSIZE; ++j){
            switch(arr[j]){
                    case 1:
                        currnet_pieace = pieces[1];
                        break;
                    case 2:
                        currnet_pieace = pieces[2];
                        break;
                    case 3:
                        currnet_pieace = pieces[3];
                        break;
                    case 4:
                        currnet_pieace = pieces[4];
                        break;
                    case 11:
                        currnet_pieace = pieces[11];
                        break;
                    case 12:
                        currnet_pieace = pieces[12];
                        break;
                    case 13:
                        currnet_pieace = pieces[13];
                        break;
                    case 14:
                        currnet_pieace = pieces[14];
                        break;
                    case 15:
                        currnet_pieace = pieces[15];
                        break;
                    case 16:
                        currnet_pieace = pieces[16];
                        break;
                    case 17:
                        currnet_pieace = pieces[17];
                        break;
                    case 18:
                        currnet_pieace = pieces[18];
                        break;
                    case 21:
                        currnet_pieace = pieces[21];
                        break;
                    case 22:
                        currnet_pieace = pieces[22];
                        break;
                    case 23:
                        currnet_pieace = pieces[23];
                        break;
                    case 24:
                        currnet_pieace = pieces[24];
                        break;
                    case 25:
                        currnet_pieace = pieces[25];
                        break;
                    case 26:
                        currnet_pieace = pieces[26];
                        break;
                    case 27:
                        currnet_pieace = pieces[27];
                        break;
                    case 28:
                        currnet_pieace = pieces[28];
                        break;

                }
            strcpy(Printline + j*(SQRSIZE), currnet_pieace.image[i]);
            }
        printf("%s\n", Printline);
        }
    }

void PrintBoard(int arr[][BRDSIZE], square pieces[])
    {
    int i;
    for(i = 0; i < BRDSIZE; ++i) PrintBoardLine(arr[i], pieces);
    }

//blocks 1 white blocks 2 black blocks 3 white block 4 black pieces number 1-8 11-18 letter A-H 21-28
int PieceMove(int *PBoard[], int turn)
    {
    int sn = 0, dn = 0, dflag = 0, sstone =0,dstone=0, RFlag=0;
    char sc = 'a', dc = 'a';
    switch(turn){
            case 1:
                printf("white turn: Please enter Stone (L N)(keep it small letter): ");
                break;
            case 2:
                printf("black turn: Please enter Stone (L N)(keep it small letter): ");
                break;
        }
    while(sstone != turn + 2){
        scanf("%c%d", &sc, &sn);
        sstone = *(PBoard + (sn-1)*BRDSIZE + (sc - 'a'+1));
        if (sstone != turn + 2) printf("you have chosen a bad stone pick again: ");
        rewind(stdin);
        }
    while(dflag == 0){
        printf("Pick destination: ");
        scanf("%c%d", &dc, &dn);
        dstone = *(PBoard + (dn-1)*BRDSIZE + (dc - 'a'+1));
        //check which move check if legal with the simple stone then check the stone he landed
        if((turn - 1) ? (dn - sn) == 1 && (dc - sc)*(dc - sc) == 1 : (dn - sn) == -1 && (dc - sc)*(dc - sc) == 1){
            switch(dstone){
                    case 1:
						RFlag = (turn - 1) ? turn - 1 : turn + 1;
                        dflag = 1;									//eating
                        break;
                    case 3:case 4:
						if(turn + 2 != dstone){						//eating part
							if(CheckSimpleEat(&PBoard, sc, sc, dc, dn)){
								*(PBoard + (dn - 1) * BRDSIZE + (dc - 'a' + 1)) = 1;
								dn += dn - sn;
								dc += dc - sc;
								RFlag = turn;
								dflag = 1;
								}
							}			
                        else printf("you have chosen you own stone\n");
                        break;
                    default:
                        printf("bad destination\n");
                }
            } else printf("Bad move\n");
        rewind(stdin);
        }
    *(PBoard + (sn-1) * BRDSIZE + (sc - 'a'+1)) = 1;
    *(PBoard + (dn-1) * BRDSIZE + (dc - 'a'+1)) = turn + 2;
	return RFlag;
    }

int CheckSimpleEat(int *PBoard[], char sc, int sn,char dc,int dn)
	{
	int sstone, dstone, nextstone;
	sstone = *(PBoard + (sn + 1)*BRDSIZE + (sc - 'a' + 1));
	dstone = *(PBoard + (dn + 1)*BRDSIZE + (dc - 'a' + 1));
	nextstone = *(PBoard + (dn + 1 + (dn - sn)) + (dc - 'a' + 1 + (dc - sc)));
	if((2 - sstone) ? (3 - dstone) : (2 - dstone)|| nextstone ==1){
		return 1;
		}
	return 0;
	}

void LiveGame(int *PBoard[], square pieces[])
	{
	int i,turn =1;
	for(i = 0; i < 5; ++i){
		PrintBoard(PBoard, pieces);
		turn = PieceMove(PBoard, turn);
		}
	}