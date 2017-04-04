/* NIM/Nama : 13515057 / Erick Wijaya */
/* File     : Main.java               */

import java.io.*;
import java.util.*;

class Main {
  public static void main(String[] args) {
    try{
      Scanner in = new Scanner(new File(args[0]));

      MatrixGraph reducedCostMatrix = new MatrixGraph(in);
      reducedCostMatrix.tsp1();
      reducedCostMatrix.display();

      System.out.println();
      
      MatrixGraph bobotTourLengkap = new MatrixGraph(in);
      bobotTourLengkap.tsp2();

    } catch(FileNotFoundException e) {
      System.out.println(e);
    }
  }

}
