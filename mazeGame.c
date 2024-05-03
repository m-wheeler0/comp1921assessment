#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIMENSION_VALUE 100
#define MIN_DIMENSION_VALUE 5

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
    char** maze;
    coord start;
    coord end;
}maze_map;

typedef struct
{
    int rows;
    int columns;
}dimensions;

/*Validation function, gets the filename as a string and a reference to a dimensions struct which
will be edited within the function for use in other functions

Puts the file through multiple checks to ensure the maze is valid*/

int validation(char filename[], dimensions* fileDimensions){
    /*In this function, the file which is imported is then iterated through, going through
    multiple checks to make sure the maze file is valid (row/column limits, invalid
    characters etc...)*/

    FILE *pFile = fopen(filename, "r");
    /*FIRST Check if the file is a valid file*/

    char c;
    int trailing;
    int actCharacters;
    int sCount = 0;
    int eCount = 0;

    if (pFile == NULL){
        //Return a file error if it cannot be found/opened
        return 2;
    }
    else
    {
        //First find out the dimensions of the file

        //This loop returns the number of columns in the file.
        fseek(pFile, 0, SEEK_SET);
        int charCount = 0;
        while(fgetc(pFile) != '\n'){
            charCount ++;
        }

        //A second loop returns the number of rows in the file.
        fseek(pFile, 0, SEEK_SET);
        char tempString[charCount + 1]; 
        int rowCount = 0;
        /*We must use tempString + 1 as a parameter to accomodate for
        newline and null characters*/

        while((fgets(tempString, sizeof(tempString) + 1, pFile)) != NULL){
            rowCount++;
        }

        fileDimensions -> rows = rowCount;
        fileDimensions -> columns = charCount;

        // Check if the last character is a new line and accomodate the rowCount if it is:
        fseek(pFile, -1, SEEK_END);
        c = fgetc(pFile);

        if(c == '\n'){
            trailing = 1;
        }
        else{
            trailing = 0;
        }

        if (trailing == 0){
            actCharacters = 0;
        }
        else{
            actCharacters = -1;
        }
        
        fseek(pFile, 0, SEEK_SET);

        while((c = fgetc(pFile)) != EOF){
            /*It would be better here to check if any of the characters do not match the allowed
            characters stated by the assignment {" ", "S", "E", "#"}, since we are checking every
            character anyway.*/
            if(c != ' ' && c != 'S' && c != 'E' && c != '#' && c != '\n' && c != '\0'){
                fclose(pFile);
                return 3;
                }
                else{
                    if(c == 'S'){
                        sCount ++;
                    }
                    else if(c == 'E'){
                        eCount ++;
                    }
                    actCharacters++;
                }
            }

        //If sCount or eCount are not equal to 1, reject maze as too many start or/and end points

        if (sCount != 1 || eCount != 1){
            return 3;
        }


        /*The final check to do before returning the 2D Array of characters is to make sure the dimensions
        are within bounds > 5 AND < 100 for both.*/

        if((rowCount < MIN_DIMENSION_VALUE) || (rowCount > MAX_DIMENSION_VALUE)
        ||(charCount < MIN_DIMENSION_VALUE) || (charCount > MAX_DIMENSION_VALUE)){
            return 3;
        }
        else{
            /*Make sure the number of characters in said file is consistent
            with it's dimensions (make sure it is a square or rectangle)*/

            if (actCharacters == ((charCount * rowCount) + (rowCount - 1))){
                return 0;
            }
            else{
                return 3;
            }
        }
    }
}

/*Read the file, and store it into a two dimensional array of characters like a grid
return a maze_map struct of the maze containing rows, columns and default coord structs for the
start and end characters to be operated on in the mapBuilder function*/

maze_map fileToArray(char filename[], dimensions fileDimensions){
    char tempString[fileDimensions.columns + 1]; 
    FILE *pFile = fopen(filename, "r");
    fseek(pFile, 0, SEEK_SET);

    //Allocate memory for the array, it will be used and processed frequently

    char** pArray = (char**) malloc(sizeof(char*) * fileDimensions.rows);

    for(int i = 0; i < fileDimensions.rows; i++){
        pArray[i] = malloc(sizeof(char) * (fileDimensions.columns + 1));
        fgets(tempString, sizeof(tempString) + 1, pFile);
        strcpy(pArray[i], tempString);
    }

    /*Create a maze_map structure, passing the start and end coords as default values of 0,0
    We will change these values later in the mapBuilder function.*/
    maze_map mazeMap;
    mazeMap.rows = fileDimensions.rows;
    mazeMap.columns = fileDimensions.columns;
    mazeMap.maze = pArray;
    mazeMap.start.x = mazeMap.start.y = 0;
    mazeMap.end.x = mazeMap.end.y = 0;

    return mazeMap;
}

coord mapBuilder(maze_map map, coord player){
    /*All this function should do is iterate through every character in the 2D
    Char array until it finds an S and the same with the E, then alter the default
    coord structs within the start and end members of map_maze*/

    /*It should then set the coordinates of the player to the start coordinates of the map*/
    for (int y = 0; y < map.rows; y++){
        for(int x = 0; x < map.columns; x++){
            if (map.maze[y][x] == 'S'){
                map.start.x = x;
                map.start.y = y;
            }
            else if (map.maze[y][x] == 'E'){
                map.end.x = x;
                map.end.y = y;
            }
        }
    }

    player.x = map.start.x;
    player.y = map.start.y;

    return player;
}

/*This function prints the maze when the user inputs an "M"
It should print the entire maze replacing the player position with an 'X'*/

void printMaze(maze_map map, coord player){
    printf("\n");
    for(int i = 0; i < map.rows; i++){
        if (i == player.y){
            for(int j = 0; j <= map.columns; j++){
                if (j == player.x){
                    printf("%c",'X');
                }
                else{
                    printf("%c", map.maze[i][j]);
                }
            }
        }
        else
        {
            printf("%s", map.maze[i]);
        }
    }
    printf("\n");
}

int checkMove(maze_map map, coord* player, char userInput){
    /*This function gets a user input, and then looks at the 'coordinate' the user
    wants to move to, it then checks the character stored in that,
    If it is '#', or out of bounds, inform the user and reject the input,
    If it is a ' ', allow the player to move there, end the game if it is an 'E'*/

    //This variable stores the character it wants to move to
    char futurePos;

    /*If the user wants to move up, make sure it is not into the wall nor the end of a line,
    nor the end of the file, nor are they at the top of the file (at map[0][n]
    where n is any integer value)*/

    if (userInput == 'W' || userInput == 'w'){
        if(player -> y != 0){
            futurePos = map.maze[player -> y - 1][player -> x];

            if(futurePos == '#'){
                printf("Cannot move into a wall\n");
            }
            else if (futurePos == ' ' || futurePos == 'S'){
                player -> y = player -> y - 1;
                return 0;
            }
            else if (futurePos == 'E'){
                printf("Congratulations, you completed the maze!\n");
                //Return the value 1 on completion of the maze
                return 1;
            }
        }
        else{
            printf("Trying to move out of bounds\n");
        }
    }

    /*If the user wants to move left, make sure it is not into a wall nor the start of a line,
    nor are they at the leftmost side of the file (at map[n][0] where n is any
    integer value)*/

    else if (userInput == 'A' || userInput == 'a'){
        if(player -> x != 0){
            futurePos = map.maze[player -> y][player -> x - 1];
        
            if(futurePos == '#'){
                printf("Cannot move into a wall\n");
            }
            //Move only in the case of a empty space OR the start symbol 'S'
            else if (futurePos == ' ' || futurePos == 'S'){
                player -> x = player -> x - 1;
                return 0;
            }
            else if (futurePos == 'E'){
                printf("Congratulations, you completed the maze!\n");
                //Return the value 1 on completion of the maze
                return 1;
            }
        }
        else{
            printf("Trying to move out of bounds\n");
        }
    }

    /*Repeat similar functions for each direction*/

    /*If the user wants to move down, make sure it is not into the wall,
    nor are they at the top of the file (at map[LAST_ROW][n] where n is any integer value)*/

    else if (userInput == 'S' || userInput == 's'){
        futurePos = map.maze[player -> y + 1][player -> x];
        if(player -> y != map.rows - 1){
            if(futurePos == '#'){
            printf("Cannot move into a wall\n");
            }
            else if (futurePos == ' ' || futurePos == 'S'){
                player -> y = player -> y + 1;
                return 0;
            }
            else if (futurePos == 'E'){
                printf("Congratulations, you completed the maze!\n");
                //Return the value 1 on completion of the maze
                return 1;
            }
        }
        else{
            printf("Trying to move out of bounds\n");
        }
    }

    /*If the user wants to move right, make sure it is not into the wall,
    nor are they at the rightmost of the file (at map[n][LAST_COLUMN] where n is any integer value)*/

    else if (userInput == 'D' || userInput == 'd'){
        if(player -> x != map.columns - 1){
            futurePos = map.maze[player -> y][player -> x + 1];
        
            if(futurePos == '#'){
                printf("Cannot move into a wall\n");
            }
            else if (futurePos == ' ' || futurePos == 'S'){
                player -> x = player -> x + 1;
                return 0;
            }
            else if (futurePos == 'E'){
                printf("Congratulations, you completed the maze!\n");
                //Return the value 1 on completion of the maze
                return 1;
            }
        }
        else{
            printf("Trying to move out of bounds\n\n");
        }
    }
    else if (userInput == 'M' || userInput == 'm'){
        printMaze(map, *player);
    }
    else{
        printf("Invalid input.\n");
    }
}

int main(int argc, char* argv[]){

    /*The main function in this code will ask the user to input the filename, and then validate that
    by calling upon the previous function*/

    /*The main function then processes user inputs and validates them by calling upon the previous function*/

    if (argc == 2){
        //Any invalid inputs for the argument will already be handled by the validation function
        dimensions fileDimensions;
        int status = validation(argv[1], &fileDimensions);
        coord playerChar;
        char input = 'M';

        if (status == 0){
            maze_map mazeMap = fileToArray(argv[1], fileDimensions);
            playerChar = mapBuilder(mazeMap, playerChar);

            while (checkMove(mazeMap, &playerChar, input) != 1){
                printf("\nWhat move would you like to make?: ");
                scanf(" %c", &input);
            }

            free(mazeMap.maze);
            return 0;
        }
        else if(status == 2){
            printf("File error\n");
            return 2;
        }
        else if(status == 3){
            printf("Invalid maze\n");
            return 3;
        }
        else{
            printf("Program execution unsuccessful\n");
            return 100;
        }
    }
    else{
        printf("Argument error\n");
        return 1;
    }
}