#pragma once
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

namespace task {
    
    const double EPS_TASK = 1e-7;
    std::vector<double> operator+(const std::vector<double> &v1,
                                  const std::vector<double> &v2) {
        std::vector<double> res(v1.size());
        for (int i = 0; i < v1.size(); ++i)
            res[i] = v1[i] + v2[i];
        return res;
    }
    
    std::vector<int> operator+(const std::vector<int> &v1,
                               const std::vector<int> &v2) {
        std::vector<int> res(v1.size());
        for (int i = 0; i < v1.size(); ++i)
            res[i] = v1[i] + v2[i];
        return res;
    }
    
    std::vector<double> operator+(const std::vector<double> &v1) { return v1; }
    
    std::vector<int> operator+(const std::vector<int> &v1) { return v1; }
    
    std::vector<double> operator-(const std::vector<double> &v1,
                                  const std::vector<double> &v2) {
        std::vector<double> res(v1.size());
        for (int i = 0; i < v1.size(); ++i)
            res[i] = v1[i] - v2[i];
        return res;
    }
    
    std::vector<int> operator-(const std::vector<int> &v1,
                               const std::vector<int> &v2) {
        std::vector<int> res(v1.size());
        for (int i = 0; i < v1.size(); ++i)
            res[i] = v1[i] - v2[i];
        return res;
    }
    
    std::vector<double> operator-(const std::vector<double> &v1) {
        std::vector<double> res(v1.size());
        for (int i = 0; i < v1.size(); ++i)
            res[i] = -v1[i];
        return res;
    }
    
    std::vector<int> operator-(const std::vector<int> &v1) {
        std::vector<int> res(v1.size());
        for (int i = 0; i < v1.size(); ++i)
            res[i] = -v1[i];
        return res;
    }
    
    double operator*(const std::vector<double> &v1, const std::vector<double> &v2) {
        double res = 0;
        for (int i = 0; i < v1.size(); ++i)
            res += v1[i] * v2[i];
        return res;
    }
    
    int operator*(const std::vector<int> &v1, const std::vector<int> &v2) {
        int res = 0;
        for (int i = 0; i < v1.size(); ++i)
            res += v1[i] * v2[i];
        return res;
    }
    
    std::vector<double> operator%(const std::vector<double> &v1,
                                  const std::vector<double> &v2) {
        std::vector<double> res(3);
        res[0] = v1[1] * v2[2] - v1[2] * v2[1];
        res[1] = v1[2] * v2[0] - v1[0] * v2[2];
        res[2] = v1[0] * v2[1] - v1[1] * v2[0];
        return res;
    }
    
    std::vector<int> operator%(const std::vector<int> &v1,
                               const std::vector<int> &v2) {
        std::vector<int> res(3);
        res[0] = v1[1] * v2[2] - v1[2] * v2[1];
        res[1] = v1[2] * v2[0] - v1[0] * v2[2];
        res[2] = v1[0] * v2[1] - v1[1] * v2[0];
        return res;
    }
    
    bool operator||(const std::vector<double> &v1, const std::vector<double> &v2) {
        // нулевой коллинеарен любому
        bool isCollinear = false;
        bool allNull = true;
        double k = 1;
        for (int i = 0; i < v2.size(); ++i) {
            if (v2[i] == 0) {
                if ((allNull) or (v1[i] == 0))
                    continue;
                else
                    return isCollinear;
            } else {
                if (allNull) {
                    allNull = false;
                    k = v1[i] / v2[i];
                }
                if (fabs(k - v1[i] / v2[i]) > EPS_TASK)
                    return isCollinear;
            }
        }
        isCollinear = true;
        return isCollinear;
    }
    
    bool operator||(const std::vector<int> &v1, const std::vector<int> &v2) {
        bool isCollinear = false;
        bool allNull = true;
        double k = 1;
        for (int i = 0; i < v2.size(); ++i) {
            if (v2[i] == 0) {
                if ((allNull) or (v1[i] == 0))
                    continue;
                else
                    return isCollinear;
            } else {
                if (allNull) {
                    allNull = false;
                    k = v1[i] / double(v2[i]);
                } else if (fabs(k - v1[i] / v2[i]) > EPS_TASK)
                    return isCollinear;
            }
        }
        isCollinear = true;
        return isCollinear;
    }
    
    bool operator&&(const std::vector<double> &v1, const std::vector<double> &v2) {
        if (v1 || v2) {
            for (int i = 0; i < v2.size(); ++i) {
                if (v2[i] == 0)
                    continue;
                else
                    return (v1[i] / v2[i] > 0);
            }
        }
        return false;
    }
    
    bool operator&&(const std::vector<int> &v1, const std::vector<int> &v2) {
        if (v1 || v2) {
            for (int i = 0; i < v2.size(); ++i) {
                if (v2[i] == 0)
                    continue;
                else
                    return (v1[i] / double(v2[i]) > 0);
            }
        }
        return false;
    }
    
    template <typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
        for (int i = 0; i < v.size() - 1; ++i)
            os << v[i] << " ";
        os << v.back() << '\n';
        return os;
    }
    
    template <typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &v) {
        v.clear();
        int size;
        is >> size;
        T temp;
        for (int i = 0; i < size; ++i) {
            is >> temp;
            v.push_back(temp);
        }
        return is;
    }
    
    template <typename T> void reverse(std::vector<T> &v) {
        int last = v.size() - 1;
        for (int i = 0; i < v.size() / 2; ++i) {
            std::swap(v[i], v[last]);
            --last;
        }
    }
    
    std::vector<int> operator|(const std::vector<int> &v1,
                               const std::vector<int> &v2) {
        std::vector<int> res(v1.size());
        for (int i = 0; i < v1.size(); ++i) {
            res[i] = v1[i] | v2[i];
        }
        return res;
    }
    
    std::vector<int> operator&(const std::vector<int> &v1,
                               const std::vector<int> &v2) {
        std::vector<int> res(v1.size());
        for (int i = 0; i < v1.size(); ++i) {
            res[i] = v1[i] & v2[i];
        }
        return res;
    }
    
} // namespace task

