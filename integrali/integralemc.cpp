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
    return (exp(x) + 1 + pow(x, 9) - 8 * pow(x, 8) + sinh(5 * x)) * exp(-pow(x, 2));
}

IntegraleMC::IntegraleMC(double a, double b)
    : m_a(a),
      m_b(b)
{
    for (int i = 0; i < DOUBLEEXP; i++) {
        m_partialIntegral[i] = 0;
    }

    // "Mersenne Twister: A 623-dimensionally equidistributed uniform pseudo-random
    // number generator", Makoto Matsumoto and Takuji Nishimura, ACM Transactions
    // on Modeling and Computer Simulation: Special Issue on Uniform Random Number
    // Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
    m_gen = new boost::random::mt19937(time(0) + getpid());

    // Statistica
    for (int i = 10; i < pow(10, 10); i *= 1.25) {
        m_n = i;
        std::cout.precision(std::numeric_limits<double>::digits10 + 1);
        std::cout << "[" <<  i << ", " << run() - 417.8077704440582 << "]," << std::endl;
    }
}

double IntegraleMC::run()
{
    boost::random::uniform_real_distribution<double> dist(0, 1);

    double integrale = 0.;

    for (int i = 0; i < m_n; i++) {
        integrale += f_mc(m_a + (m_b - m_a) * dist(*m_gen)) * (m_b - m_a);
    }
    return (integrale / m_n);
}

void IntegraleMC::add(double value)
{
    int i;
    //extracting the exponent
    double result = frexp(value , &i);

    // let's ensure we sum with same orders of magnitude
    m_partialIntegral[i+1022] += value;
}

double IntegraleMC::getIntegral()
{
    double integral;
    for (int i = 0; i < DOUBLEEXP; i++) {
        integral += m_partialIntegral[i];
    }
    return integral;
}


