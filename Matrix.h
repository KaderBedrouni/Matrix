/*===========================================================================
 * Project: BRAIN CORPORATION
 * 
 * File:    Matrix.h
 * Author:  KADER BEDROUNI
 * Date: 03/03/2019
 * 
 * Windows 10 Home Edition.
 * Visual C++ 17.9.7 Express Edition.
 *
 * This file contains defition and implementation of Matrix class.
 * Container used vector of vectors 
 * Type: Matrix class template
 *===========================================================================*/
#ifndef BRAINCORP_MATRIX_H
#define BRAINCORP_MATRIX_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

using namespace std;

namespace BrainCorp
{
   const int WIDTH = 4;
   
   template <typename T>
   class Matrix
   {
      // friend function overload of the stream insertion operator.
      template <typename T>
      friend ostream &operator<<(ostream &out, const Matrix<T> &source);

   public:
      Matrix();                                                      // Default Constructor
      Matrix(size_t rows_, size_t cols_, const T& initialValue_);    // Parameter Constructor
      Matrix(const Matrix<T>& source);                               // Copy Constructor                                                         // Empty Constructor
      ~Matrix();                                                     // Destructor

      size_t get_rows() const;                                       // Accessors for rows and columns
      size_t get_cols() const;
      void setValue(size_t i, size_t j, const T& value);             // Set individual value
      T& operator()(const size_t& i, const size_t& j);               // Access individual value
      const T& operator()(const size_t& i, const size_t& j) const;

      Matrix<T>& operator=(const Matrix<T>& source);                 // Assignment Operator
      Matrix<T> operator*(const Matrix<T>& other);                   // Multiplication
      Matrix<T>& operator*=(const Matrix<T>& other);

      Matrix<T> transpose() const;                                   // transpose
      void swap(Matrix &);                                           // swap 

   private:
      size_t rows, cols;
      vector<vector<T> > matrix;
   };

   // Default Constructor Matrix 1x1 with default value = 0
   template <typename T>
   Matrix<T>::Matrix()
      : rows(1), cols(1), matrix(1, vector<T>(1))
   {}

   // Parameter Constructor
   template <typename T>
   Matrix<T>::Matrix(size_t rows_, size_t cols_, const T& initValue_)
      : rows(rows_), cols(cols_)
   {
      // TO DO: bool f() to return the size.
      if (rows_ == 0 || cols_ == 0)
         throw invalid_argument("Attempt to create invalid matrix.");
      // Matrix allocation rows X cols, then initialialization. 
      matrix.resize(rows_);
      for (size_t i = 0; i < matrix.size(); ++i)
      {
         matrix[i].resize(cols_, initValue_);
      }
   }

   // Copy Constructor
   template <typename T>
   Matrix<T>::Matrix(const Matrix<T>& source)
      : rows(source.rows), cols(source.cols), matrix(source.matrix)
   {}

   // Destructor
   template<typename T>
   Matrix<T>::~Matrix() 
   {
      //cout << "Destructor is called. " << "\n";
   }

   // Get the number of rows of the matrix                                                                                                                                       
   template<typename T>
   size_t Matrix<T>::get_rows() const { return rows;}

   // Get the number of columns of the matrix                                                                                                                                    
   template<typename T>
   size_t Matrix<T>::get_cols() const { return cols;}

   // Access individual element                                                                                                                                            
   template<typename T>
   T& Matrix<T>::operator()(const size_t& i, const size_t& j)
   {
      return matrix[i][j];
   }

   //Access individual element (const)                                                                                                                                     
   template<typename T>
   const T& Matrix<T>::operator()(const size_t& i, const size_t& j) const 
   {
      return matrix[i][j];
   }

   template<typename T>
   void Matrix<T>::setValue(size_t i, size_t j, const T& value)
   {
      if (i >= get_rows())
         throw range_error("matrix access row out of range");
      if (j >= get_cols())
         throw range_error("matrix access col out of range");
      matrix[i][j] = value;
   }
 
   // Assignment Operator
   template <typename T>
   Matrix<T> & Matrix<T>::operator=(const Matrix<T> &source)
   {
      // Allocate temp from source then swap
      Matrix<T> temp(source);
      swap(temp);
      return *this;
   }

   //Matrix<T> operator*(const T& other);
   template<typename T>
   Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
   {
      size_t r = other.get_rows();
      size_t c = other.get_cols();
      // A(m x n) * B(n x p) = Result(m x p)
      // # of cols of Matrix A must be equal to # of rows of Matrix B.
      // n's must be same.
      // result Matrix will have # of rows of Matrix A and # of cols of Matrix B.
      
      if (this->cols != r)
         throw range_error("Matrices cannot be multiplied! cols of A != rows of B");
      Matrix result(this->rows, c, 0);
      // Lopp through rows of matrix 
      for (size_t i = 0; i < this->rows; ++i){
         // Loop through cols of other
         for (size_t j = 0; j < c; ++j){
            // Loop through cols of matrix
            for (size_t k = 0; k < this->cols; ++k) {
               // perform Dot Product.
               result(i, j) += matrix[i][k] * other(k, j);
            }
         }
      }
      return result;
   }

   template<typename T>
   Matrix<T> &Matrix<T>::operator*=(const Matrix<T>& other)
   {
      Matrix result = (*this) * other;
      return *this = result;
   }

   template<typename T>
   Matrix<T> Matrix<T>::transpose() const
   {
      // transpose rows becomes cols.
      size_t c = matrix.size();
      size_t r = matrix[0].size();

      Matrix<T> result(r, c, 0);

      for (size_t i = 0; i < r; ++i){
         for (size_t j = 0; j < c; ++j){
            result(i, j) = matrix[j][i];
         }
      }
      return result;
   }

   // Format matrix output by overloading stream insertion operator.
   template<typename T>
   ostream &operator<<(ostream &out, const Matrix<T>& source)
   {
      //for (size_t i = 0; i < source.rows; ++i)
      for (size_t i = 0; i < source.get_rows(); ++i){
         //for (size_t j = 0; j < source.cols; ++j)
         for (size_t j = 0; j < source.get_cols(); ++j){
            out << setw(WIDTH) << source(i, j) << " ";
         }
         out << "\n";
      }
      return out << "\n";
   }

   // swap f() used for assignment operator.
   template<typename T>
   void Matrix<T>::swap(Matrix &other)
   {
      swap(rows, other.rows);
      swap(cols, other.cols);
      swap(matrix, other.matrix);
   }
}
#endif
