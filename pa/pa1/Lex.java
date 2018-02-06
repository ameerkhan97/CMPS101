//-----------------------------------------------------------------------------
//  Lex.java
//  Ameer Khan
//  ammukhan
//  CS101 PA1
//  Takes two command line arguments giving the names of an 
//  input file and an output file.
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;
   
class Lex {
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String line = null;
      String[] token = null;
      List list = new List();
      int lineNumber = 0;
      int i = 0;

      // checks for exactly two arguments otherwise error
      if(args.length != 2){
         System.err.println("Usage: FileIO infile outfile");
         System.exit(1);
      }
      
      in = new Scanner(new File(args[0])); // takes input file
      out = new PrintWriter(new FileWriter(args[1])); // proudces output file

      while (in.hasNextLine()) {
         lineNumber++;
         in.nextLine();
      }
      in.close();
      in = null;


      token = new String[lineNumber];
      in = new Scanner(new File(args[0])); // takes input file
      out = new PrintWriter(new FileWriter(args[1])); // produces output file

      for (i = 0; i < lineNumber; i++) {
         line = in.nextLine()+" "; // add extra space so split works right
         token[i] = line;
      }
      list.append(0);

      // insertion sort algorithm
      for (int j = 1; j < token.length; j++) {
         i = (j - 1);
         String temp = token[j];
         list.moveBack();
         while (i >= 0 && (temp.compareTo(token[list.get()]) <= 0)) {
            list.movePrev();
            i--;
         }
         if (list.index() >= 0) {
            list.insertAfter(j);
         } else {
            list.prepend(j);
         }
      }

      list.moveFront();
      while (list.index() >= 0) {
         out.println(token[list.get()]);
         list.moveNext();
      }

      in.close();
      out.close();
   }
}