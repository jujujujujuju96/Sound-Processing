#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define N 100

int main(int argc, char **argv){

  double c = 0.4;   
  int n;
  struct stat buf;
  short wave[800000];
  double y[800000];
  short wave_out[800000];
  int i,j,m;
  int size;
  double time;
  int num[N+1];
  double fil[N+1];

  FILE *fpin;
  FILE *filter;
  FILE *fpout;

  //input
  if((fpin = fopen(argv[1], "rb")) == NULL){//音声ファイルの読込み
    printf("%sOpening error\n");
    return 1;
  }
  if((filter = fopen(argv[2], "r")) == NULL){//音声ファイルの読込み
    printf("%sOpening error\n");
    return 2;
  }
  if((fpout = fopen(argv[3], "wb")) == NULL){//音声ファイルの読込み
    printf("%sOpening error\n");
    return 3;
  }

  //stat
  stat(argv[1],&buf);
  size = buf.st_size/2;
  fread( wave , 2 , size , fpin);

  //inputインパルス応答
  for(n=0; n<=N; n++){
    fscanf(filter,"%d %lf", &num[n], &fil[n]);
    printf("%d %lf \n",num[n],fil[n]);
  }

  //計算
  for(i=0; i<size; i++){
    for(j=0; j<=N+1; j++){
      if(i>=j){
	y[i] += (double)wave[i-j] * (double)fil[j];
      }
    }
    wave_out[i] = (short)y[i];
  }

  //output
  fwrite(wave_out, 2, size, fpout);

  //fclose
  fclose(fpin);
  fclose(filter);
  fclose(fpout);

  return 0;
}
