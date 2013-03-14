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

double f_test(double x)
{
    return x+1;
}

IntegraleDeterministico::IntegraleDeterministico()
{
    intervalli = 10;
    a = 1;
    b = 10;

    l = (b-a)/intervalli; // Larghezza dell'intervallo


}

double IntegraleDeterministico::trapezi()
{
    double integrale = 0;
    for (int i = 0; i < intervalli; i++) {

        integrale += l/2 * (f_test(x_i(i)), f_test(x_i(i+1)) ) ;
    }
}

double IntegraleDeterministico::simpson()
{
    return 0;
}

double IntegraleDeterministico::gauss()
{
    return 0;
}

double IntegraleDeterministico::x_i(int i)
{
    return (a + l*i);
}
