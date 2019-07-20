#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

#define L 320

int main(int argc,char **argv){

  FILE *fpin;
  FILE *fpout;

  char *filename;
  char *output; 
  short wave[262144];
  int n;
  int size;
  double time;
  float t = 0.02;
  float s = 16000;
  float sample_size = 0;
  double offset;
  double yd[320],w[320],yr[1024],yi[1024],spe[1024];
  

  if((fpin = fopen(argv[1], "rb")) == NULL){//音声ファイルの読込み
    printf("%sOpening error\n",argv[1]);
    return 1;
  }
  if((fpout = fopen(argv[2], "w")) == NULL){//出力ファイルの読込み
    printf("%sOpening error\n",argv[2]);
    return 2;
  }

  sample_size = t * s; 

  //stat;
  struct stat buf;
  stat(argv[1],&buf);
  size = buf.st_size/2;
  offset = (size/2 - sample_size/2)*2;
  fseek(fpin,offset,SEEK_SET);
  fread( wave , 2 , size , fpin);

  //窓掛け
  for(n=0;n<L;n++){
    w[n] = 0.54-0.46*cos(2*(double)n*M_PI/(double)((L)-1));
    yd[n] = w[n]*(double)wave[n];
    printf("%f\n",yd[n]);
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

  //スペクトル計算
  for(n=0;n<1024;n++){
    spe[n] = 10*(double)log10(yr[n]*yr[n]+yi[n]*yi[n]);
  }
  
  //output
  for(n=0;n<1024;n++){
    fprintf(fpout,"%lf\t%lf\n",(float)16/1024*n,spe[n]);
  }

  //fclose
  fclose(fpin);
  fclose(fpout);
  
  return 0;
}
