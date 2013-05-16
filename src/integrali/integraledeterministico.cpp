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

real f_test(real x)
{
    return (exp(x)+1+pow(x,9)-8*pow(x,8)+sinh(5*x))*exp(-pow(x,2));
}

IntegraleDeterministico::IntegraleDeterministico(int a, int b)
  : IntegraleBase(a, b)
{
    setIntervalli(10);
    std::cout.precision(std::numeric_limits<real>::digits10 + 1);

    m_f.assign("417.8077683550236335115029616847558823314866942");
    setMinIterations(2);
    setMaxIterations(pow(10, 6));
    setExecType(EsBase::Quadratic);

    printHeader("intervalli,trapezi,simpson,gauss");
}

void IntegraleDeterministico::exec(int n)
{
    setIntervalli(n);
    print(n, abs(trapezi()-m_f), abs(simpson()-m_f), abs(m_f-gauss()));
}

real IntegraleDeterministico::trapezi()
{
    resetIntegral();

    for (int i = 0; i < intervalli(); i++) {
        add( h()/2 * (f_test(x_i(i)) + f_test(x_i(i+1)) ) );
    }

    return getIntegral();
}

real IntegraleDeterministico::simpson()
{
    resetIntegral();

    for (int i = 0; i < intervalli()-1; i+=2) {
        add( h()/3 * (f_test(x_i(i)) + 4*f_test(x_i(i+1)) + f_test(x_i(i+2)) ) );
    }

    return getIntegral();
}

real IntegraleDeterministico::gauss()
{
    resetIntegral();


    real omega1 = ((real)128.)/225;
    real omega23 = ((322+13*sqrt((real)70))/900);
    real omega45 = ((322-13*sqrt((real)70))/900);

    real xi23 = ( ((real)1) /3)*sqrt(5-2*sqrt( (real)(10./7) ));
    real xi45 = ( ((real)1) /3)*sqrt(5+2*sqrt( (real)(10./7) ));

//     std::cout << xi23 << std::endl;
//     std::cout << " 1: " << omega1 << " - 2: " << omega23 << " - 3: " << omega45 << std::endl;

    for (int i = 0; i < intervalli(); i++) {

        real c = (x_i(i+1)+x_i(i))/2.;
        real m = (x_i(i+1)-x_i(i))/2.;

        // http://mathworld.wolfram.com/Legendre-GaussQuadrature.html


        add( m*omega1*f_test(c) ); // root = 0

        add( m*omega23*f_test(c - m*xi23) );
        add( m*omega23*f_test(c + m*xi23) );

        add( m*omega45*f_test(c - m*xi45) );
        add( m*omega45*f_test(c + m*xi45) );
    }

    return getIntegral();
}
