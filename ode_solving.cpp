// we solve the simple ODE x’ = 3/(2t^2) + x/(2t) * with initial condition x(1) = 0.
// Analytic solution is x(t) = sqrt(t) - 1/t 

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
using namespace boost::numeric::odeint;
using namespace std;


// defining constants and initial conditions
const double A = 0.03;  // rate at which zombies are killed by K
const double B = 0.02;  // rate at which regular people are turned into Z
const double C = 0.03;  // rate as which zombie killers are turned into Zombies
const double E = 0.015; // rate at which zombie killers teach regular people how to kill zombies
const double K0 = 9;
double Z0 = 5; // will be varying this value
double S0 = 491 - Z0;
double S = S0; // number of regular people who can't kill zombies
double K = K0; // number of people who can kill zombeis
double Z = Z0; // number of zombies


const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

typedef boost::array< double , 3 > state_type;

void write_lorenz( const state_type &x , const double t )
{
    cout << t << '\t' << x[0] << '\t' << x[1] << '\t' << x[2] << endl;
}

void lorenz( const state_type &x , state_type &dxdt , double t )
{
    dxdt[0] = sigma * ( x[1] - x[0] );
    dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
    dxdt[2] = -b * x[2] + x[0] * x[1];
}

void write_cout(const double &x, const double t) { 
  cout << t << "\t" << x << endl;
}

typedef runge_kutta_dopri5 <double > stepper_type;

int main() { 
  state_type x = { 10.0 , 1.0 , 1.0 }; // initial conditions
  integrate( lorenz , x , 0.0 , 25.0 , 0.1 , write_lorenz );
}
