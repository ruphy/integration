/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2013  Riccardo Iaconelli <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "serie.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits>
#include <string>
// #include <lexical_cast>

// using namespace std;

Serie::Serie()
{
    std::cout << "---------------------" << std::endl;
    std::cout << "Esercizio delle serie" << std::endl;
    std::cout << "---------------------" << std::endl;
    run();
}


float Serie::sommaCrescente(int N)
{
    float somma = 0;
    for (int i = 1; i <= N; i++) {
        somma += 1./pow(i, 2);
    }
    return somma;
}

float Serie::sommaDecrescente(int N)
{
    float somma = 0;
    for (int i = N; i >= 1; i--) {
        somma += 1./pow(i, 2);
    }
    return somma;
}

#define EXPECTED 1.64493406685

void Serie::run()
{
    int N = pow(2,30);
    
//     std::cout.precision(std::numeric_limits<float>::digits10 + 1);
//     std::cout.precision(7);
//     std::cout << std::numeric_limits<float>::digits10 + 1 << endl;
    
    std::cout << "Risultato del calcolo" << std::endl;
    float somma1 = sommaCrescente(N);
    std::cout << "Somma crescente 1->" << N << ": " << somma1 << std::endl;
    
    float somma2 = sommaDecrescente(N);   
    std::cout << "Somma decrescente " << N << "->1: " << somma2 << std::endl;
    
    std::cout << std::endl;
    std::cout << "Differenza tra le somme: "  << somma1 - somma2 << std::endl;
    std::cout << std::endl;
    std::cout << "Errore della somma crescente: " << somma1 - EXPECTED << std::endl;
    std::cout << "Errore della somma decrescente: " << somma2 - EXPECTED << std::endl;
    std::cout << std::endl;
}

