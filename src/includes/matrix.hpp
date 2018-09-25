#pragma once
#include <stdio.h>
#include <cmath>

class Matrix
{
  public:
	int row;
	int col;
	double **matrix;

	Matrix(int _row, int _col);
	Matrix operator*(Matrix &m);
	Matrix operator*(double x);
	double det();
	Matrix foo(int r, int c);
	Matrix transpose();
	Matrix inverse();
	void print();
	~Matrix();
};