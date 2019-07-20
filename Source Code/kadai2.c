#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char **argv){

  FILE *fpin;
  FILE *fpout;
  FILE *fpout1;

  char *filename;
  char *output; 
  short wave[20000];
  int i,j;
  int size;
  double time;

  //input
  if((fpin = fopen(argv[1], "rb")) == NULL){//音声ファイルの読込み
    printf("%sOpening error\n",argv[1]);
    return 1;
  }
  if((fpout = fopen(argv[2], "w")) == NULL){//出力ファイルの読込み
    printf("%sOpening error\n",argv[2]);
    return 2;
  }
  if((fpout1 = fopen(argv[3], "wb")) == NULL){//出力ファイルの読込み
    printf("%sOpening error\n",argv[3]);
    return 3;
  }

  //stat
  struct stat buf;
  stat(argv[1],&buf);
  size = buf.st_size/2;
  fread( wave , 2 , size , fpin);

  //output
  for(i=0;i<size;i++){
    time = (double)i*0.0625;                     
    fprintf(fpout,"%f %d\n",time,wave[i]*3);      
  }
  for(j=0;j<size;j++){
    wave[j] = wave[j]*3;
  }
  fwrite(wave, 2, size, fpout1);

  //fclose
  fclose(fpin);
  fclose(fpout);
  fclose(fpout2);
  
  return 0;
}
