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

#include "esbase.h"

#include <iostream>
#include <string>

EsBase::EsBase()
{
    m_minIterations = 0;
    m_maxIterations = 0;
    m_execType = EsBase::Quadratic;

    std::cout.precision(std::numeric_limits<real>::digits10 + 1);
}

void EsBase::statRun()
{
    if (m_execType == Quadratic) {
        int sqrtMax = sqrt(m_maxIterations);
        for (int i = sqrt(m_minIterations); i <= sqrtMax; i++) {
            exec(pow(i, 2));
        }
    } else if (m_execType == Linear) {
        for (int i = m_minIterations; i <= m_maxIterations; i++) {
            exec(i);
        }
    }
}

void EsBase::setExecType(EsBase::ExecType execType)
{
    m_execType = execType;
}

void EsBase::setIterations(int min, int max)
{
    setMaxIterations(max);
    setMinIterations(min);
}

int EsBase::maxIterations()
{
    return m_maxIterations;
}

int EsBase::minIterations()
{
    return m_minIterations;
}

void EsBase::setMaxIterations(int max)
{
    m_maxIterations = max;
}

void EsBase::setMinIterations(int min)
{
    m_minIterations = min;
}

void EsBase::printHeader(const std::string &header)
{
    std::cout << header << std::endl;
}
