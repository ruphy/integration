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
    resetIntegral();

    // "Mersenne Twister: A 623-dimensionally equidistributed uniform pseudo-random
    // number generator", Makoto Matsumoto and Takuji Nishimura, ACM Transactions
    // on Modeling and Computer Simulation: Special Issue on Uniform Random Number
    // Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
    m_gen = new boost::random::mt19937(time(0) + getpid());

    // Statistica
//     for (int i = 100; i < pow(10, 8); i += 100) {
//         m_n = i;
//         std::cout.precision(std::numeric_limits<double>::digits10 + 1);
//         std::cout << "[" <<  i << ", " << run() - 417.8077704440582 << "]," << std::endl;
//     }

    for (int i = 1000; i < pow(10, 8); i += 1000*log(i/2)) {
        m_n = i;
        statRun();
    }
}

void IntegraleMC::statRun()
{
    boost::random::uniform_real_distribution<double> dist(0, 1);

    double intMean = 0;
    double intErr = 0;
    unsigned int jmax = 30;

    // 30 run per ogni n, così da avere risultati più stabili
    for (int j = 0; j < jmax; j++) {
        double mean = 0;
        double stddev = 0;
        double sigmaI = 0;

        for (int i = 0; i < m_n; i++) {
            double fxi = f_mc(m_a + (m_b - m_a) * dist(*m_gen)) * (m_b - m_a);
            add(fxi);

            // Errori di arrotondamento nel calcolo dell'incertezza sono trascurabili
            sigmaI += pow(fxi, 2);
        }

        mean = (getIntegral() / m_n);
        sigmaI = sqrt(sigmaI/m_n-pow(mean,2));
        stddev = (m_b - m_a)*sigmaI/sqrt(m_n);

//         std::cout << stddev <<std::endl;

        intMean += mean;
        intErr += pow(stddev, 2); // somma in quadrature

        resetIntegral();
    }

    intErr = sqrt(intErr)/jmax;
    intMean = intMean/jmax;

    std::cout.precision(std::numeric_limits<double>::digits10 + 1);
    std::cout << "[" <<  m_n << "," << intMean << "," << intErr << "]," << std::endl;

}

double IntegraleMC::run()
{
    boost::random::uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < m_n; i++) {
        add(f_mc(m_a + (m_b - m_a) * dist(*m_gen)) * (m_b - m_a));
    }
    return (getIntegral() / m_n);
}

void IntegraleMC::resetIntegral()
{
    for (int i = 0; i < DOUBLEEXP; i++) {
        m_partialIntegral[i] = 0;
    }
}

void IntegraleMC::add(double value)
{
    int i;
    //extracting the exponent
    double result = frexp(value , &i);

    // let's ensure we sum with same orders of magnitude
    m_partialIntegral[i + 1022] += value;
}

double IntegraleMC::getIntegral()
{
    double integral;
    for (int i = 0; i < DOUBLEEXP; i++) {
        integral += m_partialIntegral[i];
    }
    return integral;
}


