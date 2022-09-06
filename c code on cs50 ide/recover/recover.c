#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int  BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./volume input.raw\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    bool first = true;
    int numberfile = 0;
    char namefile[8];
    FILE *output;

    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (first)
            {
                first = false;
            }
            //if new jpg close old jpg
            else
            {
                fclose(output);
                numberfile++;
            }
            //make revover file
            sprintf(namefile, "%03i.jpg", numberfile);
            output = fopen(namefile, "w");
            //first write on jpg
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
        //if not first file continue write
        else if (!first)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
    }

    fclose(input);
    fclose(output);

}