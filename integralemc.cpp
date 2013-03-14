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


#include "integralemc.h"

#include <iostream>
#include <math.h>
#include <time.h>

#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

double f_mc(double x)
{
    return (exp(x)+1+pow(x,9)-8*pow(x,8)+sinh(5*x))*exp(-pow(x,2));
}

IntegraleMC::IntegraleMC(double a, double b)
    : m_a(a),
      m_b(b)
{
    m_gen = new boost::random::mt19937(time(0) + getpid());
    m_n = 1000000;
    std::cout << run() << std::endl;
}

double IntegraleMC::run()
{
    boost::random::uniform_real_distribution<double> dist(0, 1);

    double integrale = 0.;

    for (int i = 0; i < m_n; i++) {
        integrale += f_mc( m_a + (m_b-m_a)*dist(*m_gen))*(m_b-m_a) ;//(dist(*m_gen)-m_a)/(m_b-m_a) );
    }
    return (integrale/m_n);
}


