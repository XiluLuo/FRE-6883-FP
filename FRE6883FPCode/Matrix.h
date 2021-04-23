#ifndef __6883_FP_MATRIX_H_
#define __6883_FP_MATRIX_H_

#include <vector>
#include <ostream>

class Vector
{
private:
    std::vector<double> vec;

public:
    // Constructor
    Vector(unsigned int len_)
    {
        vec.resize(len_);
    }

    // Copy constructor
    Vector(const Vector &other)
    {
        vec = other.vec;
    }

    // Getter
    unsigned int Len() const
    {
        return vec.size();
    }

    // Accessing
    double & operator[](const int i)
    {
        return vec[i];
    }

    const double & operator[](const int i) const
    {
        return vec[i];
    }
};

class Matrix
{
private:
    unsigned int nrow;
    unsigned int ncol;
    std::vector<std::vector<double>> mtx;

public:
    // Constructor
    Matrix(unsigned int nrow_, unsigned int ncol_, const double init_value_ = 0): nrow(nrow_), ncol(ncol_)
    {
        mtx.resize(nrow);
        for (unsigned int r = 0; r < nrow; r++)
        {
            mtx[r].resize(ncol, init_value_);
        }
    }

    // Copy constructor
    Matrix(const Matrix &other)
    {
        nrow = other.nrow;
        ncol = other.ncol;
        mtx = other.mtx;
    }

    // Getter
    unsigned int Row() const
    {
        return nrow;
    }

    unsigned int Col() const
    {
        return ncol;
    }

    // Accessing
    std::vector<double> & operator[](const unsigned int r)
    {
        return mtx[r];
    }

    const std::vector<double> & operator[](const unsigned int r) const
    {
        return mtx[r];
    }
};

// Vector
Vector operator+(const Vector &vtr1, const Vector &vtr2);
Vector operator-(const Vector &vtr1, const Vector &vtr2);
double operator*(const Vector &vtr1, const Vector &vtr2);
Vector exp(const Vector &other);
void operator+=(Vector &vtr1, const Vector &vtr2);
void operator-=(Vector &vtr1, const Vector &vtr2);
Vector operator*(const Vector &vtr, const double c);
Vector operator*(const double c, const Vector &vtr);
void operator*=(Vector &vtr, const double c);

double sum(const Vector &vtr);
double mean(const Vector &vtr);
double stdevp(const Vector &vtr);  // Population Standard Deviation
double stdevs(const Vector &vtr);  // Sample Standard Deviation

// Matrix
Matrix operator+(const Matrix &mtx1, const Matrix &mtx2);
Matrix operator-(const Matrix &mtx1, const Matrix &mtx2);
Matrix operator*(const Matrix &mtx1, const Matrix &mtx2);
Matrix exp(const Matrix &other);
void operator+=(Matrix &mtx1, const Matrix &mtx2);
void operator-=(Matrix &mtx1, const Matrix &mtx2);
Matrix operator*(const Matrix &mtx, const double c);
Matrix operator*(const double c, const Matrix &mtx);
void operator*=(Matrix &mtx, const double c);

Vector sum(const Matrix &mtx, unsigned int axis = 0);
Vector mean(const Matrix &mtx, unsigned int axis = 0);
Vector stdevp(const Matrix &mtx, unsigned int axis = 0);
Vector stdevs(const Matrix &mtx, unsigned int axis = 0);

// Matrix x Vector
Matrix operator+(const Matrix &mtx, const Vector &vtr);
Matrix operator-(const Matrix &mtx, const Vector &vtr);
void operator+=(Matrix &mtx, const Vector &vtr);
void operator-=(Matrix &mtx, const Vector &vtr);

// Vector x Matrix
Matrix operator+(const Vector &vtr, const Matrix &mtx);
Matrix operator-(const Vector &vtr, const Matrix &mtx);

// Display
std::ostream & operator<<(std::ostream &out, const Vector &vtr);
std::ostream & operator<<(std::ostream &out, const Matrix &mtx);

#endif