#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2) {
        printf("Usage: ./recover image");
        return 1;
    }

    // Open input file
    FILE *memCard = fopen(argv[1], "r");
    if (memCard == NULL) {
        fprintf(stderr, "Could not open file");
        return 2;
    }
    //bool eof = false;

    // Remember filenames
    int img_num = 0;

    typedef uint8_t BYTE;
    BYTE buffer[512];

    // Create pointer for output file
    FILE *img;

    // Read memory card
    while (fread(buffer, sizeof(buffer), 1, memCard)) {
       
        //size_t elements = fread(buffer, sizeof(buffer), 1, memCard);
        
        // if (elements < 1) {
        //     eof = true;
        //     printf("Reached end of memory card.\n");
        // }

        // Look for JPEG signature
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            //printf("Found new JPEG\n");
            // if not first
            if (img_num) {
                fclose(img);
            }

            // Create new filename
            char filename[8];
            sprintf(filename, "%03i.jpg", img_num);
            // Write block to file
            printf("Writing to file: %s\n", filename);
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(buffer), 1, img);
            img_num++;
        }
        // New block, same file
        else {
            if (img != NULL) {
                fwrite(buffer, sizeof(buffer), 1, img);
            }
        }
    }

    // Close files
    fclose(img);
    fclose(memCard);
}
