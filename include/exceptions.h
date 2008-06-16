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


#include <stdexcept>
using namespace std;

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
// The following exception is raised when two incomaptible matrices are asked to be multiplied,
// added or subtracted. 
class IncompatibleMatricesException : public runtime_error
{
	public:
		IncompatibleMatricesException()
			:runtime_error("Attempted to operate on Incompatible Matrices") {}
};

#endif
