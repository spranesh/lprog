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

#define SMALL 0.00000001
#define ABS(X) ((X<0)?(-X):(X))
typedef double detType;


template <typename T>
class Matrix
{
	public:
		// We define as a double dimensional array. This should
		// speed up things quite a lot
		T** matrix;

		//Constructor for the class, with two arguments
		Matrix(size_t n, size_t m);
		Matrix(const Matrix<T> &Other);

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

		// We declare the subscript overloads
		T& operator() (size_t row, size_t col);
		T operator() (size_t row, size_t col) const;


		// Now declare the comparison operations
		bool operator==(Matrix<T> &Other);
		bool operator!=(Matrix<T> &Other);


		// Next we declare the usual Matrix Functions
		Matrix<T> GaussianElimination();
		vector<T> GetRow(size_t row);
		vector<T> GetCol(size_t col);

		bool ExchangeRows(size_t i, size_t j);
		bool ExchangeCols(size_t i, size_t j);


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
		Matrix<T> ReducedRowEchelon();

		void Print();

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

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &Other)
{
	nRows = Other.nRows;
	mCols = Other.mCols;

	matrix = new T*[nRows];
	for(size_t i=0;i<nRows; ++i)
		matrix[i] = new T[mCols];

	for(size_t i=0;i<nRows; ++i)
		for(size_t j=0;j<mCols; ++j)
			matrix[i][j]=Other.matrix[i][j];
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
 * Matrix<T>::Print -- Prints a matrix
 * Args:  
 * Returns: void
 *------------------------------------------------------*/
template <typename T>
void Matrix<T>::Print()
{
	size_t i, j;

	for(i=0;i<nRows;i++)
	{
		cout << setiosflags(ios::right);
		cout << setiosflags(ios::fixed);
		for(j=0;j<mCols;j++)
			cout << setprecision(6)<<matrix[i][j]<<setw(15);

		cout << "\n";
	}

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
 *  -- 
 * Args: size_t row, size_t col
 * Returns: T & 
 * Throws: IncompatibleMatricesException
 *------------------------------------------------------*/
template<typename T>
T & Matrix<T>::operator() (size_t row, size_t col)
{
	if (row >= nRows || col >= mCols)
		throw IncompatibleMatricesException();
	return matrix[row][col];
}
 
/*------------------------------------------------------
 *  -- 
 * Args:size_t row, size_t col
 * Returns: T 
 * Throws: IncompatibleMatricesException
 *------------------------------------------------------*/
template<typename T>
T Matrix<T>::operator() (size_t row, size_t col) const
{
	if (row >= nRows || col >= mCols)
		throw IncompatibleMatricesException();
	return matrix[row][col];
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

/*----------------------------------------------------------------------------
 * Matrix<T>::ReducedRowEchelon -- Returns the RowEchelon form of the calling Matrix
 * Args: None 
 * Returns: Matrix<T>&
 *---------------------------------------------------------------------------*/
template <typename T> 
Matrix<T> Matrix<T>::ReducedRowEchelon( )
{
	// This function was coded based on the pseudo code given at 
	// http://en.wikipedia.org/wiki/Hermite_normal_form#Pseudocode
	// Please check URL for further clarification
	Matrix<T> copy(nRows, mCols);
	copy = *this;

	size_t lead = 0;
	const size_t rowCount = copy.nRows;
	const size_t columnCount = copy.mCols;

	size_t i,r;
	for(r=0;r<rowCount;++r)
	{
		if(columnCount<=lead)
		{
			//Following line for debugging only
			//cout<<"Stopping at condition 1";
			return copy;
		}

		i=r;
		while(copy.matrix[i][lead]==0)
		{
			++i;
			if(rowCount == i)
			{
				i=r;
				++lead;
				if(columnCount == lead)
				{	
					//Following line for debugging only
					//cout<<"Stopping at condition 2";
					return copy;
				}
			}
		}

		//swap rows i and r 
		ExchangeRows(i, r);

		T divider = copy.matrix[r][lead];
		//Divide row r by copy[r][lead]
		for(size_t j=0; j<columnCount; ++j)
		{
			copy.matrix[r][j]/=divider;
		}

		//FOR all rows j, from 0 to number of rows, every row except r
		//Subtract copy[j][lead] multiplied by row r from row j 
		//END FOR
		for(size_t j=0; j<rowCount; ++j)
		{
			if(j!=r)
			{
				T multiplier = copy.matrix[j][lead];
				for(size_t k=0; k<columnCount; ++k)
					copy.matrix[j][k]-=multiplier*copy.matrix[r][k];
			}
		}

		++lead;
	}

	return copy;
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
	// we will return the RowEchelon Matrix to the user
	Matrix<T> R(nRows, mCols);
	size_t i=0, j, k, l, t;
	T mx;
	detType factor;

	// Breif Description of the Algorithm :
	// Run through columns 1 to mCols-1 using var j
	// start with i=0. For each col find the maximum 
	// absolute element, below i, mx, at position t.
	// if mx == 0 continue
	// else swap the t and i row, using the swap function.
	// for l in i+1 -> nRows
	//   factor = (l,j)/(i,j) 
	//   (l,j) = 0
	//   for k in j+1 -> mCols
	//   	(l,k) -= (i,j) * factor
	// increment i
	// continue
	
	R = *this;
	

	for(j=0;j<mCols-1 && i<nRows;j++)
	{
		mx = R.matrix[i][j];
		t = i;
		for(l=j+1;l<nRows;l++)
			if(R.matrix[l][j] > mx){ 
				mx = R.matrix[l][j];
				t = l;
			}
		//cout << "("<<mx<<","<<t<<")"<<"max and t\n";


		if(mx==0) continue;
		
		// Else
		if(i!=t) 
			R.ExchangeRows(i, t);

		for(l=i+1; l<nRows; l++)
		{
			factor = R.matrix[l][j]/(detType)(R.matrix[i][j]);
			//cout << "("<<i<<","<<l<<")"<<factor;
			//cout << "\n";
			R.matrix[l][j] = 0;

			for(k=j+1; k<mCols;k++)
				R.matrix[l][k] -= (T) (R.matrix[i][k] * factor);
		}

		//cout<<"After "<< i << "th row \n";
		//R.Print();
		//cout <<"\n\n";
		i+=1;
	}

	//we also compute the rank as a side effect

	return R;

}

/*------------------------------------------------------
 * Matrix<T>::Rank -- 
 * Args: None 
 * Returns: size_t
 *------------------------------------------------------*/
template<typename T>
size_t Matrix<T>::Rank( )
{
	bool isRowEmpty;
	size_t rank;
	size_t i, j;

	for(i=0;i<nRows; ++i)
	{
		isRowEmpty = true;
		for(j=0;j<mCols; ++j)
		{
			if((*this).matrix[i][j]!=0)
				isRowEmpty = false;
		}

		if(isRowEmpty == true)
			break;
	}

	rank = i;
	return rank;

}



/*------------------------------------------------------
 * &operator<< -- overloading the << operator
 * Args: ostream &output, const Matrix &Instance
 * Returns: ostream
 * Pretty Print
 *------------------------------------------------------*/
/*
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


