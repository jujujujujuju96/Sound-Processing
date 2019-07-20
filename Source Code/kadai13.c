#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#define N 100

int main(int argc, char **argv){

  double PI = M_PI;
  double c = 0.4;   
  double h[1025];
  double hi[1025];
  double spe[1025];
  int size; 
  int n,i,j;

  struct stat buf;
  short wave[800000];
  double y[800000];
  short wave_out[800000];

  FILE *fpin;
  FILE *fpout1;
  FILE *fpout2;

  if((fpin = fopen(argv[1], "rb")) == NULL){
    fprintf(stderr, "Opening ERROR\n");
    return 1;
  }
  if((fpout1 = fopen(argv[2], "wb")) == NULL){
    fprintf(stderr, "Opening ERROR\n");
    return 1;
  }
  if((fpout2 = fopen(argv[3], "wb")) == NULL){
    fprintf(stderr, "Opening ERROR\n");
    return 1;
  }

  stat(argv[1], &buf);
  size = buf.st_size/2;
  fread(wave,2,size,fpin);

  
  for(n=0;n<=N;n++){
    if(n==N/2){
      h[n]=c;
    }else{
      h[n] = sin((double)(n-N/2)*PI*c)/((double)(n-N/2)*PI);
    }
    if(n%2==1){
      h[n] = (-1.0)*h[n];
    }
    hi[n]= 0;
  }

  //計算
  for(i=0; i<size; i++){
    for(j=0; j<=N+1; j++){
      if(i>=j){
	y[i] += (double)wave[i-j] * (double)h[j];
      }
    }
    wave_out[i] = (short)y[i];
  }

  for(n=N; n<1024; n++){
    h[n] = 0;
    hi[n] = 0;
  }

  fft(1024, h, hi);

  for(n=0; n<1024; n++){
    spe[n] = 10*log10(h[n]*h[n] + hi[n]*hi[n]);
  }

  for(n=0; n<512; n++){
    //printf("%f",spe[n]);  
    fprintf(fpout2, "%f %f\n", 0.015625 * n / 8, spe[n]);
  }

  fwrite(wave_out,2,size,fpout1);

  fclose(fpin);
  fclose(fpout1);
  fclose(fpout2);
  return 0;
}
