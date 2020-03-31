#include "matrix.h"

using namespace std;

int main()
{

    size_t rows = 10;
    size_t cols = 15;

    Matrix matrix(rows, cols);

    assert(matrix.getRows() == 10 && matrix.getColumns() == 15);

    matrix[0][1] = 79;
    assert(matrix[0][1] == 79);

    matrix[0][1] = 6;
    matrix *= 7;
    assert(matrix[0][1] == 42);

    Matrix another_matrix(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = (i + j) * j;
        }
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            another_matrix[i][j] = (i + j) * j;
        }
    }

    assert(another_matrix == matrix);

    matrix[0][1] = 100;
    assert(another_matrix != matrix);

    another_matrix[0][1] = 100;
    assert(another_matrix == matrix);

    cout << "All tests are passed\n";
}
