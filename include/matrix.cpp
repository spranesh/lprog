/*
 * =====================================================================================
 *
 *       Filename:  matrix.cpp
 *
 *    Description:  Contains function definitions for Matrices
 *
 *        Created:  Friday 13 June 2008 08:30:58 IST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Naveen, Pranesh, Samhita
 *
 * =====================================================================================
 */


#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

/*------------------------------------------------------
 * Matrix -- constructor for the Matrix Class
 * Args: size_t nRows, size_t  mCols
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
 * Matrix -- copy constructor for the Matrix Class
 * Args: const Matrix<T> &Other
 *------------------------------------------------------*/
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
			matrix[i][j]=Other(i,j);
}

/*------------------------------------------------------
 * Matrix<T>::ClearValidity() - clears validity of cache
 * Returns: void
 *------------------------------------------------------*/
template <typename T>
void Matrix<T>::ClearValidity()
{
	rankValid = detValid = false;
	rank = 0;
	det = 0;
}

/*------------------------------------------------------
 * Matrix<T>::GetNumRows -- return no. of Rows in Matrix
 * Returns: size_t
 *------------------------------------------------------*/
template <typename T>
size_t Matrix<T>::GetNumRows() const
{
	return nRows;
}

/*------------------------------------------------------
 * Matrix<T>::GetNumCols -- return no. of Cols in Matrix
 * Returns: size_t
 *------------------------------------------------------*/
template <typename T>
size_t Matrix<T>::GetNumCols() const
{
	return mCols;
}

/*------------------------------------------------------
 * Matrix<T>::Print -- Prints a matrix
 * Args: None
 * Returns: void
 *------------------------------------------------------*/
template <typename T>
void Matrix<T>::Print() const
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
 * Ensures no-self-assignment, and resizes matrix if necessary
 *------------------------------------------------------*/
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> &Other)
{
	size_t i, j;
	

	//avoid self assignment
	if(&Other != this) 
	{	
		// we resize the object if necessary
		if(nRows!=Other.GetNumRows() || mCols!=Other.GetNumCols())
		{
			for(i=0; i<nRows; i++)
				delete [] matrix[i];

			delete [] matrix;

			// we now assign space by calling the
			// constructor again
			Matrix(Other.GetNumRows(), Other.GetNumCols());
		}

		for(i=0;i<nRows;i++)
			for(j=0;j<mCols; j++)
				matrix[i][j] = Other(i,j);
	}

	ClearValidity();

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
				matrix[i][j] += Other(i,j);
	}

	ClearValidity();

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
				matrix[i][j] -= Other(i,j);
	}

	
	ClearValidity();

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

	// Returning *this to ensure C style assignment
	
	ClearValidity();

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

	size_t i, j;
	static Matrix<T> returnMatrix (nRows, mCols);

	if(nRows != Other.GetNumRows()||mCols != Other.GetNumCols())
		throw IncompatibleMatricesException();

	else
	{
		for(i=0;i<nRows;i++)
			for(j=0;j<mCols;j++)
				returnMatrix(i,j) = matrix[i][j] + Other(i,j);
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

	size_t i, j;
	Matrix<T> returnMatrix (nRows, mCols);

	if(nRows != Other.GetNumRows()||mCols != Other.GetNumCols())
		throw IncompatibleMatricesException();

	else
	{
		for(i=0;i<nRows;i++)
			for(j=0;j<mCols;j++)
				returnMatrix(i,j) = matrix[i][j] - Other(i,j);
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
	size_t i, j, k;
	Matrix <T> returnMatrix (nRows, Other.GetNumCols());

	if(mCols != Other.GetNumRows())
		throw IncompatibleMatricesException();

	else
	{
		// we take Sigma(A[i][k]*B[k][j]) to form C[i][j]
		for (i=0;i<nRows;i++)
			for(j=0;j<Other.GetNumCols();j++)
			{
				returnMatrix(i,j)=0;

				for(k=0;k<mCols;k++)
					returnMatrix(i,j) += 
						matrix[i][k] * Other(k,j);
			}
	}

	return returnMatrix;
}

/*------------------------------------------------------
 * Matrix<T>::operator()
 * Instead of accessing elements by ObjectName.matrix[i][j],
 * we overload the () so that we can access by ObjectName(i, j)
 * Args: size_t row, size_t col
 * Returns: T & 
 * Throws: IncompatibleMatricesException
 *------------------------------------------------------*/
template<typename T>
T & Matrix<T>::operator() (size_t row, size_t col)
{
	if (row >= nRows || col >= mCols)
		//exception
		throw OutOfBoundsException();

	ClearValidity();

	return matrix[row][col];
}
 
/*------------------------------------------------------
 * Matrix<T>::operator()
 * Instead of accessing elements by ObjectName.matrix[i][j],
 * we overload the () so that we can access by ObjectName(i, j)
 * Args:size_t row, size_t col
 * Returns: T 
 * Throws: IncompatibleMatricesException
 *------------------------------------------------------*/
template<typename T>
T Matrix<T>::operator() (size_t row, size_t col) const
{
	if (row >= nRows || col >= mCols)
		//exception
		throw OutOfBoundsException();
	return matrix[row][col];
} 

/*------------------------------------------------------
 * operator== -- overloads the equality operator
 * Args: constant reference to another matrix
 * Returns: boolean value
 *------------------------------------------------------*/
template <typename T> 
bool Matrix<T>::operator==(Matrix<T> &Other) const
{
	size_t i, j;

	if(nRows!=Other.GetNumRows() || mCols!=Other.GetNumCols())
		return false;

	for(i=0;i<nRows;i++)
		for(j=0;j<mCols;j++)
			if(matrix[i][j]!=Other(i,j))
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
bool Matrix<T>::operator!=(Matrix<T> &Other) const
{
	return !(*this == Other);
}


/*------------------------------------------------------
 * Matrix<T>::operator| -- acts as a pubilc wrapper for 
 * augment
 * Args: Matrix<T> Other
 * Returns: Matrix<T>
 *------------------------------------------------------*/
template<typename T>
Matrix<T> Matrix<T>::operator|(Matrix<T> Other)
{
	return Augment(Other);
}

/*------------------------------------------------------
 * Matrix<T>::GetRow -- Get a Row
 * Args: size_t row
 * Returns: vector<T>
 *------------------------------------------------------*/
template <typename T> 
vector<T> Matrix<T>::GetRow(size_t row) const
{
	vector<T> rowAsked;

	for(size_t j = 0; j<mCols; j++)
		rowAsked.push_back(matrix[row][j]);

	return rowAsked;
}


/*------------------------------------------------------
 * Matrix<T>::GetCol -- Get a Column
 * Args: size_t col
 * Returns: vector<T>
 *------------------------------------------------------*/
template <typename T> 
vector<T> Matrix<T>::GetCol(size_t col) const
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

	ClearValidity();

	return true;
}
	
template<typename T>
/*------------------------------------------------------
 * Matrix<T>::ExchangeCols -- 
 * Args: size_t i, size_t j
 * Returns: bool
 *------------------------------------------------------*/
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

	ClearValidity();

	return true;
}

/*----------------------------------------------------------------------------
 * Matrix<T>::ReducedRowEchelon -- Returns the RowEchelon form of the calling Matrix
 * Args: None 
 * Returns: Matrix<T>
 *---------------------------------------------------------------------------*/
template <typename T> 
Matrix<T> Matrix<T>::ReducedRowEchelon( )
{
	// http://en.wikipedia.org/wiki/Hermite_normal_form#Pseudocode
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
			return copy;
		}

		i=r;
		while(copy(i,lead)==0)
		{
			++i;
			if(rowCount == i)
			{
				i=r;
				++lead;
				if(columnCount == lead)
				{	
					return copy;
				}
			}
		}

		copy.ExchangeRows(i, r);

		T divisor = copy(r,lead);
		// Divide row r by copy[r][lead]
		for(size_t j=0; j<columnCount; ++j)
		{
			copy(r,j)/=divisor;
		}

		// For row 0 -> rowCount except row r 
		// copy(j,k)-=multiplier*copy(r,k);
 
		for(size_t j=0; j<rowCount; ++j)
		{
			if(j!=r)
			{
				T multiplier = copy(j,lead);
				for(size_t k=0; k<columnCount; ++k)
				copy(j,k)-=multiplier*copy(r,k);
			}
		}

		++lead;
	}

	return copy;
}

/*------------------------------------------------------
 * Matrix<T>::Inverse -- Returns inverse of matrix if possible
 * Args:  
 * Returns: Matrix<T>
 *------------------------------------------------------*/
template<typename T>
Matrix<T> Matrix<T>::Inverse( ) 
{
	Matrix<T> R(nRows, mCols);
	Matrix<T> I(nRows, mCols);
	Matrix<T> Zero(nRows, mCols);
	size_t i=0, j, k, l, t;
	T mx;
	detType factor;
	detType d = 1.0;

	// Inverting a Matrix
	// Brief Description of the Algorithm :
	// Run through columns 1 to mCols-1 using var j
	// start with i=0. For each col find the maximum 
	// absolute element, below i, mx, at position t.
	// if mx == 0 continue
	// else swap the t and i row, using the swap function.
	// for l in j -> nRows
	//   factor = (l,j)/(j,j) 
	//   for k in 0 -> mCols
	//      if l != j
	//   	(l,k) -= (i,j) * factor
	// continue
	
	R = *this;
	
	if(nRows!=mCols)
	{
		det = 0.0;
		//Exception 
		throw MatrixTypeException();
	}
		

	for(i=0;i<nRows;i++)
		for(j=0;j<nRows;j++)
		{
			I(i,j) = (i==j)? 1 : 0;
			Zero(i,j) = 0;
		}

	for(j=0;j<mCols;j++)
	{
		mx = ABS(R(j,j));
		t = j;
		for(l=j+1;l<mCols;l++)
			if(ABS(R(l,j)) > mx)
			{ 
				mx = R(l,j);
				t = l;
			}


		if(mx<SMALL) 
		{
			cout << "Matrix is Singular\n";
			det = 0.0;
			return Zero;
		}
		
		R.ExchangeRows(j,t);
		I.ExchangeRows(j,t);

		for(l=0; l<mCols; l++)
		{
			factor = R(l,j)/(detType)(R(j,j));
			if(l!=j)
				for(k=0; k<mCols;k++)
				{
					R(l,k) -= (T) (R(j,k) * factor);
					I(l,k) -= (T) (I(j,k) * factor);
				}
			
		}

		for(k=0;k<mCols;k++)
		{
			R(j,k)/=mx;
			I(j,k)/=mx;
		}
		d *= mx;


		cout <<"\n"<< "j : "<<j<<"\n";
		cout <<"\n"<< "R : \n";
		R.Print();
		cout <<"\n"<< "I : \n";
		I.Print();
		cout<<"\n";
	}
	detValid = true;
	det = d;

	return I;

}


/*------------------------------------------------------
 * Matrix<T>::Determinant -- 
 * Args:  
 * Returns: detType
 *------------------------------------------------------*/
template<typename T>
detType Matrix<T>::Determinant( )
{
	if (detValid)
		return det;

	else
	{
		Inverse();
		return det;
	}
}


/*------------------------------------------------------
 * Matrix<T>::RowEchelon -- 
 * Args:  
 * Returns: Matrix<T>
 *------------------------------------------------------*/
template<typename T>
Matrix<T> Matrix<T>::RowEchelon( )
{
	Matrix<T> R(nRows, mCols);
	size_t i=0, j, k, l, t;
	T mx;
	detType factor;
	bool isRowEmpty;

	// Brief Description of the Algorithm :
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
		mx = ABS(R(i,j));
		t = i;
		for(l=j+1;l<nRows;l++)
		{
			if(ABS(R(l,j)) > mx)
			{ 
				mx = ABS(R(l,j));
				t = l;
			}
		}


		if(mx<SMALL) continue;
		
		if(i!=t) 
			R.ExchangeRows(i, t);

		for(l=i+1; l<nRows; l++)
		{
			factor = R(l,j)/(detType)(R(i,j));
			R(l,j) = 0;

			for(k=j+1; k<mCols;k++)
				R(l,k) -= (T) (R(i,k) * factor);
		}

		i+=1;
	}

	

	// Computing rank
	for(i=0;i<nRows; ++i)
	{
		isRowEmpty = true;
		for(j=0;j<mCols; ++j)
		{
			if(ABS(R(i,j)) > SMALL)
			{
				isRowEmpty = false;
				break;
			}
		}

		if(isRowEmpty == true)
			break;
	}

	rank = i;
	rankValid = true;

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
	if(rankValid)
		return rank;

	else
	{
		RowEchelon();
		return rank;
	}
}


/*------------------------------------------------------
 * Augment -- Augments Other matrix to the right of *this
 * Private function, forming the back of '|'
 * Args: Matrix<T> Other
 * Returns: Matrix<T>
 *------------------------------------------------------*/
template<typename T>
Matrix<T> Matrix<T>::Augment(Matrix<T> Other)
{
	size_t newCols = mCols + Other.GetNumCols();
	size_t newRows = nRows;
	size_t i, j;

	if(nRows!=Other.GetNumRows())
		throw IncompatibleMatricesException();

	Matrix<T> R(newRows, newCols);

	for(i=0; i<nRows;i++)
	{
		for(j=0; j<mCols;j++)
			R(i,j) = matrix[i][j];
		
		for(j=0;j<Other.GetNumCols();j++)
			R(i,j+mCols) = Other(i,j);
	}

	return R;
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
			output << setw(5) << Instance(i,j);
		output << endl; 
	}
return output; 
} 
*/




