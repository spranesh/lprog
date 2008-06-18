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
		Matrix(size_t n, size_t m);
		Matrix(const Matrix<T> &Other);

		size_t GetNumRows() const;
		size_t GetNumCols() const;

		void Print() const;

		vector<T> GetRow(size_t row) const;
		vector<T> GetCol(size_t col) const;

		Matrix<T>& operator=(Matrix<T> &Other);

		Matrix<T>& operator+=(Matrix<T> &Other);
		Matrix<T>& operator-=(Matrix<T> &Other);
		Matrix<T>& operator*=(Matrix<T> &Other);

		Matrix<T> operator+(Matrix<T> &Other) const;
		Matrix<T> operator-(Matrix<T> &Other) const;
		Matrix<T> operator*(Matrix<T> &Other) const;

		T& operator() (size_t row, size_t col);
		T operator() (size_t row, size_t col) const;

		bool operator==(Matrix<T> &Other) const;
		bool operator!=(Matrix<T> &Other) const;

		bool ExchangeRows(size_t i, size_t j);
		bool ExchangeCols(size_t i, size_t j);


		void Print() const;
		
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

#include "matrix.cpp"
// http://www.neowin.net/forum/index.php?s=b67d2e75582fb412b7b5c1152e934836&showtopic=633585&pid=589358876&st=0&#entry589358876

#endif





