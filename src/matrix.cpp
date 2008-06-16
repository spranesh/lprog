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

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;

/*------------------------------------------------------
 * Matrix -- constructor for the Matrix Class
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
	*this = *this * Other;

	// we return *this only to ensure that we can
	// have for whatever reason, a chain of assignments
	// and thereby sticking to the C rule of every statement
	// evaluating to something.
	return *this;
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
	int i, j, k;
	Matrix <T> returnMatrix (nRows, Other.GetNumCols());

	if(mCols != Other.GetNumCols())
		throw IncompatibleMatricesException();

	else
	{
		// we take Sigma(A[i][k]*B[k][j]) to form C[i][j]
		for (i=0;i<nRows;i++)
			for(j=0;j<Other.GetNumCols();j++)
			{
				returnMatrix[i][j]=0;

				for(k=0;k<mCols;k++)
					returnMatrix[i][j] += 
						matrix[i][k] * Other.matrix[k][j];
			}
	}

	return &returnMatrix;
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
{	// This function was coded based on the pseudo code given at 
	// http://en.wikipedia.org/wiki/Hermite_normal_form#Pseudocode
	// Please check URL for further clarification

	Matrix<T> copy(nRows, mCols);
	copy = *this;

	size_t lead = 0;
	size_t rowCount = copy.nRows;
	size_t columnCount = copy.mCols;

	for(size_t r=0;r<rowCount;++r)
	{
		if(columnCount<=lead)
			break;
		size_t i=r;
		while(copy.matrix[i][lead]==0)
		{
			++i;
			if(rowCount == i)
			{
				i=r;
				++lead;
				if(columnCount == lead)
					break;
			}
		}

		//swap rows i and r 
		for(size_t j=0;j<columnCount; ++j)
		{
			T temp;
			temp = copy.matrix[i][j];
			copy.matrix[i][j]=copy.matrix[r][j];
			copy.matrix[r][j]=temp;
		}

		//Divide row r by copy[r][lead]
		for(size_t j=0; j<columnCount; ++j)
		{
			if(copy.matrix[r][lead]!=0)
				copy.matrix[r][j]/=copy.matrix[r][lead];
		}

		//FOR all rows j, from 0 to number of rows, every row except r
		//Subtract copy[j][lead] multiplied by row r from row j 
		//END FOR
		for(size_t j=0; j<rowCount; ++j)
		{
			if(j!=r)
				for(size_t k=0; k<columnCount; ++k)
					copy.matrix[j][k]-=copy.matrix[j][lead]*copy.matrix[r][k];
		}

		++lead;
	}

	return copy;



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



/*------------------------------------------------------
 * Matrix<T>::GetRow -- Get the 'row' Row
 * Args: size_t row
 * Returns: vector<T>
 *------------------------------------------------------*/
template <typename T> 
vector<T> Matrix<T>::GetRow(size_t row)
{
	// the (row)th row will have mCols elements
	vector<T> rowAsked;

	for(size_t j = 0; j<mCols; j++)
		rowAsked.push_back(matrix[row][j]);

	return rowAsked;
}


/*------------------------------------------------------
 * Matrix<T>::GetCol -- Get the 'col' Column
 * Args: size_t col
 * Returns: vector<T>
 *------------------------------------------------------*/
template <typename T> 
vector<T> Matrix<T>::GetCol(size_t col)
{
	vector<T> colAsked;

	for(size_t i = 0; i<mCols; i++)
		colAsked.push_back(matrix[i][col]);

	return colAsked;
}



/*------------------------------------------------------
 * &operator<< -- overloading the << operator
 * Args: ostream &output, const Matrix &Instance
 * Returns: ostream
 * Pretty Print
 *------------------------------------------------------*/
template <typename T> 
ostream& operator<<(ostream &output, const Matrix<T> &Instance)
{
	for (int i=0; i<Instance.GetNumRows(); i++)
	{
		for (int j=0; j<Instance.GetNumCols(); j++)
			output << setw(5) << Instance.matrix[i][j];
		output << endl; 
	}
return output; 
} 


