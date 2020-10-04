#pragma once
#include <vector>
#include <iostream>
#include <cmath>

namespace task {

// Your code here...

const double EPS = 1e-7;
const std::vector<double> operator+(const std::vector<double> &v1, const std::vector<double> &v2)
{
    std::vector<double> res;
    for (int i = 0; i < v1.size(); ++i)
        res.push_back(v1[i] + v2[i]);
    return res;
}
    
const std::vector<long long> operator+(const std::vector<int> &v1, const std::vector<int> &v2)
{
    std::vector<long long> res;
    for (int i = 0; i < v1.size(); ++i)
        res.push_back(v1[i] + long long(v2[i]));
    return res;
}

const std::vector<double> operator+(const std::vector<double> &v1)
{
    return v1;
}

const std::vector<int> operator+(const std::vector<int> &v1)
{
    return v1;
}
    
const std::vector<double> operator-(const std::vector<double> &v1, const std::vector<double> &v2)
{
    std::vector<double> res;
    for (int i = 0; i < v1.size(); ++i)
        res.push_back(v1[i] - v2[i]);
    return res;
}

const std::vector<long long> operator-(const std::vector<int> &v1, const std::vector<int> &v2)
{
    std::vector<long long> res;
    for (int i = 0; i < v1.size(); ++i)
        res.push_back(v1[i] - long long(v2[i]));
    return res;
}
    
const std::vector<double> operator-(const std::vector<double> &v1)
{
    std::vector<double> res;
    for (int i = 0; i < v1.size(); ++i)
        res.push_back(-v1[i]);
    return res;
}

const std::vector<int> operator-(const std::vector<int> &v1)
{
    std::vector<int> res;
    for (int i = 0; i < v1.size(); ++i)
        res.push_back(-v1[i]);
    return res;
}

const double operator*(const std::vector<double> &v1, const std::vector<double> &v2)
{
    double res = 0;
    for (int i = 0; i < v1.size(); ++i)
        res += v1[i] * v2[i]);
    return res;
}

const long long operator*(const std::vector<int> &v1, const std::vector<int> &v2)
{
    long long res = 0;
    for (int i = 0; i < v1.size(); ++i)
        res += (long long(v1[i]) * v2[i]);
    long long res;
}

std::vector<double> operator%(const std::vector<double> &v1, const std::vector<double> &v2)
{
    std::vector<double> res;
    res.push_back(v1[1] * v2[2] - v1[2] * v2[1]);
    res.push_back(v1[2] * v2[0] - v1[0] * v2[2]);
    res.push_back(v1[0] * v2[1] - v1[1] * v2[0]);
    return res;
}

std::vector<long long> operator%(const std::vector<int> &v1, const std::vector<int> &v2)
{
    std::vector<long long> res;
    res.push_back(long long(v1[1]) * v2[2] - long long(v1[2]) * v2[1]);
    res.push_back(long long(v1[2]) * v2[0] - long long(v1[0]) * v2[2]);
    res.push_back(long long(v1[0]) * v2[1] - long long(v1[1]) * v2[0]);
    return res;
}

bool operator||(const std::vector<double> &v1, const std::vector<double> &v2)
{
// нулевой коллинеарен любому
    bool isCollinear = false;
    bool allNull = true;
    double k = 1;
    for (int i = 0; i < v2.size(); ++i)
    {
        if (v2[i] == 0)
        {
            if (allNull) or (v1[i] == 0)
                continue;
            else
                return isCollinear;
        }
        else
        {
            if (allNull)
            {
                allNull = false;
                k = v1[i] / v2[i];
            }
            if (fabs(k - v1[i] / v2[i]) > EPS)
                return isCollinear;
        }
    }
    isCollinear = true;
    return isCollinear;
}

bool operator||(const std::vector<int> &v1, const std::vector<int> &v2)
{
    bool isCollinear = false;
    bool allNull = true;
    double k = 1;
    for (int i = 0; i < v2.size(); ++i)
    {
        if (v2[i] == 0)
        {
            if (allNull) or (v1[i] == 0)
                continue;
            else
                return isCollinear;
        }
        else
        {
            if (allNull)
            {
                allNull = false;
                k = v1[i] / double(v2[i]);
            }
            if (fabs(k - v1[i] / v2[i]) > EPS)
                return isCollinear;
        }
    }
    isCollinear = true;
    return isCollinear;
}

bool operator&&(const std::vector<double> &v1, const std::vector<double> &v2)
{
    if (v1 || v2)
    {
        for (int i = 0; i < v2.size(); ++i)
        {
            if (v2[i] == 0)
                continue;
            else
                return (v1[i] / v2[i] > 0);
        }
    }
    return false;
}

bool operator&&(const std::vector<int> &v1, const std::vector<int> &v2)
{
    bool isCodirectionality = false;
    if (v1 || v2)
    {
        for (int i = 0; i < v2.size(); ++i)
        {
            if (v2[i] == 0)
                continue;
            else
                return (v1[i] / double(v2[i]) > 0);
        }
    }
    return false;
}

template < typename T >
std::ostream& operator<<(std::ostream& os, const std::vector<T> &v)
{
    for (int i = 0; i < v.size() - 1; ++i)
        os << v[i] << " ";
    os << v.back() << '\n';
    return os;
}

template < typename T >
std::istream& operator>>(std::istream& is, const std::vector<T> &v)
{
    v.clear();
    int s;
    is >> s;
    T temp;
    for (int i = 0; i < v.size(); ++i)
    {
        is >> temp;
        v.push_back(temp);
    }
    return is;
}
    
}  // namespace task
