#include "helpers.h"
#include "math.h"
#include "string.h"
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find the average of GBR values for each pixel
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Replace each color with avg
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Grab GBR values
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            // Caluclate colors using sepia formula
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);

            // Apply sepia filter, capping values at 255
            image[i][j].rgbtBlue = (sepiaBlue <= 255) ? sepiaBlue : 255;
            image[i][j].rgbtGreen = (sepiaGreen <= 255) ? sepiaGreen : 255;
            image[i][j].rgbtRed = (sepiaRed <= 255) ? sepiaRed : 255;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Storage for swap
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap current pixel with pixel on opposite side
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of image
    RGBTRIPLE ogImage[height][width];
    memcpy(ogImage, image, sizeof(RGBTRIPLE) * height * width);

    // Iterate through every row and column of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;

            // Add BGR values from current pixels
            int blue = ogImage[i][j].rgbtBlue;
            int green = ogImage[i][j].rgbtGreen;
            int red = ogImage[i][j].rgbtRed;
            count++;

            // Check bounds
            bool upper = (i - 1 >= 0) ? true : false;
            bool lower = (i + 1 < height) ? true : false;
            bool left = (j - 1 >= 0) ? true : false;
            bool right = (j + 1 < width) ? true : false;

            if (left)
            {
                // Add Left
                blue += ogImage[i][j - 1].rgbtBlue;
                green += ogImage[i][j - 1].rgbtGreen;
                red += ogImage[i][j - 1].rgbtRed;
                count++;
            }

            if (right)
            {
                // Add right
                blue += ogImage[i][j + 1].rgbtBlue;
                green += ogImage[i][j + 1].rgbtGreen;
                red += ogImage[i][j + 1].rgbtRed;
                count++;
            }

            if (upper)
            {
                // Add upper
                blue += ogImage[i - 1][j].rgbtBlue;
                green += ogImage[i - 1][j].rgbtGreen;
                red += ogImage[i - 1][j].rgbtRed;
                count++;

                if (left)
                {
                    // Add upLe
                    blue += ogImage[i - 1][j - 1].rgbtBlue;
                    green += ogImage[i - 1][j - 1].rgbtGreen;
                    red += ogImage[i - 1][j - 1].rgbtRed;
                    count++;
                }

                if (right)
                {
                    // Add upRi
                    blue += ogImage[i - 1][j + 1].rgbtBlue;
                    green += ogImage[i - 1][j + 1].rgbtGreen;
                    red += ogImage[i - 1][j + 1].rgbtRed;
                    count++;
                }
            }

            if (lower)
            {
                // Add below
                blue += ogImage[i + 1][j].rgbtBlue;
                green += ogImage[i + 1][j].rgbtGreen;
                red += ogImage[i + 1][j].rgbtRed;
                count++;

                if (left)
                {
                    // Add loLe
                    blue += ogImage[i + 1][j - 1].rgbtBlue;
                    green += ogImage[i + 1][j - 1].rgbtGreen;
                    red += ogImage[i + 1][j - 1].rgbtRed;
                    count++;
                }

                // Check right columns
                if (right)
                {
                    // Add loRi
                    blue += ogImage[i + 1][j + 1].rgbtBlue;
                    green += ogImage[i + 1][j + 1].rgbtGreen;
                    red += ogImage[i + 1][j + 1].rgbtRed;
                    count++;
                }
            }
            // Update current pixel with average of surrounding pixels
            image[i][j].rgbtBlue = round(blue / (count * 1.0));
            image[i][j].rgbtGreen = round(green / (count * 1.0));
            image[i][j].rgbtRed = round(red / (count * 1.0));
        }
    }
    return;
}
