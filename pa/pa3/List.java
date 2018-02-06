//-----------------------------------------------------------------------------
//  List.java
//  Ameer Khan
//  ammukhan
//  CS101 PA3
//  Integer List ADT
//-----------------------------------------------------------------------------

class List {

	private class Node {
		// Fields
		Object data;
		Node next;
		Node prev;

		// Constructor
		Node(Object data) {
			this.data = data;
			next = prev = null;
		}

		// toString(): overrides Object's toString() method
		public String toString() {
			return String.valueOf(data);
		}

		// equals(): ovverides Object's equals method
		public boolean equals(Object x) {
			boolean eq = false;
			Node that;

			if (x instanceof Node) {
				that = (Node) x;
				eq = (this.data == that.data);
			}
			return eq;
		}
	}

	// Fields
	private Node front;
    private Node back;
    private Node locator;
    private int length;
    private int index;

    // Constructor
    List() {
    	front = back = locator = null;
    	length = 0;
    	index = -1;
   }

   // Access Functions --------------------------------------------------------

   // isEmpty()
   // returns length = 0
   boolean isEmpty() {
   	return (length == 0);
   }

   // length()
   // Returns the number of elements in this List.
   int length() { 
      return length; 
   }

   // index()
   // If cursor is defined, returns the index of the cursor element,
   // otherwise returns -1.
   int index() {
   	if (locator != null) {
   		return index;
   	} else {
   		return -1;
   	}
   }

   // front()
   // Returns front element.
   // Pre: length() > 0
   Object front() {
   	if (length >= 0) {
   		return front.data;
   	} else {
   		throw new RuntimeException("List Error: front() called on empty list.");
   	}
   }

   // back()
   // Returns back element.
   // Pre: length() > 0
   Object back() {
   	if (length >= 0) {
   		return back.data;
   	} else {
   		throw new RuntimeException("List Error: back() called on empty list.");
   	}
   }

   // get()
   // Returns cursor element.
   // Pre: length() > 0, index() >= 0
   Object get() {
   	if (length <= 0) {
   		throw new RuntimeException("List Error: get() called on empty list."); 
   	}
   	if (index < 0) {
   		throw new RuntimeException("List Error: get() called on invalid index.");
   	}
   	return locator.data;
   }

   // boolean equals()
   // Returns true if and only if this List and L are the same integer sequence.
   // The states of the cursors in the two Lists are not used in determining equality.
   public boolean equals(List L) {
   	boolean eq = false;
   	Node N = this.front;
   	Node M = L.front;
   	eq = (this.length == L.length);

   	while (eq && N != null) {
   		eq = N.equals(M);
   		N = N.next;
   		M = M.next;
   	}
   	return eq;
   }

	// Manipulation Procedures -------------------------------------------------

	// clear()
	// Resets this List to its original empty state.
	void clear() {
		front = back = locator = null;
		length = 0;
		index = -1;
	}

	// moveFront()
	// If List is non-empty, places the cursor under the front element, otherwise does nothing.
	void moveFront() {
		if (length > 0) {
			locator = front;
			index = 0;
		}
	}

	// moveBack()
	// If List is non-empty, places the cursor under the back element, otherwise does nothing.
	void moveBack() {
		if (length > 0) {
			locator =  back;
			index = (length - 1);
		}
	}

	// movePrev()
	// If cursor is defined and not at front, moves cursor one step toward front of this List.
	// If cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
	void movePrev() {
		if (locator != null && index != 0) {
			locator = locator.prev;
			index--;
		} else if (locator != null && index == 0) {
			locator = null;
			index = -1;
		}
	}

	// moveNext()
	// If cursor is defined and not at back, moves cursor one step toward back of this List.
	// If cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
	void moveNext() {
		if (locator != null && index != (length - 1)) {
			locator = locator.next;
			index++;
		} else if (locator != null && index == (length - 1)) {
			locator = null;
			index = -1;
		}
	}

	// prepend()
	// Insert new element into this List.  
	// If List is non-empty, insertion takes place before front element.
	void prepend(Object data) {
		if (front == null) {
			front = new Node(data);
			back = front;
			locator = front;
		} else {
			Node N = front;
			N.prev = new Node(data);
			front = N.prev;
			front.next = N;
		}
		length++;
	}

	// append()
	// Insert new element into this List.  
	// If List is non-empty, insertion takes place after back element.
	void append(Object data) {
		if (back == null) {
			back = new Node(data);
			front = back;
			locator = back;
		} else {
			Node N = back;
			N.next = new Node(data);
			back = N.next;
			back.prev = N;
		}
		length++;
	}

	// insertBefore()
	// Insert new element before cursor.
	// Pre: length() > 0, index() >= 0
	void insertBefore(Object data) {
		if (length < 0 && index < 0) {
			throw new RuntimeException("List Error: insertBefore() called on empty List");
		} else {
			if (index == 0) {
				prepend(data);
			} else {
				Node N = new Node(data);
				Node temp = locator.prev;
				N.prev = temp;
				N.next = locator;
				temp.next = N;
				locator.prev = N;
				length++;
				index++;
			}
		}
	}

	// insertAfter()
	// Insert new element after cursor.
	// Pre: length() > 0, index() >= 0
	void insertAfter(Object data) {
		if (length < 0 && index < 0) {
			throw new RuntimeException("List Error: insertAfter() called on empty List");
		} else {
			if (index == (length - 1)) {
				append(data);
			} else {
				Node N = new Node(data);
				Node temp = locator.next;
				N.next = temp;
				N.prev = locator;
				temp.prev = N;
				locator.next = N;
				length++;
			}
		}
	}

	// deleteFront()
	// Deletes the front element.
	// Pre: length() > 0
	void deleteFront() {
		if (length < 1) {
			throw new RuntimeException("List Error: deleteFront() called on empty list");
		}
		if (locator == front) {
			locator = null;
			index = -1;
		}
		front = front.next;
		front.prev = null;
		length--;
	}

	// deleteBack()
	// Deletes the back element.
	// Pre: length() > 0
	void deleteBack() {
		if (length < 1) {
			throw new RuntimeException("List Error: deleteBack() called on empty list");
		}
		if (locator == back) {
			locator = null;
			index = -1;
		}
		back = back.prev;
		back.next = null;
		length--;
	}

	// delete()
	// Deletes cursor element, making cursor undefined.
	// Pre: length() > 0, index() >= 0
	void delete() {
		if (length < 1) {
			throw new RuntimeException("List Error: delete() called on empty List");
		} 
		if (index < 0) {
			throw new RuntimeException("List Error: delete() called on undefined cursor");
		} 
		if (locator == back) {
			deleteBack();
		} else if (locator == front) {
			deleteFront();
		} else {
			locator.prev.next = locator.next;
			locator.next = locator.prev;
			locator = null;
			index = -1;
			length--; 
		}
	}

	// Other methods ---------------------------------------------------------

	// toString()
	// Overrides Object's toString method. 
	// Returns a String representation of this List consisting of a space separated sequence of integers, with front on left.
	public String toString(){
      String str = "";
      Node N;
      for (N = front; N != null; N = N.next) {
      		str += N.toString() + " ";
      }
      return str;
   }
}
