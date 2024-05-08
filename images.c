//Erinstagram//
//Authors: Dannie Marquez-Montano, Soycott A Razzak//
//Date: 5/6/24//
//Purpose: Create a mock image editing software.//

#include <stdio.h>
#include <stdbool.h>

#define MAX_WIDTH 100 //for array 
#define MAX_HEIGHT 100

bool loadFile(const char *filename, int array[MAX_HEIGHT][MAX_WIDTH], int *width, int *height);
void dim(int array[MAX_HEIGHT][MAX_WIDTH], int rows, int cols);
void brighten(int array[MAX_HEIGHT][MAX_WIDTH], int rows, int cols);
void crop(int array[MAX_HEIGHT][MAX_WIDTH], int startX, int startY, int endX, int endY);
void saveFile(int array[MAX_HEIGHT][MAX_WIDTH], int width, int height);
void display(int array[MAX_HEIGHT][MAX_WIDTH], int rows, int cols);
int readInteger(const char* prompt); // all the functions and the insane amount of paramaters

int main() {
    int image[MAX_HEIGHT][MAX_WIDTH] = {0}; //array
    int width = 0, height = 0;

    while (true) {//main menu
        printf("\nMain Menu\n");
        printf("1. Load Image\n");
        printf("2. Edit Menu\n");
        printf("3. Display Image\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        int choice = readInteger("");

        switch (choice) {
            case 1: {//loading
                char filename[100];
                printf("Enter the file you would like to use: ");
                scanf("%99s", filename); 

                if (loadFile(filename, image, &width, &height)) {
                    printf("File loaded.\n");
                } else {
                    printf("Failed to load file.\n");
                }
                break;
            }
            case 2: {//edit menu
                int editChoice = readInteger("\nEdit Menu\n1. Crop Image\n2. Dim\n3. Brighten\nEnter your choice: ");

                switch (editChoice) {
                    case 1://crop
                        printf("Enter crop coords (startX startY endX endY): ");
                        int startX, startY, endX, endY;
                        scanf("%d %d %d %d", &startX, &startY, &endX, &endY);
                        crop(image, startX, startY, endX, endY);
                        break;
                    case 2:
                        dim(image, height, width);
                        break;
                    case 3:
                        brighten(image, height, width);
                        break;
                    default:
                        printf("INVALID choice! Enter a number between 1 and 3.\n");
                }
                break;
            }
            case 3:
                display(image, height, width);
                break;
            case 0:
                return 0;
            default:
                printf("INVALID choice! Enter a number between 0 and 3.\n");
        }
    }
}

int readInteger(const char* prompt) {//deals with errors, couldnt fix it in main for some reason
    int input;
    printf("%s", prompt);
    while (scanf("%d", &input) != 1) {
        while (getchar() != '\n'); 
        printf("Invalid input, please enter a number: ");
    }
    return input;
}



bool loadFile(const char *filename, int array[MAX_HEIGHT][MAX_WIDTH], int *width, int *height) {
    FILE *file = fopen(filename, "r"); //loads the file up
    if (!file) {
        printf("ERROR opening file!\n");
        return false;
    }

    if (fscanf(file, "%d %d", width, height) != 2) {
        fclose(file);
        return false;
    }

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            if (fscanf(file, "%d", &array[i][j]) != 1) {
                fclose(file);
                return false;
            }
        }
    }

    fclose(file);
    return true;
}


void dim(int array[MAX_HEIGHT][MAX_WIDTH], int rows, int cols) { //for dim and brighten, the pixel value table would not open, so I used literal values, like 2,1, and 0. Dim takes 1 from all values.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j]--;
        }
    }
    saveFile(array, cols, rows);
}

void brighten(int array[MAX_HEIGHT][MAX_WIDTH], int rows, int cols) { //Adds 1 to all values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j]++;
        }
    }
    saveFile(array, cols, rows);
}

void crop(int array[MAX_HEIGHT][MAX_WIDTH], int startX, int startY, int endX, int endY) { //Uses X and Y coords to know where to crop the photo. Has a start X, endX startY, and endY. Hate this.
    if (startX >= 0 && startY >= 0 && endX < MAX_WIDTH && endY < MAX_HEIGHT && startX <= endX && startY <= endY) {
        int newWidth = endX - startX + 1;
        int newHeight = endY - startY + 1;

        int croppedImage[newHeight][newWidth];

        for (int i = startY; i <= endY; i++) {
            for (int j = startX; j <= endX; j++) {
                croppedImage[i - startY][j - startX] = array[i][j];
            }
        }
        for (int i = 0; i < newHeight; i++) {
            for (int j = 0; j < newWidth; j++) {
                array[i][j] = croppedImage[i][j];
            }
        }
        saveFile(array, newWidth, newHeight);
        
        printf("Image cropped :)\n");
    } else {
        printf("Invalid coords for cropping!\n");
    }
    
}

void saveFile(int array[MAX_HEIGHT][MAX_WIDTH], int width, int height) { //saves file, and ask for name to save in folder. If you want to see edited image, u have to load it from main menu.
    char choice;
    char filename[100];

    printf("Would you like to save the new image? [y]/[n]: ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        printf("Enter file name: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("ERROR opening file!!!\n");
            return;
        }

        fprintf(file, "%d %d\n", width, height);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                fprintf(file, "%d ", array[i][j]);
            }
            fprintf(file, "\n");
        }

        fclose(file);
        printf("File SAVED as %s\n", filename);
    } else {
        printf("File no work.\n");
    }
}

void display(int array[MAX_HEIGHT][MAX_WIDTH], int rows, int cols) { //displays the image with the array loop thing
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
      
    }
}
