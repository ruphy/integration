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


#include "integraledeterministico.h"

#include <iostream>
#include <math.h>
#include <limits>

double f_test(double x)
{
    return (exp(x)+1+pow(x,9)-8*pow(x,8)+sinh(5*x))*exp(-pow(x,2));
}

IntegraleDeterministico::IntegraleDeterministico()
{
    m_a = 1;
    m_b = 10;
    setIntervalli(10);


    std::cout << "L'integrale della funzione con il metodo dei trapezi e'" << std::endl;
    std::cout << trapezi() << std::endl;
    std::cout << std::endl;

    std::cout << "L'integrale della funzione con il metodo di Simpson e'" << std::endl;
    std::cout << simpson() << std::endl;
    std::cout << std::endl;

    std::cout << "L'integrale della funzione con il metodo delle quadrature gaussiane e'" << std::endl;
    std::cout << gauss() << std::endl;
    std::cout << std::endl;


    std::cout.precision(std::numeric_limits<double>::digits10 + 1);
//     std::cout.precision(7);
//     std::cout << std::numeric_limits<double>::digits10 + 1 << std::endl;

    // Statistica
    for (int i = 0; i <= 1000; i++) {
        setIntervalli(i);
        std::cout << i << " " << trapezi() << " " << simpson() << " " << gauss() << std::endl;
    }

}

double IntegraleDeterministico::trapezi()
{
    double integrale = 0;
    for (int i = 0; i < m_intervalli; i++) {
        integrale += m_l/2 * (f_test(x_i(i)) + f_test(x_i(i+1)) ) ;
    }
    return integrale;
}

double IntegraleDeterministico::simpson()
{
    double integrale = 0;
    for (int i = 0; i < m_intervalli-1; i+=2) {
        integrale += m_l/3 * (f_test(x_i(i)) + 4*f_test(x_i(i+1)) + f_test(x_i(i+2)) ) ;
    }
    return integrale;
}

double IntegraleDeterministico::gauss()
{
    double integrale = 0;

    for (int i = 0; i < m_intervalli; i++) {

        double c = (x_i(i+1)+x_i(i))/2.;
        double m = (x_i(i+1)-x_i(i))/2.;

        //roots    weights
        // 0.0   0.56888889
        // +-0.53846931 0.47862867
        // +-0.90617985 0.23692689

        integrale += m*0.56888889*f_test(c); // root = 0

        integrale += m*0.47862867*f_test(c - m*0.53846931);
        integrale += m*0.47862867*f_test(c + m*0.53846931);

        integrale += m*0.23692689*f_test(c - m*0.90617985);
        integrale += m*0.23692689*f_test(c + m*0.90617985);
    }

    return integrale;
}

void IntegraleDeterministico::setIntervalli(int intervalli)
{
    m_intervalli = intervalli;
    m_l = (m_b-m_a)/m_intervalli; // Larghezza dell'intervallo
}

double IntegraleDeterministico::x_i(int i)
{
    return (m_a + m_l*i);
}
