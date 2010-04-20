/*******************************************************************************************
      File           :  Oufff_LibMatrice.cpp
      See details on :  Oufff_LibMatrice.h
      Authors        :  Bashar      (baptiste.charmette@cpe.fr)
                        Fifi_one    (philippe.bechet@cpe.fr)
      Team           :  OUFFF TEAM
/*******************************************************************************************/

#include "Oufff_LibMatrice.h"


Matrix::Matrix(int _nrow, int _ncol)
:nrow(_nrow), ncol(_ncol)
{
   if(nrow<=0)
   {
      error err(OUFFF_ERROR_INVALIDVALUE, "Matrix::Matrix(nrow,ncol)", "Try to create a matrix with bad (<=0) height");
      throw err;
   }
   if(ncol<=0)
   {
      error err(OUFFF_ERROR_INVALIDVALUE, "Matrix::Matrix(nrow,ncol)", "Try to create a matrix with bad (<=0) width");
      throw err;
   }
   allocate_value();
}

Matrix::Matrix(int n)
:nrow(n), ncol(n)
{
   if(n<=0)
   {
      error err(OUFFF_ERROR_INVALIDVALUE, "Matrix::Matrix(n)", "Try to create a matrix with bad (<=0) dimension");
      throw err;
   }
   allocate_value();
}

Matrix::Matrix(const Matrix& M)
:nrow(M.nrow), ncol(M.ncol)
{
   int i=0;

   allocate_value();
   for(i=0;i<nrow*ncol;i++)
   {
      value[0][i]=M.value[0][i];
   }

}

Matrix::Matrix()
:nrow(0), ncol(0)
{
   int i=0;
   value=NULL;	
}

Matrix::~Matrix(void)
{
   if(value != NULL)
   {
      delete[] *value;
      delete[] value;
   }
}


val_matrix& Matrix::operator () (int row, int col)
{
   if(row<0 || row>=nrow || col<0 || col>=ncol)
   {
      error err(OUFFF_ERROR_OUTOFTABLE, "Matrix::(row,col)", "Try to access value out of the table");
      throw err;
   }
   return value[row][col];
}

val_matrix& Matrix::operator () (int n)
{
   if(n<0 || n>=nrow*ncol)
   {
      error err(OUFFF_ERROR_OUTOFTABLE, "Matrix::(n)", "Try to access value out of the vector");
      throw err;
   }
   return value[0][n];
}

Matrix Matrix::operator+ (val_matrix n)//operator+ with a scalar value
{
   int i;
   Matrix M(nrow,ncol);

   for(i=0; i<nrow*ncol; i++)
      M(i)=value[0][i] + n;
   return M;
}

Matrix Matrix::operator- (val_matrix n)//operator- with a scalar value
{
   int i;
   Matrix M(nrow,ncol);

   for(i=0; i<nrow*ncol; i++)
      M(i)=value[0][i] - n;
   return M;
}

Matrix Matrix::operator* (val_matrix n)//operator* with a scalar value
{
   int i;
   Matrix M(nrow,ncol);

   for(i=0; i<nrow*ncol; i++)
      M(i)=value[0][i] * n;
   return M;
}

Matrix Matrix::operator/ (val_matrix n)//operator/ with a scalar value
{
   int i;

   if(n==0)
      throw error(OUFFF_ERROR_MATHS, "Matrix::/(val)", "Try to divide a matrix by 0");

   Matrix M(nrow,ncol);

   for(i=0; i<nrow*ncol; i++)
      M(i)=value[0][i] / n;
   return M;
}

Matrix Matrix::operator+ (Matrix M)//operator+ with an other matrix
{
   int i,j;

   M.Dimension(&i,&j);
   if(i!=nrow || j!= ncol)
   {
      throw error(OUFFF_ERROR_DIMENSIONDISAGREE, "Matrix::+(matrix)", "Try to make sum with matrix of different size");;
   }
   Matrix N(nrow,ncol);
   for(i=0; i<nrow*ncol; i++)
      N(i)=value[0][i] + M(i);
   return N;
}

Matrix Matrix::operator- (Matrix M)//operator+ with an other matrix
{
   int i,j;

   M.Dimension(&i,&j);
   if(i!=nrow || j!= ncol)
   {
      error err(OUFFF_ERROR_DIMENSIONDISAGREE, "Matrix::-(matrix)", "Try to make difference with matrix of different size");
      throw err;
   }
   Matrix N(nrow,ncol);

   for(i=0; i<nrow*ncol; i++)
      N(i)=value[0][i] - M(i);
   return N;
}

Matrix Matrix::operator* (Matrix M)//operator+ with an other matrix
{
   int i,j,k;
   int nrow2, ncol2;

   //test the dimension
   M.Dimension(&nrow2,&ncol2);
   if(nrow2!=ncol)
   {
      error err(OUFFF_ERROR_DIMENSIONDISAGREE, "Matrix::*(matrix)", "Try to make product between matrix of bad size");
      throw err;
   }

   //creation of the new matrix
   Matrix N(nrow,ncol2);
   for(i=0; i<nrow; i++)
   {
      for(j=0;j<ncol2;j++)
      {
         //N(i,j) is the product of the ith row from this by the jth col from M
         N(i,j)=0;//init value to 0
         for(k=0; k<ncol; k++)
         {
            N(i,j) += value[i][k]*M(k,j);
         }
      }
   }
   return N;
}

Matrix Matrix::operator =(const Matrix& M)
{
   int i;
   nrow=M.nrow;
   ncol=M.ncol;
   if(value != NULL)
   {
      delete[] *value;
      delete[] value;
   }
   allocate_value();
   for(i=0; i<nrow*ncol;i++)
   {
      value[0][i]=M.value[0][i];
   }
   return *this;

}

bool Matrix::operator== (const Matrix& M)
{
   int i;

   if(M.nrow!=nrow || M.ncol!=ncol)//if dimension are different, matrix are different
      return false;

   for(i=0;i<nrow*ncol;i++)
   {
      if(value[0][i] != M.value[0][i] )
	      return false;
   }
   return true;
}

//semi operator (function used as operator)
Matrix Matrix::transpose()
{
   int i,j;
   Matrix T(ncol, nrow);	//creation of the new matrix with coordinate inverted (T.ncol = nrow and T.nrow=ncol)

   for(i=0; i<ncol; i++)
   {
      for(j=0;j<nrow;j++)
      {
         T(i,j)=value[j][i];
      }
   }
   return T;
}

//semi operator which work only with square matrix
val_matrix Matrix::Determinant()
{
   Matrix* Rows;	//every rows will be a matrix
   int i,j;
   val_matrix det;
   Matrix current;

   if (ncol!= nrow)
      throw error(OUFFF_ERROR_MATRIXNOTSQUARE, "Matrix::Determinant", "Try to calculate determinant from a non-square matrix");


   //creation of the table of rows (to use quick operation on row after and save value of matrix
   Rows = new Matrix[nrow];
   for(i=0; i<nrow; i++)
   {
      Rows[i].Redim(1,ncol);	//create a vector with value of the current line
      for(j=0; j<ncol; j++)
         Rows[i](j) = value[i][j];
   }

   det=1;
   for(i=0; i<nrow-1; i++)//Rows[i] is the actual pivot
   {
      current = Rows[i];	//store the pivot in current
      if(current(i)==0)	//so current can not be used as pivot
      {
         for(j=i+1; j<nrow && Rows[j](i)==0; j++);	//search a pivot

         if(j==nrow)//no pivot found so determinant is null
         {
            delete[] Rows;
            return 0;
         }
         //so pivot found in Rows[j]
         current = Rows[j];//store the pivot in current

         //invert the rows
         Rows[j] = Rows[i];
         Rows[i] = current;
         det = -det;	//if 2 lines are inverted det is opposite
      }

	   for(j=i+1; j<nrow; j++)
	   {
         Rows[j] = Rows[j] - current*( Rows[j](i)/current(i) ); //make operation to have 0 on the ith position of every row (except pivot)
	   }
         det = det*Rows[i](i);
   }

   det = det*Rows[nrow-1](nrow-1);

   delete[] Rows;

   return det;
}

val_matrix Matrix::Trace()
{
   int i;
   val_matrix tr;

   //Check matrix is square
   if (ncol!= nrow)
      throw error(OUFFF_ERROR_MATRIXNOTSQUARE, "Matrix::Trace", "Try to calculate trace from a non-square matrix");

   tr=0;//init tr to 0
   for (i=0; i<ncol; i++)
   {
      tr = tr + value[i][i];//add every diag value
   }
   return tr;
}

Matrix Matrix::Inverse()
{
   Matrix current;
   Matrix* Rows;
   int i,j;
   int argmax;

   if (ncol!= nrow)
      throw error(OUFFF_ERROR_MATRIXNOTSQUARE, "Matrix::Inverse", "Try to calculate inverse from a non-square matrix");

   //creation of the table of rows (to use quick operation on row after and save value of matrix)
   Rows = new Matrix[nrow];
   for(i=0; i<nrow; i++)
   {
      Rows[i].Redim(1,2*ncol);	//create a vector with value of the current line
      for(j=0; j<ncol; j++)
         Rows[i](j) = value[i][j];

      Rows[i](ncol+i)=1;	//create the matrix identity next to the matrix
   }

   for(i=0; i<nrow; i++)
   {
      //search the pivot with the max value (better stability)
      current=Rows[i];
      argmax=i;
      for(j=i+1; j<nrow; j++)
      {
         if(abs(Rows[j](i))>abs(current(i)))
         {
            current=Rows[j];
            argmax=j;
         }
      }
      if( current(i) == 0 )//if no pivot found, so no invert possible
      throw error(OUFFF_ERROR_INVALIDVALUE, "Matrix::Inverse", "Try to calculate inverse from a non-inversible matrix");

      current = current/current(i); //normalized pivot

      //invert line i with the pivot
      Rows[argmax] = Rows[i]; //store line i instead of the pivot line
      Rows[i] = current;	//store (normalized) pivot in the line i

      //make 0 in every other lines with the pivot
      for(j=0; j<nrow; j++)
      {
         if(j == i)	//no change on the pivot
            continue;

         Rows[j] = Rows[j] - current*Rows[j](i);
      }
   }

   //store the inverse in current
   current.Redim(nrow, ncol);
   for (i=0; i<nrow; i++)
   {
      for(j=0;j<ncol; j++)
      {
         current(i, j) = Rows[i](ncol+j);
      }
   }

   delete[] Rows;
   return current;
}

//public function
void Matrix::Dimension(int* Height, int* Width)
{
   if(Height!=NULL)
      *Height=nrow;
   if(Width!=NULL)
      *Width=ncol;
}

void Matrix::Redim(int new_row, int new_col)
{
   val_matrix** old;
   int oldrow, oldcol;
   int i,j;

   //save old value
   old=value;
   oldrow=nrow;
   oldcol=ncol;

   //creation of the new matrix
   nrow=new_row;
   ncol=new_col;
   allocate_value();

   //keep the old value in matrix
   for(i=0; i<nrow && i<oldrow; i++)
   {
      for(j=0; j<ncol && j<oldcol; j++)
      {
         value[i][j] = old[i][j];
      }
   }

   //free memory allocated in the old matrix
   if(old != NULL)
   {
      delete[] *old;
      delete[] old;
   }
}



//private functions

void Matrix::allocate_value()
{
   int i,j;
   value = new val_matrix*[nrow];//on construit la matrice comme un vecteur de ligne
   if(value==NULL)
   {
      error err(OUFFF_ERROR_ALLOCATION, "Matrix::allocate_value", "Can not allocate value in the matrix");
      throw err;
   }
   *value = new val_matrix[nrow*ncol];//on alloue l'ensemble de la matrice sur la premiere ligne
   if(value==NULL)
   {
      error err(OUFFF_ERROR_ALLOCATION, "Matrix::allocate_value", "Can not allocate *value in the matrix");
      throw err;
   }
   for(i=0; i<nrow; i++)
   {
      value[i]=value[0]+i*ncol;//chaque debut de ligne pointe vers la premiere valeur		
      for(j=0;j<ncol;j++)//init values with 0
         value[i][j]=0;
   }
}



//useful function which create Matrix 

OUFFF_API_DLL Matrix identity(int n)
{
   int i;
   Matrix I(n);

   for(i=0;i<n;i++)
      I(i,i)=1;
   return I;
}

OUFFF_API_DLL Matrix diag(int n, val_matrix val[])
{
   int i;
   Matrix D(n);

   for(i=0;i<n;i++)
      D(i,i)=val[i];
   return(D);
}

OUFFF_API_DLL Matrix ones(int nrow, int ncol)
{
   Matrix M(nrow, ncol);

   return M+1;
}
