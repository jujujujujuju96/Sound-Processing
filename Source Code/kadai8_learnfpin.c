#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define N 100

int main(int argc, char **argv){

  double c = 0.4;   
  int n,r;
  struct stat buf;
  short wave[800000];
  double y[800000];
  short wave_out[800000];
  int i,j,m;
  int size;
  double time;
  int num[N+1];
  double fil[N+1];

  FILE *fpout;

    if((fpout = fopen(argv[1], "wb")) == NULL){//音声ファイルの読込み
      printf("%sOpening error\n");
      return 1;
    }

    mic2file(argv[1]);

    stat(argv[1],&buf);
    size = buf.st_size;
    fwrite(argv[1], 2, size, fpout);
    fclose(fpout);

  return 0;
}
