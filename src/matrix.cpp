#include "includes/matrix.hpp"

Matrix::Matrix(int _row, int _col)
{
    row = _row;
    col = _col;

    matrix = new double *[_row];
    for (int i = 0; i < _row; i++)
        matrix[i] = new double[_col];
}

Matrix Matrix::operator*(Matrix m)
{
    Matrix out(this->row, m.col);

    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < m.col; j++)
        {
            double tmp = 0.0f;
            for (int k = 0; k < this->col; k++)
                tmp += this->matrix[i][k] * m.matrix[k][j];
            out.matrix[i][j] = tmp;
        }
    }

    return out;
}

void Matrix::print()
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
            printf("%f ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

Matrix::~Matrix()
{
    for (int i = 0; i < row; i++)
        delete matrix[i];
    delete matrix;
}