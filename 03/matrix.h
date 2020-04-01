#pragma once
#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cassert>

class Matrix {
public:
    Matrix(size_t num_rows, size_t num_cols);
    ~Matrix();

    size_t getRows() const;
    size_t getColumns() const;

    class Row {
        int* array;
        size_t length;

    public:
        Row(int* matrix, size_t cols);
        int& operator[](size_t col);
        const int operator[](size_t col) const;
    };

    int* matrix;
    size_t rows;
    size_t cols;

public:
    Matrix& operator*=(int n);
    Row operator[](size_t row);
    const Row operator[](size_t row) const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};
