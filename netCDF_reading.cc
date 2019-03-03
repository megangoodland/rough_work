// Module for reading the netCDF files for GW_detection.cc
#include <iostream>
#include <rarray>
#include <rarrayio>
#include <vector>
#include <netcdf> // for file i/o
#include <complex>
#include "netCDF_reading.h"

using namespace std;
using namespace netCDF;

// get_f: This function reads f from the file and returns it in an rarray
//      Input: name of the file
//      Output: 1D complex double rarray
rarray<complex<double>,1> get_f(string s){
  NcFile file(s, NcFile::read); // selects the file to read
  rarray<complex<double>,1> f(file.getDim("nt").getSize()); // defining rarray called f to hold the data
  file.getVar("f").getVar(&f[0]); // putting data in rarray
  return f;
}

// get_f_size: This function returns the size of variable f from a netCDF file
//      Input: name of the file
//      Output: size of variable f in the file
int get_f_size(string s){
  NcFile file(s, NcFile::read); // selects the file to read
  rarray<complex<double>,1> f(file.getDim("nt").getSize()); // defining rarray called f to hold the data
  file.getVar("f").getVar(&f[0]); // putting data in rarray
  int f_size = f.extent(0);
  return f_size;
}
