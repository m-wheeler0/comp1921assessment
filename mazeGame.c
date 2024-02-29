#include<stdio.h>
#include<stdbool.h>

/*Each maze map will be stored within this struct, showing rows, columns allowing for easier
iteration over each character.*/

typedef struct
{
    int rows;
    int columns;
    FILE *mazeFile;
}maze_map;

int validation(FILE *fileName){
    bool valid = true;

    /*In this function, the file which is imported is then iterated through, going through
    multiple checks to make sure the maze file is valid (row/column limits, invalid
    characters etc...)
    
    If it is successful, it should return two values for the number of rows and columns of the
    file, allowing easier iteration for a coordinate system.*/

    return columns;
    return rows;

}

bool checkMove(){
    /*This function gets a user input, and then looks at the 'coordinate' the user
    wants to move to, it then checks the character stored in that,
    If it is '#', reject the input,
    If it is an 'E', congratulate the user and end the maze,
    If it is a ' ', allow the player to move there.*/
}

/*All functions and structs defined will likely be in a header file when I am finshing the
program.*/

int main(){

    /*The main function in this code will ask the user to input the filename, and then validate that
    by calling upon the previous function*/

    /*The main function then processes user inputs and validates them by calling upon the previous function*/

    return 0;
}