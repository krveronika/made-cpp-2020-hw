#include "matrix.h"

using namespace task;

Matrix::Matrix() {
  m_rows = 1;
  m_column = 1;
  m = new double *[m_rows];
  for (size_t i = 0; i < m_rows; ++i)
    m[i] = new double[m_column];
  m[0][0] = 1;
}

Matrix::Matrix(size_t rows, size_t cols) {
  m_rows = rows;
  m_column = cols;
  m = new double *[m_rows];
  for (size_t i = 0; i < m_rows; ++i)
    m[i] = new double[m_column]();
  for (size_t i = 0; i < std::min(m_rows, m_column); ++i)
    m[i][i] = 1;
}

Matrix::Matrix(const Matrix &copy) {
  this->m_rows = copy.m_rows;
  this->m_column = copy.m_column;
  this->m = new double *[copy.m_rows];
  for (size_t i = 0; i < copy.m_rows; ++i)
    this->m[i] = new double[copy.m_column]();
  for (size_t i = 0; i < copy.m_rows; ++i)
    for (size_t j = 0; j < copy.m_column; ++j)
      this->m[i][j] = copy.m[i][j];
}

Matrix &Matrix::operator=(const Matrix &a) {
  if (&a != this) {
    Matrix temp(a);
    std::swap(m, temp.m);
    std::swap(m_rows, temp.m_rows);
    std::swap(m_column, temp.m_column);
  }

  return *this;
}

double &Matrix::get(size_t row, size_t col) {
  if ((m_rows < row + 1) or (m_column < col + 1))
    throw OutOfBoundsException();
  return m[row][col];
}

double &Matrix::get(size_t row, size_t col) const {
  if ((m_rows < row + 1) or (m_column < col + 1))
    throw OutOfBoundsException();
  return m[row][col];
}

void Matrix::set(size_t row, size_t col, const double &value) {
  if ((m_rows < row + 1) or (m_column < col + 1))
    throw OutOfBoundsException();
  m[row][col] = value;
}

double *Matrix::operator[](size_t row) { return m[row]; }

double *Matrix::operator[](size_t row) const { return m[row]; }

void Matrix::resize(size_t new_rows, size_t new_cols) {
  if (new_rows <= 0 || new_cols <= 0)
    throw SizeMismatchException();

  if (m_rows == new_rows && m_column == new_cols)
    return;

  Matrix cur(new_rows, new_cols);

  size_t k = 0;
  size_t l = 0;

  for (size_t i = 0; i < new_rows; ++i) {
    for (size_t j = 0; j < new_cols; ++j) {
      if (k < m_rows) {
        if (l < m_column) {
          cur[i][j] = m[k][l];
          l++;
        } else {
          if (++k < m_rows) {
            l = 0;
            cur[i][j] = m[k][l];
            l++;
          } else
            cur[i][j] = 0;
        }
      } else
        cur[i][j] = 0;
    }
  }
  *this = cur;
}

Matrix &Matrix::operator+=(const Matrix &a) {
  if ((m_column != a.m_column) or (m_rows != a.m_rows))
    throw SizeMismatchException();
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      m[i][j] += a.m[i][j];
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &a) {
  if ((m_column != a.m_column) or (m_rows != a.m_rows))
    throw SizeMismatchException();
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      m[i][j] -= a.m[i][j];
  return *this;
}

Matrix &Matrix::operator*=(const Matrix &a) {
  if (m_column != a.m_rows)
    throw SizeMismatchException();
  Matrix res(m_rows, a.m_column);

  for (size_t i = 0; i < m_rows; ++i) {
    for (size_t j = 0; j < a.m_column; ++j) {
      if (i == j)
        res.m[i][j] = 0;
      for (size_t k = 0; k < m_column; ++k)
        res.m[i][j] += m[i][k] * a.m[k][j];
    }
  }
  std::swap(res, *this);
  return *this;
}

Matrix &Matrix::operator*=(const double &number) {
  for (size_t i = 0; i < m_rows; ++i) {
    for (size_t j = 0; j < m_column; ++j) {
      m[i][j] *= number;
    }
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix &a) const {
  if ((m_column != a.m_column) or (m_rows != a.m_rows))
    throw SizeMismatchException();
  Matrix res(m_rows, m_column);
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      res.m[i][j] = m[i][j] + a.m[i][j];
  return res;
}

Matrix Matrix::operator-(const Matrix &a) const {
  if ((m_column != a.m_column) or (m_rows != a.m_rows))
    throw SizeMismatchException();
  Matrix res(m_rows, m_column);
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      res.m[i][j] = m[i][j] - a.m[i][j];
  return res;
}

Matrix Matrix::operator*(const Matrix &a) const {
  if (m_column != a.m_rows)
    throw SizeMismatchException();
  Matrix res(m_rows, a.m_column);

  for (size_t i = 0; i < m_rows; ++i) {
    for (size_t j = 0; j < a.m_column; ++j) {
      if (i == j)
        res.m[i][j] = 0;
      for (size_t k = 0; k < m_column; ++k)
        res.m[i][j] += m[i][k] * a.m[k][j];
    }
  }
  return res;
}

Matrix Matrix::operator*(const double &a) const {
  Matrix res(m_rows, m_column);
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      res.m[i][j] = m[i][j] * a;
  return res;
}

Matrix Matrix::operator-() const {
  Matrix res(*this);
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      res[i][j] = -m[i][j];
  return res;
}

Matrix Matrix::operator+() const { return *this; }

double Matrix::det() const {
  // для устойчивости надо разложение LU делать...
  /*
   A = LU => det(A) = det(L)*det(U)
   Ax=y => LUx = y => Ux = b, Lb = y
   */
  if (m_rows != m_column)
    throw SizeMismatchException();

  size_t n = m_rows;

  double **L = new double *[n];
  double **U = new double *[n];
  for (size_t i = 0; i < n; ++i) {
    L[i] = new double[n]();
    U[i] = new double[n]();
  }

  // init
  for (size_t i = 0; i < n; ++i) {
    U[i][i] = 1;
    L[i][0] = m[i][0];
    U[0][i] = m[0][i] / L[0][0];
  }

  double sum = 0;
  // find L and U
  for (size_t i = 1; i < n; ++i) {
    for (size_t j = 1; j < n; ++j) {
      if (i >= j) //нижний треугольник
      {
        sum = 0;
        for (int k = 0; k < j; k++)
          sum += L[i][k] * U[k][j];
        L[i][j] = m[i][j] - sum;
      } else // верхний треугольник
      {
        sum = 0;
        for (int k = 0; k < i; k++)
          sum += L[i][k] * U[k][j];
        U[i][j] = (m[i][j] - sum) / L[i][i];
      }
    }
  }
  //---

  double detL = 1;
  double detU = 1;
  for (size_t i = 0; i < n; ++i) {
    detL *= L[i][i];
    detU *= U[i][i];
  }
  for (size_t i = 0; i < n; ++i) {
    delete L[i];
    delete U[i];
  }
  delete[] L;
  delete[] U;
  return detL * detU;
}

void Matrix::transpose() {
  Matrix res(m_column, m_rows);
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      res[j][i] = m[i][j];
  *this = res;
}

Matrix Matrix::transposed() const {
  Matrix res(m_column, m_rows);
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      res[j][i] = m[i][j];
  return res;
}

double Matrix::trace() const {
  if (m_rows != m_column)
    throw SizeMismatchException();
  double t = 0;
  for (size_t i = 0; i < m_rows; ++i)
    t += m[i][i];
  return t;
}

std::vector<double> Matrix::getRow(size_t row) {
  std::vector<double> t;
  for (int j = 0; j < m_column; ++j)
    t.push_back(m[row][j]);
  return t;
}
std::vector<double> Matrix::getColumn(size_t column) {
  std::vector<double> t;
  for (int i = 0; i < m_rows; ++i)
    t.push_back(m[i][column]);
  return t;
}

bool Matrix::operator==(const Matrix &a) const {
  if ((m_rows != a.m_rows) or (m_column != a.m_column))
    return false;
  for (size_t i = 0; i < m_rows; ++i)
    for (size_t j = 0; j < m_column; ++j)
      if (std::fabs(m[i][j] - a.m[i][j]) > EPS) // !=
        return false;
  return true;
}

bool Matrix::operator!=(const Matrix &a) const { return !(*this == a); }

Matrix task::operator*(const double &a, const Matrix &b) {
  Matrix res = Matrix(b);
  for (size_t i = 0; i < res.m_rows; ++i)
    for (size_t j = 0; j < res.m_column; ++j)
      res.m[i][j] = b.m[i][j] * a;
  return res;
}

std::ostream &task::operator<<(std::ostream &output, const Matrix &matrix) {
  for (size_t i = 0; i < matrix.m_rows; ++i) {
    for (size_t j = 0; j < matrix.m_column; ++j)
      output << matrix.m[i][j] << " "; //*(matrix.m[i]+j);
    output << std::endl;
  }
  return output;
}

std::istream &task::operator>>(std::istream &input, Matrix &matrix) {
  size_t row, col;
  input >> row >> col;
  matrix = Matrix(row, col);
  for (size_t i = 0; i < matrix.m_rows; ++i)
    for (size_t j = 0; j < matrix.m_column; ++j)
      input >> matrix.m[i][j];
  return input;
}

Matrix::~Matrix() {
  for (size_t i = 0; i < m_rows; ++i)
    delete m[i];
  delete[] m;
}
