#include <stdio.h>

int main()
{
    FILE *fInput;
    FILE *fOutput;
    char line[255];
    int x, ascii, skipLine = 0;
    int pair[2];

    //ask user for file name

    fInput = fopen("encrypted.crp", "r");
    fOutput = fopen("encrypted.txt", "w");
    
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
    return 0;
    fclose(fInput);
    fclose(fOutput);
}