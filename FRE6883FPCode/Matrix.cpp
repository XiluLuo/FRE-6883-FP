#include "Matrix.h"
#include <iomanip>
#include <cmath>

// Vector
Vector operator+(const Vector &vtr1, const Vector &vtr2)
{
    Vector vtr(vtr1);
    vtr += vtr2;
    return vtr;
}

Vector operator-(const Vector &vtr1, const Vector &vtr2)
{
    Vector vtr(vtr1);
    vtr -= vtr2;
    return vtr;
}

double operator*(const Vector &vtr1, const Vector &vtr2)
{
    double tot = 0.;

    for (unsigned int i = 0; i < vtr1.Len(); i++)
        tot += vtr1[i] * vtr2[i];

    return tot;
}

Vector exp(const Vector &other)
{
    Vector vtr(other.Len());

    for (unsigned int i = 0; i < other.Len(); i++)
    {
        vtr[i] = exp(other[i]);
    }

    return vtr;
}

void operator+=(Vector &vtr1, const Vector &vtr2)
{
    for (unsigned int i = 0; i < vtr1.Len(); i++)
        vtr1[i] += vtr2[i];
}

void operator-=(Vector &vtr1, const Vector &vtr2)
{
    for (unsigned int i = 0; i < vtr1.Len(); i++)
        vtr1[i] -= vtr2[i];
}

Vector operator*(const Vector &vtr, const double c)
{
    Vector V(vtr);
    V *= c;
    return V;
}

Vector operator*(const double c, const Vector &vtr)
{
    return vtr * c;
}

void operator*=(Vector &vtr, const double c)
{
    for (unsigned int i = 0; i < vtr.Len(); i++)
        vtr[i] *= c;
}

double sum(const Vector &vtr)
{
    double tot = 0.;

    for (unsigned int i = 0; i < vtr.Len(); i++)
        tot += vtr[i];

    return tot;
}

double mean(const Vector &vtr)
{
    double tot = sum(vtr);
    return tot / vtr.Len();
}

double stdevp(const Vector &vtr)
{
    double avg = mean(vtr);
    double tot = 0.;

    for (unsigned int i = 0; i < vtr.Len(); i++)
        tot += pow(vtr[i] - avg, 2);

    return sqrt(tot / vtr.Len());
}

double stdevs(const Vector &vtr)
{
    double avg = mean(vtr);
    double tot = 0.;

    for (unsigned int i = 0; i < vtr.Len(); i++)
        tot += pow(vtr[i] - avg, 2);

    return sqrt(tot / (vtr.Len() - 1));
}

// Matrix
Matrix operator+(const Matrix &mtx1, const Matrix &mtx2)
{
    Matrix mtx(mtx1);
    mtx += mtx2;
    return mtx;
}

Matrix operator-(const Matrix &mtx1, const Matrix &mtx2)
{
    Matrix mtx(mtx1);
    mtx -= mtx2;
    return mtx;
}

Matrix operator*(const Matrix &mtx1, const Matrix &mtx2)
{
    unsigned int nrow1 = mtx1.Row();
    unsigned int ncol1 = mtx1.Col();
    unsigned int ncol2 = mtx2.Col();

    Matrix M(nrow1, ncol2);
    double tot;

    for (unsigned int r = 0; r < nrow1; r++)
    {
        for (unsigned int c = 0; c < ncol2; c++)
        {
            tot = 0.;
            for (unsigned int k = 0; k < ncol1; k++)
            {
                tot += mtx1[r][k] * mtx2[k][c];
            }
            M[r][c] = tot;
        }
    }

    return M;
}

Matrix exp(const Matrix &other)
{
    unsigned int nrow = other.Row();
    unsigned int ncol = other.Col();

    Matrix mtx(nrow, ncol);
    
    for (unsigned int r = 0; r < nrow; r++)
        for (unsigned int c = 0; c < ncol; c++)
            mtx[r][c] = exp(other[r][c]);

    return mtx;
}

void operator+=(Matrix &mtx1, const Matrix &mtx2)
{
    unsigned int nrow = mtx1.Row();
    unsigned int ncol = mtx1.Col();
    
    for (unsigned int r = 0; r < nrow; r++)
        for (unsigned int c = 0; c < ncol; c++)
            mtx1[r][c] += mtx2[r][c];
}

void operator-=(Matrix &mtx1, const Matrix &mtx2)
{
    unsigned int nrow = mtx1.Row();
    unsigned int ncol = mtx1.Col();
    
    for (unsigned int r = 0; r < nrow; r++)
        for (unsigned int c = 0; c < ncol; c++)
            mtx1[r][c] -= mtx2[r][c];
}

Matrix operator*(const Matrix &mtx, const double c)
{
    Matrix M(mtx);
    M *= c;
    return M;
}

Matrix operator*(const double c, const Matrix &mtx)
{
    return mtx * c;
}

void operator*=(Matrix &mtx, const double c)
{
    for (unsigned int r = 0; r < mtx.Row(); r++)
        for (unsigned int c = 0; c < mtx.Col(); c++)
            mtx[r][c] *= c;
}

Vector sum(const Matrix &mtx, unsigned int axis)
{
    unsigned int len = (axis == 0) ? mtx.Col() : mtx.Row();
    Vector vtr(len);
    double tot;

    if (axis == 0)
    {
        for (unsigned int c = 0; c < mtx.Col(); c++)
        {
            tot = 0.;
            for (unsigned int r = 0; r < mtx.Row(); r++)
                tot += mtx[r][c];
            vtr[c] = tot;
        }
    }
    else
    {
        for (unsigned int r = 0; r < mtx.Row(); r++)
        {
            tot = 0.;
            for (unsigned int c = 0; c < mtx.Col(); c++)
                tot += mtx[r][c];
            vtr[r] = tot;
        }
    }

    return vtr;
}

Vector mean(const Matrix &mtx, unsigned int axis)
{
    Vector sumvtr = sum(mtx, axis);
    unsigned int nitem = (axis == 0) ? mtx.Row() : mtx.Col();
    double recip = 1. / nitem;

    return sumvtr * recip;
}

Vector stdevp(const Matrix &mtx, unsigned int axis)
{
    Vector avgvtr = mean(mtx, axis);
    Vector vtr(avgvtr.Len());

    if (axis == 0)
    {
        for (unsigned int c = 0; c < mtx.Col(); c++)
        {
            double tot = 0.;
            for (unsigned int r = 0; r < mtx.Row(); r++)
                tot += pow(mtx[r][c] - avgvtr[c], 2);
            vtr[c] = sqrt(tot / mtx.Row());
        }
    }
    else
    {
        for (unsigned int r = 0; r < mtx.Row(); r++)
        {
            double tot = 0.;
            for (unsigned int c = 0; c < mtx.Col(); c++)
                tot += pow(mtx[r][c] - avgvtr[r], 2);
            vtr[r] = sqrt(tot / mtx.Col());
        }
    }

    return vtr;
}

Vector stdevs(const Matrix &mtx, unsigned int axis)
{
    Vector avgvtr = mean(mtx, axis);
    Vector vtr(avgvtr.Len());

    if (axis == 0)
    {
        for (unsigned int c = 0; c < mtx.Col(); c++)
        {
            double tot = 0.;
            for (unsigned int r = 0; r < mtx.Row(); r++)
                tot += pow(mtx[r][c] - avgvtr[c], 2);
            vtr[c] = sqrt(tot / (mtx.Row() - 1));
        }
    }
    else
    {
        for (unsigned int r = 0; r < mtx.Row(); r++)
        {
            double tot = 0.;
            for (unsigned int c = 0; c < mtx.Col(); c++)
                tot += pow(mtx[r][c] - avgvtr[r], 2);
            vtr[r] = sqrt(tot / (mtx.Col() - 1));
        }
    }

    return vtr;
}

// Matrix x Vector

Matrix operator+(const Matrix &mtx, const Vector &vtr)
{
    Matrix M(mtx);
    M += vtr;
    return M;
}

Matrix operator-(const Matrix &mtx, const Vector &vtr)
{
    Matrix M(mtx);
    M -= vtr;
    return M;
}

void operator+=(Matrix &mtx, const Vector &vtr)
{
    for (unsigned int r = 0; r < mtx.Row(); r++)
        for (unsigned int c = 0; c < mtx.Col(); c++)
            mtx[r][c] += vtr[c];
}

void operator-=(Matrix &mtx, const Vector &vtr)
{
    for (unsigned int r = 0; r < mtx.Row(); r++)
        for (unsigned int c = 0; c < mtx.Col(); c++)
            mtx[r][c] -= vtr[c];
}

// Vector x Matrix

Matrix operator+(const Vector &vtr, const Matrix &mtx)
{
    unsigned int nrow = mtx.Row();
    unsigned int ncol = mtx.Col();

    Matrix M(nrow, ncol);

    for (unsigned int r = 0; r < nrow; r++)
        for (unsigned int c = 0; c < ncol; c++)
            M[r][c] = vtr[c] + mtx[r][c];

    return M;
}

Matrix operator-(const Vector &vtr, const Matrix &mtx)
{
    unsigned int nrow = mtx.Row();
    unsigned int ncol = mtx.Col();

    Matrix M(nrow, ncol);

    for (unsigned int r = 0; r < nrow; r++)
        for (unsigned int c = 0; c < ncol; c++)
            M[r][c] = vtr[c] - mtx[r][c];

    return M;
}

// Display

std::ostream & operator<<(std::ostream &out, const Vector &vtr)
{
    out << std::setiosflags(std::ios::fixed) << std::setprecision(4);

    for (unsigned int i = 0; i < vtr.Len(); i++)
    {
        if (i == 0) out << "[";
        else out << " ";
        out << vtr[i];
    }
    out << "]";

    return out;
}

std::ostream & operator<<(std::ostream &out, const Matrix &mtx)
{
    out << std::setiosflags(std::ios::fixed) << std::setprecision(4);

    for (unsigned int r = 0; r < mtx.Row(); r++)
    {
        for (unsigned int c = 0; c < mtx.Col(); c++)
        {
            if (c == 0) out << "[";
            else out << " ";
            out << mtx[r][c];
        }
        out << "]";
        if (r != mtx.Row() - 1) out << std::endl;
    }
    return out;
}