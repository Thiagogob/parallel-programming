#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define MAX_WIDTH 1000
#define MAX_HEIGHT 1000

int main()
{
    double sumOfTimes = 0;
    for (int i = 0; i < 10000; i++)
    {

        char filename[] = "./images/test3.pbm"; // Replace with your PBM file path

        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("Failed to open the file.\n");
            return 1;
        }

        // Read PBM file header
        char magicNumber[3];
        int width, height;

        if (fscanf(file, "%2s", magicNumber) != 1)
        {
            printf("Failed to read magic number.\n");
            fclose(file);
            return 1;
        }

        if (strcmp(magicNumber, "P1") != 0)
        {
            printf("Invalid PBM file format.\n");
            fclose(file);
            return 1;
        }

        if (fscanf(file, "%d %d", &width, &height) != 2)
        {
            printf("Failed to read image dimensions.\n");
            fclose(file);
            return 1;
        }


        if (width > MAX_WIDTH || height > MAX_HEIGHT)
        {
            printf("Image dimensions exceed the maximum array size.\n");
            fclose(file);
            return 1;
        }

        // Read pixel data
        int i, j;
        int image[MAX_HEIGHT][MAX_WIDTH];

        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                if (fscanf(file, "%d", &image[i][j]) != 1)
                {
                    printf("Failed to read pixel data.\n");
                    fclose(file);
                    return 1;
                }
            }
        }

        fclose(file);

        // Print the 2D array
        // printf("Image dimensions: %d x %d\n", width, height);

// -------------------------------Start Saito and Toriwaki algorithm and set timer-------------------------------------- 

        double ti, tf, tempo;
        ti = tf = tempo = 0;
        struct timeval tempo_inicio, tempo_fim;
        gettimeofday(&tempo_inicio, NULL);

        int T1[height][width];
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                T1[i][j] = 0;
            }
        }

// --------------------------------------------Perform first transformation---------------------------------------------------------------
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (image[i][j] == 0)
                {
                    for (int k = 0; k < width; k++)
                    {
                        if (image[i][k] == 1)
                        {
                            int distanceSquared = (i - i) * (i - i) + (j - k) * (j - k);

                            if (distanceSquared < T1[i][j] || T1[i][j] == 0)
                            {
                                T1[i][j] = distanceSquared;
                            }
                        }
                    }
                }
            }
        }

// ---------------------------------------Perform Second transformation-------------------------------------------


        int TDE[height][width];

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                TDE[i][j] = 0;
            }
        }


        for (int j = 0; j < width; j++)
        {

            for (int i = 0; i < height; i++)
            {
                int sum = 0;
                for (int k = 0; k < height; k++)
                {

                    int p = T1[k][j];

                    if (T1[k][j] == 0 && image[k][j] != 1)
                    {
                        p = width * width;
                    }

                    int distanceSquared = ((i - k) * (i - k)) + p;

                    if (distanceSquared < sum || sum == 0)
                    {
                        sum = distanceSquared;
                    }
                }
                if (image[i][j] == 1)
                    TDE[i][j] = 0;
                else if (image[i][j] == 0)
                {
                    TDE[i][j] = sum;
                }
            }
        }

// ----------------------------------------Print Data------------------------------------------
        /*
        printf("Image data:\n");

        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                printf("%d ", image[i][j]);
            }
            printf("\n");
        }


        printf("\n\n");
        printf("First Transform data\n");

        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
            {
                printf("%d ", T1[i][j]);
            }
            printf("\n");
        }



        printf("\n\n");
        printf("TDE Final data\n");

        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++){
                printf("%d ", TDE[i][j]);
            }
            printf("\n");
        }
        */

// ---------------------------------------End Timer------------------------------------------

        gettimeofday(&tempo_fim, NULL);
        tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
        ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
        tempo = (tf - ti) / 1000;
        sumOfTimes += tempo;
    }

// ---------------------------------------Print Mean Time------------------------------------------

    printf("\n\nMean time of execution: %.3f ms\n", sumOfTimes / 10000);
    return 0;
}
