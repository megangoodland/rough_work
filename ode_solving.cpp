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
#include <netcdf>
#include <rarray>
#include <rarrayio>
using namespace boost::numeric::odeint;
using namespace std;


// write data to the netCDF file
// function here
    

// defining constants and initial conditions
const double A = 0.03;  // rate at which zombies are killed by K
const double B = 0.02;  // rate at which regular people are turned into Z
const double C = 0.01;  // rate as which zombie killers are turned into Zombies
const double E = 0.015; // rate at which zombie killers teach regular people how to kill zombies
const double K0 = 9; // number of people who can kill zombies
int i = 0; // counter for integrate steps
int saves = 0; // counter for number of saves
double num = 50; // number of steps to perform

// defining boost array to hold x = ( S, K, Z )
typedef boost::array<double, 3> state_type;
    
// defining 3D array to hold data history
// dimensions: tSKZ, time, 2 saves
rarray<double,3> history(4,num+1,2);

// saves data in array
void add_to_array(const state_type &x , const double t){
   // cout << i << '\t' << saves << '\t' << num << endl;
    cout << t << '\t' << x[0] << '\t' << x[1]<< '\t'<< x[2]<<endl;
    history[0][i][saves] = t; history[1][i][saves] = x[0]; history[2][i][saves] = x[1]; history[3][i][saves] = x[2]; 
    i = i+1; // increment
}

void print_array(rarray<double,3>& print){
    int len0 = print.extent(0); int len1 = print.extent(1); int len2 = print.extent(2);
        for (int y = 0; y < len1; y++) {
            cout << print[0][y][0] << '\t' << print[1][y][0] << '\t' << print[2][y][0] << '\t' << print[3][y][0] << endl;
        }
}


// x = ( S, K, Z )
void zombie_odes( const state_type &x , state_type &dxdt , double t ){
    dxdt[0] = -(B*x[0]*x[2])-(E*x[0]*x[1]);
    dxdt[1] = -(C*x[1]*x[2])+(E*x[0]*x[1]);
    dxdt[2] = -(B*x[0]*x[2])+(C*x[1]*x[2])-(A*x[1]*x[2]);
}


int main() { 
  double Z0 = 5; // number of zombies: will be varying this value 263
  double S0 = 491 - Z0; // number of regular people who can't kill zombies
  state_type x = {S0, K0, Z0}; // initial conditions
  // integrate needs (system, x0, t0, t1, dt, observer)
  integrate(zombie_odes , x , 0.0 , num , 0.01 , add_to_array);
  //print_array(history);
  
  Z0 = 263; // new number of zombies 5
  S0 = 491 - Z0; // number of regular people who can't kill zombies
  x = {S0, K0, Z0}; // new initial conditions
  i = 0; // reset counter for integrate steps
  saves = 1; // counter for number of saves
  integrate(zombie_odes , x , 0.0 , num , 0.01 , add_to_array);
  //print_array(history);
  
}
