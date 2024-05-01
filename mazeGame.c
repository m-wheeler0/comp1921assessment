#include<stdio.h>
#include<stdbool.h>
#include<string.h>

/*Each maze map will be stored within this struct, showing rows, columns allowing for easier
iteration over each character.*/

typedef struct
{
    /*Inspiration for representing the coord as a struct came from the code skeleton template provided*/
    int x;
    int y;
}coord;

typedef struct
{
    int rows;
    int columns;
    char maze[100][100];
    coord start;
    coord end;
}maze_map;

void validation(char filename[]){
    /*In this function, the file which is imported is then iterated through, going through
    multiple checks to make sure the maze file is valid (row/column limits, invalid
    characters etc...)*/

    FILE *pFile = fopen(filename, "r");
    /*FIRST Check if the file is a valid file*/

    if (pFile == NULL){
        printf("Unable to open file\n.");
    }
    else
    {
        //SECOND Find out the dimensions of the file

        //This loop returns the number of columns in the file.
    int charCount = 0;
    while(fgetc(pFile) != '\n'){
        charCount += 1;
    }

        //A second loop returns the number of rows in the file.

        /*THIRD Make sure the number of characters in said file is consistent
         with it's dimensions (make sure it is a square or rectangle)*/

         /*FOURTH Make sure all characters within the maze are valid characters*/
    }

}

bool checkMove(){
    /*This function gets a user input, and then looks at the 'coordinate' the user
    wants to move to, it then checks the character stored in that,
    If it is '#', reject the input,
    If it is a ' ', allow the player to move there*/
}

bool checkWin(){
    /*This function looks at the character in the maze that the user currently resides at,
    if it is an E; the user wins returning True. Otherwise return False and continue to ask for user inputs*/
}

void executeMove(){
    /*This function is ran if checkMove registers the user input as a valid input, it will go to the direction the user
    intends either going up into the previous line or to the next character and overwrite it, making sure to overwrite the
    original player position with a space " " to not remove characters and keep its rows and columns consistent*/

}

void printMaze(){
    /*This function prints the maze when the user inputs an "M"*/
}

/*All functions and structs defined will likely be in a header file when I am finshing the
program.*/


int main(){

    /*The main function in this code will ask the user to input the filename, and then validate that
    by calling upon the previous function*/

    /*The main function then processes user inputs and validates them by calling upon the previous function*/

    validation("testmaze.txt");
}