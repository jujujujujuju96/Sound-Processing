#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char **argv){

  FILE *fpin;
  FILE *fpout;

  char *filename;
  char *output; 
  short wave[20000];
  int i;
  int size;
  double time;

  float t = 0.02;
  float s = 16000;
  float sample_size = 0;
  double offset;

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

  //fprintf
  for(i=0;i<sample_size;i++){
    time = (double)(i/s*1000+offset/2/s*1000);  
    fprintf(fpout,"%f %d\n",time,wave[i]);    
  }

  //fclose
  fclose(fpin);
  fclose(fpout);
  
  return 0;
}
