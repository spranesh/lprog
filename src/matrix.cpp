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


template <typename T>
Matrix<T>::Matrix<T>& operator=(const Matrix<T> &Other)
{
	

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

template <typename T> 
Matrix<T>::bool operator==(const Matrix<T> &Other)
{


}

template <typename T> 
Matrix<T>::bool operator!=(const Matrix<T> &Other)
{


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


}

template <typename T> 
Matrix<T>::vector<T> GetCol(size_t col)
{


}


