#include <stdio.h>
#include <stdlib.h>
#include "draw.h"
#include "draw.c"

int parameter,
matrix[X_PIXEL][Y_PIXEL][ARRAY_DEPTH] = {0};

int main(int argc, char** argv){

    printf("Bitte N eingeben:\n");
    scanf("%d", &parameter);

    drawFigure(parameter, matrix);

    createPpm(matrix);

    return EXIT_SUCCESS;
}
