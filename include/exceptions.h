/*
 * =====================================================================================
 *
 *       Filename:  exceptions.h
 *
 *    Description:  Defines a list of user-defined exceptions we come across
 *
 *        Created:  Sunday 15 June 2008 04:40:29  IST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Naveen, Pranesh Srinivasan, Samhita
 *
 * =====================================================================================
 */


#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
using namespace std;
// The following exception is raised when two incomaptible matrices are asked to be multiplied
// added or subtracted. 
class IncompatibleMatricesException : public runtime_error
{
	public:
		IncompatibleMatricesException()
			:runtime_error("Attempted to operate on Incompatible Matrices") {}
		
};

// The following Exception is raised when an element out of array bounds is accessed.
class  OutOfBoundsException: public runtime_error
{
	public:
		OutOfBoundsException()
			:runtime_error("Trying to access element out of array bounds") {}
		
};

// The following Exception is raised when a rectangulat matrix is provided instead of a square one.
class  MatrixTypeException: public runtime_error
{
	public:
		MatrixTypeException()
			:runtime_error("Square matrix required. Rectangular matrix was given.") {}
		
};


#endif
