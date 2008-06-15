/*
 * =====================================================================================
 *
 *       Filename:  matrix.cpp
 *
 *    Description:  Contains function definitions for Matrices
 *
 *        Created:  Friday 13 June 2008 08:30:58  IST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Naveen, Pranesh, Samhita
 *
 * =====================================================================================
 */

#include "matrix.h"
/*------------------------------------------------------
 * Matrix -- init function of the Matrix Class
 * Args: size_t nRows, size_t  mCols
 * Returns: void
 *------------------------------------------------------*/
template <typename T> 
Matrix<T>::void Matrix(size_t n, size_t m)
{
	nRows = n; mCols = m;
	matrix = new T*[nRows];

	for (size_t i=0;i<nRows; i++)
		matrix[i] = new T[nCols];
}


/*------------------------------------------------------
 * operator= -- overloads the = operator for matrices
 * Args: A constant reference to another Matrix, Other
 * Returns: reference to matrix of the same type
 *
 * Ensures no-self-assignment, and resizes matrix if necessary
 *------------------------------------------------------*/
template <typename T>
Matrix<T>::Matrix<T>& operator=(const Matrix<T> &Other)
{
	size_t i, j;

	if(&Other != this) //avoid self assignment
	{	
		// we resize the object if necessary
		if(nRows!=Other.nRows || mCols!=Other.mCols)
		{
			for(i=0; i<nRows; i++)
				delete [] matrix[i];

			delete [] matrix;

			// we now assign space by calling the
			// constructor again
			Matrix(Other.nRows, Other.mCols); // will this Work?
		}

		// now we assign the values of Other to our matrix

		for(i=0;i<nRows;i++)
			for(j=0;j<mCols; j++)
				matrix[i][j] = Other.matrix[i][j];
	}

	return *this;
}



template <typename T> 
Matrix<T>::Matrix<T>& operator+=(const Matrix<T> &Other)
{


}

template <typename T> 
Matrix<T>::Matrix<T>& operator-=(const Matrix<T> &Other)
{


}

template <typename T> 
Matrix<T>::Matrix<T>& operator*=(const Matrix<T> &Other)
{


}

template <typename T> 
Matrix<T>::Matrix<T>& operator+(const Matrix<T> &Other)
{


}

template <typename T> 
Matrix<T>::Matrix<T>& operator-(const Matrix<T> &Other)
{


}

template <typename T> 
Matrix<T>::Matrix<T>& operator*(const Matrix<T> &Other)
{


}

/*------------------------------------------------------
 * operator== -- overloads the equality operator
 * Args: constant reference to another matrix
 * Returns: boolean value
 *------------------------------------------------------*/
template <typename T> 
Matrix<T>::bool operator==(const Matrix<T> &Other)
{
	if(nRows!=Other.nRows || mCols!=Other.mCols)
		return false;

	for(i=0;i<nRows;i++)
		for(j=0;j<mCols;j++)
			if(matrix[i][j]!=Other.matrix[i][j])
				return false;

	return true;
}


template <typename T> 
/*------------------------------------------------------
 * operator== -- overloads the equality operator
 * Args: constant reference to another matrix
 * Returns: boolean value
 * uses the == operator
 *------------------------------------------------------*/
Matrix<T>::bool operator!=(const Matrix<T> &Other)
{
	return !(*this == Other);
}



template <typename T> 
Matrix<T>::Matrix<T>& RowEchelon()
{


}



template <typename T> 
Matrix<T>::Matrix<T>& Inverse()
{


}



template <typename T> 
Matrix<T>::size_t Rank()
{


}



template <typename T> 
Matrix<T>::T Determinant()
{


}



template <typename T> 
Matrix<T>::vector<T> GetRow(size_t row)
{
	// the (row)th row will have mCols elements
	vector<T> rowAsked = new T[mCols];




}


template <typename T> 
Matrix<T>::vector<T> GetCol(size_t col)
{


}


