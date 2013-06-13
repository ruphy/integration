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


#include "agobuffon.h"

#include <iostream>

#include <boost/math/constants/constants.hpp>

AgoBuffon::AgoBuffon()
{
    m_gen = new boost::random::mt19937(time(0) + getpid());

//     for (int i = 1000; i < 10000; i += 1000) {
//         run(pow(i, 2), 1);
//     }
    for (float i = 0.1; i < 1.; i+=.01) {
        run(100000, i);
    }
}

void AgoBuffon::run(int n, float L)
{
    boost::random::uniform_real_distribution<float> distx(0, boost::math::constants::pi<float>());
    boost::random::uniform_real_distribution<float> disty(0, 1);

    m_L = L;

    float picalc;
    unsigned long int tempcalc = 0;

    for (int i = 0; i < n; i++) {
        float x = distx(*m_gen);
        float y = disty(*m_gen);
        tempcalc += tocco(x, y);
    }

//     debug(n);
    picalc = 2*m_L*n/(float)tempcalc;
    float sigma2 = (2*m_L/picalc)*(1-2*m_L/picalc);
    print(m_L,  sqrt(sigma2), picalc);
//     std::cout << picalc << std::endl;
}

inline
unsigned int AgoBuffon::tocco(float x, float y)
{
    if (y < sin(x)*m_L/2 or y > 1-sin(x)*m_L/2) {
        return 1;
    } else {
        return 0;
    }
}

