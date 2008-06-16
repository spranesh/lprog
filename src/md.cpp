/*
 * ====================================================================
 *
 *       Filename:  md.cpp
 *
 *    Description:  the matrix driver program for testing 
 *
 *        Created:  06/16/2008 02:46:20 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Pranesh Srinivasan 
 *        Institution:  IIT, Madras
 *
 * ======================================================================
 */

#include <iostream>
#include "bigHead.h"
using namespace std;

int main()
{
	size_t i, j;
	size_t row, col;
	cin >> row >> col;
	Matrix<float> myMatrix(row, col);
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			cin >> myMatrix.matrix[i][j];

//	cin >> row>> col;
//
//	Matrix<float> myMatrix2(row, col);
//	for(i=0;i<row;i++)
//		for(j=0;j<col;j++)
//			cin >> myMatrix2.matrix[i][j];
//
	//works
	//cout << myMatrix.GetNumRows() <<"\t"<< myMatrix.GetNumCols();
	//cout << "\n";
	
	//works
	//if (myMatrix != myMatrix2)	cout<<"True";
	//else cout << "False";
	
	//=, +, -, *  works
	//Matrix<float> newMatrix = myMatrix - myMatrix2;
	
	//=, *=, += all work
	//myMatrix *= myMatrix2;
	

	Matrix<float> myMatrix2 = myMatrix.RowEchelon();
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
			cout << myMatrix2.matrix[i][j]<<"\t";
		cout<<"\n";
	}
	

	return 0;
}



