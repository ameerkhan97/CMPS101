//-----------------------------------------------------------------------------
//  Sparse.java
//  Ameer Khan
//  ammukhan
//  CS101 PA3
//  Takes two command line arguments giving the names of an 
//  input file and an output file.
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

class Sparse {
	public static void main(String[] args) throws IOException {

		Scanner in = null;
		PrintWriter out = null;
		int size, a, b;
		Matrix A, B;

		// checks for exactly two arguments otherwise error
		if (args.length != 2) {
			System.err.println("Usage: Sparse infile outfile");
			System.exit(1);
		}

		in = new Scanner(new File(args[0])); // takes input file
		out = new PrintWriter(args[1]); // produces output file

		size = in.nextInt();
		a = in.nextInt();
		b = in.nextInt();
		A = new Matrix(size);
		B = new Matrix(size);

		in.nextLine();
		for (int i = 0; i < a; i++) {
			int row = in.nextInt();
			int column = in.nextInt();
			double value = in.nextDouble();
			A.changeEntry(row, column, value);
		}

		in.nextLine();
		for (int i = 0; i < b; i++) {
			int row = in.nextInt();
			int column = in.nextInt();
			double value = in.nextDouble();
			B.changeEntry(row, column, value);
		}

		//A has "a" non-zero entries:
		out.println("A has "+a+" non-zero entries:");
		out.println(A);

		//B has "b" non-zero entries:
		out.println("B has "+b+" non-zero entries:");
		out.println(B);

		//(1.5)*A =
		out.println("(1.5)*A =");
		out.println(A.scalarMult(1.5));

		//A+B =
		out.println("A+B =");
		out.println(A.add(B));

		//A+A =
		out.println("A+A =");
		out.println(A.add(A));

		//B-A =
		out.println("B-A =");
		out.println(B.sub(A));

		//A-A =
		out.println("A-A =");
		out.println(A.sub(A));

		//Transpose(A)
		out.println("Transpose(A) =");
		out.println(A.transpose());

		//A*B =
		out.println("A*B =");
		out.println(A.mult(B));

		//B*B =
		out.println("B*B =");
		out.println(B.mult(B));

		//closes files
		in.close();
		out.close();
	}
}