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

void rhs(const double x, double &dxdt, const double t) { 
  dxdt = 3.0/(2.0*t*t) + x/(2.0*t);
}

void write_cout(const double &x, const double t) { 
  cout << t << "\t" << x << endl;
}

typedef runge_kutta_dopri5 <double > stepper_type;

int main() { 
  double x = 0.0;
  
  integrate_adaptive(
      make_controlled(1E-6, 1E-6, stepper_type()), rhs, x, 1.0, 10.0, 0.1, write_cout);
}
