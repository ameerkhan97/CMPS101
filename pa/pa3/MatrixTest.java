//-----------------------------------------------------------------------------
//  MatrixTest.java
//  Ameer Khan
//  ammukhan
//  CS101 PA3
//  A test client for the Matrix ADT. Use this to test your matrix module. The
//  correct output is given below. Taken from class website.
//-----------------------------------------------------------------------------

public class MatrixTest{
   public static void main(String[] args){
      int i, j, n=100000;
      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);

      A.changeEntry(1,1,1); B.changeEntry(1,1,1);
      A.changeEntry(1,2,2); B.changeEntry(1,2,0);
      A.changeEntry(1,3,3); B.changeEntry(1,3,1);
      A.changeEntry(2,1,4); B.changeEntry(2,1,0);
      A.changeEntry(2,2,5); B.changeEntry(2,2,1);
      A.changeEntry(2,3,6); B.changeEntry(2,3,0);
      A.changeEntry(3,1,7); B.changeEntry(3,1,1);
      A.changeEntry(3,2,8); B.changeEntry(3,2,1);
      A.changeEntry(3,3,9); B.changeEntry(3,3,1);

      System.out.println(A.getNNZ());
      System.out.println(A);

      System.out.println(B.getNNZ());
      System.out.println(B);

      Matrix C = A.scalarMult(1.5);
      System.out.println(C.getNNZ());
      System.out.println(C);

      Matrix D = A.add(A);
      System.out.println(D.getNNZ());
      System.out.println(D);

      Matrix E = A.sub(A);
      System.out.println(E.getNNZ());
      System.out.println(E);

      Matrix F = B.transpose();
      System.out.println(F.getNNZ());
      System.out.println(F);

      Matrix G = B.mult(B);
      System.out.println(G.getNNZ());
      System.out.println(G);

      Matrix H = A.copy();
      System.out.println(H.getNNZ());
      System.out.println(H);
      System.out.println(A.equals(H));
      System.out.println(A.equals(B));
      System.out.println(A.equals(A));

      A.makeZero();
      System.out.println(A.getNNZ());
      System.out.println(A);
   }
}

// 9
// 1: (1, 1.0) (2, 2.0) (3, 3.0)
// 2: (1, 4.0) (2, 5.0) (3, 6.0)
// 3: (1, 7.0) (2, 8.0) (3, 9.0)

// 6
// 1: (1, 1.0) (3, 1.0)
// 2: (2, 1.0)
// 3: (1, 1.0) (2, 1.0) (3, 1.0)

// 9
// 1: (1, 1.5) (2, 3.0) (3, 4.5)
// 2: (1, 6.0) (2, 7.5) (3, 9.0)
// 3: (1, 10.5) (2, 12.0) (3, 13.5)

// 9
// 1: (1, 2.0) (2, 4.0) (3, 6.0)
// 2: (1, 8.0) (2, 10.0) (3, 12.0)
// 3: (1, 14.0) (2, 16.0) (3, 18.0)

// 0

// 6
// 1: (1, 1.0) (3, 1.0)
// 2: (2, 1.0) (3, 1.0)
// 3: (1, 1.0) (3, 1.0)

// 7
// 1: (1, 2.0) (2, 1.0) (3, 2.0)
// 2: (2, 1.0)
// 3: (1, 2.0) (2, 2.0) (3, 2.0)

// 9
// 1: (1, 1.0) (2, 2.0) (3, 3.0)
// 2: (1, 4.0) (2, 5.0) (3, 6.0)
// 3: (1, 7.0) (2, 8.0) (3, 9.0)

// true
// false
// true
// 0