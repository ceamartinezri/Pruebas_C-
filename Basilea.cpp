
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;


double cuadratica(int a, int b)
{

    double sum =0.0;
    double aux =0.0;
    for (int k=a;k<=b;k++)
    {
        aux = 1/pow(k, 2);
        sum = sum + aux;
        std::cout<<"aux: "<<aux<<"sum: "<<sum<<std::endl;
    }

  
  return sum;
}



int main()
{
    int a = 10;
    int b = 1500;
    double suma = cuadratica (a,b);
    printf("El valor de la suma es %5.4f", suma);
    std::cin.get();
    return 0;
}
