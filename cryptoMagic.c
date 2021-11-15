/*
    This program is an encryption/decryption utility called cryptoMagic
    Written By: William Rocheleau, Gabe Bigas
    Date: 14/11/21
*/
#include <stdio.h>
#include <string.h>

void encrypt(char base[], char filename[]);

int main(int argc, char *argv[]){
    int fileNameLen;

    //user did not input any parameters, or too many parameters were entered
    if (argc < 2 || argc > 3){
        printf("Error: please specify either encryption or decryption and a file name");
        return 0;
    }

    //no switch was specified, but a file name was specified
    else if (argc == 2 && strcmp(argv[1], "-encrypt") != 0 && strcmp(argv[1], "-decrypt") != 0){
        int hasExt = 0;
        
        //find length of base file name (no extension) and if the filename has an extension
        for (int x = 0; x < strlen(argv[1]); x++){
            if (argv[1][x] == '.'){
                fileNameLen = x;
                hasExt = 1;
            }
        }

        if (hasExt==0)
            fileNameLen = strlen(argv[1]);

        //creates array to store base file name
        char fileNameBase[fileNameLen+1];

        //fills base file name array
        for (int a = 0; a < fileNameLen; a++){
            fileNameBase[a] = argv[1][a];
        }

        //adds eos operator to base name
        fileNameBase[fileNameLen]='\0';

        //calls encryption function using argv[1] if it has an extension
        if (hasExt == 1){
            encrypt(fileNameBase, argv[1]);
        }
        
        //adds .txt extension if one was not given
        else{
            char filename[strlen(fileNameBase)+5];
            
            int i;
            for (i = 0; i < strlen(fileNameBase); i++)
                filename[i]=fileNameBase[i];
            
            strcat(filename, ".txt\0");

            encrypt(fileNameBase, filename);
        }

        return 0;
    }

    //if a switch was specified, but a file name was not
    else if (argc == 2 && (strcmp(argv[1], "-encrypt") == 0 || strcmp(argv[1], "-decrypt") == 0)){
        printf("Error: please specify either encryption or decryption and a file name");
    }

    if (strcmp(argv[1], "-encrypt") == 0){
        int hasExt = 0;
        
        //find length of base file name (no extension) and if the filename has an extension
        for (int x = 0; x < strlen(argv[2]); x++){
            if (argv[2][x] == '.'){
                fileNameLen = x;
                hasExt = 1;
            }
        }

        if (hasExt==0)
            fileNameLen = strlen(argv[2]);

        //creates array to store base file name
        char fileNameBase[fileNameLen+1];

        //fills base file name array
        for (int a = 0; a < fileNameLen; a++){
            fileNameBase[a] = argv[2][a];
        }

        //adds eos operator to base name
        fileNameBase[fileNameLen]='\0';

        //calls encryption function using argv[2] if it has an extension
        if (hasExt == 1){
            encrypt(fileNameBase, argv[2]);
        }
        
        //adds .txt extension if one was not given
        else{
            char filename[strlen(fileNameBase)+5];
            
            int i;
            for (i = 0; i < strlen(fileNameBase); i++)
                filename[i]=fileNameBase[i];
            
            strcat(filename, ".txt\0");

            encrypt(fileNameBase, filename);
        }

        return 0;
    }
}

void encrypt(char base[], char filename[]){
    int index=0;
    int charAscii;
    int outChar;

    FILE *input;
    FILE *output;
    input = fopen(filename, "r");

    char crpName[strlen(base)+5];
    strcpy(crpName, base);  
    strcat(crpName, ".crp\0");

    output = fopen(crpName, "w");
    output = fopen(crpName, "a");

    char line[120];

    //check to see if the file exists
    if (input == NULL)
        printf("Error: %s does not exist", filename);

    else{
        while (!feof(input)){
            fgets(line, 120, input);

            for (int i=0; i<120; i++){
                charAscii = (int)line[i];

                if (&charAscii == NULL){
                    i=120;
                }
                else if (charAscii == 0){
                    i=120;
                }
                else if (charAscii == 9){
                    fputs("TT", output);
                }
                else if (charAscii == 10){
                    fputs("\n", output);
                    i=120;
                }
                else{
                    outChar = charAscii-16;

                    if (outChar < 32)
                        outChar = (outChar - 32) + 144;
                    
                    fprintf(output, "%X", outChar);
                }
            }
        }
    }
    
    fclose(input);
    fclose(output);
}