//-----------------------------------------------------------------------------
//  Matrix.java
//  Ameer Khan
//  ammukhan
//  CS101 PA3
//  Matrix List ADT
//-----------------------------------------------------------------------------

public class Matrix {

	private class Entry {
		//Fields
		int column;
		double value;

		//Contructor
		Entry(int column, double value) {
			this.column = column;
			this.value = value;
		}

		// toString(): overrides Object's toString() method
		public String toString() {
			return "(" + column + ", " + value + ")";
		}

		// equals(): ovverides Object's equals method
		public boolean equals(Object x) {
			boolean eq = false;
			Entry that;

			if (x instanceof Entry) {
				that = (Entry)x;
				eq = ((this.column == that.column) && (this.value == that.value));
			}
			return eq;
		}
	}

	//Fields
	private List[] matrix;
	private int entries = 0;
	private int size;

	//Contructor
	//Makes a new n x n zero Matrix.  pre: n>=1
	Matrix(int n) {
		if (n < 1) {
			throw new RuntimeException("Matrix Error: Matrix with dimensions less than 1 cannot be created.");
		} else {
			size = n;
			entries = 0;
			matrix = new List[n+1];
			for (int i = 1; i <= size; i++) {
				matrix[i] = new List();
			} 
		}
	}

	// Access Functions --------------------------------------------------------

	//Returns n, the number of rows and columns of this Matrix
	int getSize() {
		return size;
	}

	//Returns the number of non-zero entries in this Matrix
	int getNNZ() {
		return entries;
	}

	//overrides Object's equals() method
	public boolean equals(Object x) {
		Matrix m;
		if (x instanceof Matrix) {
			m = (Matrix)x;
			if (getSize() != m.getSize()) {
				return false;
			}
			for (int i = 1; i <= getSize(); i++){
				if (!(matrix[i].equals(m.matrix[i]))) {
					return false;
				}
			}
		}
		return true;
	}

	// Manipulation Procedures -------------------------------------------------

	//sets this Matrix to the zero state
	void makeZero() {
		for (int i = 1; i < getSize(); i++) {
			matrix[i] = new List();
		}
		entries = 0;
	}

	//returns a new Matrix having the same entries as this matrix
	Matrix copy() {
		Matrix c = new Matrix(size);
		for (int i = 1; i <= size; i++) {
			matrix[i].moveFront();
			while (matrix[i].index() != -1) {
				Entry temp = (Entry)matrix[i].get();
				c.changeEntry(i, temp.column, temp.value);
				matrix[i].moveNext();
			}
		}
		c.entries = entries;
		return c;
	}

	//changes ith row, jth column of this Matrix to x
	//pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x) {
		if (i < 1 || i > getSize() || j < 1 || j > getSize()) {
			throw new RuntimeException("Matrix Error: changeEntry() called on Matrix with invalid ith postion, jth postion.");
		}

		boolean change;
		matrix[i].moveFront();

		while (matrix[i].index() >= 0) {
			Entry temp = (Entry)matrix[i].get();
			if (temp.column != j) {
				change = false;
			} else {
				change = true;
			}
			if (change = false) {
				if (x == 0.0) {
					matrix[i].delete();
					entries--;
				} else {
					temp.value = x;
				}
			}
			matrix[i].moveNext();
		}

		if (change = true && x != 0.0) {
			matrix[i].moveFront();
			if (matrix[i].index() == -1) {
				matrix[i].append(new Entry(j,x));
				entries++;
			} else {
				while (matrix[i].index() >= 0 && ((Entry)matrix[i].get()).column < j) {
					matrix[i].moveNext();
				}
				if (matrix[i].index() > -1) {
					matrix[i].insertBefore(new Entry(j, x));
					entries++;
				} else {
					matrix[i].append(new Entry(j,x));
					entries++;
				}
			}
		}
	}

	//returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x) {
		Matrix sM = new Matrix(size);
		for (int i = 1; i <= getSize(); i++) {
			matrix[i].moveFront();
			while (matrix[i].index() != -1) {
				Entry temp = (Entry)matrix[i].get();
				sM.changeEntry(i, temp.column, (temp.value * x));
				matrix[i].moveNext();
			}
		}
		return sM;
}


	//returns a new Matrix that is the sum of this Matrix with M
	//pre: getSize()==M.getSize()
	Matrix add(Matrix M) {
		if(getSize() != M.getSize()) {
			throw new RuntimeException("Matrix Error: Matrices must be the same size");
		}

		List temp1, temp2;
		Matrix a = new Matrix(size);

		for (int i =1; i < matrix.length; i++) {
			temp1 = M.matrix[i];
			temp2 = matrix[i];
			if (temp1.isEmpty() && !(temp2.isEmpty())) {
				temp2.moveFront();
				while (temp2.index() != -1) {
					a.changeEntry(i, ((Entry)temp2.get()).column, ((Entry)temp2.get()).value);
					temp2.moveNext();
					a.entries++;
				}
			} else if (!(temp1.isEmpty()) && temp2.isEmpty()) {
				temp1.moveFront();
				while (temp1.index() != -1) {
					a.changeEntry(i, ((Entry)temp1.get()).column, ((Entry)temp1.get()).value);
					temp1.moveNext();
					a.entries++;
				}
			} else if (!(temp1.isEmpty()) && !(temp2.isEmpty())) {
				temp2.moveFront();
				temp1.moveFront();
				while (temp1.index() != -1 && temp2.index() != -1) {
					if (((Entry)temp1.get()).column == ((Entry)temp2.get()).column) {
						a.changeEntry(i, ((Entry)temp2.get()).column, (((Entry)temp1.get()).value + ((Entry)temp2.get()).value));
						temp1.moveNext();
						if (!(this.equals(M))) {
							temp2.moveNext();
						} 
					} else if (((Entry)temp1.get()).column < ((Entry)temp2.get()).column) {
							a.changeEntry(i, ((Entry)temp1.get()).column, ((Entry)temp1.get()).value);
							temp1.moveNext();
							a.entries++;
					} else if (((Entry)temp1.get()).column > ((Entry)temp2.get()).column) {
							a.changeEntry(i, ((Entry)temp2.get()).column, ((Entry)temp2.get()).value);
							temp2.moveNext();
							a.entries++;
					}
				}
				while (temp1.index() != -1) {
					a.changeEntry(i, ((Entry)temp1.get()).column, ((Entry)temp1.get()).value);
					temp1.moveNext();
					a.entries++;
				}
				while (temp2.index() != -1) {
					a.changeEntry(i, ((Entry)temp2.get()).column, ((Entry)temp2.get()).value);
					temp2.moveNext();
					a.entries++;
				}
			}
		}
		if (entries >= M.entries) {
	 		a.entries = entries;
	 	} else {
	 		a.entries = M.entries;
	 	}
		return a;
	}

	//returns a new Matrix that is the difference of this Matrix with M
	//pre: getSize()==M.getSize()
	Matrix sub(Matrix M) {
		if (getSize() != M.getSize()) {
			throw new RuntimeException("Matrix Error: sub() called on two matrices of unequal sizes.");
		}

		Matrix s = new Matrix(size);

		if (this.equals(M)) {
			return s;
		}

		for (int i = 1; i <= getSize(); i++) {
			matrix[i].moveFront();
			M.matrix[i].moveFront();
			while (matrix[i].index() != -1 || M.matrix[i].index() != -1) {
				if (matrix[i].index() != -1 && M.matrix[i].index() != -1) {
					Entry temp1 = (Entry)matrix[i].get();
					Entry temp2 = (Entry)M.matrix[i].get();
					if (temp1.column < temp2.column) {
						s.changeEntry(i, temp1.column, temp1.value);
						matrix[i].moveNext();
					} else if (temp1.column > temp2.column) {
						s.changeEntry(i, temp2.column, (-temp2.value));
						M.matrix[i].moveNext();
					} else {
						if (temp1.value == temp2.value) {
							matrix[i].moveNext();
							M.matrix[i].moveNext();
						} else {
							s.changeEntry(i, temp1.column, (temp1.value - temp2.value));
							matrix[i].moveNext();
							M.matrix[i].moveNext();
						}
					}
				} else if (matrix[i].index() == -1) {
					Entry temp2 = (Entry)M.matrix[i].get();
					s.changeEntry(i, temp2.column, (-temp2.value));
					M.matrix[i].moveNext();
				} else {
					Entry temp1 = (Entry)matrix[i].get();
					s.changeEntry(i, temp1.column, temp1.value);
					matrix[i].moveNext();
				}
			}
		}
		return s;
	}

	//returns a new Matrix that is the transpose of this Matrix
	Matrix transpose() {
		Matrix t = new Matrix(size);
		for (int i = 1; i <= getSize(); i++) {
			matrix[i].moveFront();
			while (matrix[i].index() != -1) {
				Entry temp = (Entry)matrix[i].get();
				t.changeEntry(temp.column, i, temp.value);
				matrix[i].moveNext();
			}
		}
		t.entries = entries;
		return t;
		
	}

	//returns a new Matrix that is the product of this Matrix with M
	//pre: getSize()==M.getSize()
	Matrix mult(Matrix M) {
		if (getSize() != M.getSize()) {
			throw new RuntimeException("Matrix Error: mult() called on two matrices of unequal sizes.");
		}

		Matrix a = new Matrix(size);
		Matrix b = M.transpose();

		for (int i = 1; i <= getSize(); i++) {
			if (matrix[i].length() > 0) {
				for (int j = 1; j <= getSize(); j++) {
					if (b.matrix[j].length() != 0) {
						a.changeEntry(i, j, dot(matrix[i], b.matrix[j]));
					}
				}
			}
		}
		return a;
	}

	// Other functions -------------------------------------------------------

	//overrides Object's toString() method
	public String toString() {
		String str = "";
		for (int i = 1; i <= getSize(); i++) {
			if (!(matrix[i].isEmpty())) {
				str += i +": " + matrix[i].toString() +"\n";
			}
		}
		return str;
	}

	//helper function dot()
	//computes the vector dot product of two matrix rows represented by Lists P and Q
	private static double dot(List P, List Q) {
		double dotresult = 0.0;
		for (P.moveFront(); P.index() != -1; P.moveNext()) {
			Entry ptemp = (Entry)P.get();
			for (Q.moveFront(); Q.index() != -1; Q.moveNext()) {
				Entry qtemp = (Entry)Q.get();
				if (ptemp.column == qtemp.column) {
					dotresult += (qtemp.value * ptemp.value);
					break;
				}
			}
		}
		return dotresult;
	}
}