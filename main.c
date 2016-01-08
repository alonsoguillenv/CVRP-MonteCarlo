#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

//latitud y longitud del punto 1, latitud y longitud del punto 2
double haversine( double th1, double ph1, double th2, double ph2 )
{
    const double R = 6371.0; //radio de al tierra
    const double fact ( 3.14159265358979323846 / 180.0 ); //factor de conversion a radianes

    double dx, dy, dz;
	ph1 -= ph2;
	ph1 *= fact;
    th1 *= fact;
    th2 *= fact;

	dz = sin(th1) - sin(th2);
	dx = cos(ph1) * cos(th1) - cos(th2);
	dy = sin(ph1) * cos(th1);

	return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R; //formula de distancia de Haversine
}




void create_saving_list(int m, FILE * input_file )
{
    int index = 0;
    double *latitude = (double *)calloc(m, sizeof(double) );
    double *longitude = (double *)calloc(m, sizeof(double) );
    double *weight = (double *)calloc(m, sizeof(double) );
    int *id = (int *)calloc(m, sizeof(int) );
    fscanf( input_file, "%d,%lf,%lf,%lf", &id[index], &latitude[index], &longitude[index], &weight[index] );
    //lee la cantidad de caracteres en el archivo!
    char letter;
    int count;
    while( ( letter = fgetc( input_file ) ) )
    {
        if( letter == EOF ) break;
        else count += 1;
    }
    rewind( input_file );
    char * line = malloc(0.5*count*sizeof(char));
    if( line == NULL ) printf("No hay memoria :( \n");
    fgets(line, count + 1, input_file);
    printf("%d", count);
    char * token;
    printf("%s", line);
    for( index = 1; index < m; index += 1 )
    {
        token = strtok( line, ", " );
        id[index] = (int)*token;
        token = strtok( line, ", " );
        latitude[index] = (double)*token;
        token = strtok( line, ", " );
        longitude[index] = (double)*token;
        token = strtok( line, ", " );
        weight[index] = (double)token;
    }

    //inicializando la matriz de costos
    double ** c = (double **)malloc(m*sizeof( double *));
    for( index = 0; index < m; index += 1 )
    {
        c[index] = (double *)malloc(m*sizeof(double) );
    }

    int i = 0, j = 0;
    for( i = 0; i < m; i += 1 )
    {
        for( j = 0; j < m; j += 1 )
        {
            if( i == j )
            {
                c[i][j] = 0.0;
            }
            else
            {
                c[i][j] = haversine(90.0, 0.0, latitude[i], longitude[i]) + haversine( 90.0, 0.0, latitude[j], longitude[j] );
                c[i][j] -= haversine( latitude[i], longitude[i], latitude[j], longitude[j]);
            }

        }
    }


    return;
}


void sort_list()
{



}



int main()
{
    const int m = 100000;
    FILE * gift_file = fopen("gifts.csv", "r");
    create_saving_list(m , gift_file);



    return 0;
}
