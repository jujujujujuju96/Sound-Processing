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

  if((fpin = fopen(argv[1], "rb")) == NULL){//音声ファイルの読込み
    printf("%sOpening error\n",argv[1]);
    return 1;
  }
  if((fpout = fopen(argv[2], "w")) == NULL){//出力ファイルの読込み
    printf("%sOpening error\n",argv[2]);
    return 2;
  }

  //stat;
  struct stat buf;
  stat(argv[1],&buf);
  
  size = buf.st_size/2;

  fread( wave , 2 , size , fpin);
  //fprintf
  for(i=0;i<size;i++){
    time = (double)i*0.0625;                      //横軸の時間の計算
    fprintf(fpout,"%f %d\n",time,wave[i]);      //ファイルに時間と標本値を書き込む
  }
  //fclose
  fclose(fpin);
  fclose(fpout);
  
  return 0;
}
