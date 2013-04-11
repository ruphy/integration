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

IntegraleBase::IntegraleBase(real a, real b)
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

real IntegraleBase::getIntegral() const
{
    real integral;
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

real IntegraleBase::intervalli() const
{
    return m_intervalli;
}
