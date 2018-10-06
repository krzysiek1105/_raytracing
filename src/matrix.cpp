#include "includes/matrix.hpp"

Matrix::Matrix(int _row, int _col)
{
    row = _row;
    col = _col;

    matrix.resize(_row);
    for(int i = 0; i < _row; i++)
        matrix[i].resize(_col);
}

Matrix Matrix::operator*(Matrix &m)
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

Matrix Matrix::operator*(double x)
{
    Matrix out(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            out.matrix[i][j] = matrix[i][j] * x;

    return out;
}

Matrix Matrix::foo(int r, int c)
{
    Matrix out(row - 1, col - 1);

    int x = 0;
    for (int i = 0; i < row; i++)
    {
        if (i == r)
            continue;

        int y = 0;
        for (int j = 0; j < col; j++)
        {
            if (j == c)
                continue;
            out.matrix[x][y] = matrix[i][j];
            y++;
        }
        x++;
    }

    return out;
}

double Matrix::det()
{
    if (row != col)
        return -1.0;

    if (row == 1)
        return matrix[0][0];
    else if (row == 2)
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    else
    {
        double det = 0.0;
        for (int k = 0; k < col; k++)
            det += matrix[0][k] * pow(-1.0, (k + 1) + 1) * this->foo(0, k).det();

        return det;
    }
}

Matrix Matrix::transpose()
{
    Matrix out(col, row);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            out.matrix[j][i] = matrix[i][j];

    return out;
}

Matrix Matrix::inverse()
{
    Matrix comp(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            comp.matrix[i][j] = pow(-1.0, (i + 1) + (j + 1)) * this->foo(i, j).det();

    Matrix out = comp * (1 / this->det());
    return out.transpose();
}

void Matrix::print()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            printf("%f\t", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

Matrix::~Matrix()
{
}