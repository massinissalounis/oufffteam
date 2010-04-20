/*******************************************************************************************
   File           :  Oufff_LibMatrice.h
   Authors        :  Bashar		(baptiste.charmette@cpe.fr)   
                     Fifi_one	   (philippe.bechet@cpe.fr)
   Team           :  OUFFF TEAM

   Description	   :  Dynamic Library to use Matrix computing
   History        :
      2008_03_04 (Fifi_one)	: DLL version 1.0
      2008_02_27 (Bashar)		: Initial version (C++ dev)

   Dependencies   :
      Oufff_LibError    - Tested version : 1.0.0 
/*******************************************************************************************/

// Specific declarations

#ifdef WIN32		// Target = Windows
	//windows libraries
	#include <windows.h>

	// DLL Declaration
	#ifdef OUFFF_DLL_EXPORTS
	   #define OUFFF_API_DLL __declspec(dllexport)
	#else
	   #define OUFFF_API_DLL __declspec(dllimport)
	#endif
#else				// Target = Linux
	#define OUFFF_API_DLL 
#endif


// Common declarations
#ifndef OUFFF_LIBMATRICE_H
#define OUFFF_LIBMATRICE_H

//global libraries
#include <iostream>
#include <string>
#include <stdlib.h>

//personnal libraries
#include "Oufff_LibError.h"

// DLL import (dependencies)
#pragma message("Automatic link to Oufff_LibError.lib")
#pragma comment(lib, "Oufff_LibError.lib")



// Variables Declarations

OUFFF_API_DLL typedef double val_matrix;	//define the used type in matrix

using namespace std;

class OUFFF_API_DLL Matrix
{
public:
   //constructor and destructor
   Matrix(int _nrow, int _ncol);	//Constructor with dimension (nrow, ncol)
   Matrix(int n); //Square matrix (n,n)
   Matrix(const Matrix & M);	//constructor by copying
   Matrix();
   ~Matrix(void);//destructor (save memory)

   //operator
   val_matrix& operator() (int row, int col);//operator () to access to the values with 2 val
   val_matrix& operator() (int n);//operator () to access to the values with 1 val
   Matrix operator+ (val_matrix n);//operator+ with a scalar value
   Matrix operator- (val_matrix n);//operator- with a scalar value
   Matrix operator* (val_matrix n);//operator* with a scalar value
   Matrix operator/ (val_matrix n);//operator/ with a scalar value
   Matrix operator+ (Matrix M);//operator+ with an other matrix
   Matrix operator- (Matrix M);//operator/ with an other matrix
   Matrix operator* (Matrix M);//operator* with an other matrix
   Matrix operator= (const Matrix& M);//operator for affectation
   bool operator== (const Matrix& M);//comparison operator

   //semi operator (function used as operator)
   Matrix transpose();

   //semi operator which work only with square matrix
   val_matrix Determinant();
   val_matrix Trace();
   Matrix Inverse();

   //function
   void Dimension(int* Height=NULL, int* Width=NULL);	//update value with the matrix dimension
   void Redim(int new_row, int new_col);	//change matrix dimension (and save actual value)

protected:
   int nrow, ncol;
   val_matrix** value;

protected:
   void allocate_value();
};

//useful function which create Matrix 
OUFFF_API_DLL Matrix identity(int n);
OUFFF_API_DLL Matrix diag(int n, val_matrix val[]);
OUFFF_API_DLL Matrix ones(int nrow, int ncol);

#endif // OUFFF_LIBMATRICE_H
