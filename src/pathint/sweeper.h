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


#ifndef SWEEPER_H
#define SWEEPER_H

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/math/constants/constants.hpp>

#include "../esbase.h"

#define N 64

class Sweeper
{
public:
    Sweeper();
    ~Sweeper();

    void doSweep();
    double S();

    double* meanCorrelator();
    int sweepsDone();

    void setTotalSweeps(int totalSweeps);

    // Returns a vector of lenght sweepsDone();
    // containing the correlator for physical time 3
    // at Markovian time [i]
    std::vector<double> corr_0();

    int nElements();

    std::vector<double> get_cluster(int i);

private:
    void reset();

    /**
     * Try to change the state of the i-th element
     */
    void changeState(int i);

    inline double deltaS(double xmin, double xi, double xplus, double b);
    inline bool acceptState(double xmin, double xi, double xplus, double b);

    double m_x[N];
    double m_xN[N];
    double m_correlator[N];
    double m_meanCorrelator[N];

    double m_M, m_W, m_A, m_Del;
    boost::random::mt19937* m_gen;
    
    std::vector<double> m_corr_0;

    int m_sweepsDone;
    int m_totalSweeps;
    int m_tau;
//     std::vector<double> m_binnedCorrelator[N];
    std::vector< std::vector<double> > m_binnedCorrelator;
    int m_totalBins;

};

bool Sweeper::acceptState(double xmin, double xi, double xplus, double b)
{
    double DS = pow(boost::math::constants::e<double>(), deltaS(xmin, xi, xplus, b));
    if (DS >= 1) {
        return true;
    } else {
        boost::random::uniform_real_distribution<double> dist(0, 1);
        return DS > dist(*m_gen);
    }
}

double Sweeper::deltaS(double xmin, double xi, double xplus, double b)
{
    double U = m_M*pow(m_W, 2)*(pow(b,2) - pow(xi, 2))/2;
    double Tb = pow((b-xmin)/m_A, 2) + pow((b-xplus)/m_A, 2);
    double Ta = pow((xplus-xi)/m_A, 2) + pow((xmin-xi)/m_A, 2);
    return -m_A*(U)-m_A*m_M*(Tb-Ta)/2;
}

#endif // SWEEPER_H
