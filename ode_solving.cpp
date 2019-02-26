// ode_solving.cpp

// Differential equations describing populations in an apartment building of 500 people infested by zombies:
// dS/dt = - BSZ - ESK
// dK/dt = - CKZ + ESK
// dZ/dt = BSZ + CKZ - AKZ

// Want to numerically solve the set of ODEs for several values of Z0 to determine the number of Z0 above which
// the zombies will win. 
// Outputs a netcdf file that contains (S, K, Z) population vs. time for two values of the initial Z0 values:
// one in which the zombies win (everyone is zombies), and one in which they all disappear (Z<1). 


#include <iostream>
#include <boost/numeric/odeint.hpp>
#include <boost/array.hpp>
#include <netcdfcpp.h>
#include <rarray>
#include <rarrayio>
using namespace boost::numeric::odeint;
using namespace std;


// write data to the netCDF file
// function here
    
// Create the file.
NcFile dataFile("pres_temp_4D.nc", NcFile::Replace);
// Define dimensions
// One dimension for the S K Z data
// One dimension for time
// One dimension for the two result sets
NcDim *lvlDim, *latDim, *lonDim, *recDim;
latDim = dataFile.add_dim("latitude", NLAT);
lonDim = dataFile.add_dim("longitude", NLON);
recDim = dataFile.add_dim("time"); //this is an unlimited dimension

// defining constants and initial conditions
const double A = 0.03;  // rate at which zombies are killed by K
const double B = 0.02;  // rate at which regular people are turned into Z
const double C = 0.01;  // rate as which zombie killers are turned into Zombies
const double E = 0.015; // rate at which zombie killers teach regular people how to kill zombies
const double K0 = 9; // number of people who can kill zombies
double Z0 = 263; // number of zombies: will be varying this value
double S0 = 491 - Z0; // number of regular people who can't kill zombies
double num = 50; // number of steps to perform
int i = 0;

// defining boost array to hold x = ( S, K, Z )
typedef boost::array< double , 3 > state_type;
    
// defining 3D array to hold data history
// dimensions: tSKZ, time, 2 saves
rarray<double,3> history(4,num,2);

// saves data in array
void add_to_array(const state_type &x , const double t){
    cout << t << '\t' << x[0] << '\t' << x[1] << '\t' << x[2] << endl; 
    i = i++; // increment
}



// x = ( S, K, Z )
void zombie_odes( const state_type &x , state_type &dxdt , double t ){
    dxdt[0] = -(B*x[0]*x[2])-(E*x[0]*x[1]);
    dxdt[1] = -(C*x[1]*x[2])+(E*x[0]*x[1]);
    dxdt[2] = -(B*x[0]*x[2])+(C*x[1]*x[2])-(A*x[1]*x[2]);
}


int main() { 
  state_type x = {S0, K0, Z0}; // initial conditions
  // integrate needs (system, x0, t0, t1, dt, observer)
  int n; //n is the number of steps performed
  n = integrate(zombie_odes , x , 0.0 , num , 0.01 , add_to_array);
  cout << n << endl;
}
