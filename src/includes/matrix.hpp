#pragma once
#include <stdio.h>
#include <cmath>
#include <vector>

class Matrix
{
  public:
	int row;
	int col;
	std::vector<std::vector<double>> matrix;

	Matrix(int row, int col);

	Matrix operator*(Matrix &m) const;
	Matrix operator*(double x) const;

	void print() const;
};