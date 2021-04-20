#include <iostream>
#include <cmath>

using fptr = double (double); // puntero de funcion con forma : double function(double x);

const double M = 68.1;
const double G = 9.81;
const double VT = 40;
const double T = 10;

double f(double x);
double fderiv(double x);
double g(double x);

// retorna la raiz, que es un double
// fptr es un apuntador a funcion del tipo
// using fptr = double(double)
// por ejemplo
double bisection(double xl, double xu, double eps, fptr func, int nmax, int & nsteps);
double regulafalsi(double xl, double xu, double eps, fptr func, int nmax, int & nsteps);
double fixedpoint(double x0, double eps, fptr func, int nmax, int & nsteps);
double newton(double x0, double eps, fptr func, fptr deriv, int nmax, int & nsteps);
double secant(double xl, double xu, double eps, fptr func, int nmax, int & nsteps);

int main (int argc, char *argv[])
{
   // double XL = std::atof(argv[1]);
    double XL = 30;
   // double XU = std::atof(argv[2]);
    double XU =10;
    double eps = 0;
    int NMAX = 1000;
        for (int ii =1; ii<=9; ++ii){
    double eps = std::pow(10.0,-ii);

    std::cout.precision(2); std::cout.setf(std::ios::scientific);
    int steps = 0;
    double root = bisection(XL, XU, eps, f, NMAX, steps);
    std::cout << "\t" << root << "\t" << eps << "\t" << steps << "\n";

    root = regulafalsi(XL, XU, eps, f, NMAX, steps);
    std::cout << "\t" << root << "\t" << eps << "\t" << steps << "\n";

    root = fixedpoint(XL, eps, g , NMAX, steps);
    std::cout << "\t" << root << "\t" << eps << "\t" << steps << "\n";

    root = newton(XL, eps, f, fderiv, NMAX, steps);
    std::cout << "\t" << root << "\t" << eps << "\t" << steps << "\n";

    root = secant(XL, XU, eps, f, NMAX, steps);
    std::cout << "\t" << root << "\t" << eps << "\t" << steps << "\n";
    
    std::cout << '\n';
    }
    

    system("pause");
    return 0;
}

double f(double x)
{
    return M*G*(1 - std::exp(-x*T/M))/x - VT;
}

double fderiv(double x)
{
    double h = 0.001;
    return (f(x+h/2) - f(x-h/2))/h;
}

double g(double x)
{
    return M*G*(1 - std::exp(-x*T/M))/VT;
}


double bisection(double xl, double xu, double eps, fptr func, int nmax, int & nsteps)
{
    nsteps = 0;
    double xr = xl;
    do {
        xr = 0.5*(xl + xu);
        nsteps++;
        //std::cout << xr << "\n";
        if (std::fabs(func(xr)) < eps) {
            break;
        } else if (func(xl)*func(xr) < 0) {
            xu = xr;
        } else {
            xl = xr;
        }
        //std::cout << xl << "\t" << xu << "\n";
    } while (nsteps <= nmax);
    return xr;
}


double regulafalsi(double xl, double xu, double eps, fptr func, int nmax, int & nsteps)
{
    nsteps = 0;
    double xr = xl;
    do {
        double fxu = func(xu);
        double fxl = func(xl);
        xr = xu - (fxu*(xl -xu))/(fxl - fxu);
        nsteps++;
        //std::cout << xr << "\n";
        if (std::fabs(func(xr)) < eps) {
            break;
        } else if (fxl*func(xr) < 0) {
            xu = xr;
        } else {
            xl = xr;
        }
        //std::cout << xl << "\t" << xu << "\n";
    } while (nsteps <= nmax);
    return xr;
}
double fixedpoint(double x0, double eps, fptr func, int nmax, int & nsteps)
{
    nsteps = 0;
    double xr = x0;
    while(nsteps <= nmax) {
        if (std::fabs(func(xr) - xr) < eps) {
            break;
        } else {
            xr = func(xr); // NOTE: func es g(x), no f(x)
        }
        nsteps++;
    }

    return xr;
}
double newton(double x0, double eps, fptr func, fptr deriv, int nmax, int & nsteps)
{
    nsteps = 0;
    double xr = x0;
    while(nsteps <= nmax) {
        if (std::fabs(func(xr)) < eps) {
            break;
        } else {
            xr = xr - func(xr)/deriv(xr);
        }
        nsteps++;
    }

    return xr;
}

double secant(double xl, double xu, double eps, fptr func, int nmax, int & nsteps)
{
    nsteps = 0;
    double xr = 0;
    do {
        //Calculando el valor intermedio
        double fxu = func(xu);
        double fxl = func(xl);
        xr = xu - (fxu*(xl -xu))/(fxl - fxu);
        nsteps++;
        //std::cout << xr << "\n";
        if (std::fabs(func(xr)) < eps) {
            break;
        } else if (fxl*func(xr) < 0) {
            xl = xu;
            xu = xr;
        } else {
            xl=xr;
        }
        //std::cout << xl << "\t" << xu << "\n";
    } while (nsteps <= nmax);
    return xr;
}