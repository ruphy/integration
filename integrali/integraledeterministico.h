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


#ifndef INTEGRALEDETERMINISTICO_H
#define INTEGRALEDETERMINISTICO_H
#include "esbase.h"

class IntegraleDeterministico : public EsBase
{
public:
    IntegraleDeterministico(int a, int b);

    void setIntervalli(int intervalli);

private:
    double trapezi();
    double simpson();
    double gauss();

    /**
     * Ritorna il valore di x dell'intervallo i-esimo, dove
     * x_i(0) = a
     * x_i(intervalli) = b
     */
    double x_i(int i);

    const double m_a, m_b;
    double m_l;
    int m_intervalli;
};

#endif // INTEGRALEDETERMINISTICO_H
