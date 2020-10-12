#include "matrix.h"

using namespace task;


// Your code goes here...

Matrix::Matrix()
{
    m_rows = 1;
    m_column = 1;
    m = new double * [m_rows];
    for (size_t i = 0; i < m_rows; ++i)
        m[i] = new double[m_column];
    m[0][0] = 1;
}

Matrix::Matrix(size_t rows, size_t cols)
{
    m_rows = rows;
    m_column = cols;
    m = new double * [m_rows];
    for (size_t i = 0; i < m_rows; ++i)
        m[i] = new double[m_column]();
    for (size_t i = 0; i < std::min(m_rows, m_column); ++i)
        m[i][i] = 1;
}

Matrix::Matrix(const Matrix& copy)
{
    this->m_rows = copy.m_rows;
    this->m_column = copy.m_column;
    this->m = new double * [copy.m_rows];
    for (size_t i = 0; i < copy.m_rows; ++i)
        this->m[i] = new double[ copy.m_column]();
    for (size_t i = 0; i < copy.m_rows; ++i)
        for (size_t j = 0; j < copy.m_column; ++j)
                this->m[i][j] = copy.m[i][j];
}

Matrix& Matrix::operator=(const Matrix& a)
{
    if (&a != this)
    {
        Matrix temp(a);
        std::swap(m, temp.m);
        std::swap(m_rows, temp.m_rows);
        std::swap(m_column, temp.m_column);
    }
    
    return *this;
}

double& Matrix::get(size_t row, size_t col)
{
    if ((m_rows < row) or (m_column < col))
        throw OutOfBoundsException();
    return m[row][col];
}

double& Matrix::get(size_t row, size_t col) const
{
    if ((m_rows < row) or (m_column < col))
        throw OutOfBoundsException();
    return m[row][col];
}

void Matrix::set(size_t row, size_t col, const double& value)
{
    if ((m_rows < row) or (m_column < col))
        throw OutOfBoundsException();
    m[row][col] = value;
}

double *Matrix::operator[] (size_t row)
{
    return m[row];
}

double *Matrix::operator[] (size_t row) const
{
    return m[row];
}

void Matrix::resize(size_t new_rows, size_t new_cols)
{
    //pass
    Matrix cur(new_rows, new_cols);
    size_t k = 0;
    size_t l = 0;
    
    
//    for (size_t i = 0; i < new_rows; ++i)
//    {
//        for (size_t j = 0; j < new_cols; ++j)
//        {
//            
//        }
//    }
}

Matrix& Matrix::operator+=(const Matrix& a)
{
    if ((m_column != a.m_column) or (m_rows != a.m_rows))
        throw SizeMismatchException();
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_rows; ++j)
            m[i][j] += a.m[i][j];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& a)
{
    if ((m_column != a.m_column) or (m_rows != a.m_rows))
        throw SizeMismatchException();
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_rows; ++j)
            m[i][j] -= a.m[i][j];
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& a)
{
    if (m_column != a.m_rows)
        throw SizeMismatchException();
    Matrix res(m_rows, a.m_column);
    
    for (size_t i = 0; i < m_rows; ++i)
    {
        for (size_t j = 0; j < a.m_column; ++j)
        {
            if (i == j)
                res.m[i][j] = 0;
            for (size_t k = 0; k < m_column; ++k)
                res.m[i][j] += m[i][k] * a.m[k][j];
        }
    }
    std::swap(res, *this);
    return *this;
}

Matrix& Matrix::operator*=(const double& number)
{
    for (size_t i = 0; i < m_rows; ++i)
    {
        for (size_t j = 0; j < m_column; ++j)
        {
            m[i][j] *= number;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& a) const
{
    if ((m_column != a.m_column) or (m_rows != a.m_rows))
        throw SizeMismatchException();
    Matrix res(m_rows, m_column);
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_column; ++j)
            res.m[i][j] = m[i][j] + a.m[i][j];

    return res;
}

Matrix Matrix::operator-(const Matrix& a) const
{
    if ((m_column != a.m_column) or (m_rows != a.m_rows))
        throw SizeMismatchException();
    Matrix res(m_rows, m_column);
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_column; ++j)
            res.m[i][j] = m[i][j] - a.m[i][j];
    return res;
}

Matrix Matrix::operator*(const Matrix& a) const
{
    if (m_column != a.m_rows)
        throw SizeMismatchException();
    Matrix res(m_rows, a.m_column);
    
    for (size_t i = 0; i < m_rows; ++i)
    {
        for (size_t j = 0; j < a.m_column; ++j)
        {
            if (i == j)
                res.m[i][j] = 0;
            for (size_t k = 0; k < m_column; ++k)
                res.m[i][j] += m[i][k] * a.m[k][j];
        }
    }
    return res;
}

Matrix Matrix::operator*(const double& a) const
{
    Matrix res(m_rows, m_column);
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_column; ++j)
            res.m[i][j] = m[i][j] * a;
    return res;
}

Matrix Matrix::operator-() const
{
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_column; ++j)
            m[i][j] = -m[i][j];
    return *this;
}

Matrix Matrix::operator+() const
{
    return *this;
}

double Matrix::det() const
{
    // для устойчивости надо разложение LU делать, но посчитаю по определению
    if (m_rows != m_column)
        throw SizeMismatchException();
    return 0;
}

void Matrix::transpose()
{
    Matrix res(m_column, m_rows);
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_column; ++j)
            res[j][i] = m[i][j];
    *this = res;
}

Matrix Matrix::transposed() const
{
    Matrix res(m_column, m_rows);
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_column; ++j)
            res[j][i] = m[i][j];
    return res;
}

double Matrix::trace() const
{
    if (m_rows != m_column)
        throw SizeMismatchException();
    double t = 0;
    for (size_t i = 0; i < m_rows; ++i)
        t += m[i][i];
    return t;
}

std::vector<double> Matrix::getRow(size_t row)
{
    std::vector<double> t;
    for (int j = 0; j < m_column; ++j)
        t.push_back(m[row][j]);
    return t;
    
}
std::vector<double> Matrix::getColumn(size_t column)
{
    std::vector<double> t;
    for (int i = 0; i < m_rows; ++i)
        t.push_back(m[i][column]);
    return t;
}

bool Matrix::operator==(const Matrix& a) const
{
    if ((m_rows != a.m_rows) or (m_column != a.m_column))
        return false;
    for(size_t i = 0; i < m_rows; ++i)
        for(size_t j = 0; j < m_column; ++j)
            if (m[i][j] != a.m[i][j])
                return false;
    return true;
}

bool Matrix::operator!=(const Matrix& a) const
{
    return !(*this == a);
}

Matrix task::operator*(const double& a, const Matrix& b)
{
    return Matrix();
}


std::ostream& task::operator<<(std::ostream& output, const Matrix& matrix)
{
    for(size_t i = 0; i < matrix.m_rows; ++i)
    {
        for(size_t j = 0; j < matrix.m_column; ++j)
            output << matrix.m[i][j] << " ";//*(matrix.m[i]+j);
        output << std::endl;
    }
    return output;
}

std::istream& task::operator>>(std::istream& input, Matrix& matrix)
{
    size_t row, col;
    input >> row >> col;
    matrix = Matrix(row, col);
    for(size_t i = 0; i < matrix.m_rows; ++i)
        for(size_t j = 0; j < matrix.m_column; ++j)
            input >> matrix.m[i][j];
    return input;
}

Matrix::~Matrix()
{
    for(size_t i = 0; i < m_rows; ++i)
        delete m[i];
    delete[] m;
}

