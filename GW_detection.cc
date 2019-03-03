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
#include <netcdf>
#include <complex>
#include <fftw3.h>
using namespace std;
using namespace netCDF;

// This function reads f from the file and returns it in an rarray
// Input: name of the file
// Output: 1D complex double rarray
rarray<complex<double>,1> get_f(string s){
  NcFile file(s, NcFile::read); // selects the file to read
  rarray<complex<double>,1> f(file.getDim("nt").getSize()); // defining rarray called f to hold the data
  file.getVar("f").getVar(&f[0]); // putting data in rarray
  return f;
}

// This function returns the size of variable f from a netCDF file
int get_f_size(string s){
  NcFile file(s, NcFile::read); // selects the file to read
  rarray<complex<double>,1> f(file.getDim("nt").getSize()); // defining rarray called f to hold the data
  file.getVar("f").getVar(&f[0]); // putting data in rarray
  int f_size = f.extent(0);
  return f_size;
}

// fast fourier transform function
// Input: f rarray
// Output: fhat rarray
rarray<complex<double>,1> fft(rarray<complex<double>,1>& f){
  int f_size = f.extent(0);
  rarray<complex<double>,1> fhat(f_size); // initialize array to hold fhat
  fftw_plan p = fftw_plan_dft_1d(f_size,
                      (fftw_complex*)f.data(), (fftw_complex*)fhat.data(),
                      FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p); // dont destroy the plan if you are reusing it 
  return fhat;
}




int main(){
  // int n_detections = 32; // number of detections

  // First, compute fft of the two complex quantities using FFTW
  // Get f
  const int f_size = get_f_size("GWprediction.nc"); // Only need to do this once because f is same size in all files
  rarray<complex<double>,1> f(f_size); // initialize array to hold f
  rarray<complex<double>,1> fhat(f_size); // initialize array to hold fhat
  
  f = get_f("GWprediction.nc"); // fill f with data from netCDF file
  cout << f_size << endl;
  // get fast fourier transform
  fhat = fft(f);
    
    
  
 // rarray<complex<double>,2> detections(n_detections); // rarray to hold all detection data
  
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

