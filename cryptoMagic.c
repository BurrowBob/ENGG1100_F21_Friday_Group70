/*
    This program is an encryption/decryption utility called cryptoMagic see a more in depth description in README.txt
    Written By: William Rocheleau, Gabe Bigas
    Date: 14/11/21
*/
#include <stdio.h>
#include <string.h>

void encrypt(char base[], char filename[]);

void decrypt(char base[], char filename[]);

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
            strcpy(filename, fileNameBase);
            strcat(filename, ".txt\0");

            encrypt(fileNameBase, filename);
        }

        return 0;
    }

    //if a switch was specified, but a file name was not
    else if (argc == 2 && (strcmp(argv[1], "-encrypt") == 0 || strcmp(argv[1], "-decrypt") == 0)){
        printf("Error: please specify either encryption or decryption and a file name");
    }

    //if -encrypt was specified along with a file name
    else if (strcmp(argv[1], "-encrypt") == 0){
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
            strcpy(filename, fileNameBase);
            strcat(filename, ".txt\0");

            encrypt(fileNameBase, filename);
        }

        return 0;
    }

    //if -decrypt was specified along with a filename
    else if (strcmp(argv[1], "-decrypt") == 0){
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

        //calls decryption function using argv[2] if it has an extension
        if (hasExt == 1){
            decrypt(fileNameBase, argv[2]);
        }
        
        //adds .crp extension if one was not given
        else{
            char filename[strlen(fileNameBase)+5];
            strcpy(filename, fileNameBase);
            strcat(filename, ".crp\0");

            decrypt(fileNameBase, filename);
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

void decrypt(char base[], char filename[]){
    FILE *fInput;
    FILE *fOutput;
    char line[255];
    int x, ascii, skipLine = 0;
    int pair[2];

    //ask user for file name

    fInput = fopen(filename, "r");

    char fullName[strlen(base)+5];
    strcpy(fullName, base);  
    strcat(fullName, ".txt\0");

    fOutput = fopen(fullName, "w");
    fOutput = fopen(fullName, "a");
    
    while (!feof(fInput))
    {
        fgets(line, 255, (FILE *)fInput);
        x = 0;
        while (x < 255 && skipLine == 0)
        {
            if (line[x] == 'T' && line[x + 1] == 'T')
            {
                fprintf(fOutput, "\t", line);
            }
            else
            {
                for (int i = 0; i < 2; i++)
                {
                    switch (line[x + i])
                    {
                    case '0':
                        pair[i] = 0;
                        break;

                    case '1':
                        pair[i] = 1;
                        break;

                    case '2':
                        pair[i] = 2;
                        break;

                    case '3':
                        pair[i] = 3;
                        break;

                    case '4':
                        pair[i] = 4;
                        break;

                    case '5':
                        pair[i] = 5;
                        break;

                    case '6':
                        pair[i] = 6;
                        break;

                    case '7':
                        pair[i] = 7;
                        break;

                    case '8':
                        pair[i] = 8;
                        break;

                    case '9':
                        pair[i] = 9;
                        break;

                    case 'A':
                        pair[i] = 10;
                        break;

                    case 'B':
                        pair[i] = 11;
                        break;

                    case 'C':
                        pair[i] = 12;
                        break;

                    case 'D':
                        pair[i] = 13;
                        break;

                    case 'E':
                        pair[i] = 14;
                        break;

                    case 'F':
                        pair[i] = 15;
                        break;

                    default:
                        fprintf(fOutput, "\n", line);
                        x = 255;
                        break;
                    }
                    ascii = pair[0] * 16 + pair[1] + 16;
                    if (ascii > 127)
                        ascii = (ascii - 144) + 32;
                }
                    if(x!=255)
                    fprintf(fOutput, "%c", ascii);

            }
            x += 2;
        }
    }
    
    fclose(fInput);
    fclose(fOutput);
}