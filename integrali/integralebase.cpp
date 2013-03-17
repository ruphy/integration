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


#include "integralebase.h"
#include <math.h>

IntegraleBase::IntegraleBase(double a, double b)
    : m_a(a),
      m_b(b)
{
    resetIntegral();
}


void IntegraleBase::resetIntegral()
{
    for (int i = 0; i < DOUBLEEXP; i++) {
        m_partialIntegral[i] = 0;
    }
}

void IntegraleBase::add(double value)
{
    int i;
    //extracting the exponent
    double result = frexp(value , &i);

    // let's ensure we sum with same orders of magnitude
    m_partialIntegral[i + 1022] += value;
}

double IntegraleBase::getIntegral() const
{
    double integral;
    for (int i = 0; i < DOUBLEEXP; i++) {
        integral += m_partialIntegral[i];
    }
    return integral;
}


void IntegraleBase::setIntervalli(int intervalli)
{
    m_intervalli = intervalli;
    m_l = (m_b-m_a)/m_intervalli; // Larghezza dell'intervallo
}

double IntegraleBase::x_i(int i) const
{
    return (m_a + m_l*i);
}

double IntegraleBase::h() const
{
    return m_l;
}

double IntegraleBase::intervalli() const
{
    return m_intervalli;
}
