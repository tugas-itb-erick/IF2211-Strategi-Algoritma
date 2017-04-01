/* NIM/Nama : 13515057 / Erick Wijaya */
/* File     : Main.java               */

import java.io.*;
import java.util.*;

class Main {
  public static void main(String[] args) {
    try{
      Scanner in = new Scanner(new File("tsp.txt"));
      MatrixGraph mg = new MatrixGraph(in);

      mg.tsp();

    } catch(FileNotFoundException e) {
      System.out.println(e);
    }
  }

}
