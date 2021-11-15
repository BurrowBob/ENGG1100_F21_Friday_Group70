#include <stdio.h>

int main()
{
    const int lineLength = 255;
    FILE *fInput;
    FILE *fOutput;
    char line[lineLength];
    int x, hexa, skipLine = 0, done = 0;
    int pair[2];

    //ask user for file name

    fInput = fopen("encrypted.crp", "r");
    fOutput = fopen("encrypted.txt", "w");

    fgets(line, lineLength, (FILE *)fInput);
    printf("Line 1: %s", line);
    while (done == 0)
    {
        
        x = 0;
        skipLine = 0;
        while (x < lineLength && skipLine == 0)
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
                        skipLine = 1;
                        x = lineLength;
                        break;
                    }
                    hexa = pair[0] * 16 + pair[1] + 16;
                    if (hexa > 127)
                        hexa = (hexa - 144) + 32;
                }
                if (skipLine == 1)
                {
                    fprintf(fOutput, "\n", line);
                    x = lineLength;
                }

                else
                {
                    fprintf(fOutput, "%c", hexa);
                }
            }
            x += 2;
        }
        fgets(line, lineLength, (FILE *)fInput);
        if(line[0] == '0' || line[0] == '1' || line[0] == '2' || line[0] == '3' || line[0] == '4' || line[0] == '5' || line[0] == '6' || line[0] == '7' || line[0] == '8' || line[9] == 'A' || line[0] == 'B' || line[0] == 'C' || line[0] == 'D' || line[0] == 'E' || line[0] == 'F' || line[0] == 'T' )
        done = 0;
        else
        done = 1;
    }
    return 0;
}