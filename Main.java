/* NIM/Nama : 13515057 / Erick Wijaya */
/* File     : Main.java               */

import java.io.*;
import java.util.*;

class Main {
  public static void main(String[] args) {
    try{
      Scanner in = new Scanner(new File("tsp.txt"));
      MatrixGraph mg = new MatrixGraph();

      mg.read(in);
      mg.print();
      for(int i=0; i<mg.size(); i++){
        mg.reduceRow(i);
      }
      for(int j=0; j<mg.size(); j++){
        mg.reduceCol(j);
      }
      mg.print();

    } catch(FileNotFoundException e) {
      System.out.println(e);
    }
  }

}
