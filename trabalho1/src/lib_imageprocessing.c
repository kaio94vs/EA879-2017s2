

#include <stdlib.h>
#include <stdio.h>

#include "imageprocessing.h"

#include <FreeImage.h>

/*
imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo);
void liberar_imagem(imagem *i);
 */

imagem abrir_imagem(char *nome_do_arquivo) {
  FIBITMAP *bitmapIn;
  int x, y;
  int i,j,idx;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (i=0; i<x; i++) {
     for (j=0; j <y; j++) {
      
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed;
      I.g[idx] = color.rgbGreen;
      I.b[idx] = color.rgbBlue;
    }
   }
  return I;

}

void liberar_imagem(imagem *I) {
  free(I->r);
  free(I->g);
  free(I->b);
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
  FIBITMAP *bitmapOut;
  RGBQUAD color;
  int i,j;

  printf("Salvando imagem %d por %d...\n", I->width, I->height);
  bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

   for (i=0; i<I->width; i++) {
     for (j=0; j<I->height; j++) {
      int idx;

      idx = i + (j*I->width);
      color.rgbRed = (float)I->r[idx];
      color.rgbGreen = (float)I->g[idx];
      color.rgbBlue = (float)I->b[idx];

      FreeImage_SetPixelColor(bitmapOut, i, j, &color);
    }
  }

  FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}

void brilho_imagem(imagem *I, float intensidade){
int i, j, k = 0;
    for (i=0; i<I->width; i++) {
    for (j=0; j<I->height; j++) {
        k = i + (j*I->width);
           
            if ((I->r[k] * intensidade) <= 255) {
            I->r[k] = (I->r[k] * intensidade);}
            else {I->r[k] = 255;}
           
            if ((I->g[k] * intensidade) <= 255) {
            I->g[k] = (I->g[k] * intensidade);}
            else {I->g[k] = 255;}
           
            if ((I->b[k] * intensidade) <= 255) {
            I->b[k] = (I->b[k] * intensidade);}
            else {I->b[k] = 255;}       
           }
      }
}


void vmax_imagem (imagem *I, float vmax[3]){

	int i, j, idx;
	vmax[0] = 0.0; 
	vmax[1] = 0.0;
	vmax[2] = 0.0;
	
	for (i=0; i<I->width; i++) {
		for (j=0; j<I->height; j++){
			idx = i + (j*I->width);			
			if (I->r[idx] >= vmax[0]){
				vmax[0] = I->r[idx];
			}
			if (I->g[idx] >= vmax[1]){
				vmax[1] = I->g[idx];
			}
			if (I->b[idx] >= vmax[2]){
				vmax[2] = I->b[idx];
			}			
		}
	}	
}



/*void vmax_imagem(imagem *I){
float valor_maximo, valor_analisado = 0;
int i=0,j=0,k = 0;
  for (i=0; i<I->width; i++) {
  for (j=0; j<I->height; j++) {
     
      k = i + (j*I->width);
     
      valor_analisado = (I->r[k] + I->g[k] + I->b[k]) / 3.0; //média aritmética das intensidades
     
      if(valor_analisado > valor_maximo){
        valor_maximo = valor_analisado;
          }
        }
    }
}

*/




void imprime (imagem *I){

	int i, j, idx;

	for (i=0; i<I->width; i++) {
		for (j=0; j<I->height; j++){
			idx = i + (j*I->width);			
			if (I->r[idx] - (int)I->r[idx] != 0 | I->g[idx] - (int)I->g[idx] != 0 | I->b[idx] - (int)I->b[idx] != 0){
				printf ("%f %f %f\n", I->r[idx], I->g[idx], I->b[idx]);
			}			
		}
	}
	printf ("fim de impressão\n");
}