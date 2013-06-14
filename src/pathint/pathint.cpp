/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2013  Riccardo Iaconelli <riccardo@kde.org>

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


#include "pathint.h"

// #include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>

#include <functional>
#include <numeric>


#include "sweeper.h"

PathInt::PathInt()
 : m_sweeper(new Sweeper)
{
    setExecType(EsBase::Linear);
    setMaxIterations(1000); // n of sweeps
    setMinIterations(1);

    m_sweeper->setTotalSweeps(maxIterations());
//     printHeader("n,S");
}

PathInt::~PathInt()
{
    delete m_sweeper;
}

void PathInt::exec(int sweepN)
{
    m_sweeper->doSweep();
//     print(sweepN, m_sweeper->S());

    if (sweepN == maxIterations()) {

        double *meanCorr = m_sweeper->meanCorrelator();
        for (int i = 0; i < m_sweeper->nElements(); i++) {
            print(i, meanCorr[i]);
        }

        std::vector<double> corr_0 = m_sweeper->corr_0();
        double meancorr_0 = meanCorr[0];
        double gamma0 = 0;

        for (int t = 0; t < 100; t++) {

            double variance = 0;

            for (int i = 0; i < sweepN - t; i++) {
                variance += corr_0[i]*corr_0[i+t]/(sweepN-t);
            }

            variance -= pow(meancorr_0, 2.0);

            if (t == 0) {
                gamma0 = variance;
            }

//             print(t, variance/gamma0);
        }

        for (int i = 0; i < m_sweeper->nElements(); i++) {
            std::vector<double> v = m_sweeper->get_cluster(i);
            double sum = std::accumulate(v.begin(), v.end(), 0.0);
            double mean = sum / v.size();

            double stddev = 0.0;
            for (std::vector<double>::iterator j = v.begin(); j != v.end(); j++) {
                stddev += std::pow(*j-mean, 2);
            }
            stddev *= (double)(m_sweeper->nElements()-1)/m_sweeper->nElements();
//             double sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
//             double stdev = std::sqrt(sq_sum / v.size() - mean * mean);
//             print(i, mean, stddev);
        }

        for (int t = 1; t < 7; t++) {
            // Delta E
            // t between 2 and n-1
            std::vector<double> Ek;
            for (int i = 0; i < m_sweeper->nElements(); i++) {
                if (i > 0 and i < 5) {
                    double deltaEi = m_sweeper->get_cluster(t+1)[i]+m_sweeper->get_cluster(t-1)[i];
                    deltaEi /= 2*m_sweeper->get_cluster(t)[i];
                    deltaEi = acosh(deltaEi);
                    Ek.push_back(deltaEi);
                }
            }
            double sum = std::accumulate(Ek.begin(), Ek.end(), 0.0);
            double mean = sum / Ek.size();

            double variance = 0.0;
            for (std::vector<double>::iterator j = Ek.begin(); j != Ek.end(); j++) {
                variance += std::pow((*j)-mean, 2);

//                 print(1, (*j));
            }
            variance *= (double)(m_sweeper->nElements()-1)/m_sweeper->nElements();


//             print (t, mean, sqrt(variance));
        }

    }
}




