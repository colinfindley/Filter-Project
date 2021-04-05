#include "helpers.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float mean;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Reset mean to 0 and turn back to float
            mean = (float) 0;
            //Average the values
            mean = (((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3);
            //Round the mean and set each value equal to mean
            image[i][j].rgbtRed = (int) round(mean);
            image[i][j].rgbtGreen = (int) round(mean);
            image[i][j].rgbtBlue = (int) round(mean);
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
            //Redeclare variables
            int r = image[i][j].rgbtRed;
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            //Sepia formula and setting it to 255 if it runs over
            if ((int) round(.393 * r + .769 * g + .189 * b) < 255)
            {
                image[i][j].rgbtRed = (int) round(.393 * r + .769 * g + .189 * b);
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }
            if ((int) round(.349 * r + .686 * g + .168 * b) < 255)
            {
                image[i][j].rgbtGreen = (int) round(.349 * r + .686 * g + .168 * b);
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if ((int) round(.272 * r + .534 * g + .131 * b) < 255)
            {
                image[i][j].rgbtBlue = (int) round(.272 * r + .534 * g + .131 * b);
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
//loop through array of pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < round(width / 2); j++)
        {
            //Initialize temp variable and swap one row at a time
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_blue;
            int sum_green;
            int sum_red;
            float counter;
            sum_blue = sum_green = sum_red = counter = 0;
            //iterate through the column, from -1 to +1
            for (int h = -1; h < 2; h++)
            {
                //iterate similarly through rows
                for (int w = -1; w < 2; w++)
                {
                    //if pixel is outside the image (column)
                    if (i + h < 0 || i + h > (height - 1))
                    {
                        continue; //skip
                    }
                    //if pixel is outside the image (row)
                    if (j + w  < 0 || j + w > (width - 1))
                    {
                        continue; //skip
                    }
                    //sum up the values of all the pixels
                    sum_blue += temp[i + h][j + w].rgbtBlue;
                    sum_red += temp[i + h][j + w].rgbtRed;
                    sum_green += temp[i + h][j + w].rgbtGreen;
                    counter++;
                }
            }
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);

        }
    }
    return;
}
