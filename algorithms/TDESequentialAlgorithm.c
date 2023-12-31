#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


int main()
{
    //opening file to write
    //This file is going to be used in the python script to plot the graph
    FILE *textFile = fopen("meanTimesSequential.txt", "w");
    if (textFile== NULL) {
        printf("Error opening file!");
        return 1;
    }

    char filenames[5][100] = {
        "../images/image200.pbm",
        "../images/image300.pbm",
        "../images/image400.pbm",
        "../images/image500.pbm",
        "../images/image600.pbm"
    };


for(int n=0; n<5; n++){

        char filename[100];
        strcpy(filename, filenames[n]);
        //char filename[] = "./images/image200.pbm"; // Replace with your PBM file path

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



        // Read pixel data
        int i, j;
        int image[height][width];

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


    double sumOfTimes = 0;
    for (int i = 0; i < 100; i++)
    {


// -------------------------------Start Saito and Toriwaki algorithm and set timer-------------------------------------- 

        double ti, tf, time;
        ti = tf = time = 0;
        struct timeval time_init, time_final;
        gettimeofday(&time_init, NULL);

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

        gettimeofday(&time_final, NULL);
        tf = (double)time_final.tv_usec + ((double)time_final.tv_sec * (1000000.0));
        ti = (double)time_init.tv_usec + ((double)time_init.tv_sec * (1000000.0));
        time = (tf - ti) / 1000;
        //times[i].time = tempo;
        //printf("%.3f ms\n", times[i].time);
        //fprintf(textFile, "%.3f\n", times[i].time);
        sumOfTimes += time;
    }

// ---------------------------------------Print Mean Time------------------------------------------

    double meanTime = sumOfTimes / 100;
    fprintf(textFile, "%.3f\n", meanTime);
    printf("\n\nMean time of execution: %.3f ms\n", meanTime);
}
    fclose(textFile);
    return 0;
}
