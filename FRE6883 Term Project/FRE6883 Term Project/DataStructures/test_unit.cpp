//
//  test_unit.cpp
//  FRE6883 Term Project
//
//  Created by DevonC on 5/9/21.
//

#include "acutest.h"
#include "Matrix.hpp"
#include <iomanip>
#include <cmath>

void test_Vector_default_constructor(void)
{
    Vector v;
    unsigned long vector_len = 0;
    TEST_CHECK_(v.len() == vector_len, "v.len(): Expected=%ld, Actual=%ld", vector_len, v.len());
}

void test_Vector_parameterized_constructor(void)
{
    unsigned long vector_len = 10;
    Vector v(vector_len);
    TEST_CHECK_(v.len() == 10, "v.len(): Expected=%ld, Actual=%ld", vector_len, v.len());
}

void test_Vector_parameterized_constructor_invalid_arg(void)
{
    unsigned int vector_len = 0;
    TEST_EXCEPTION(Vector{vector_len}, std::invalid_argument);
}

void test_Vector_stdvector_constructor(void)
{
    unsigned long num_elements = 10;
    std::vector<double> vec;
    for (int i = 0; i < num_elements; i++)
    {
        vec.push_back(i);
    }

    Vector v(vec);

    TEST_CHECK_(v.len() == num_elements, "v.len(): Expected=%ld, Actual=%ld", num_elements, v.len());
    TEST_CHECK_(vec.size() == 0, "vec.size(): Expected=%d, Actual=%lu", 0, vec.size());

    for (int i = 0; i < num_elements; i++)
    {
        TEST_CHECK(v[i] == i);
    }
}

void test_Matrix_default_constructor(void)
{
    Matrix m;
    
    unsigned long m_row = 0;
    unsigned long m_col = 0;
    
    TEST_CHECK_(m.row() == m_row, "m.row(): Expected=%ld, Actual=%ld", m_row, m.row());
    TEST_CHECK_(m.col() == m_col, "m.col(): Expected=%ld, Actual=%ld", m_col, m.col());
}

void test_Matrix_parameterized_constructor(void)
{
    unsigned long matrix_row = 10;
    unsigned long matrix_col = 10;

    Matrix m(matrix_row, matrix_col, 6);
    
    TEST_CHECK_(m.row() == 10, "m.row(): Expected=%ld, Actual=%ld", matrix_row, m.row());
    TEST_CHECK_(m.col() == 10, "m.col(): Expected=%ld, Actual=%ld", matrix_col, m.col());
    TEST_CHECK_(m[0][1] == 6, "m.value: Expected=%f, Actual=%f", 6., m[0][1]);
}

void test_Matrix_copy_constructor(void)
{
    unsigned long matrix_row = 10;
    unsigned long matrix_col = 10;
    
    Matrix m(matrix_row,matrix_col,12);
    Matrix m1(m);

    TEST_CHECK_(m1.row() == 10, "m.row(): Expected=%ld, Actual=%ld", matrix_row, m1.row());
    TEST_CHECK_(m1.col() == 10, "m.col(): Expected=%ld, Actual=%ld", matrix_col, m1.col());
    TEST_CHECK_(m1[0][1] == 12, "m.value: Expected=%f, Actual=%f", 12., m1[0][1]);
}

void test_vops_plus(void)
{
    Vector v1(5);
    Vector v2(6);
    
    for (int i = 0; i < 5; i++)
    {
        v1[i] = 1;
        v2[i] = i;
    }
    
    Vector v;
    v = v1 + v1;
    
    TEST_CHECK_(v.len() == 5, "vector plus: Expected=%ld, Actual=%ld", (unsigned long) 5, v.len());
    TEST_CHECK_(v[0] == 2, "vector plus: Expected=%f, Actual=%f", 2., v[0]);

    TEST_EXCEPTION(v1+v2, std::invalid_argument);
}

void test_vops_minus(void)
{
    Vector v1(5);
    Vector v2(6);
    Vector v3(5);
    for (int i = 0; i < 5; i++)
    {
        v1[i] = 2;
        v3[i] = 1;
        v2[i] = i;
    }
    
    Vector v;
    v = v1 - v3;
    
    TEST_CHECK_(v.len() == 5, "vector minus length: Expected=%ld, Actual=%ld", (unsigned long) 5, v.len());
    TEST_CHECK_(v[0] == 1, "vector minus value: Expected=%f, Actual=%f", 0., v[0]);

    TEST_EXCEPTION(v1-v2, std::invalid_argument);
}

void test_vops_times(void)
{
    Vector v1(5);
    Vector v2(6);
    
    for (int i = 0; i < 5; i++)
    {
        v1[i] = 1;
        v2[i] = i;
    }
    
    double v;
    v = v1 * v1;
    
    TEST_CHECK_(v == 5, "vector times: Expected=%f, Actual=%f", 5., v);
    TEST_EXCEPTION(v1*v2, std::invalid_argument);
}

void test_vops_timesc(void)
{
    Vector v1(5);
    Vector v2(6);
    
    for (int i = 0; i < 5; i++)
    {
        v1[i] = 1;
        v2[i] = i;
    }
    
    v1 = v1 * 6;
    v2 = 6 * v2;
    
    TEST_CHECK_(v1.len() == 5, "vector timesc: Expected=%ld, Actual=%ld", (unsigned long) 5, v1.len());
    TEST_CHECK_(v1[0] == 6, "vector timesc: Expected=%f, Actual=%f", 6., v1[0]);
    TEST_CHECK_(v2.len() == 6, "vector timesc2: Expected=%ld, Actual=%ld", (unsigned long) 6, v2.len());
    TEST_CHECK_(v2[0] == 0, "vector timesc2: Expected=%f, Actual=%f", 0., v2[0]);
}

void test_vops_exp(void)
{
    Vector v1(5,1);
    Vector v2(5);

    v2 = exp(v1);

    TEST_CHECK_(v2.len() == 5, "vector timesc: Expected=%ld, Actual=%ld", (unsigned long) 5, v2.len());
    TEST_CHECK_(v2[0] == exp(1), "vector timesc: Expected=%f, Actual=%f", exp(1), v2[0]);
}

void test_vops_pe(void)
{
    Vector v1(5,1);
    Vector v2(5,2);
    Vector v3(6,1);

    v1 += v2;
    
    TEST_CHECK_(v1.len() == 5, "vector pe length: Expected=%ld, Actual=%ld", (unsigned long) 5, v1.len());
    TEST_CHECK_(v1[0] == 3, "vector pe value: Expected=%f, Actual=%f", 3., v1[0]);
    TEST_EXCEPTION(v1+=v3, std::invalid_argument);
}

void test_vops_me(void)
{
    Vector v1(5,1);
    Vector v2(5,2);
    Vector v3(6,1);

    v1 -= v2;
    
    TEST_CHECK_(v1.len() == 5, "vector me length: Expected=%ld, Actual=%ld", (unsigned long) 5, v1.len());
    TEST_CHECK_(v1[0] == -1, "vector me value: Expected=%f, Actual=%f", -1., v1[0]);
    TEST_EXCEPTION(v1+=v3, std::invalid_argument);
}

void test_vops_te(void)
{
    Vector v1(5,1);

    v1 *= 6;
    
    TEST_CHECK_(v1.len() == 5, "vector te length: Expected=%ld, Actual=%ld", (unsigned long) 5, v1.len());
    TEST_CHECK_(v1[0] == 6, "vector te value: Expected=%f, Actual=%f", 6., v1[0]);
}

void test_vops_sum(void)
{
    Vector v1(5,1);

    int n = sum(v1);
    
    TEST_CHECK_(n == 5, "vector sum value: Expected=%d, Actual=%d", 5, n);
}

void test_vops_mean(void)
{
    Vector v1(5,1);

    double n;
    n = mean(v1);
    TEST_CHECK_(n == 1, "vector mean value: Expected=%f, Actual=%f", 1., n);
}

void test_vops_stdevp(void)
{
    Vector v1(5);
    for (int i = 0; i < 5; i++) v1[i] = i;

    double n;
    n = stdevp(v1);
    TEST_CHECK_(n-1.707825 <= 0.001, "vector stdevp value: Expected=%f, Actual=%f", 1.707825, n);
}

void test_vops_stdevs(void)
{
    Vector v1(5);
    for (int i = 0; i < 5; i++) v1[i] = i;

    double n;
    n = stdevs(v1);
    TEST_CHECK_(n-1.870829 <= 0.001, "vector stdevs value: Expected=%f, Actual=%f", 1.870829, n);
}

void test_mops_plus(void)
{
    Matrix m1(5,5,2);
    Matrix m2(3,5,1);
    Matrix m3(5,3,1);

    m1 = m1 + m1;
    
    TEST_CHECK_(m1.row() == 5, "matrix plus row: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.row());
    TEST_CHECK_(m1.col() == 5, "matrix plus col: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.col());
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            TEST_CHECK_(m1[i][j] == 4, "matrix plus value: Expected=%f, Actual=%f", 4., m1[i][j]);
        }
    }

    TEST_EXCEPTION(m1+m2, std::invalid_argument);
    TEST_EXCEPTION(m1+m3, std::invalid_argument);
}

void test_mops_minus(void)
{
    Matrix m1(5,5,2);
    Matrix m2(3,4,1);
    Matrix m3(5,3,1);

    m1 = m1 - m1;
    
    TEST_CHECK_(m1.row() == 5, "matrix minus row: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.row());
    TEST_CHECK_(m1.col() == 5, "matrix minus col: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.col());
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            TEST_CHECK_(m1[i][j] == 0, "matrix plus value: Expected=%f, Actual=%f", 0., m1[i][j]);
        }
    }

    TEST_EXCEPTION(m1-m2, std::invalid_argument);
    TEST_EXCEPTION(m1-m3, std::invalid_argument);
}

void test_mops_times(void)
{
    Matrix m1(2,2,2);
    Matrix m2(3,4,1);
    Matrix m3(2,3,7);

    m1 = m1 * m1;
    
    TEST_CHECK_(m1.row() == 2, "matrix times row: Expected=%ld, Actual=%ld", (unsigned long) 2, m1.row());
    TEST_CHECK_(m1.col() == 2, "matrix times col: Expected=%ld, Actual=%ld", (unsigned long) 2, m1.col());
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            TEST_CHECK_(m1[i][j] == 8, "matrix times value: Expected=%f, Actual=%f", 8., m1[i][j]);
        }
    }
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            m1[i][j] = 2;
        }
    }

    Matrix m4(2,3);
    m4 = m1 * m3;
    
    TEST_CHECK_(m4.row() == 2, "matrix times row: Expected=%ld, Actual=%ld", (unsigned long) 2, m4.row());
    TEST_CHECK_(m4.col() == 3, "matrix times col: Expected=%ld, Actual=%ld", (unsigned long) 3, m4.col());

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            TEST_CHECK_(m4[i][j] == 28, "matrix times value: Expected=%d, Actual=%f", 28, m4[i][j]);
        }
    }

    TEST_EXCEPTION(m1*m2, std::invalid_argument);
    TEST_EXCEPTION(m2*m3, std::invalid_argument);
}

void test_mops_timesc(void)
{
    Matrix m1(5,5,2);
    double n = 6;

    m1 = m1 * n;
    
    TEST_CHECK_(m1.row() == 5, "matrix timesc row: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.row());
    TEST_CHECK_(m1.col() == 5, "matrix timesc col: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.col());
    TEST_CHECK_(m1[0][0] == 12, "matrix timesc value: Expected=%d, Actual=%f", 12, m1[0][0]);

    m1 = n * m1;
    
    TEST_CHECK_(m1.row() == 5, "matrix timesc row: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.row());
    TEST_CHECK_(m1.col() == 5, "matrix timesc col: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.col());
    TEST_CHECK_(m1[0][0] == 72, "matrix timesc value: Expected=%d, Actual=%f", 72, m1[0][0]);
}

void test_mops_te(void)
{
    Matrix m1(5,5,2);

    m1 *= 6;
    
    TEST_CHECK_(m1.row() == 5, "matrix te row: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.row());
    TEST_CHECK_(m1.col() == 5, "matrix te col: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.col());
    TEST_CHECK_(m1[0][0] == 12, "matrix te value: Expected=%d, Actual=%f", 12, m1[0][0]);
}

void test_mops_pe(void)
{
    Matrix m1(5,5,2);
    Matrix m2(5,5,7);
    Matrix m3(3,2,1);

    m1 += m2;
    
    TEST_CHECK_(m1.row() == 5, "matrix pe row: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.row());
    TEST_CHECK_(m1.col() == 5, "matrix pe col: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.col());
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            TEST_CHECK_(m1[i][j] == 9, "matrix pe value: Expected=%d, Actual=%f", 9, m1[i][j]);
        }
    }
    
    TEST_EXCEPTION(m1+=m3, std::invalid_argument);
}

void test_mops_me(void)
{
    Matrix m1(5,5,2);
    Matrix m2(5,5,7);
    Matrix m3(3,2,1);

    m1 -= m2;
    
    TEST_CHECK_(m1.row() == 5, "matrix me row: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.row());
    TEST_CHECK_(m1.col() == 5, "matrix me col: Expected=%ld, Actual=%ld", (unsigned long) 5, m1.col());
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            TEST_CHECK_(m1[i][j] == -5, "matrix me value: Expected=%d, Actual=%f", -5, m1[i][j]);
        }
    }
    
    TEST_EXCEPTION(m1-=m3, std::invalid_argument);
}

void test_mops_sum(void)
{
    Matrix m(2,3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;

    Vector sum0 = sum(m,0);
    Vector sum1 = sum(m,1);

    TEST_EXCEPTION(sum(m,3), std::invalid_argument);

    TEST_CHECK_(sum0[0] == 5, "matrix sum row: Expected=%f, Actual=%f", 5., sum0[0]);
    TEST_CHECK_(sum0[1] == 7, "matrix sum row: Expected=%f, Actual=%f", 7., sum0[1]);
    TEST_CHECK_(sum0[2] == 9, "matrix sum row: Expected=%f, Actual=%f", 9., sum0[2]);
    TEST_CHECK_(sum1[0] == 6, "matrix sum col: Expected=%f, Actual=%f", 6., sum1[0]);
    TEST_CHECK_(sum1[1] == 15, "matrix sum col: Expected=%f, Actual=%f", 15., sum1[1]);
}

void test_mops_mean(void)
{
    Matrix m(2,3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;

    Vector mean0 = mean(m,0);
    Vector mean1 = mean(m,1);

    TEST_EXCEPTION(mean(m,3), std::invalid_argument);

    TEST_CHECK_(mean0[0] == 2.5, "matrix mean row: Expected=%f, Actual=%f", 2.5, mean0[0]);
    TEST_CHECK_(mean0[1] == 3.5, "matrix mean row: Expected=%f, Actual=%f", 3.5, mean0[1]);
    TEST_CHECK_(mean0[2] == 4.5, "matrix mean row: Expected=%f, Actual=%f", 4.5, mean0[2]);
    TEST_CHECK_(mean1[0] == 2, "matrix mean col: Expected=%f, Actual=%f", 2., mean1[0]);
    TEST_CHECK_(mean1[1] == 5, "matrix mean col: Expected=%f, Actual=%f", 5., mean1[1]);
}

void test_mops_stdevp(void)
{
    Matrix m(2,3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;

    Vector s0 = stdevp(m,0);
    Vector s1 = stdevp(m,1);

    TEST_EXCEPTION(stdevp(m,3), std::invalid_argument);

    TEST_CHECK_(s0[0] == 1.5, "matrix std row: Expected=%f, Actual=%f", 1.5, s0[0]);
    TEST_CHECK_(s0[1] == 1.5, "matrix std row: Expected=%f, Actual=%f", 1.5, s0[1]);
    TEST_CHECK_(s0[2] == 1.5, "matrix std row: Expected=%f, Actual=%f", 1.5, s0[2]);
    TEST_CHECK_(s1[0]-0.81649 <= 0.0001, "matrix std col: Expected=%f, Actual=%f", 0.81649, s1[0]);
    TEST_CHECK_(s1[1]-0.81649 <= 0.0001, "matrix std col: Expected=%f, Actual=%f", 0.81649, s1[1]);
}

void test_mops_stdevs(void)
{
    Matrix m(2,3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;

    Vector s0 = stdevs(m,0);
    Vector s1 = stdevs(m,1);

    TEST_EXCEPTION(stdevs(m,3), std::invalid_argument);

    TEST_CHECK_(s0[0] - 2.12132 <= 0.0001, "matrix std row: Expected=%f, Actual=%f", 2.12132, s0[0]);
    TEST_CHECK_(s0[1] - 2.12132 <= 0.0001, "matrix std row: Expected=%f, Actual=%f", 2.12132, s0[1]);
    TEST_CHECK_(s0[2] - 2.12132 <= 0.0001, "matrix std row: Expected=%f, Actual=%f", 2.12132, s0[2]);
    TEST_CHECK_(s1[0] == 1, "matrix std col: Expected=%f, Actual=%f", 1., s1[0]);
    TEST_CHECK_(s1[1] == 1, "matrix std col: Expected=%f, Actual=%f", 1., s1[1]);
}

void test_mv_plus(void)
{
    Matrix m1(2,2,1);
    Vector v1(2,7);
    Vector v2(3,7);

    Matrix m = m1 + v1;
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            TEST_CHECK_(m[i][j] == 8, "matrix vector plus value: Expected=%f, Actual=%f", 8., m[i][j]);
        }
    }

    TEST_EXCEPTION(m1+v2, std::invalid_argument);
}

void test_mv_minus(void)
{
    Matrix m1(2,2,1);
    Vector v1(2,7);
    Vector v2(3,7);

    Matrix m = m1 - v1;
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            TEST_CHECK_(m[i][j] == -6, "matrix vector minus value: Expected=%f, Actual=%f", -6., m[i][j]);
        }
    }

    TEST_EXCEPTION(m1-v2, std::invalid_argument);
}

void test_vcal_pct(void)
{
    Vector v1(4);
    
    for (int i = 0; i < 4; i++) v1[i] = i+1;

    Vector v = pct_change(v1);
    
    TEST_CHECK_(v[0] == 1, "vector pct value0: Expected=%f, Actual=%f", 1., v[0]);
    TEST_CHECK_(v[1] == 0.5, "vector pct value1: Expected=%f, Actual=%f", 0.5, v[1]);
    TEST_CHECK_(v[2] - 0.333 <= 0.01, "vector pct value2: Expected=%f, Actual=%f", 0.33, v[2]);
}

void test_mcal_pct(void)
{
    Matrix m(4,4,1);

    Matrix m1 = pct_change(m);
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            TEST_CHECK_(m1[i][j] == 0, "matrix pct value: Expected=%f, Actual=%f", 0., m1[i][j]);
        }
    }
}

void test_vcal_cum(void)
{
    Vector v1(4);
    
    for (int i = 0; i < 4; i++) v1[i] = i+1;

    Vector v = cum_return(v1);
    
    TEST_CHECK_(v[0] == 1, "vector pct value0: Expected=%f, Actual=%f", 1., v[0]);
    TEST_CHECK_(v[1] == 2, "vector pct value1: Expected=%f, Actual=%f", 2., v[1]);
    TEST_CHECK_(v[2] == 3, "vector pct value2: Expected=%f, Actual=%f", 3., v[2]);
}

void test_mcal_cum(void)
{
    Matrix m(4,4,1);

    Matrix m1 = cum_return(m);
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            TEST_CHECK_(m1[i][j] == 0, "matrix pct value: Expected=%f, Actual=%f", 0., m1[i][j]);
        }
    }
}

void test_matrix_append(void)
{
    Matrix m(2,2,1);
    Vector v(2,6);
    Vector v1(5,5);

    m.append(v,0);
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            TEST_CHECK_(m[i][j] == 1, "matrix append value: Expected=%f, Actual=%f", 1., m[i][j]);
        }
    }
    
    TEST_CHECK_(m[2][0] == 6, "matrix append value0: Expected=%d, Actual=%f", 6, m[2][0]);
    TEST_CHECK_(m[2][1] == 6, "matrix append value0: Expected=%d, Actual=%f", 6, m[2][1]);

    Matrix m2(2,2,1);
    m2.append(v,1);
    
    TEST_CHECK_(m2[0][2] == 6, "matrix append value1: Expected=%d, Actual=%f", 6, m2[0][2]);
    TEST_CHECK_(m2[1][2] == 6, "matrix append value1: Expected=%d, Actual=%f", 6, m2[1][2]);

    TEST_EXCEPTION(m.append(v1,0), std::invalid_argument);
    TEST_EXCEPTION(m.append(v1,1), std::invalid_argument);
}

// DO NOT MODIFY CODE BELOW
TEST_LIST =
{
    { "void test_Vector_default_constructor(void);", test_Vector_default_constructor },
    { "void test_Vector_parameterized_constructor(void);", test_Vector_parameterized_constructor },
    { "void test_Vector_parameterized_constructor_invalid_arg(void);", test_Vector_parameterized_constructor_invalid_arg },
    { "void test_Vector_stdvector_constructor(void);", test_Vector_stdvector_constructor },
    { "void test_Matrix_default_constructor(void);", test_Matrix_default_constructor},
    { "void test_Matrix_parameterized_constructor(void);", test_Matrix_parameterized_constructor },
    { "void test_Matrix_copy_constructor(void);", test_Matrix_copy_constructor },
    { "void test_vops_plus; ", test_vops_plus},
    { "void test_vops_minus; ", test_vops_minus},
    { "void test_vops_times; ", test_vops_times},
    { "void test_vops_timesc; ", test_vops_timesc},
    { "void test_vops_exp; ", test_vops_exp},
    { "void test_vops_pe; ", test_vops_pe},
    { "void test_vops_me; ", test_vops_me},
    { "void test_vops_te; ", test_vops_te},
    { "void test_vops_sum; ", test_vops_sum},
    { "void test_vops_mean; ", test_vops_mean},
    { "void test_vops_stdevp; ", test_vops_stdevp},
    { "void test_vops_stdevs; ", test_vops_stdevs},
    { "void test_mops_plus; ", test_mops_plus},
    { "void test_mops_minus; ", test_mops_minus},
    { "void test_mops_times; ", test_mops_times},
    { "void test_mops_timesc; ", test_mops_timesc},
    { "void test_mops_te; ", test_mops_te},
    { "void test_mops_pe; ", test_mops_pe},
    { "void test_mops_me; ", test_mops_me},
    { "void test_mops_sum; ", test_mops_sum},
    { "void test_mops_mean; ", test_mops_mean},
    { "void test_mops_stdevp; ", test_mops_stdevp},
    { "void test_mops_stdevs; ", test_mops_stdevs},
    { "void test_mv_plus; ", test_mv_plus},
    { "void test_mv_minus; ", test_mv_minus},
    { "test_vcal_pct; ", test_vcal_pct},
    { "test_mcal_pct; ", test_mcal_pct},
    { "test_vcal_cum; ", test_vcal_cum},
    { "test_mcal_cum; ", test_mcal_cum},
    { "void test_matrix_append; ", test_matrix_append},
    { NULL }
};

