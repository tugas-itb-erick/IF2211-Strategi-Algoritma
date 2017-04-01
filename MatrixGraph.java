/* NIM/Nama : 13515057 / Erick Wijaya */
/* File     : MatrixGraph.java        */

import java.io.*;
import java.util.*;

public class MatrixGraph {
	private int[][] data;
	private int size;
	private final int UNDEF = Integer.MAX_VALUE;

	public void read(Scanner in){
		size = in.nextInt();
		data = new int[size][size];
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				int x = in.nextInt();
				if (x < 0)
					data[i][j] = UNDEF;
				else
					data[i][j] = x;
			}
		}
	}

	public void print(){
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				if (data[i][j] == UNDEF){
					System.out.print("X   ");
				}
				else{
					System.out.print(data[i][j]);
					if (data[i][j] < 10)
						System.out.print("   ");
					else if (data[i][j] < 100)
						System.out.print("  ");
					else
						System.out.print(" ");
				}
			}
			System.out.println();
		}
	}

	public int size(){
		return size;
	}

	public int getMinRow(int r){
		int min = data[r][0];
		for(int j=1; j<size; j++){
			if (data[r][j] < min)
				min = data[r][j];
		}
		return min;
	}

	public int getMinCol(int c){
		int min = data[0][c];
		for(int i=1; i<size; i++){
			if (data[i][c] < min)
				min = data[i][c];
		}
		return min;
	}

	public void reduceRow(int r){
		int min = getMinRow(r);
		for(int j=0; j<size; j++){
			if (data[r][j] != UNDEF)
				data[r][j] -= min;
		}
	}

	public void reduceCol(int c){
		int min = getMinCol(c);
		for(int i=1; i<size; i++){
			if (data[i][c] != UNDEF)
				data[i][c] -= min;
		}
	}

}
