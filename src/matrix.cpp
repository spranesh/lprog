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
Matrix<T>::Matrix(size_t n, size_t m)
{
	nRows = n; mCols = m;
	matrix = new T*[nRows];

	for (size_t i=0;i<nRows; i++)
		matrix[i] = new T[mCols];
}

/*------------------------------------------------------
 * Matrix<T>::GetNumRows -- return no. of Rows in Matrix
 * Returns: size_t
 *------------------------------------------------------*/
template <typename T>
size_t Matrix<T>::GetNumRows()
{
	return nRows;
}


/*------------------------------------------------------
 * Matrix<T>::GetNumCols -- return no. of Cols in Matrix
 * Returns: size_t
 *------------------------------------------------------*/
template <typename T>
size_t Matrix<T>::GetNumCols()
{
	return mCols;
}


/*------------------------------------------------------
 * operator= -- overloads the = operator for matrices
 * Args: A constant reference to another Matrix, Other
 * Returns: reference to matrix of the same type
 *
 * Ensures no-self-assignment, and resizes matrix if necessary
 *------------------------------------------------------*/
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &Other)
{
	size_t i, j;

	if(&Other != this) //avoid self assignment
	{	
		// we resize the object if necessary
		if(nRows!=Other.GetNumRows() || mCols!=Other.GetNumCols())
		{
			for(i=0; i<nRows; i++)
				delete [] matrix[i];

			delete [] matrix;

			// we now assign space by calling the
			// constructor again
			Matrix(Other.GetNumRows(), Other.GetNumCols()); // will this Work?
		}

		// now we assign the values of Other to our matrix

		for(i=0;i<nRows;i++)
			for(j=0;j<mCols; j++)
				matrix[i][j] = Other.matrix[i][j];
	}

	return *this;
}



/*------------------------------------------------------
 * Matrix<T>::operator+= -- overloads the += operator
 * Args: const Matrix<T> &Other
 * Returns: Matrix<T>&
 *------------------------------------------------------*/
template <typename T> 
Matrix<T>& Matrix<T>::operator+=(const Matrix<T> &Other)
{
	int i, j;

	if(nRows != Other.GetNumRows()||mCols != Other.GetNumCols())
		throw IncompatibleMatricesException();

	else
	{
		for(i=0;i<nRows;i++)
			for(j=0;j<mCols;j++)
				matrix[i][j] += Other.matrix[i][j];
	}

	return *this;
}


/*------------------------------------------------------
 * Matrix<T>::operator-= -- Defines and overloads the -= operator
 * Args: const Matrix<T> &Other
 * Returns: Matrix<T>&
 *------------------------------------------------------*/
template <typename T> 
Matrix<T>& Matrix<T>::operator-=(const Matrix<T> &Other)
{
	int i, j;

	if(nRows != Other.GetNumRows()||mCols != Other.GetNumCols())
		throw IncompatibleMatricesException();

	else
	{
		for(i=0;i<nRows;i++)
			for(j=0;j<mCols;j++)
				matrix[i][j] -= Other.matrix[i][j];
	}

	
	return *this;
}


/*------------------------------------------------------
 * Matrix<T>::operator*= -- implements the *= operator using the
 * operator
 * Args: const Matrix<T> &Other
 * Returns: Matrix<T>&
 *------------------------------------------------------*/
template <typename T> 
Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &Other)
{
	// There is no direct way to do this.
	// Hence we define C = A*B using the * operator
	// and then delete A, and return C

}


/*------------------------------------------------------
 * Matrix<T>::operator+ -- overloads the sum of two matrices
 * Args: const Matrix<T> &Other
 * Returns: Matrix<T>&
 * const in nature since *this is not changed
 *------------------------------------------------------*/
template <typename T> 
Matrix<T>& Matrix<T>::operator+(const Matrix<T> &Other) const
{

	int i, j;
	Matrix<T> returnMatrix (nRows, mCols);

	if(nRows != Other.GetNumRows()||mCols != Other.GetNumCols())
		throw IncompatibleMatricesException();

	else
	{
		for(i=0;i<nRows;i++)
			for(j=0;j<mCols;j++)
				returnMatrix.matrix[i][j] = 
					matrix[i][j] + Other.matrix[i][j];
	}

	return &returnMatrix;
}



/*------------------------------------------------------
 * Matrix<T>::operator- -- overloads the - operator
 * Args: const Matrix<T> &Other
 * Returns: Matrix<T>&
 * const in nature since *this is not changed
 *------------------------------------------------------*/
template <typename T> 
Matrix<T>& Matrix<T>::operator-(const Matrix<T> &Other) const
{

	int i, j;
	Matrix<T> returnMatrix (nRows, mCols);

	if(nRows != Other.GetNumRows()||mCols != Other.GetNumCols())
		throw IncompatibleMatricesException();

	else
	{
		for(i=0;i<nRows;i++)
			for(j=0;j<mCols;j++)
				returnMatrix.matrix[i][j] = 
					matrix[i][j] - Other.matrix[i][j];
	}

	return &returnMatrix;
}


/*------------------------------------------------------
 * Matrix<T>::operator* -- overloads the * operator
 * Args: const Matrix<T> &Other
 * Returns: Matrix<T>&
 * const in nature since *this is not changed
 *------------------------------------------------------*/
template <typename T> 
Matrix<T>& Matrix<T>::operator*(const Matrix<T> &Other) const
{


}

/*------------------------------------------------------
 * operator== -- overloads the equality operator
 * Args: constant reference to another matrix
 * Returns: boolean value
 *------------------------------------------------------*/
template <typename T> 
bool Matrix<T>::operator==(const Matrix<T> &Other)
{
	int i, j;

	if(nRows!=Other.GetNumRows() || mCols!=Other.GetNumCols())
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
bool Matrix<T>::operator!=(const Matrix<T> &Other)
{
	return !(*this == Other);
}



template <typename T> 
Matrix<T>& Matrix<T>::RowEchelon()
{


}



template <typename T> 
Matrix<T>& Matrix<T>::Inverse()
{


}



template <typename T> 
size_t Matrix<T>::Rank()
{


	return;
}



template <typename T> 
T Matrix<T>::Determinant()
{


}



template <typename T> 
vector<T> Matrix<T>::GetRow(size_t row)
{
	// the (row)th row will have mCols elements
	vector<T> rowAsked;

	for(size_t j = 0; j<mCols; j++)
		rowAsked.push_back(matrix[row][j]);

	return rowAsked;
}


template <typename T> 
vector<T> Matrix<T>::GetCol(size_t col)
{
	vector<T> colAsked;

	for(size_t i = 0; i<mCols; i++)
		colAsked.push_back(matrix[i][col]);

	return colAsked;
}


