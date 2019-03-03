//  Header for the module for reading the netCDF files for GW_detection.cc

//  File   netCDF_reading.h
//  Author PHYS1610
//  Date   2019-03-02.
//  Brief  Functions to be used on netCDF files to put in a usable form in main code

#ifndef netCDF_reading_h
#define netCDF_reading_h

// get_f: This function reads f from the file and returns it in an rarray
//      Input: name of the file
//      Output: 1D complex double rarray
rarray<complex<double>,1> get_f(string s);

// get_f_size: This function returns the size of variable f from a netCDF file
//      Input: name of the file
//      Output: size of variable f in the file
int get_f_size(string s);

#endif /* netCDF_reading */
