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

real f_mc(real x)
{
    return (exp(x) + 1 + pow(x, 9) - 8 * pow(x, 8) + sinh(5 * x)) * exp(-pow(x, 2));
}

IntegraleMC::IntegraleMC(real a, real b)
    : IntegraleBase(a, b)
{
    // "Mersenne Twister: A 623-dimensionally equidistributed uniform pseudo-random
    // number generator", Makoto Matsumoto and Takuji Nishimura, ACM Transactions
    // on Modeling and Computer Simulation: Special Issue on Uniform Random Number
    // Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
    m_gen = new boost::random::mt19937(time(0) + getpid());

    for (int i = 1000; i < pow(10, 8); i += 1000*log(i/2)) {
        m_n = i;
        statRun();
    }
}

void IntegraleMC::statRun()
{
    boost::random::uniform_real_distribution<real> dist(0, 1);

    real intMean = 0;
    real intErr = 0;
    unsigned int jmax = 30;

    // 30 integrazioni per ogni n, valutiamo poi la media e la dev std,
    // così da avere risultati più stabili
    for (int j = 0; j < jmax; j++) {
        real mean = 0;
        real stddev = 0;
        real sigmaI = 0;

        for (int i = 0; i < m_n; i++) {
            real fxi = f_mc(m_a + (m_b - m_a) * dist(*m_gen)) * (m_b - m_a);
            add(fxi);

            // Errori di arrotondamento nel calcolo dell'incertezza sono trascurabili
            sigmaI += pow(fxi, 2);
        }

        mean = (getIntegral() / m_n);
        sigmaI = sqrt(sigmaI/m_n-pow(mean,2));
        stddev = (m_b - m_a)*sigmaI/sqrt(m_n);

        intMean += mean;
        intErr += pow(stddev, 2); // somma in quadrature

        resetIntegral();
    }

    intErr = sqrt(intErr)/jmax;
    intMean = intMean/jmax;

    std::cout.precision(std::numeric_limits<real>::digits10 + 1);
    std::cout << "[" <<  m_n << "," << intMean << "," << intErr << "]," << std::endl;

}

real IntegraleMC::run()
{
    boost::random::uniform_real_distribution<real> dist(0, 1);

    for (int i = 0; i < m_n; i++) {
        add(f_mc(m_a + (m_b - m_a) * dist(*m_gen)) * (m_b - m_a));
    }
    return (getIntegral() / m_n);
}
