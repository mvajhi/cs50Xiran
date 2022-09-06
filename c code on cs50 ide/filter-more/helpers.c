#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //get average
            //printf("r: %i   g: %i   b: %i\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            int av = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            //set average
            image[i][j].rgbtRed = av;
            image[i][j].rgbtGreen = av;
            image[i][j].rgbtBlue = av;
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
            //save original color
            int OR = image[i][j].rgbtRed;
            int OG = image[i][j].rgbtGreen;
            int OB = image[i][j].rgbtBlue;

            //convert
            int red = round(0.393 * OR + 0.769 * OG + 0.189 * OB);
            int green = round(0.349 * OR + 0.686 * OG + 0.168 * OB);
            int blue = round(0.272 * OR + 0.534 * OG + 0.131 * OB);
            //if above 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            //save new color
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            if (round(width / 2) == j && width % 2 == 1)
            {
                return;
            }
            //for swap
            RGBTRIPLE tmp;
            tmp.rgbtRed = image[i][j].rgbtRed;
            tmp.rgbtGreen = image[i][j].rgbtGreen;
            tmp.rgbtBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tmp.rgbtRed;
            image[i][width - j - 1].rgbtGreen = tmp.rgbtGreen;
            image[i][width - j - 1].rgbtBlue = tmp.rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE cimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;

            float counter = 0;
            int a = -1;
            int b = 1;
            int c = -1;
            int d = 1;

            //edge finder
            if (i == 0)
            {
                a = 0;
            }
            else if (i == height - 1)
            {
                b = 0;
            }


            if (j == 0)
            {
                c = 0;
            }
            else if (j == width - 1)
            {
                d = 0;
            }


            //sum pixcel
            for (int h = a; h <= b; h++)
            {
                for (int w = c; w <= d; w++)
                {
                    red += image[i + h][j + w].rgbtRed;
                    green += image[i + h][j + w].rgbtGreen;
                    blue += image[i + h][j + w].rgbtBlue;
                    counter++;
                }
            }
            //save new color
            cimage[i][j].rgbtRed = round(red / counter);
            cimage[i][j].rgbtGreen = round(green / counter);
            cimage[i][j].rgbtBlue = round(blue / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = cimage[i][j].rgbtRed;
            image[i][j].rgbtGreen = cimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = cimage[i][j].rgbtBlue;
        }
    }
    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //copy image
    RGBTRIPLE cimage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cimage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //          R  G  Bsubmit50 cs50/problems/2022/x/filter/mor
            int gx[] = {0, 0, 0};
            int gy[] = {0, 0, 0};


            /*ij
             -1-1  -10  -11
              0-1   00   01
              1-1   10   11
            */

            //-1 0
            if ((i - 1) >= 0)
            {
                gx[0] += (cimage[i - 1][j].rgbtRed *  0);
                gy[0] += (cimage[i - 1][j].rgbtRed * -2);
                gx[1] += (cimage[i - 1][j].rgbtGreen *  0);
                gy[1] += (cimage[i - 1][j].rgbtGreen * -2);
                gx[2] += (cimage[i - 1][j].rgbtBlue *  0);
                gy[2] += (cimage[i - 1][j].rgbtBlue * -2);

            }
            //1 0
            if ((i + 1) < height)
            {
                gx[0] += (cimage[i + 1][j].rgbtRed *  0);
                gy[0] += (cimage[i + 1][j].rgbtRed *  2);
                gx[1] += (cimage[i + 1][j].rgbtGreen *  0);
                gy[1] += (cimage[i + 1][j].rgbtGreen *  2);
                gx[2] += (cimage[i + 1][j].rgbtBlue *  0);
                gy[2] += (cimage[i + 1][j].rgbtBlue *  2);
            }

            //0 -1
            if ((j - 1) >= 0)
            {
                gx[0] += (cimage[i][j - 1].rgbtRed * -2);
                gy[0] += (cimage[i][j - 1].rgbtRed *  0);
                gx[1] += (cimage[i][j - 1].rgbtGreen * -2);
                gy[1] += (cimage[i][j - 1].rgbtGreen *  0);
                gx[2] += (cimage[i][j - 1].rgbtBlue * -2);
                gy[2] += (cimage[i][j - 1].rgbtBlue *  0);
            }
            //0 1
            if ((j + 1) < width)
            {
                gx[0] += (cimage[i][j + 1].rgbtRed *  2);
                gy[0] += (cimage[i][j + 1].rgbtRed *  0);
                gx[1] += (cimage[i][j + 1].rgbtGreen *  2);
                gy[1] += (cimage[i][j + 1].rgbtGreen *  0);
                gx[2] += (cimage[i][j + 1].rgbtBlue *  2);
                gy[2] += (cimage[i][j + 1].rgbtBlue *  0);
            }
            //-1 -1
            if ((i - 1) >= 0 && (j - 1) >= 0)
            {
                gx[0] += (cimage[i - 1][j - 1].rgbtRed * -1);
                gy[0] += (cimage[i - 1][j - 1].rgbtRed * -1);
                gx[1] += (cimage[i - 1][j - 1].rgbtGreen * -1);
                gy[1] += (cimage[i - 1][j - 1].rgbtGreen * -1);
                gx[2] += (cimage[i - 1][j - 1].rgbtBlue * -1);
                gy[2] += (cimage[i - 1][j - 1].rgbtBlue * -1);
            }
            //-1 1
            if ((i - 1) >= 0 && (j + 1) < width)
            {
                gx[0] += (cimage[i - 1][j + 1].rgbtRed *  1);
                gy[0] += (cimage[i - 1][j + 1].rgbtRed * -1);
                gx[1] += (cimage[i - 1][j + 1].rgbtGreen *  1);
                gy[1] += (cimage[i - 1][j + 1].rgbtGreen * -1);
                gx[2] += (cimage[i - 1][j + 1].rgbtBlue *  1);
                gy[2] += (cimage[i - 1][j + 1].rgbtBlue * -1);
            }
            //1 -1
            if ((i + 1) < height && (j - 1) >= 0)
            {
                gx[0] += (cimage[i + 1][j - 1].rgbtRed * -1);
                gy[0] += (cimage[i + 1][j - 1].rgbtRed *  1);
                gx[1] += (cimage[i + 1][j - 1].rgbtGreen * -1);
                gy[1] += (cimage[i + 1][j - 1].rgbtGreen *  1);
                gx[2] += (cimage[i + 1][j - 1].rgbtBlue * -1);
                gy[2] += (cimage[i + 1][j - 1].rgbtBlue *  1);
            }
            //1 1
            if ((i + 1) < height && (j + 1) < width)
            {
                gx[0] += (cimage[i + 1][j + 1].rgbtRed *  1);
                gy[0] += (cimage[i + 1][j + 1].rgbtRed *  1);
                gx[1] += (cimage[i + 1][j + 1].rgbtGreen *  1);
                gy[1] += (cimage[i + 1][j + 1].rgbtGreen *  1);
                gx[2] += (cimage[i + 1][j + 1].rgbtBlue *  1);
                gy[2] += (cimage[i + 1][j + 1].rgbtBlue *  1);
            }

            //int for save new color
            int newcolor[3];

            //calculat color
            newcolor[0] = round(sqrt(pow(gx[0], 2) + pow(gy[0], 2)));
            newcolor[1] = round(sqrt(pow(gx[1], 2) + pow(gy[1], 2)));
            newcolor[2] = round(sqrt(pow(gx[2], 2) + pow(gy[2], 2)));

            //check under 255
            if (newcolor[0] > 255)
            {
                newcolor[0] = 255;
            }
            if (newcolor[1] > 255)
            {
                newcolor[1] = 255;
            }
            if (newcolor[2] > 255)
            {
                newcolor[2] = 255;
            }

            //save new color
            image[i][j].rgbtRed = newcolor[0];
            image[i][j].rgbtGreen = newcolor[1];
            image[i][j].rgbtBlue = newcolor[2];

        }
    }
    return;
}

