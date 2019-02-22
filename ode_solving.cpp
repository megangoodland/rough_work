// we solve the simple ODE x’ = 3/(2t^2) + x/(2t) * with initial condition x(1) = 0.
// Analytic solution is x(t) = sqrt(t) - 1/t 

#include <iostream>
#include <boost/numeric/odeint.hpp>
using namespace boost::numeric::odeint;

void rhs(const double x, double &dxdt, const double t) { 
  dxdt = 3.0/(2.0*t*t) + x/(2.0*t);
}

void write_cout(const double &x, const double t) { 
  std::cout << t << ’\t’ << x << std::endl;
}

typedef runge_kutta_dopri5 <double > stepper_type;

int main() { 
  double x = 0.0;
  integrate_adaptive(
      make_controlled(1E-6, 1E-6, stepper_type()), rhs, x, 1.0, 10.0, 0.1, write_cout);
}
