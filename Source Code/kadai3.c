#include <stdio.h>
#include <math.h>
#define N 100

int main(int argc, char **argv){

  double PI = M_PI;
  double c = 0.4;   
  double h[N+1];
  int n;

  //input
  FILE *fpout;
  if((fpout = fopen(argv[1], "wb")) == NULL){
    fprintf(stderr, "Opening ERROR\n");
    return 1;
  }
  
  //calculation & output
  for(n=0;n<=N;n++){
    if(n==N/2){
      h[n]=c;
    }else{
      h[n] = sin((double)(n-N/2)*PI*c)/((double)(n-N/2)*PI);
    }
    fprintf(fpout, "%d %lf\n", n, h[n]);
  }

  fclose(fpout);
  return 0;
}
