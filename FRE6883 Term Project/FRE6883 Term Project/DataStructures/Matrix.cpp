//
//  Matrix.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#include "Matrix.hpp"
#include <iomanip>
#include <cmath>

void Vector::append(const double value)
{
    vec.push_back(value);
}

void Matrix::append(const Vector &v, unsigned int axis)
{
    if (axis != 0 && axis != 1)
    {
        throw std::invalid_argument("Axis must be 0 or 1.");
    }

    if (v.len() == 0)
    {
        throw std::invalid_argument("Cannot append empty Vector.");
    }

    if (axis == 0)
    {
        // Append horizontally
        if (row() != 0 && v.len() != col())
        {
            throw std::invalid_argument("Vector size does not match column width.");
        }

        mtx.push_back(v);
    }
    else
    {
        // Append vertically
        if (col() != 0 && v.len() != row())
        {
            throw std::invalid_argument("Vector size does not row height.");
        }

        if (row() == 0)
        {
            for (unsigned int i = 0; i < v.len(); i++)
            {
                mtx.push_back(Vector());
            }
        }

        for (unsigned int r = 0; r < row(); r++)
        {
            mtx[r].append(v[r]);
        }
    }
}

// Vector operations
Vector operator+(const Vector &v1, const Vector &v2)
{
    if (v1.len() != v2.len())
    {
        throw std::invalid_argument("Vector length does not match.");
    }

    Vector v(v1);
    v += v2;
    return v;
}

Vector operator-(const Vector &v1, const Vector &v2)
{
    if (v1.len() != v2.len())
    {
        throw std::invalid_argument("Vector length does not match.");
    }

    Vector v(v1);
    v -= v2;
    return v;
}

double operator*(const Vector &v1, const Vector &v2)
{
    if (v1.len() != v2.len())
    {
        throw std::invalid_argument("Vector length does not match.");
    }

    double tot = 0.;

    for (unsigned int i = 0; i < v1.len(); i++)
    {
        tot += v1[i] * v2[i];
    }

    return tot;
}

Vector operator*(const Vector &v, const double c)
{
    Vector v_new(v);
    v_new *= c;
    return v_new;
}

Vector operator*(const double c, const Vector &v)
{
    return v * c;
}

Vector exp(const Vector &other)
{
    Vector v(other.len());

    for (unsigned int i = 0; i < other.len(); i++)
    {
        v[i] = exp(other[i]);
    }

    return v;
}

void operator+=(Vector &v1, const Vector &v2)
{
    if (v1.len() != v2.len())
    {
        throw std::invalid_argument("Vector length does not match.");
    }

    for (unsigned int i = 0; i < v1.len(); i++)
    {
        v1[i] += v2[i];
    }
}

void operator-=(Vector &v1, const Vector &v2)
{
    if (v1.len() != v2.len())
    {
        throw std::invalid_argument("Vector length does not match.");
    }

    for (unsigned int i = 0; i < v1.len(); i++)
    {
        v1[i] -= v2[i];
    }
}

void operator*=(Vector &v, const double c)
{
    for (unsigned int i = 0; i < v.len(); i++)
    {
        v[i] *= c;
    }
}

double sum(const Vector &v)
{
    double tot = 0.;

    for (unsigned int i = 0; i < v.len(); i++)
    {
        tot += v[i];
    }

    return tot;
}

double mean(const Vector &v)
{
    return sum(v) / v.len();
}

double stdevp(const Vector &v)
{
    double avg = mean(v);
    double tot = 0.;

    for (unsigned int i = 0; i < v.len(); i++)
    {
        tot += pow(v[i] - avg, 2);
    }

    return sqrt(tot / v.len());
}

double stdevs(const Vector &v)
{
    double avg = mean(v);
    double tot = 0.;

    for (unsigned int i = 0; i < v.len(); i++)
    {
        tot += pow(v[i] - avg, 2);
    }

    return sqrt(tot / (v.len() - 1));
}

// Matrix operations
Matrix operator+(const Matrix &m1, const Matrix &m2)
{
    if (m1.row() != m2.row())
    {
        throw std::invalid_argument("Matrix row count does not match.");
    }

    if (m1.col() != m2.col())
    {
        throw std::invalid_argument("Matrix column count does not match.");
    }

    Matrix m(m1);
    m += m2;
    return m;
}

Matrix operator-(const Matrix &m1, const Matrix &m2)
{
    if (m1.row() != m2.row())
    {
        throw std::invalid_argument("Matrix row count does not match.");
    }

    if (m1.col() != m2.col())
    {
        throw std::invalid_argument("Matrix column count does not match.");
    }

    Matrix m(m1);
    m -= m2;
    return m;
}

Matrix operator*(const Matrix &m1, const Matrix &m2)
{
    if (m1.col() != m2.row())
    {
        throw std::invalid_argument("Column count of M1 must match row count of M2.");
    }

    unsigned long nrow1 = m1.row();
    unsigned long ncol1 = m1.col();
    unsigned long ncol2 = m2.col();

    Matrix m(nrow1, ncol2);
    double tot;

    for (unsigned long r = 0; r < nrow1; r++)
    {
        for (unsigned long c = 0; c < ncol2; c++)
        {
            tot = 0.;
            for (unsigned long k = 0; k < ncol1; k++)
            {
                tot += m1[r][k] * m2[k][c];
            }
            m[r][c] = tot;
        }
    }

    return m;
}

Matrix operator*(const Matrix &m, const double k)
{
    Matrix m_new(m);
    m_new *= k;
    return m_new;
}

Matrix operator*(const double k, const Matrix &m)
{
    return m * k;
}

void operator+=(Matrix &m1, const Matrix &m2)
{
    if (m1.row() != m2.row())
    {
        throw std::invalid_argument("Matrix row count does not match.");
    }

    if (m1.col() != m2.col())
    {
        throw std::invalid_argument("Matrix column count does not match.");
    }

    unsigned long nrow = m1.row();
    unsigned long ncol = m1.col();

    for (unsigned int r = 0; r < nrow; r++)
    {
        for (unsigned int c = 0; c < ncol; c++)
        {
            m1[r][c] += m2[r][c];
        }
    }
}

void operator-=(Matrix &m1, const Matrix &m2)
{
    if (m1.row() != m2.row())
    {
        throw std::invalid_argument("Matrix row count does not match.");
    }

    if (m1.col() != m2.col())
    {
        throw std::invalid_argument("Matrix column count does not match.");
    }

    unsigned long nrow = m1.row();
    unsigned long ncol = m1.col();

    for (unsigned int r = 0; r < nrow; r++)
    {
        for (unsigned int c = 0; c < ncol; c++)
        {
            m1[r][c] -= m2[r][c];
        }
    }
}

void operator*=(Matrix &m, const double k)
{
    unsigned long nrow = m.row();
    unsigned long ncol = m.col();

    for (unsigned int r = 0; r < nrow; r++)
    {
        for (unsigned int c = 0; c < ncol; c++)
        {
            m[r][c] *= k;
        }
    }
}

Vector sum(const Matrix &m, unsigned int axis)
{
    if (axis != 0 && axis != 1)
    {
        throw std::invalid_argument("Axis must be 0 or 1.");
    }

    unsigned long len = axis == 0 ? m.col() : m.row();
    Vector v(len);
    double tot;

    if (axis == 0)
    {
        for (unsigned int c = 0; c < m.col(); c++)
        {
            tot = 0.;
            for (unsigned int r = 0; r < m.row(); r++)
            {
                tot += m[r][c];
            }
            v[c] = tot;
        }
    }
    else
    {
        for (unsigned int r = 0; r < m.row(); r++)
        {
            v[r] = sum(m[r]);
        }
    }

    return v;
}

Vector mean(const Matrix &m, unsigned int axis)
{
    if (axis != 0 && axis != 1)
    {
        throw std::invalid_argument("Axis must be 0 or 1.");
    }

    Vector sv = sum(m, axis);

    unsigned long n = axis == 0 ? m.row() : m.col();
    double recip = 1. / n;

    return sv * recip;
}

Vector stdevp(const Matrix &m, unsigned int axis)
{
    if (axis != 0 && axis != 1)
    {
        throw std::invalid_argument("Axis must be 0 or 1.");
    }

    Vector av = mean(m, axis);
    Vector v(av.len());

    if (axis == 0)
    {
        for (unsigned int c = 0; c < m.col(); c++)
        {
            double tot = 0.;
            for (unsigned int r = 0; r < m.row(); r++)
            {
                tot += pow(m[r][c] - av[c], 2);
            }
            v[c] = sqrt(tot / m.row());
        }
    }
    else
    {
        for (unsigned int r = 0; r < m.row(); r++)
        {
            double tot = 0.;
            for (unsigned int c = 0; c < m.col(); c++)
            {
                tot += pow(m[r][c] - av[r], 2);
            }
            v[r] = sqrt(tot / m.col());
        }
    }

    return v;
}

Vector stdevs(const Matrix &m, unsigned int axis)
{
    if (axis != 0 && axis != 1)
    {
        throw std::invalid_argument("Axis must be 0 or 1.");
    }

    Vector av = mean(m, axis);
    Vector v(av.len());

    if (axis == 0)
    {
        for (unsigned int c = 0; c < m.col(); c++)
        {
            double tot = 0.;
            for (unsigned int r = 0; r < m.row(); r++)
            {
                tot += pow(m[r][c] - av[c], 2);
            }
            v[c] = sqrt(tot / (m.row() - 1));
        }
    }
    else
    {
        for (unsigned int r = 0; r < m.row(); r++)
        {
            double tot = 0.;
            for (unsigned int c = 0; c < m.col(); c++)
            {
                tot += pow(m[r][c] - av[r], 2);
            }
            v[r] = sqrt(tot / (m.col() - 1));
        }
    }

    return v;
}

// Matrix x Vector
Matrix operator+(const Matrix &m, const Vector &v)
{
    if (m.col() != v.len())
    {
        throw std::invalid_argument("Matrix must have same column count as vector length.");
    }

    Matrix m_new(m);
    m_new += v;
    return m_new;
}

Matrix operator-(const Matrix &m, const Vector &v)
{
    if (m.col() != v.len())
    {
        throw std::invalid_argument("Matrix must have same column count as vector length.");
    }

    Matrix m_new(m);
    m_new -= v;
    return m_new;
}

void operator+=(Matrix &m, const Vector &v)
{
    if (m.col() != v.len())
    {
        throw std::invalid_argument("Matrix must have same column count as vector length.");
    }

    for (unsigned int r = 0; r < m.row(); r++)
    {
        for (unsigned int c = 0; c < m.col(); c++)
        {
            m[r][c] += v[c];
        }
    }
}

void operator-=(Matrix &m, const Vector &v)
{
    if (m.col() != v.len())
    {
        throw std::invalid_argument("Matrix must have same column count as vector length.");
    }

    for (unsigned int r = 0; r < m.row(); r++)
    {
        for (unsigned int c = 0; c < m.col(); c++)
        {
            m[r][c] -= v[c];
        }
    }
}

// Vector x Matrix
Matrix operator+(const Vector &v, const Matrix &m)
{
    if (v.len() != m.col())
    {
        throw std::invalid_argument("Vector must have same length as matrix column count.");
    }

    unsigned long nrow = m.row();
    unsigned long ncol = m.col();

    Matrix m_new(nrow, ncol);

    for (unsigned long r = 0; r < nrow; r++)
    {
        for (unsigned long c = 0; c < ncol; c++)
        {
            m_new[r][c] = v[c] + m[r][c];
        }
    }

    return m_new;
}

Matrix operator-(const Vector &v, const Matrix &m)
{
    if (v.len() != m.col())
    {
        throw std::invalid_argument("Vector must have same length as matrix column count.");
    }

    unsigned long nrow = m.row();
    unsigned long ncol = m.col();

    Matrix m_new(nrow, ncol);

    for (unsigned long r = 0; r < nrow; r++)
    {
        for (unsigned long c = 0; c < ncol; c++)
        {
            m_new[r][c] = v[c] - m[r][c];
        }
    }

    return m_new;
}

// Display
std::ostream & operator<<(std::ostream &out, const Vector &v)
{
    if (v.len() == 0)
    {
        out << "[]";
        return out;
    }

    out << std::setiosflags(std::ios::fixed) << std::setprecision(4);

    for (unsigned int i = 0; i < v.len(); i++)
    {
        if (i == 0) out << "[";
        else out << " ";
        out << v[i];
    }
    out << "]";

    return out;
}

std::ostream & operator<<(std::ostream &out, const Matrix &m)
{
    if (m.row() == 0 || m.col() == 0)
    {
        out << "[]";
        return out;
    }

    out << std::setiosflags(std::ios::fixed) << std::setprecision(4);

    for (unsigned int r = 0; r < m.row(); r++)
    {
        if (r == 0) out << "[";
        else out << " ";

        for (unsigned int c = 0; c < m.col(); c++)
        {
            if (c == 0) out << "[";
            else out << " ";
            out << m[r][c];
        }
        out << "]";
        if (r != m.row() - 1) out << std::endl;
    }
    out << "]";

    return out;
}

// Calculation
Vector pct_change(const Vector &v)
{
    unsigned long n = v.len();
    Vector v_new(n - 1);

    for (unsigned long i = 0; i < n - 1; i++)
    {
        v_new[i] = (v[i+1] - v[i]) / v[i];
    }

    return v_new;
}

Matrix pct_change(const Matrix &m)
{
    unsigned long nrow = m.row();

    Matrix m_new;

    for (unsigned int r = 0; r < nrow; r++)
    {
        m_new.append(pct_change(m[r]));
    }

    return m_new;
}

Vector cum_return(const Vector &v)
{
    unsigned long n = v.len();
    Vector v_new(n - 1);

    for (unsigned int i = 0; i < n - 1; i++)
    {
        v_new[i] = (v[i+1] - v[0]) / v[0];
    }

    return v_new;
}

Matrix cum_return(const Matrix &m)
{
    unsigned long nrow = m.row();
    Matrix m_new;

    for (unsigned int r = 0; r < nrow; r++)
    {
        m_new.append(cum_return(m[r]));
    }

    return m_new;
}
