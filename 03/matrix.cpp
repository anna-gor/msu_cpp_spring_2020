#include "matrix.h"
#include <stdexcept>
#include <new>

using namespace std;

Matrix::Row::Row(int* matrix, size_t cols)
{
    array = matrix;
    length = cols;
}

int& Matrix::Row::operator[](size_t col)
{
    if (col <= length)
        return *(array + col);
    
    
    throw out_of_range("out of range");
    
}

const int Matrix::Row::operator[](size_t col) const
{
    if (col <= length)
        return *(array + col);
        
    throw out_of_range("out of range");
}

Matrix::Matrix(size_t num_rows, size_t num_cols)
    : cols(num_cols)
    , rows(num_rows)
{
    
    matrix = (int*)(malloc(num_rows * num_cols * sizeof(int)));
    if (matrix == NULL)
        throw bad_alloc();
}

Matrix::~Matrix()
{
    free(matrix);
}

size_t Matrix::getRows() const
{
    return rows;
}

size_t Matrix::getColumns() const
{
    return cols;
}

Matrix& Matrix::operator*=(int n)
{
    for (size_t i = 0; i < cols * rows; ++i) {
        matrix[i] = matrix[i] * n;
    }
    return *this;
}

bool Matrix::operator==(const Matrix& other) const
{
    for (size_t i = 0; i < cols * rows; ++i)
        if (matrix[i] != other.matrix[i])
            return false;
    return true;
}

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

Matrix::Row Matrix::operator[](size_t row)
{
    try {
        return Row(matrix + row * cols, cols);
    }
    catch (const std::out_of_range) {
        throw out_of_range("out of range");
    }
}

const Matrix::Row Matrix::operator[](size_t row) const
{
    try {
        const Row res(matrix + row * cols, cols);
        return res;
    }
    catch (const std::out_of_range) {
        throw out_of_range("out of range");
    }
}
