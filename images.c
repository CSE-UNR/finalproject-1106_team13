//Erinstagram//
//Authors: Dannie Marquez-Montano, Soycott A Razzak//
//Date: 5/6/24//
//Purpose: Create a mock image editing software.//

#include <stdio.h>
#include <stdbool.h>

char 

int editMenu;
void saveFile;
bool loadFile:
void dim;
void brighten;
void crop;
int image;

int heigt, width;



int main(){ //Will be the main menu

















    char filename[100];		//load file option for menu
    printf("Enter the file you would like to use: ");
    scanf("%s", filename);

    if (loadFile(filename)) {
        printf("File loaded.\n");
    } else {
        printf("ERROR! Failed to load.\n");
    }

    return 0;
}



int editMenu(){ //Side menu


}

int display(){ //Displays "image"

}


void saveFile(){ //saves files 
	char choice;
  	char filename[100];

  	printf("Would you like to save? [y]/[n]: ");
   	scanf(" %c", &choice);

  	if (choice == 'y' || choice == 'Y') {
        	printf("Name file: ");
       		scanf("%s", filename);

        	FILE *file = fopen(filename, "w");
	if (file == NULL) {
        	printf("ERROR opening file!!!\n");
        	return;
        }

        fclose(file);
        printf("File saved as %s\n", filename);
    } else {
        printf("File no work.\n");
    }
}


bool loadFile(const char *filename, int **array, int width, int height) { //loads files
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR with file!!!\n");
        return false;
    }

    char content[1000]; 			// Adjustable
    while (fgets(content, sizeof(content), file) != NULL) {
        printf("%s", content); 			// Prints file
    }

    fclose(file);
    return true;
}



void dim(int **array, int rows, int cols){	//for dim and brighten, the Values table provided will not load, so I am using literal numbers instead

   for (int i = 0; i < rows; i++) { 
        for (int j = 0; j < cols; j++) {
            array[i][j]--;
        }
    }
}
    saveFile();
    return 0;
}

 									//adds 1 to all values
void brighten(int **array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j]++;
        }
    }
}
    saveFile();
    return 0;
}

void crop(){ //ask for X and Y dimensions from user to "crop" image 





    saveFile();
    return 0;
}

int image(int width, int height, int cols, int rows){ //allocates memory

int **array = (int **)malloc(height * sizeof(int *));
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    for (int i = 0; i < height; i++) {
        array[i] = (int *)malloc(width * sizeof(int));
        if (array[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
    }


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = 0;
        }
 
    return 0;
}




}






























































