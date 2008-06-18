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
#include "matrix.h"
using namespace std;


int main()
{
	size_t i, j;
	size_t row, col;
	cin >> row >> col;
	Matrix<float> myMatrix(row, col);
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			cin >> myMatrix(i,j);

	// cin >> row>> col;

	// Matrix<float> myMatrix2(row, col);
	// for(i=0;i<row;i++)
	// 	for(j=0;j<col;j++)
	// 		cin >> myMatrix2.matrix[i][j];

	// //works
	// cout << myMatrix.GetNumRows() <<"\t"<< myMatrix.GetNumCols();
	// cout << "\n";
	
	// works
	// if (myMatrix != myMatrix2)	cout<<"True";
	// else cout << "False";
	
	// =, +, -, *  works
	// Matrix<float> newMatrix = myMatrix - myMatrix2;
	
	// =, *=, += all work
	// myMatrix *= myMatrix2;
	
	// Matrix<float> myMatrix2 = myMatrix.RowEchelon();
	// cout<<myMatrix.matrix[0]<<'\n';
	
	// RowEchelon works
	// Matrix<float> RE = myMatrix.RowEchelon();

	// ReducedRowEchelon works
	// Matrix<float> myMatrix2 = myMatrix.ReducedRowEchelon();


	// cout<<myMatrix.matrix[0]<<'\n';
	// myMatrix.ExchangeCols(0,1);

	Matrix<float> myMatrix2(myMatrix);
	Matrix<float> myMatrix3(myMatrix + myMatrix2);

	myMatrix3.Print();
//	cout<<"\n"<<(myMatrix2!=myMatrix)<<"\n";
//	cin>>myMatrix(0,0);
//	cout<<"\n"<<myMatrix(0,0);
	return 0;
}



