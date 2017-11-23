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
double gi_lyman;  //statistical weight i
double *gk_lyman;  //statistical weight k
double *Aki_lyman; //Emission coefficient k->i in 1/second
double *fik_lyman; //oscillator strength i->k


void InitializeLymanSeries(void)
{
  int i;

  //data from Wieser et al. 1966
  double l_lyman_in[39] = {1215.67, 1025.72, 792.537, 949.743, 937.803, 930.748, 926.226, 923.150, 920.963, 919.352, 918.129, 917.181, 916.429, 915.824, 915.329, 914.919, 914.576, 914.286, 914.039, 913.826, 913.641, 913.480, 913.339, 913.215, 913.104, 913.006, 912.918, 912.839, 912.768, 912.703, 912.645, 912.592, 912.543, 912.499, 912.458, 912.420, 912.385, 912.353, 912.324};
  double E_lyman_in[39] = {82259,97492,102824,105292,106632,107440,107965,108325,108582,108772,108917,109030,109119,109191,109250,109299,109340,109375,109405,109430,109452,109471,109488,109503,109517,109528,109539,109548,109557,109565,109572,109578,109584,190589,109594,109599,109603,109607,109610};
  double gk_lyman_in[39] = {8,18,32,50,72,98,128,162,200,242,288,338,392,450,512,578,648,722,800,882,968,1058,1152,1250,1352,1458,1568,1682,1800,1992,2048,2178,2312,2450,2592,2738,2888,3042,3200};
  double Aki_lyman_in[39] = {4.699e8,5.575e7,1.278e7,4.125e6,1.644e6,7.568e5,3.869e5,2.143e5,1.263e5,7.834e4,5.066e4,3.393e4,2.341e4,1.657e4,1.200e4,8858,6654,5077,3928,3077,2438,1952,1578,1286,1057,875.3,729.7,612.2,516.7,438.6,374.2,320.8,276.3,239.0,207.6,181.0,158.4,139.1,122.6};
  double fik_lyman_in[39] = {0.4162,7.910e-2,2.899e-2,1.394e-2,7.799e-3,4.814e-3,3.183e-3,2.216e-3,1.605e-3,1.201e-3,9.214e-4,7.227e-4,5.774e-4,4.686e-4,3.856e-4,3.211e-4,2.702e-4,2.296e-4,1.967e-4,1.698e-4,1.476e-4,1.291e-4,1.136e-4,1.005e-4,8.928e-5,7.970e-5,7.144e-5,6.429e-5,5.806e-5,5.261e-5,4.782e-5,4.360e-5,3.986e-5,3.653e-5,3.357e-5,3.092e-5,2.854e-5,2.640e-5,2.446e-5};


  if(flag_lyman==0)
  {
    n_lyman = 39; //set the number of transitions we use

    //allocate the atomic data arrays
    l_lyman = AllocateLymanMemory(n_lyman);
    E_lyman = AllocateLymanMemory(n_lyman);
    gi_lyman = 2.0;
    gk_lyman = AllocateLymanMemory(n_lyman);
    Aki_lyman = AllocateLymanMemory(n_lyman);
    fik_lyman = AllocateLymanMemory(n_lyman);

    //set the data

    for(i=0;i<n_lyman;i++)
    {
      l_lyman[i] = l_lyman_in[i];
      E_lyman[i] = E_lyman_in[i];
      gk_lyman[i] = gk_lyman_in[i];
      Aki_lyman[i] = Aki_lyman_in[i];
      fik_lyman[i] = fik_lyman_in[i];
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
  //produce H-Table A. from Wiese et al. 1966
  int i;
  int k;
  if(flag_lyman==1)
  {
    k=0;
    for(i=0;i<n_lyman;i++)
    {
      printf("1-%d | %6.3f | 0 | %6.0f | %d  | %d | %5.4e | %4.3e\n",i+2,l_lyman[i],E_lyman[i],(int) gi_lyman, (int) gk_lyman[i], Aki_lyman[i], fik_lyman[i]);
      k++;
      if(k==5)
      {
        printf("\n");
        k=0;
      }
    }

  }else{
    printf("Lyman series information not allocated (flag = %d).\n",flag_lyman);
  }
}
