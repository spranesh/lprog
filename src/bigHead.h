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


#include <stdexcept>
#include<vector>
#include <iostream>
#include <iomanip>
using namespace std;

typedef double detType;


template<typename T>
/*------------------------------------------------------
 * abs -- Returns absolute value 
 * Args: T x
 * Returns: T
 *------------------------------------------------------*/
T abs(T x)
{
	if (x<0)
		return -x;
	return x;
}



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
		Matrix<T>& operator=(Matrix<T> &Other);

		// Next we declare the compound equality statements
		Matrix<T>& operator+=(Matrix<T> &Other);
		Matrix<T>& operator-=(Matrix<T> &Other);
		Matrix<T>& operator*=(Matrix<T> &Other);

		// Declare the normal operations
		Matrix<T> operator+(Matrix<T> &Other) const;
		Matrix<T> operator-(Matrix<T> &Other) const;
		Matrix<T> operator*(Matrix<T> &Other) const;

		// Now declare the comparison operations
		bool operator==(Matrix<T> &Other);
		bool operator!=(Matrix<T> &Other);


		// Next we declare the usual Matrix Functions
		Matrix<T> GaussianElimination();
		vector<T> GetRow(size_t row);
		vector<T> GetCol(size_t col);

		bool ExchangeRows(size_t i, size_t j);
		bool ExchangeCols(size_t i, size_t j);




		// What follows next is absolutely Crazy stuff.
		// Read http://www.artima.com/cppsource/simple2.html
		// This Crazy Stuff inspires what is to follow
		// Also readhttp://gcc.gnu.org/ml/gcc-help/2005-02/msg00033.html 
		//friend ostream& operator<< <>(ostream &output, const Matrix<T> &Instance);
		

		// The following functions will be needed when we deal with matrices in Linear Algebra
		// determinat
		// inverse
		// row-echelon form
		// rank

		Matrix<T> Inverse();
		detType Determinant();
		size_t Rank();
		Matrix<T> RowEchelon();


	private:
		size_t nRows;
		size_t mCols;	

		detType det;
		size_t rank;
		
};

// A function to tell how ostream should deal with a matrix


// The following exception is raised when two incomaptible matrices are asked to be multiplied
// added or subtracted. 
class IncompatibleMatricesException : public runtime_error
{
	public:
		IncompatibleMatricesException()
			:runtime_error("Attempted to operate on Incompatible Matrices") {}
};

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
Matrix<T>& Matrix<T>::operator=(Matrix<T> &Other)
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
Matrix<T>& Matrix<T>::operator+=(Matrix<T> &Other)
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
Matrix<T>& Matrix<T>::operator-=(Matrix<T> &Other)
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
Matrix<T>& Matrix<T>::operator*=(Matrix<T> &Other)
{
	Matrix<T> newThis = *this * Other;

	*this = newThis;

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
Matrix<T> Matrix<T>::operator+(Matrix<T> &Other) const
{

	int i, j;
	static Matrix<T> returnMatrix (nRows, mCols);

	if(nRows != Other.GetNumRows()||mCols != Other.GetNumCols())
		throw IncompatibleMatricesException();

	else
	{
		for(i=0;i<nRows;i++)
			for(j=0;j<mCols;j++)
				returnMatrix.matrix[i][j] = 
					matrix[i][j] + Other.matrix[i][j];
	}

	return returnMatrix;
}



/*------------------------------------------------------
 * Matrix<T>::operator- -- overloads the - operator
 * Args: const Matrix<T> &Other
 * Returns: Matrix<T>&
 * const in nature since *this is not changed
 *------------------------------------------------------*/
template <typename T> 
Matrix<T> Matrix<T>::operator-(Matrix<T> &Other) const
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

	return returnMatrix;
}


/*------------------------------------------------------
 * Matrix<T>::operator* -- overloads the * operator
 * Args: const Matrix<T> &Other
 * Returns: Matrix<T>&
 * const in nature since *this is not changed
 *------------------------------------------------------*/
template <typename T> 
Matrix<T> Matrix<T>::operator*(Matrix<T> &Other) const
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
				returnMatrix.matrix[i][j]=0;

				for(k=0;k<mCols;k++)
					returnMatrix.matrix[i][j] += 
						matrix[i][k] * Other.matrix[k][j];
			}
	}

	return returnMatrix;
}

/*------------------------------------------------------
 * operator== -- overloads the equality operator
 * Args: constant reference to another matrix
 * Returns: boolean value
 *------------------------------------------------------*/
template <typename T> 
bool Matrix<T>::operator==(Matrix<T> &Other)
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
bool Matrix<T>::operator!=(Matrix<T> &Other)
{
	return !(*this == Other);
}



template <typename T> 
Matrix<T>& Matrix<T>::Inverse()
{


}

template <typename T> 
T Matrix<T>::Determinant()
{


}

template <typename T>
/*------------------------------------------------------
 * Matrix<T>::GaussianElimination -- 
 * Args:  
 * Returns: Matrix<T>
 * Throws:
 * See:
 * Bugs:
 *------------------------------------------------------*/
Matrix<T> Matrix<T>::GaussianElimination( )
{

	Matrix<T> copy(nRows, mCols);
	copy = *this;

	return copy;

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
 * Matrix<T>::ExchangeRows -- 
 * Args: int i, int j
 * Returns: bool
 *------------------------------------------------------*/
template<typename T>
bool Matrix<T>::ExchangeRows(size_t i, size_t j)
{
	if(i>=nRows || j>=nRows )
		return false;
	if(i==j)
		return true;
	T *temp;

	temp = matrix[i];
	matrix[i] = matrix[j];
	matrix[j] = temp;

	return true;
}
	
template<typename T>
bool Matrix<T>::ExchangeCols(size_t i, size_t j)
{
	if(i>=mCols || j>=mCols )
		return false;
	if(i==j)
		return true;
	T temp;
	int t;
	for(t=0;t<nRows;t++)
	{
		temp = matrix[t][i];
		matrix[t][i] = matrix[t][j];
		matrix[t][j] = temp;
	}

	return true;
}


/*------------------------------------------------------
 * Matrix<T>::Inverse -- 
 * Args:  
 * Returns: Matrix<T>
 *------------------------------------------------------*/
template<typename T>
Matrix<T> Matrix<T>::Inverse( )
{





}

/*------------------------------------------------------
 * Matrix<T>::Determinant -- 
 * Args:  
 * Returns: detType
 *------------------------------------------------------*/
template<typename T>
detType Matrix<T>::Determinant( )
{




}


/*------------------------------------------------------
 * Matrix<T>::RowEchelon -- 
 * Args:  
 * Returns: Matrix<T>
 *------------------------------------------------------*/
template<typename T>
Matrix<T> Matrix<T>::RowEchelon( )
{








}

/*------------------------------------------------------
 * Matrix<T>::Rank -- 
 * Args:  
 * Returns: size_t
 *------------------------------------------------------*/
template<typename T>
size_t Matrix<T>::Rank( )
{





}




/*------------------------------------------------------
 * &operator<< -- overloading the << operator
 * Args: ostream &output, const Matrix &Instance
 * Returns: ostream
 * Pretty Print
 *------------------------------------------------------*/
/* T FOR YOU
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
*/


