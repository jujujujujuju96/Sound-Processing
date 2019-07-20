#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

#define L 320

int main(int argc,char **argv){

  FILE *fpin[6];

  char *filename;
  short wave[20000];
  int n=0,r=0;
  int size;
  double time;

  float t = 0.02;
  float s = 16000;
  float sample_size = 0;
  double offset;

  double yd[320],w[320],yr[1024],yi[1024];
  double spe[6][1024];
  
  double d=0;
  double D[5]={};
  double min =0;

  char standard[5][10] = {"a00.raw", "i00.raw", "u00.raw", "e00.raw", "o00.raw"};
  
  for(r=0; r<6; r++){

    if(r!=5){
      if((fpin[r] = fopen(standard[r], "rb")) == NULL){
	printf("%sOpening error\n",standard[r]);
	return 1;
      }
    }

    else{
      if((fpin[r] = fopen(argv[1], "rb")) == NULL){
        printf("%sOpening error\n",argv[1]);
        return 1;
       }
    }
    //stat;

    sample_size = t * s;   
    struct stat buf;
    if(r!=5){
      stat(standard[r],&buf);}
    else{
      stat(argv[1],&buf);}
    size = buf.st_size/2;
    offset = (size/2 - sample_size/2)*2;
    fseek(fpin[r],offset,SEEK_SET);
    fread( wave , 2 , size , fpin[r]);
  
    //窓掛け
    for(n=0;n<L;n++){
      w[n] = 0.54-0.46*cos(2*(double)n*M_PI/(double)((L)-1));
      yd[n] = w[n]*(double)wave[n];
    }

    //フーリエ変換
    for(n=0;n<L;n++){
      yr[n] = yd[n];
      yi[n] = 0;
    }
    for(n=L;n<1024;n++){
      yr[n] = 0;
      yi[n] = 0;
    }
    fft(1024,yr,yi);

    //スペクトル
    for(n=0;n<1024;n++){
      spe[r][n] = 10*(double)log10(yr[n]*yr[n]+yi[n]*yi[n]);
    }
   }

  //ユークリッド距離
  for(r=0;r<5;r++){
    for(n=0;n<1024;n++){
      d += (spe[r][n] - spe[5][n])*(spe[r][n] - spe[5][n]);
    }
    D[r] = sqrt(d);
    d=0;
  }
  //最小ユークリッド距離を
  min = D[0];
  for(r=0; r<5; r++){
    if(min>D[r]){
      min = D[r]; 
     }
  }
  
  //結果
  for(n=0; n<5; n++){printf("%f\n", D[n]);}
  if(min == D[0]){printf("「あ」です。\n");}
  if(min == D[1]){printf("「い」です。\n");}
  if(min == D[2]){printf("「う」です。\n");}
  if(min == D[3]){printf("「え」です。\n");}
  if(min == D[4]){printf("「お」です。\n");}

  //fclose  
  for(r=0; r<5; r++){fclose(fpin[r]);}
  
  return 0;
}
