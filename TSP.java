/* NIM/Nama : 13515057 / Erick Wijaya */
/* File     : TSP.java                 */

import java.io.*;
import java.util.*;

public class TSP {
	private static int[][] tour;
	private static int size;
	private static final int UNDEF = -1;

	public static void read(Scanner in){
		size = in.nextInt();
		tour = new int[size][size];
		for(int i=0; i<size; i++)
			for(int j=0; j<size; j++)
				tour[i][j] = in.nextInt();
	}

	public static int getMinRow(int r){
		int min = Integer.MAX_VALUE;
		for(int j=0; j<size; j++){
			if ((tour[r][j] < min) && (tour[r][j] >= 0))
				min = tour[r][j];
		}
		return min;
	}

	public static int getMinCol(int c){
		int min = Integer.MAX_VALUE;
		for(int i=0; i<size; i++){
			if ((tour[i][c] < min) && (tour[i][c] >= 0))
				min = tour[i][c];
		}
		return min;
	}

	public static void reduceRow(int r){
		int min = getMinRow(r);
		for(int j=0; j<size; j++){
			if (tour[r][j] != UNDEF)
				tour[r][j] -= min;
		}
	}

	public static void reduceCol(int c){
		int min = getMinCol(c);
		for(int i=1; i<size; i++){
			if (tour[i][c] != UNDEF)
				tour[i][c] -= min;
		}
	}

  public static void print(){
    for(int i=0; i<size; i++){
      for(int j=0; j<size; j++){
        if (tour[i][j] == UNDEF){
          System.out.print("X   ");
        }
        else{
            System.out.print(tour[i][j]);
            if (tour[i][j] < 10)
              System.out.print("   ");
            else if (tour[i][j] < 100)
              System.out.print("  ");
            else
              System.out.print(" ");
        }
      }
      System.out.println();
    }
  }


	public static void main(String[] args) {
    try{
      Scanner in = new Scanner(new File("tsp.txt"));
      read(in);
      print();
			for(int i=0; i<size; i++){
				reduceRow(i);
			}
			for(int j=0; j<size; j++){
				reduceCol(j);
			}
			print();

    } catch(FileNotFoundException e) {
      System.out.println(e);
    }

	}

}
