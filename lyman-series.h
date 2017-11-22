#ifndef LYMAN_SERIES_H
#define LYMAN_SERIES_H

/* All data taken from Wiese et al. 1966

https://permanent.access.gpo.gov/LPS113182/NSRDS-NBS4.pdf

*/

extern int n_lyman; //number of lyman series transitions
extern int flag_lyman;  //did we allocate data for the lyman series
extern double *l_lyman; //wavelength of lyman series transitions in angstrom
extern double *E_lyman; //energies of lyman series transitions in cm^-1
extern double *gi_lyman;  //statistical weight i
extern double *gk_lyman;  //statistical weight k
extern double *Aki_lyman; //Emission coefficient k->i in 1/second
extern double *fik_lyman; //oscillator strength i->k

void InitializeLymanSeries(void);
double *AllocateLymanMemory(int n);
void FreeLymanSeries(void);
void PrintLymanSeries(void);

#endif //LYMAN_SERIES_H