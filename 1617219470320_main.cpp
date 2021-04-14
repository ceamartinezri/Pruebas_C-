#include <iostream>
#include <cmath>

using fptr = double (double, double, int); // apuntador de función

double f(double x);//Función para integrar en x
double integralreal(double a, double b);//Integración real sin método númerico
double velocidadfinal(double m, double W); //Cálculo de la velocidad final
double trapecio(double a, double b, int npart);//Integración método númerico trapecio
double simpson(double a, double b, int npart);//Integración  método númerico Simpson
double delta(double a, double b);//Cálculo error porcentual


int main (int argc, char *argv[]){
std::cout.precision(15);
std::cout.setf(std::ios::scientific);

    //DATOS 
    const double m = 1.25;//Masa
    double x_i = 0.0;//Desplazamiento inicial
    double x_f = 4.0;//Desplazamiento final 
    
    int p1 = 10;//partrición 1
    int p2 = 1000;//partición 2

    //TRABAJO
    double Wt1 = trapecio(x_i,x_f,p1); //Trabajo metodo trapecio partición 1
    double Wt2 = trapecio(x_i,x_f,p2); //Trabajo metodo trapecio partición 2
    double Ws1 = simpson(x_i,x_f,p1); //Trabajo metodo simpson partición 1
    double Ws2 = simpson(x_i,x_f,p2); //Trabajo metodo simpson partición 2
    double W = integralreal(x_i,x_f); //Trabajo Real

    //VELOCIDAD FINAL
    double vt1 = velocidadfinal(m,Wt1); //velocidad final método trapecio partición 1
    double vt2 = velocidadfinal(m,Wt2); //velocidad métoto trapecio partición 2
    double vs1 = velocidadfinal(m,Ws1); //velocidad final método simpson partición 1
    double vs2 = velocidadfinal(m,Ws2); //velocidad final método simpson partición 2
    double v = velocidadfinal(m,W); //velocidad final real

    //Error porcentual
    double ert1= delta(v,vt1); //error del método de trapecio con partición 1
    double ert2= delta(v,vt2); //error del método de trapecio con partición 2
    double ers1= delta(v,vs1); //error del método de simpson con partición 1
    double ers2= delta(v,vs2); //error del método de simpson con partición 2

//________________________________________________________
    //Imprime en pantalla los resultados
    std::cout << "Las velocidades son:"  <<"\n" ;
    std::cout << "V1: " << vt1 <<"\n"; //velocidad final metodo trapecio partición 1
    std::cout << "V2: " << vt2 <<"\n"; //velocidad final metodo trapecio partición 2
    std::cout << "V3: " << vs1 <<"\n"; //velocidad final metodo simpson  partición 1
    std::cout << "V4: " << vs2 <<"\n"; //velocidad final metodo simpson  partición 2
    std::cout << "Vel abs: " << v  <<"\n"; //velocidad final método integral real
    
    std::cout.precision(15);
    std::cout.setf(std::ios::scientific);
    //Errores
    std::cout << "\n" << "Los Errores son:"  <<"\n" ;
    std::cout << "\n" << "para N=" << p1 << "\t" <<"Trap1: " << ert1 ; //error trapecio partición 1
    std::cout << "\t" <<"Simp1 :" << ers1 <<"\n"; //error simpson partición 1
    std::cout << "\n" << "para N=" << p2 << "\t" <<"Trap2: " << ert2 ; //error trapecio partición 2
    std::cout << "\t" <<"Simp2: " << ers2 <<"\n"; //error simpson partición 2

    system("pause");
    return 0;
}


//Función a integrar
double f(double x){
return 2*x*std::sin(x);
}

//Integral real para comparar
double integralreal(double a, double b){
    auto f = [](double x){return 2*(std::sin(x)-(x*std::cos(x)));};
    double IntEv= f(b)-f(a);
    return IntEv;
}

// Integracion método númerico trapecio - código clase
double trapecio(double a, double b, int npart){

    double h = (b-a)/npart;
    double result = 0.0;
    double x = 0.0;
    for (int ii = 1; ii < npart; ++ii){
        x = a + ii*h;
        result += f(x);
    }
    result += 0.5*(f(a)+f(b));
    result *= h;
    return result;
}


//Integración método númerico Simpson - código clase
double simpson(double a, double b, int npart)
{
    
    double h=(b-a)/npart;
    double result = f(a)+f(b);
    double sum1=0.0;
    double sum2=0.0;
    for(int ii = 1; ii < npart/2; ++ii){
        double x = a + (2*ii)*h;
        sum1 += f(x);
    }
    for(int ii = 1; ii <= npart/2; ++ii){
        double x = a + (2*ii - 1)*h;
        sum2 += f(x);
    }
    result += 2*sum1 + 4*sum2;
    result *= h/3;
    return result;
}


//Velocidad final 
double velocidadfinal(double m, double W){
    double v = sqrt((2/m)*W);
    return v;
}


//Cálculo de error porcentual
double delta(double a, double b){
    double d=(std::abs(b-a)/a)*100;
    return d;
}

