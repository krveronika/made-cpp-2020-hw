#pragma once

#include <vector>
#include <iostream>


namespace task {

const double EPS = 1e-6;


class OutOfBoundsException : public std::exception {};
class SizeMismatchException : public std::exception {};


class Matrix
{

public:

    Matrix();
    
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix& copy);
    Matrix& operator=(const Matrix& a);
    double& get(size_t row, size_t col);
    double& get(size_t row, size_t col) const;
    void set(size_t row, size_t col, const double& value);
    void resize(size_t new_rows, size_t new_cols);
    
    
    double *operator[] (size_t row);
    double *operator[] (size_t row) const;

    /* ??? */ //operator[](size_t row);
    /* ??? */ //operator[](size_t row) const;
    
    Matrix& operator+=(const Matrix& a);
    Matrix& operator-=(const Matrix& a);
    Matrix& operator*=(const Matrix& a);
    Matrix& operator*=(const double& number);
    Matrix operator+(const Matrix& a) const;
    Matrix operator-(const Matrix& a) const;
    Matrix operator*(const Matrix& a) const;
    Matrix operator*(const double& a) const;

    Matrix operator-() const;
    Matrix operator+() const;

    double det() const;
    void transpose();
    Matrix transposed() const;
    double trace() const;

    std::vector<double> getRow(size_t row);
    std::vector<double> getColumn(size_t column);

    bool operator==(const Matrix& a) const;
    bool operator!=(const Matrix& a) const;
    
    // Your code goes here...
    ~Matrix();
    
//    friend Matrix operator*(const double& a, const Matrix& b);
    friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
//    friend std::istream& operator>>(std::istream& input, Matrix& matrix);

private:
    size_t m_rows;
    size_t m_column;
    double **m;
};
    
//Matrix operator*(const double& a, const Matrix& b)
//{
//    b.m_column;
//    return Matrix();
//}
//
std::ostream& operator<<(std::ostream& output, const Matrix& matrix)
{
//    for(size_t i = 0; i < matrix.m_rows; ++i)
//        for(size_t j = 0; j < matrix.m_column; ++j)
//            output << matrix.m[i][j] << " ";
    output << "asdasda";
    return output;
}
//
//std::istream& operator>>(std::istream& input, Matrix& matrix)
//{
//    size_t row, col;
//    input >> row >> col;
//    matrix = Matrix(row, col);
//    for(size_t i = 0; i < matrix.m_rows; ++i)
//        for(size_t j = 0; j < matrix.m_column; ++j)
//            input >> matrix.m[i][j];
//    return input;
//}
    
}  // namespace task
