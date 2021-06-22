#ifdef SPARC
#define gsl_ran_gaussian gsl_ran_gaussian_ratio_method
#endif
#ifdef INTEL
#define gsl_ran_gaussian my_gaussian
#endif

#include <iostream>
#include <gsl/gsl_sf_bessel.h>


int main(int argc, char* argv[])
{
	double x = 5.0;
	double y = gsl_sf_bessel_J0(x);
	std::cout << "J0(" << x <<") = " << y << std::endl; 


	return 0;
}
