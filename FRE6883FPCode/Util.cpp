#include "Util.h"

Matrix PctChange(const Matrix &mtx)
{
    unsigned int nrow = mtx.Row();
    unsigned int ncol = mtx.Col();

    Matrix M(nrow, ncol - 1);

    for (unsigned int r = 0; r < nrow; r++)
        for (unsigned int c = 0; c < ncol - 1; c++)
            M[r][c] = (mtx[r][c+1] - mtx[r][c]) / mtx[r][c];

    return M;
}

bool IsNumber(const std::string s)
{
    for (int i = 0; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}

int GetN()
{
    std::string buffer;
    int N;

    std::cout << "Please enter N (N>=30): ";
    std::cin >> buffer;

    if (!IsNumber(buffer))
    {
        PrintError("N must be a positive integer.");
        return -1;
    }

    N = stoi(buffer);

    if (N < 30)
    {
        PrintError("N must be >= 30.");
        return -1;
    }

    return N;
}

void PrintMenu()
{
    std::cout << "MENU" << std::endl;
    std::cout << "R) Enter N to retrieve 2N+1 days of historical price data for all stocks." << std::endl;
    std::cout << "F) Pull information for one stock from one group." << std::endl;
    std::cout << "S) Show AAR, AAR-SD, CAAR and CAAR-STD for one group." << std::endl;
    std::cout << "P) Show the Excel or gnuplot graph with CAAR for all 3 groups." << std::endl;
    std::cout << "X) Exit your program." << std::endl;
}

void PrintError(std::string msg)
{
    std::cerr << "ERROR: " << msg << std::endl;
}