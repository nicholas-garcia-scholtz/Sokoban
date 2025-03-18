#include <stdio.h>
#include <string.h>
#define ROWS 6
#define COLS 5
#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

void MakeBox(char box[], int width, int height){
    // Create edges
    int len = (width + 1) * (height);
    int i = 0;
    while (i<len){
        if (i == 0){
            for (int j = 0; j < width; j++){
                box[j] = '#';
            }
            box[width] = '\n';
            i = width + 1;
        } else if (i == len - width - 1){
            for (int j = 0; j < width; j++){
                box[i + j] = '#';
            }
            i = len;
            box[i - 1] = '\n';
        } else {
            box[i] = '#';
            for (int j = i + 1; j < i + width - 1; j++){
                box[j] = ' ';
            }
            i = i + width - 1;
            box[i] = '#';
            i++;
            box[i] = '\n';
            i++;
        }
    }

    // Locate 
    if ((width > 2 && height > 2)){
        if ((width % 2 == 1) && (height % 2 == 1)){
            box[(len/2) - 1] = 'X';
        } else if ((width % 2 == 0) && (height % 2 == 0)){
            box[(len / 2) - (width / 2) - 1] = 'X';
            box[(len / 2) - (width / 2) - 2] = 'X';
            box[(len / 2) + (width / 2)] = 'X';
            box[(len / 2) + (width / 2) - 1] = 'X';
        } else  if ((width % 2 == 0) && (height % 2 == 1)) {
            box[len / 2] = 'X';
            box[(len / 2) - 1] = 'X';
        } else {
            box[(len / 2) - (width / 2) - 2] = 'X';
            box[(len / 2) + (width / 2)] = 'X';
        }
    }
}

void PrintRoom(int room[ROWS][COLS]){
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if (room[i][j] == SPACE){
                printf(" ");
            } else if (room[i][j] == WALL){
                printf("#");
            } else if (room[i][j] == TARGET){
                printf("*");
            } else if (room[i][j] == BOX){
                printf("O");
            } else if (room[i][j] == BOX_ON_TARGET){
                printf("@");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }

}

void InitialiseRoom(int room[ROWS][COLS], char *layout){
    int len = strlen(layout);
    
    for (int i = 0; i<ROWS; i++){
        for (int j = 0; j<COLS; j++){
            if (len <= i*COLS + j){
                room[i][j] = WALL;
            } else {
                room[i][j] = layout[i*COLS + j] - 48;
            }
        }
    }
}
void LocatePerson(int room[ROWS][COLS], int *row, int *col){
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if ((room[i][j] == PERSON_ON_TARGET) || (room[i][j] == PERSON)){
                *row = i;
                *col = j;
            }
        }
    }
}


void MakeMove1(int room[ROWS][COLS], char move, char *allMoves, int moveNum, char *noBoxMoved, char *boxMoved){
    int row;
    int col;
    LocatePerson(room, &row, &col);
    
    if ((move == 'w') || (move == 's')) {
        if (room[row][col] == PERSON_ON_TARGET){
            if (room[row + moveNum][col] == SPACE){
                strcat(allMoves, noBoxMoved);
                room[row + moveNum][col] = PERSON;
                room[row][col] = TARGET;
            } else if (room[row + moveNum][col] == TARGET){
                strcat(allMoves, noBoxMoved);
                room[row + moveNum][col] = PERSON_ON_TARGET;
                room[row][col] = TARGET; 
            } else if ((room[row + moveNum][col] == BOX) && (room[row + moveNum * 2][col] == SPACE)){
                strcat(allMoves, boxMoved);
                room[row + moveNum * 2][col] = BOX;
                room[row + moveNum][col] = PERSON;
                room[row][col] = TARGET; 
            } else if ((room[row + moveNum][col] == BOX) && (room[row + moveNum * 2][col] == TARGET)){
                strcat(allMoves, boxMoved);
                room[row + moveNum * 2][col] = BOX_ON_TARGET;
                room[row + moveNum][col] = PERSON;
                room[row][col] = TARGET; 
            } else if((room[row + moveNum][col] == BOX_ON_TARGET) && (room[row + moveNum * 2][col] == SPACE)){
                strcat(allMoves, boxMoved);
                room[row + moveNum * 2][col] = BOX;
                room[row + moveNum][col] = PERSON_ON_TARGET;
                room[row][col] = TARGET; 
                
            } else if((room[row + moveNum][col] == BOX_ON_TARGET) && (room[row + moveNum * 2][col] == TARGET)){
                strcat(allMoves, boxMoved);
                room[row + moveNum * 2][col] = BOX_ON_TARGET;
                room[row + moveNum][col] = PERSON_ON_TARGET;
                room[row][col] = TARGET; 
            }
        } else {
            if (room[row + moveNum][col] == SPACE){
                strcat(allMoves, noBoxMoved);
                room[row + moveNum][col] = PERSON;
                room[row][col] = SPACE;
            } else if (room[row + moveNum][col] == TARGET){
                strcat(allMoves, noBoxMoved);
                room[row + moveNum][col] = PERSON_ON_TARGET;
                room[row][col] = SPACE; 
            } else if ((room[row + moveNum][col] == BOX) && (room[row + moveNum * 2][col] == SPACE)){
                strcat(allMoves, boxMoved);
                room[row + moveNum * 2][col] = BOX;
                room[row + moveNum][col] = PERSON;
                room[row][col] = SPACE; 
            } else if ((room[row + moveNum][col] == BOX) && (room[row + moveNum * 2][col] == TARGET)){
                strcat(allMoves, boxMoved);
                room[row + moveNum * 2][col] = BOX_ON_TARGET;
                room[row + moveNum][col] = PERSON;
                room[row][col] = SPACE; 
            } else if((room[row + moveNum][col] == BOX_ON_TARGET) && (room[row + moveNum * 2][col] == SPACE)){
                strcat(allMoves, boxMoved);
                room[row + moveNum * 2][col] = BOX;
                room[row + moveNum][col] = PERSON_ON_TARGET;
                room[row][col] = SPACE; 
                
            } else if((room[row + moveNum][col] == BOX_ON_TARGET) && (room[row + moveNum * 2][col] == TARGET)){
                strcat(allMoves, boxMoved);
                room[row + moveNum * 2][col] = BOX_ON_TARGET;
                room[row + moveNum][col] = PERSON_ON_TARGET;
                room[row][col] = SPACE; 
            }
        }
    } else if ((move == 'a') || (move == 'd')) {
  
        if (room[row][col] == PERSON_ON_TARGET){
            if (room[row][col + moveNum] == SPACE){
                strcat(allMoves, noBoxMoved);
                room[row][col + moveNum] = PERSON;
                room[row][col] = TARGET;
            } else if (room[row][col + moveNum] == TARGET){
                strcat(allMoves, noBoxMoved);
                room[row][col + moveNum] = PERSON_ON_TARGET;
                room[row][col] = TARGET; 
            } else if ((room[row][col + moveNum] == BOX) && (room[row][col + moveNum * 2] == SPACE)){
                strcat(allMoves, boxMoved);
                room[row][col + moveNum * 2] = BOX;
                room[row][col + moveNum] = PERSON;
                room[row][col] = TARGET; 
            } else if ((room[row][col + moveNum] == BOX) && (room[row][col + moveNum * 2] == TARGET)){
                strcat(allMoves, boxMoved);
                room[row][col + moveNum * 2] = BOX_ON_TARGET;
                room[row][col + moveNum] = PERSON;
                room[row][col] = TARGET; 
            } else if((room[row][col + moveNum] == BOX_ON_TARGET) && (room[row][col + moveNum * 2] == SPACE)){
                strcat(allMoves, boxMoved);
                room[row][col + moveNum * 2] = BOX;
                room[row][col + moveNum] = PERSON_ON_TARGET;
                room[row][col] = TARGET; 
                
            } else if((room[row][col + moveNum] == BOX_ON_TARGET) && (room[row][col + moveNum * 2] == TARGET)){
                strcat(allMoves, boxMoved);
                room[row][col + moveNum * 2] = BOX_ON_TARGET;
                room[row][col + moveNum] = PERSON_ON_TARGET;
                room[row][col] = TARGET; 
            }
        } else {
            if (room[row][col + moveNum] == SPACE){
                strcat(allMoves, noBoxMoved);
                room[row][col + moveNum] = PERSON;
                room[row][col] = SPACE;
            } else if (room[row][col + moveNum] == TARGET){
                strcat(allMoves, noBoxMoved);
                room[row][col + moveNum] = PERSON_ON_TARGET;
                room[row][col] = SPACE; 
            } else if ((room[row][col + moveNum] == BOX) && (room[row][col + moveNum * 2] == SPACE)){
                strcat(allMoves, boxMoved);
                room[row][col + moveNum * 2] = BOX;
                room[row][col + moveNum] = PERSON;
                room[row][col] = SPACE; 
            } else if ((room[row][col + moveNum] == BOX) && (room[row][col + moveNum * 2] == TARGET)){
                strcat(allMoves, boxMoved);
                room[row][col+ moveNum * 2] = BOX_ON_TARGET;
                room[row][col + moveNum] = PERSON;
                room[row][col] = SPACE; 
            } else if((room[row][col + moveNum] == BOX_ON_TARGET) && (room[row][col+ moveNum * 2] == SPACE)){
                strcat(allMoves, boxMoved);
                room[row][col + moveNum * 2] = BOX;
                room[row][col + moveNum] = PERSON_ON_TARGET;
                room[row][col] = SPACE; 
                
            } else if((room[row][col + moveNum] == BOX_ON_TARGET) && (room[row][col + moveNum * 2] == TARGET)){
                strcat(allMoves, boxMoved);
                room[row][col + moveNum * 2] = BOX_ON_TARGET;
                room[row][col + moveNum] = PERSON_ON_TARGET;
                room[row][col] = SPACE; 
            }
        }
    }
}
void UndoMove(int room[ROWS][COLS], char *allMoves){
    int len = strlen(allMoves);
    int r = 0, c = 0;
    LocatePerson(room, &r, &c);
    char move[2];
    move[0] = allMoves[len - 2];
    move[1] = allMoves[len - 1];

    if (len > 0){
        allMoves[len - 2] = '\0';
        if (move[0] == 'w'){
            MakeMove1(room, 's', allMoves, 1, "s0", "s1");
            if (move[1] == '1'){
                if (room[r - 1][c] == BOX_ON_TARGET){
                    room[r - 1][c] = TARGET;
                    if (room[r][c] == TARGET){
                        room[r][c] = BOX_ON_TARGET;
                    } else {
                        room[r][c] = BOX;
                    }
                } else if (room[r - 1][c] == BOX)  {
                    room[r - 1][c] = SPACE;
                    if (room[r][c] == TARGET){
                        room[r][c] = BOX_ON_TARGET;
                    } else {
                        room[r][c] = BOX;
                    }
                }
            }
        } else if (move[0] == 's'){
            MakeMove1(room, 'w', allMoves, -1, "w0", "w1");
            if (move[1] == '1'){
                if (room[r + 1][c] == BOX_ON_TARGET){
                    room[r + 1][c] = TARGET;
                    if (room[r][c] == TARGET){
                        room[r][c] = BOX_ON_TARGET;
                    } else {
                        room[r][c] = BOX;
                    }
                } else if (room[r + 1][c] == BOX) {
                    room[r + 1][c] = SPACE;
                    if (room[r][c] == TARGET){
                        room[r][c] = BOX_ON_TARGET;
                    } else {
                        room[r][c] = BOX;
                    }
                }
            }
        } else if (move[0] == 'a'){
            MakeMove1(room, 'd', allMoves, 1, "d0", "d1");
            if (move[1] == '1'){
                if (room[r][c - 1] == BOX_ON_TARGET){
                    room[r][c - 1] = TARGET;
                    if (room[r][c] == TARGET){
                        room[r][c] = BOX_ON_TARGET;
                    } else {
                        room[r][c] = BOX;
                    }
                } else if (room[r][c - 1] == BOX) {
                    room[r][c - 1] = SPACE;
                    if (room[r][c] == TARGET){
                        room[r][c] = BOX_ON_TARGET;
                    } else {
                        room[r][c] = BOX;
                    }
                }
            }
        } else if (move[0] == 'd') {      
            MakeMove1(room, 'a', allMoves, -1, "a0", "a1");
            if (move[1] == '1'){
                if (room[r][c + 1] == BOX_ON_TARGET){
                    room[r][c + 1] = TARGET;
                    if (room[r][c] == TARGET){
                        room[r][c] = BOX_ON_TARGET;
                    } else {
                        room[r][c] = BOX;
                    }
                } else if (room[r][c + 1] == BOX){
                    room[r][c + 1] = SPACE;
                    if (room[r][c] == TARGET){
                        room[r][c] = BOX_ON_TARGET;
                    } else {
                        room[r][c] = BOX;
                    }
                }
            }
        }
        allMoves[len - 2] = '\0';
        
    }
}

void MakeMove(int room[ROWS][COLS], char move, char *allMoves){
    if (move == 'z'){
        UndoMove(room, allMoves);
    } else if (move == 'w'){
        MakeMove1(room, 'w', allMoves, -1, "w0", "w1");
    } else if (move == 's'){
        MakeMove1(room, 's', allMoves, 1, "s0", "s1");
    } else if (move == 'a'){
        MakeMove1(room, 'a', allMoves, -1, "a0", "a1");
    } else if (move == 'd'){
        MakeMove1(room, 'd', allMoves, 1, "d0", "d1");
    }
    
}

void TestMove(void){
    char layout[200] = "111111005110301120311002111111";
    char moves[100] = {0};
    int room[ROWS][COLS];
    InitialiseRoom(room, layout);
    MakeMove(room, 's', moves);
    PrintRoom(room);
    printf("Moves: %s", moves);
}

int CheckGameOver(int room[ROWS][COLS]){
    int hasBoxOnTarget = 0;
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if ((room[i][j] == TARGET)|| (room[i][j] == PERSON_ON_TARGET)){
                return 0;
            }
            if (room[i][j] == BOX_ON_TARGET){
                hasBoxOnTarget = 1;
            }
        }
    }
    if (hasBoxOnTarget == 1){
        return 1;
    }
    return 0;   
}


int main()
{
    TestMove();

    return 0;
}