#pragma once
#include <vector>
#include <iostream>

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
        res += v1[i] * v2[i]);
    long long res;
}

bool operator||(const std::vector<double> &v1, const std::vector<double> &v2)
{
    // my code
    return true;
}

bool operator||(const std::vector<int> &v1, const std::vector<int> &v2)
{
    // my code
    return true;
}


}  // namespace task
