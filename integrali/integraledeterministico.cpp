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

    std::cout << "L'integrale della funzione con il metodo dei trapezi e'" << std::endl;
    std::cout << trapezi() << std::endl;
    std::cout << std::endl;

    std::cout << "L'integrale della funzione con il metodo di Simpson e'" << std::endl;
    std::cout << simpson() << std::endl;
    std::cout << std::endl;

    std::cout << "L'integrale della funzione con il metodo delle quadrature gaussiane e'" << std::endl;
    std::cout << gauss() << std::endl;
    std::cout << std::endl;


    std::cout.precision(std::numeric_limits<real>::digits10 + 1);

    real f = 417.80776835502343637108613;

    // Statistica
    for (int i = 100; i <= pow(10, 4); i+= 10) {
        setIntervalli(i);
        std::cout << "[" << i << ", " << abs(trapezi()-f) << ", " << abs(simpson()-f) << ", " <<
                    abs(gauss()-f) << "]," << std::endl;
//         std::cout << simpson() << std::endl;
    }

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

    real xi23 = (1./3)*sqrt(5-2*sqrt((real)10./7));
    real xi45 = (1./3)*sqrt(5+2*sqrt((real)10./7));

    std::cout << " 1: " << omega1 << " - 2: " << omega23 << " - 3: " << omega45 << std::endl;

    for (int i = 0; i < intervalli(); i++) {

        real c = (x_i(i+1)+x_i(i))/2.;
        real m = (x_i(i+1)-x_i(i))/2.;

        // http://mathworld.wolfram.com/Legendre-GaussQuadrature.html
        //
        // roots    weights
        // 0.0   0.56888889
        // +-0.53846931 0.47862867
        // +-0.90617985 0.23692689


        add( m*omega1*f_test(c) ); // root = 0

        add( m*omega23*f_test(c - m*xi23) );
        add( m*omega23*f_test(c + m*xi23) );

        add( m*omega45*f_test(c - m*xi45) );
        add( m*omega45*f_test(c + m*xi45) );
    }

    return getIntegral();
}
