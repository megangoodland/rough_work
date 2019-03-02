// GW_detection.cc
// 
// This file will...
// 1. Read the predicted GW signal from GWprediction.nc.
// 2. Read one of the GW signal from observations detection01.nc . . . detection32.nc.
// 3. Compute the FFT of the two complex quantities, using FFTW.
// 4. Compute the power spectrum of both signals.
// 5. Compute the correlation coefficient between the power spectra using a .BLAS call for the inner product
// 6. Output the correlation coefficient
// 7. Repeat steps 2-to-6 for each of the signals in the observation set.
// 8. Finally, determine the 5 most significant candidates (those with the 5 largest values of the correlation coefficient) from the observations set.
//
// Compile with 'make'.
// On the clusters, it will be necessary to load the "gcc" module first.
//
// Run with
//
//     ./GW_detection
// 
// Megan Goodland, March 2019, for Assignment 6 of PHY1610 at University of Toronto

#include <iostream>
#include <rarray>
#include <rarrayio>
#include <netcdf>
#include <complex>
using namespace std;
using namespace netCDF;
int main(){
  NcFile file("detection01.nc", NcFile::read); // selects the file to read
  NcDim ntDim = file.getDim("nt");
  int nt_size = ntDim.getSize(); // size of data

  NcVar data = file.getVar("f"); // Get variable named 'f'
// put data in a var
 // double dataOut[nt_size];
  //data.getVar(&dataOut);
 // eff = rarray<complex<double>,1> f(file.getDim("nt").getSize()); // defining rarray called f to hold the data

  return 0;
}

