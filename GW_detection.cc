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
// Megan Goodland, March 2019.
// Assignment 6 of PHY1610 at University of Toronto

#include <iostream>
#include <rarray>
#include <rarrayio>
#include <vector>
#include <complex>
#include <stdio.h>
#include <netCDF_reading.h>
#include <rarray_math.h>


using namespace std;




int main(){
  // int n_detections = 32; // number of detections

  // Initializing rarrays and constants
  const int f_size = get_f_size("GWprediction.nc"); // Only need to do this once because f is same size in all files
  rarray<complex<double>,1> f(f_size); // initialize array to hold f
  rarray<complex<double>,1> fhat(f_size); // initialize array to hold fhat
  rarray<double,1> Fk(f_size); // initialize array to hold Fk
  rarray<double,1> Gk(f_size); // initialize array to hold Gk
  
  // Fill f with data from netCDF file
  f = get_f("GWprediction.nc"); 
  // Get fast fourier transform
  fhat = fft(f);
  // Get Fk
  Fk = sq_norm(fhat);
  
  // Get Gk with same steps, overwriting f and fhat
  f = get_f("detection01.nc");
  fhat = fft(f);
  Gk = sq_norm(fhat);
  
  // Get the correlation between Fk and Gk
  double C = correlation(Fk, Gk);
  cout << C << endl;
    
  
 // rarray<complex<double>,2> detections(n_detections); // rarray to hold all power spectra
  
//  for (int i=1; i<(n_detections+1); i++){
 //   if (i<10){
 //     detections
 //   }
 //   if (i>10){
 //     
 //   }
 // }
  
  //get_f("detection01.nc");
  
  // The power spectrum F of a signal f is related to the fourier transform of that 
  // signal: for each wave number k (freq num in this case), the power spectrum is 
  // the square norm of the fourier component with that wavenumber.
  // First, compute fft of the two complex quantities using FFTW
  return 0;
}

