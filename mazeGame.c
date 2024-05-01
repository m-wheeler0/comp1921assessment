#include<stdio.h>
#include<stdlib.h>
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

char** validation(char filename[]){
    /*In this function, the file which is imported is then iterated through, going through
    multiple checks to make sure the maze file is valid (row/column limits, invalid
    characters etc...)*/

    FILE *pFile = fopen(filename, "r");
    /*FIRST Check if the file is a valid file*/

    char c;

    if (pFile == NULL){
        printf("Unable to open file.\n");
        exit(1);
    }
    else
    {
        //SECOND Find out the dimensions of the file

        //This loop returns the number of columns in the file.
        int charCount = 0;
        while(fgetc(pFile) != '\n'){
            charCount ++;
        }

        //A second loop returns the number of rows in the file.
        fseek(pFile, 0, SEEK_SET);
        char tempString[charCount + 1]; 
        int rowCount = 0;
        /*We must use tempString + 2 as a parameter to accomodate for
        newline and null characters*/

        while((fgets(tempString, sizeof(tempString) + 1, pFile)) != NULL){
                rowCount++;
            }
            /*THIRD Make sure the number of characters in said file is consistent
        with it's dimensions (make sure it is a square or rectangle)*/
        fseek(pFile, 0, SEEK_SET);
        int xCharacters = (charCount * rowCount) + (rowCount - 1);
        int actCharacters = 0;
        /*invalidCharacter will be used as a pseudo boolean to return whether
        there are any invalid characters in the text file*/

        while((c = fgetc(pFile)) != EOF){
            actCharacters++;
            /*It would be better here to check if any of the characters do not match the allowed
            characters stated by the assignment {" ", "S", "E", "#"}, since we are checking every
            character anyway.*/
            if(c != ' ' && c != 'S' && c != 'E' && c != '#' && c!='\n'){
                printf("Invalid character found.");
                fclose(pFile);
                exit(1);
                }
            }

        if (actCharacters == xCharacters){
            fseek(pFile, 0, SEEK_SET);
            char** pArray = (char**) malloc(sizeof(char*) * rowCount);

            for(int i = 0; i < rowCount; i++){
                *(pArray + i) = fgets(tempString, sizeof(tempString), pFile);
            }

            return pArray;
            }
        else{
            printf("Invalid maze file was inputted\n");
            fclose(pFile);
            exit(1);
            }
        }
}


maze_map mapBuilder(){

}

void checkMove(){
    /*This function gets a user input, and then looks at the 'coordinate' the user
    wants to move to, it then checks the character stored in that,
    If it is '#', reject the input,
    If it is a ' ', allow the player to move there*/
}

void checkWin(){
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

    printf("%p", validation("valid/reg_5x5.txt"));

    return 0;
}