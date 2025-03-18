/*
ENGGEN131 2024
C Project - Boxed In
Resource file - project2.c

You can use this program to test the functions that you write before grading them with CodeRunner
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define ROWS 9
#define COLS 8

#define SPACE 0
#define WALL 1
#define TARGET 2
#define BOX 3
#define BOX_ON_TARGET 4
#define PERSON 5
#define PERSON_ON_TARGET 6

// Function prototype declarations
void MakeBox(char *design, int width, int height);
void PrintRoom(int room[ROWS][COLS]);
void InitialiseRoom(int room[ROWS][COLS], char *layout);
void LocatePerson(int room[ROWS][COLS], int *row, int *col);
void MakeMove(int room[ROWS][COLS], char move, char *allMoves);
int CheckGameOver(int room[ROWS][COLS]);
void UndoMove(int room[ROWS][COLS], char *allMoves);

// Task One ///////////////////////////////////////////////////////////////
void MakeBox(char *design, int width, int height)
{
	design[1] = (char)(width + height); // This is incorrect, but prevents compiler warnings!
}

// Task Two ///////////////////////////////////////////////////////////////
void PrintRoom(int room[ROWS][COLS])
{
	printf("%d", room[0][0]);  // This is incorrect, but prevents compiler warnings!
}

// Task Three ///////////////////////////////////////////////////////////////
void InitialiseRoom(int room[ROWS][COLS], char *layout)
{
	room[0][0] = layout[0]; // This is incorrect, but prevents compiler warnings!
}

// Task Four ///////////////////////////////////////////////////////////////
void LocatePerson(int room[ROWS][COLS], int *row, int *col)
{
	room[0][0] = *row + *col; // This is incorrect, but prevents compiler warnings!
}

// Task Five - Task Eight ////////////////////////////////////////////////////////
void MakeMove(int room[ROWS][COLS], char move, char *allMoves)
{
	room[0][0] = move + allMoves[0]; // This is incorrect, but prevents compiler warnings!
}

// Task Nine /////////////////////////////////////////////////////////////////
int CheckGameOver(int room[ROWS][COLS])
{
	return room[0][0]; // This is incorrect, but prevents compiler warnings!
}

// Task Ten /////////////////////////////////////////////////////////////////
void UndoMove(int room[ROWS][COLS], char *allMoves)
{
	room[0][0] = allMoves[0]; // This is incorrect, but prevents compiler warnings!
}

/***************************************************************************************
Test functions.
You should define your own test functions here as you progress through the project.
***************************************************************************************/
void TestMakeBox(void)
{
	char box[1000] = {0};

	MakeBox(box, 12, 5);
	printf("Box = \n%s\n", box);
}

void TestPrintRoom(void)
{
	int room[ROWS][COLS] =
		{{0,0,1,1,1,1,1,0},
 		 {1,1,1,0,0,0,1,0},
 		 {1,2,5,3,0,0,1,0},
		 {1,1,1,0,3,2,1,0},
		 {1,2,1,1,3,0,1,0},
		 {1,0,1,0,2,0,1,1},
		 {1,3,0,4,3,3,2,1},
		 {1,0,0,0,2,0,0,1},
		 {1,1,1,1,1,1,1,1}};

	PrintRoom(room);
}


void TestInitialiseRoom(void)
{
	char layout[] = "001111101110001012530010111032101211301010102011130433211000200111111111";
	int room[ROWS][COLS];

	InitialiseRoom(room, layout);
	PrintRoom(room);
}

/***************************************************************************************
Test program
***************************************************************************************/
int main(void)
{
	printf("Testing Task One\n================\n\n");
	TestMakeBox();

	printf("\n\nTesting Task Two\n================\n\n");
	TestPrintRoom();

	printf("\n\nTesting Task Three\n==================\n\n");
	TestInitialiseRoom();

	return 0;
}


