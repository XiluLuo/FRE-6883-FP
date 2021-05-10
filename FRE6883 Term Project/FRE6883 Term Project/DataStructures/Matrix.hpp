//
//  Matrix.hpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/6/21.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <vector>
#include <algorithm>
#include <ostream>
#include <stdexcept>

class Vector
{
    friend class Matrix;

private:
    std::vector<double> vec;

    // Modifier
    void append(const double value);

public:
    // Default constructor
    Vector() {}

    // Constructor
    Vector(unsigned long len_, double init_value_ = 0)
    {
        if (len_ == 0)
        {
            throw std::invalid_argument("Vector length must be > 0.");
        }

        vec.reserve(len_);
        vec.insert(vec.begin(), len_, init_value_);
    }

    // Constructor accepts lvalue reference
    Vector(std::vector<double> &v)
    {
        vec = std::move(v);
    }

    // Vector accepts rvalue reference
    Vector(std::vector<double> &&v)
    {
        vec = std::move(v);
    }

    // Copy constructor
    Vector(const Vector &other)
    {
        vec.reserve(other.len());
        vec = other.vec;
    }

    // Getter
    unsigned long len() const
    {
        return vec.size();
    }

    // Operator overloading
    double & operator[](const long i)
    {
        return vec[i];
    }

    const double & operator[](const long i) const
    {
        return vec[i];
    }

    Vector & operator=(const Vector &other)
    {
        if (&other != this)
        {
            vec.reserve(other.len());
            vec = other.vec;
        }

        return *this;
    }
};

class Matrix
{
private:
    std::vector<Vector> mtx;

public:
    // Default constructor
    Matrix() {}

    // Constructor
    Matrix(unsigned long nrow_, unsigned long ncol_, const double init_value_ = 0)
    {
        mtx.reserve(nrow_);
        for (unsigned long r = 0; r < nrow_; r++)
        {
            mtx.push_back(Vector(ncol_, init_value_));
        }
    }

    // Copy constructor
    Matrix(const Matrix &other)
    {
        mtx = other.mtx;
    }

    // Getter
    unsigned long row() const
    {
        return mtx.size();
    }

    unsigned long col() const
    {
        return mtx.size() == 0 ? 0 : mtx[0].len();
    }

    // Accessing
    Vector & operator[](const unsigned long r)
    {
        return mtx[r];
    }

    const Vector & operator[](const unsigned long r) const
    {
        return mtx[r];
    }

    // Modifier
    void append(const Vector &v, unsigned int axis = 0);
};

// Vector operations
Vector operator+(const Vector &v1, const Vector &v2);
Vector operator-(const Vector &v1, const Vector &v2);
double operator*(const Vector &v1, const Vector &v2);
Vector operator*(const Vector &v, const double c);
Vector operator*(const double c, const Vector &v);
Vector exp(const Vector &other);

void operator+=(Vector &v1, const Vector &v2);
void operator-=(Vector &v1, const Vector &v2);
void operator*=(Vector &v, const double c);

double sum(const Vector &v);
double mean(const Vector &v);
double stdevp(const Vector &v);
double stdevs(const Vector &v);

// Matrix operations
Matrix operator+(const Matrix &m1, const Matrix &m2);
Matrix operator-(const Matrix &m1, const Matrix &m2);
Matrix operator*(const Matrix &m1, const Matrix &m2);
Matrix operator*(const Matrix &m, const double k);
Matrix operator*(const double k, const Matrix &m);

void operator+=(Matrix &m1, const Matrix &m2);
void operator-=(Matrix &m1, const Matrix &m2);
void operator*=(Matrix &m, const double k);

Vector sum(const Matrix &m, unsigned int axis = 0);
Vector mean(const Matrix &m, unsigned int axis = 0);
Vector stdevp(const Matrix &m, unsigned int axis = 0);
Vector stdevs(const Matrix &m, unsigned int axis = 0);

// Matrix x Vector
Matrix operator+(const Matrix &m, const Vector &v);
Matrix operator-(const Matrix &m, const Vector &v);

void operator+=(Matrix &m, const Vector &v);
void operator-=(Matrix &m, const Vector &v);

// Vector x Matrix
Matrix operator+(const Vector &v, const Matrix &m);
Matrix operator-(const Vector &v, const Matrix &m);

// Display
std::ostream & operator<<(std::ostream &out, const Vector &v);
std::ostream & operator<<(std::ostream &out, const Matrix &m);

// Calculation
Vector pct_change(const Vector &v);
Matrix pct_change(const Matrix &m);
Vector cum_return(const Vector &v);
Matrix cum_return(const Matrix &m);

#endif /* Matrix_hpp */
