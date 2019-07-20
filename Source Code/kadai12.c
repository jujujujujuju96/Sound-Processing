#include <stdio.h>
#include <math.h>
#define N 200

int main(int argc, char **argv){

  double PI = M_PI;
  double c = 0.4;   
  double h[1025];
  double hi[1025];
  double spe[1025];
  int n;

  FILE *fpout;
  if((fpout = fopen(argv[1], "wb")) == NULL){
    fprintf(stderr, "Opening ERROR\n");
    return 1;
  }
  
  for(n=0;n<=N;n++){
    if(n==N/2){
      h[n]=c;
    }else{
      h[n] = sin((double)(n-N/2)*PI*c)/((double)(n-N/2)*PI);
    }
    hi[n]= 0;
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
    fprintf(fpout, "%f %f\n", 0.015625 * n / 8, spe[n]);
  }
  fclose(fpout);
  return 0;
}
