#include <stdlib.h>
#include <stdio.h>
#include "lyman-series.h"

/* All data taken from Wiese et al. 1966

https://permanent.access.gpo.gov/LPS113182/NSRDS-NBS4.pdf

*/

int n_lyman; //number of lyman series transitions
int flag_lyman;  //did we allocate data for the lyman series
double *l_lyman; //wavelength of lyman series transitions in angstrom
double *E_lyman; //energies of lyman series transitions in cm^-1
double *gi_lyman;  //statistical weight i
double *gk_lyman;  //statistical weight k
double *Aki_lyman; //Emission coefficient k->i in 1/second
double *fik_lyman; //oscillator strength i->k


void InitializeLymanSeries(void)
{
  int i;

  //data from Wieser et al. 1966
  double l_lyman_in[39] = {1215.67, 1025.72, 792.537, 949.743, 937.803, 930.748, 926.226, 923.150, 920.963, 919.352, 918.129, 917.181, 916.429, 915.824, 915.329, 914.919, 914.576, 914.286, 914.039, 913.826, 913.641, 913.480, 913.339, 913.215, 913.104, 913.006, 912.918, 912.839, 912.768, 912.703, 912.645, 912.592, 912.543, 912.499, 912.458, 912.420, 912.385, 912.353, 912.324};

  if(flag_lyman==0)
  {
    n_lyman = 39; //set the number of transitions we use

    //allocate the atomic data arrays
    l_lyman = AllocateLymanMemory(n_lyman);
    E_lyman = AllocateLymanMemory(n_lyman);
    gi_lyman = AllocateLymanMemory(n_lyman);
    gk_lyman = AllocateLymanMemory(n_lyman);
    Aki_lyman = AllocateLymanMemory(n_lyman);
    fik_lyman = AllocateLymanMemory(n_lyman);

    //set the data

    for(i=0;i<n_lyman;i++)
    {
      l_lyman[i] = l_lyman_in[i];
     /* E_lyman[i] = E_lyman_in[i];
      gi_lyman[i] = gi_lyman_in[i];
      gk_lyman[i] = gk_lyman_in[i];
      Aki_lyman[i] = Aki_lyman_in[i];
      fik_lyman[i] = fik_lyman_in[i];*/
    }

    flag_lyman = 1; //remember we allocated the data
  }
}
void FreeLymanSeries(void)
{
  if(flag_lyman==1)
  {
    free(l_lyman);
    free(E_lyman);
    free(gi_lyman);
    free(gk_lyman);
    free(Aki_lyman);
    free(fik_lyman);
    flag_lyman = 0;
  }
}
double *AllocateLymanMemory(int n)
{
  double *x;
  if(!(x = (double*) calloc(n,sizeof(double))))
  {
    printf("Error allocating data of size %d in AllocateLymanMemory().\n",n);
    exit(-1);
  }
  return x;
}
void PrintLymanSeries(void)
{
  int i;
  int k;
  if(flag_lyman==1)
  {
    for(i=0;i<n_lyman;i++)
    {
      printf("1-%d | %6.3f | 0 | %6.0f | %d  | %d | %5.4e | %4.3e\n",i+2,l_lyman[i],E_lyman[i],(int) gi_lyman[i], (int) gk_lyman[i], Aki_lyman[i], fik_lyman[i]);
    }

  }else{
    printf("Lyman series information not allocated (flag = %d).\n",flag_lyman);
  }
}
