/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  Contains function definitions for matrix.cpp
 *
 *        Created:  Friday 13 June 2008 08:32:02  IST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Naveen, Pranesh, Samhita
 *
 * =====================================================================================
 */


# ifndef MATRIX_H
# define MATRIX_H

# include<vector>
using namespace std;

# include"exceptions.h"


template <typename T>
class Matrix
{
	public:
		// We define as a double dimensional array. This should
		// speed up things quite a lot
		T** matrix;

		//Constructor for the class, with two arguments
		Matrix(size_t n, size_t m);
		
		// functions for accessing number of rows, and number of cols
		size_t GetNumRows();
		size_t GetNumCols();

		// We first overload operators as shown below.
		// If you are new to this, I suggest you have a look at 
		// http://www.cs.caltech.edu/courses/cs11/material/cpp/donnie/cpp-ops.html
		// define  the equality statement
		Matrix<T>& operator=(const Matrix<T> &Other);

		// Next we declare the compound equality statements
		Matrix<T>& operator+=(const Matrix<T> &Other);
		Matrix<T>& operator-=(const Matrix<T> &Other);
		Matrix<T>& operator*=(const Matrix<T> &Other);

		// Declare the normal operations
		Matrix<T>& operator+(const Matrix<T> &Other) const;
		Matrix<T>& operator-(const Matrix<T> &Other) const;
		Matrix<T>& operator*(const Matrix<T> &Other) const;

		// Now declare the comparison operations
		bool operator==(const Matrix<T> &Other);
		bool operator!=(const Matrix<T> &Other);


		// Next we declare the usual Matrix Functions
		Matrix<T>& RowEchelon(); // Return another Matrix which is a RowEchelon form of this
		Matrix<T>& Inverse();
		size_t Rank();
		T Determinant();
		
		vector<T> GetRow(size_t row);
		vector<T> GetCol(size_t col);


	private:
		size_t nRows;
		size_t mCols;	
		
};

#endif





