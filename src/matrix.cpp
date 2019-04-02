#include "includes/matrix.hpp"

Matrix::Matrix(int row, int col)
{
    this->row = row;
    this->col = col;

    matrix.resize(row);
    for(int i = 0; i < row; i++)
        matrix[i].resize(col);
}

Matrix Matrix::operator*(Matrix &m) const
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

Matrix Matrix::operator*(double x) const
{
    Matrix out(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            out.matrix[i][j] = matrix[i][j] * x;

    return out;
}

void Matrix::print() const
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%f\t", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}