#include<stdio.h>
#include<stdbool.h>

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

//void fileOpener(char[] filename){
    /*In this function, the file is opened and read through, before being returned as an array of characters*/
    //char[100] line;
    //char[100][100] array;

    //FILE *pFile;
    //pFile = fopen(line, filename, "r");
    //int looper = 0;
    
    //while(fgets(line, 101, pFile)){
        //strdup(array[looper], line);
        //looper ++;
    //};

    //fclose(pFile);
//}

char* validation(){
    /*In this function, the file which is imported is then iterated through, going through
    multiple checks to make sure the maze file is valid (row/column limits, invalid
    characters etc...)*/

    bool valid = true;
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

    int a = 5;
    
    printf("%d\n", *&a);
}