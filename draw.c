#include <stdio.h>
#include <stdlib.h>
#include "draw.h"

void createPpm(int matrix[X_PIXEL][Y_PIXEL][ARRAY_DEPTH]) {
    FILE *file = fopen(FILE_NAME, "w");
    if (NULL != file) {
        fprintf (file, "P3\n%d %d\n255\n", X_PIXEL, Y_PIXEL);
        for (int i = 0; i < X_PIXEL; i++) {
            for (int j = 0; j < Y_PIXEL; j++) {
                for(int k=1; k<ARRAY_DEPTH; k++){
                    fprintf (file, "%-4d", matrix[i][j][k]);
                }
            }
            fprintf (file, "\n");
        }
        fclose (file);
    }
}

void setPixel(int matrix[X_PIXEL][Y_PIXEL][ARRAY_DEPTH], int x, int y){
    int correctY = X_PIXEL-y-1;
    matrix[correctY][x][0] = 1;
    matrix[correctY][x][1] = COLOR_R;
    matrix[correctY][x][2] = COLOR_G;
    matrix[correctY][x][3] = COLOR_B;
}

void setPixelWithDirection(int horizontalMirror, int deg45Mirror, int x, int y, int matrix[X_PIXEL][Y_PIXEL][ARRAY_DEPTH]) {
    if(horizontalMirror && !deg45Mirror){
        setPixel(matrix, x, -y);
    }
    else if(!horizontalMirror && deg45Mirror){
        setPixel(matrix, y, x);
    }
    else if(horizontalMirror && deg45Mirror){
        setPixel(matrix, y, -x);
    }
    else{
        setPixel(matrix, x, y);
    }
}

void drawLine(int startX, int startY, int endX, int endY, int matrix[X_PIXEL][Y_PIXEL][ARRAY_DEPTH]){
    int horizontalFlag = 0,
    deg45Flag = 0;

    if(endX < startX){
        int startXSave = startX,
        startYSave = startY;
        startX = endX;
        startY = endY;
        endX = startXSave;
        endY = startYSave; 
    }

    if(endY < startY ){
        endY = -endY;
        startY = -startY;
        horizontalFlag = 1;
    }

    if((endX-startX) < (endY-startY)){
        int startXSave = startX;
        startX = startY;
        startY = startXSave;

        int endXSave = endX;
        endX = endY;
        endY = endXSave;
        deg45Flag = 1;
    }

    int errorX = (2*(endY-startY)),
    errorY = (-2*(endX-startX)),
    error = errorX-(endX-startX);

    int x = startX,
    y = startY;

    setPixelWithDirection(horizontalFlag, deg45Flag, x, y, matrix);
    
    for(int i=x; i<endX;i++){
        x += 1;
        if(error>0){
            y +=1;
            error += errorY;
        }
        error += errorX;
        setPixelWithDirection(horizontalFlag, deg45Flag, x, y, matrix);
    }
}

void drawSquare(int bottomLeftX, int bottomLeftY, int width, int matrix[X_PIXEL][Y_PIXEL][ARRAY_DEPTH]){
    drawLine(bottomLeftX, bottomLeftY, bottomLeftX+width-1, bottomLeftY, matrix);
    drawLine(bottomLeftX+width-1, bottomLeftY, bottomLeftX+width-1, bottomLeftY+width-1, matrix);
    drawLine(bottomLeftX+width-1, bottomLeftY+width-1, bottomLeftX, bottomLeftY+width-1, matrix);
    drawLine(bottomLeftX, bottomLeftY+width-1, bottomLeftX, bottomLeftY, matrix);
}

void drawFigure(int parameter, int matrix[X_PIXEL][Y_PIXEL][ARRAY_DEPTH]){
    int start = 0;
    for(int i=0; i<parameter; i++){
        drawSquare(start+PICTURE_PADDING, start+PICTURE_PADDING, X_PIXEL-2*PICTURE_PADDING-start*2, matrix);
        start += (X_PIXEL-2*PICTURE_PADDING+((i+1)*2))/(parameter*2-1);
    }
}
