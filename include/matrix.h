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
# include"exceptions.h"
using namespace std;

#define SMALL 0.00001
#define ABS(X) ((X) < 0 ? -(X) : (X))
typedef double detType;


template <typename T>
class Matrix
{
	public:
		// We define as a double dimensional array. This should
		// speed up things quite a lot

		//Constructor for the class, with two arguments
		Matrix(size_t n, size_t m);
		Matrix(const Matrix<T> &Other);

		// functions for accessing number of rows, and number of cols
		size_t GetNumRows();
		size_t GetNumCols();

		//functions for accessing rows and cols
		vector<T> GetRow(size_t row);
		vector<T> GetCol(size_t col);


		// We first overload operators as shown below.

		// If you are new to this, I suggest you have a look at 
		// http://www.cs.caltech.edu/courses/cs11/material/cpp/donnie/cpp-ops.html
		// define  the equality statement
		Matrix<T>& operator=(Matrix<T> &Other);

		// Next we declare the compound equality statements
		Matrix<T>& operator+=(Matrix<T> &Other);
		Matrix<T>& operator-=(Matrix<T> &Other);
		Matrix<T>& operator*=(Matrix<T> &Other);

		// Declare the normal operations
		Matrix<T> operator+(Matrix<T> &Other) const;
		Matrix<T> operator-(Matrix<T> &Other) const;
		Matrix<T> operator*(Matrix<T> &Other) const;

		// We declare the subscript overloads
		T& operator() (size_t row, size_t col);
		T operator() (size_t row, size_t col) const;


		// Now declare the comparison operations
		bool operator==(Matrix<T> &Other);
		bool operator!=(Matrix<T> &Other);


		// Next we declare the usual Matrix Functions

		bool ExchangeRows(size_t i, size_t j);
		bool ExchangeCols(size_t i, size_t j);


		void Print();
		

		// Important Matrix Functions
		Matrix<T> Inverse();
		detType Determinant();
		size_t Rank();
		Matrix<T> RowEchelon();
		Matrix<T> ReducedRowEchelon();

		// Read http://www.artima.com/cppsource/simple2.html
		// This Crazy Stuff inspires what is to follow
		// Also readhttp://gcc.gnu.org/ml/gcc-help/2005-02/msg00033.html 
		// friend ostream& operator<< <>(ostream &output, const Matrix<T> &Instance);

	private:
		T** matrix;

		size_t nRows;
		size_t mCols;	

		detType det;
		size_t rank;

		bool rankValid, detValid;
		void ClearValidity();
};

#endif





