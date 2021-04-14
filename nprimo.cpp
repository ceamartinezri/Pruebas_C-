# include <iostream>
# include <cstdlib>
# include <cmath>
int isprime(int m);
int nthprime(int n);

int main(int argc, char *argv[])
{
int n; 
//const int n = std::atoi(argv[1]); // activar para enviarle el n al ejecutar el programa
std::cout << "Escribe el n-esimo primo a calcular: >> "; //desactivar si se envia n al ejecutar programa
std::cin >> n;   //desactivar si se envia n al ejecutar programa
std::cout << "El " <<n<<  " primo es: " << nthprime(n) << "\n";

system("pause");
return 0;
}


int isprime(int m)
{
// Esta funcion retorna 1 si m es primo, 0 en otro caso
// fill here

 if (m == 0 || m == 1 || m == 4) return false;
  for (int i = 2; i < m / 2; i++) 
  {
    if (m % i == 0) return false;
  }
  // Si no se pudo dividir por ninguno de los de arriba, sí es primo
  return true;
}





int nthprime(int n)
{
// esta funcion retorna el n-esimo primo, haciendo uso de isprime
// fill here


int contador =1;
int i = 1;

while(contador<n) 
{
    i=i+2;
  if (isprime(i)) 
  {
    //std::cout << i << " Es primo" << "\n" ;
    contador ++;
    
  } 
  else 
  {
    //std::cout << i << " NO es primo" << "\n" ;
   
  }
  
  //system("pause");
}

return i;

}