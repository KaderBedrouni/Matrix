/*===========================================================================
 * Project: BRAIN CORPORATION
 *
 * File:    main.cpp
 * Author:  KADER BEDROUNI
 * Date: 03/05/2019
 *
 * Windows 10 Home Edition.
 * Visual C++ 17.9.7 Express Edition.
 *
 * Type: Unit Test
 * Program Output:
 * Success: 10 tests passed.
 * Test time: 0.07 seconds.
 *===========================================================================*/
#include"Matrix.h"
using namespace BrainCorp;

#include "UnitTest++.h"

// UnitTest++ sanity check
TEST(integer_equality)
{
   CHECK(1 == 1);
}

TEST(default_constructor)
{
   cout << "Default Constructor Test: " << "\n";
   Matrix<int>A;
   CHECK(A.get_rows() == 1);
   CHECK(A.get_cols() == 1);
   //Get the value at index(rows=0, cols=0), default value=0
   //NOTE: Index 0 = (row1, col1)
   CHECK(A(0, 0) == 0);
   cout << "The value of Matrix A: " << A;
}

TEST(parameter_constructor)
{
   cout << "Parameter Constructor Test: " << "\n";
   Matrix<int> B(3, 4, 0);
   CHECK(B.get_rows() == 3);
   CHECK(B.get_cols() == 4);
   cout << "Matrix B(3x4) all values initialized to 0: " << "\n";
   cout << B;
   B.setValue(1, 2, 5);
   CHECK(B(1, 2) == 5);
   cout << "Set Matrix B at index B(1, 2) value = 5: " << "\n";
   cout << B;
   Matrix<double> C(2, 4, 1.5);
   C.setValue(0, 3, 3.7);
   CHECK(C(0, 3) == 3.7);
   cout << "Set Matrix C at index B(0, 3) value = 3.7: " << "\n";
   cout << C;
}

TEST(invalid_argument_matrix)
{
   cout << "Invalid Parameter Test: " << "\n";
   cout << "Create invalid Matrix with 0 rows: " << "\n";
   try {
      Matrix<float> C(0, 2, 3.1f);
      CHECK(false);// fail because we don't expect to create matrix with 0 rows or cols.
   }
   catch (invalid_argument &ex)
   {
      CHECK_EQUAL("Attempt to create invalid matrix.", ex.what());
   }
   cout << "\n";
}

TEST(copy_constructor)
{
   cout << "Copy Constructor Test: " << "\n";
   Matrix<float> L(2, 2, 3.1f);
   cout << "Matrix L : " << "\n";
   L.setValue(1, 1, 7.7f);
   cout << L;
   Matrix<float> G = L;
   CHECK(G.get_rows() == L.get_rows());
   CHECK(G.get_cols() == L.get_cols());
   CHECK(G(1, 1) == L(1, 1));
   cout << "Matrix G : " << "\n";
   cout << G;
}

TEST(destructor)
{
   cout << "\nDestructor Test: " << "\n";
   Matrix<double> H(4, 4, 5.5);
   cout << H;
   cout << "Destructor will be called when it is out of scope. " << "\n";
}

TEST(copy_assignment_operator)
{
   cout << "\nCopy and Assignment Operator Test: " << "\n";
   Matrix<long> test1, test2;
   CHECK(test2.get_rows() == test1.get_cols());
   Matrix<long> test3;
   CHECK(test3(0, 0) == test1(0, 0));
}

TEST(transpose)
{
   cout << "\nTranspose Test: " << "\n";
   Matrix<int> D(4, 4, 0);
   cout << "Matrix D(4x4) with initialiazed value to 0. " << "\n";
   cout << D;
   cout << " Setting all the values of r1 to 1." << "\n";
   D.setValue(0, 0, 1);
   D.setValue(0, 1, 1);
   D.setValue(0, 2, 1);
   D.setValue(0, 3, 1);
   cout << " Setting all the values of r2 to 2. \n";
   D.setValue(1, 0, 2);
   D.setValue(1, 1, 2);
   D.setValue(1, 2, 2);
   D.setValue(1, 3, 2);
   cout << " Setting all the values of r3 to 3. \n";
   D.setValue(2, 0, 3);
   D.setValue(2, 1, 3);
   D.setValue(2, 2, 3);
   D.setValue(2, 3, 3);
   cout << " Setting all the values of r4 to 4. \n";
   D.setValue(3, 0, 4);
   D.setValue(3, 1, 4);
   D.setValue(3, 2, 4);
   D.setValue(3, 3, 4);
   cout << "Matrix D: "<< "\n";
   cout << D;
   cout << " Transpose of D: \n";
   cout << D.transpose();
   Matrix<int> F = D.transpose();
   Matrix<int> G = F.transpose();
   // A transpose = A
   CHECK(D(2, 1) == G(2,1));
   CHECK(D(2, 1) != F(2, 1));

   Matrix<int> Z(2, 4, 0);
   Z.setValue(0, 0, 4);
   Z.setValue(0, 1, 7);
   Z.setValue(0, 2, 2);
   Z.setValue(0, 3, 1);  
   Z.setValue(1, 0, 3);
   Z.setValue(1, 1, 9);
   Z.setValue(1, 2, 8);
   Z.setValue(1, 3, 6);
   cout << Z;
   Matrix<int> Z1 = Z.transpose();
   Matrix<int> Z2 = Z1.transpose();
   CHECK(Z(1, 0) == Z2(1, 0));
   CHECK(Z(0, 3) == Z2(0, 3));
   CHECK(Z(1, 0) != Z1(1, 0));
}
TEST(out_range_matrix_multiplication)
{
   cout << "\nOut of Range Multiplication Test: " << "\n";
   Matrix<int> E(2, 3, 1);
   Matrix<int> F(1, 2, 3);  
   try {
      Matrix<int> K = E * F;
      CHECK(false);// fail because #of cols of E != #rows of F.
   }
   catch (range_error &ex)
   {
      CHECK_EQUAL("Matrices cannot be multiplied! cols of A != rows of B", ex.what());
   }
   cout << "\n";
}

TEST(matrix_multiplication)
{
   Matrix<int> G(2, 3, 1);
   G.setValue(0, 0, 1);
   G.setValue(0, 1, 2);
   G.setValue(0, 2, 3);
   G.setValue(1, 0, 4);
   G.setValue(1, 1, 5);
   G.setValue(1, 2, 6);
   cout << G;
   Matrix<int> K(3, 2, 1);
   K.setValue(0, 0, 7);
   K.setValue(0, 1, 8);
   K.setValue(1, 0, 9);
   K.setValue(1, 1, 10);
   K.setValue(2, 0, 11);
   K.setValue(2, 1, 12);
   cout << K;
   Matrix<int> M = G * K;
   cout << "MULTIPLICATION : M = G * Z \n" << M << "\n";
   CHECK(M(0, 0) == 58);
   CHECK(M(0, 1) == 64);
   CHECK(M(1, 0) == 139);
   CHECK(M(1, 1) == 154);
}

int main()
{
   return UnitTest::RunAllTests(); 
}
