/* NIM/Nama : 13515057 / Erick Wijaya */
/* File     : MatrixGraph.java        */

import java.io.*;
import java.util.*;

public class MatrixGraph {
	private int[][] data;
	private int size;
	private static final int UNDEF = Integer.MAX_VALUE;
	private static final int FIRST_NODE = 0;

	public MatrixGraph(Scanner in){
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

	public MatrixGraph(MatrixGraph in){
		size = in.getSize();
		data = new int[size][size];
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				data[i][j] = in.getData(i,j);
			}
		}
	}

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

	public int getSize(){
		return size;
	}

	public int getData(int i, int j){
		return data[i][j];
	}

	public void setUndefRow(int r){
		for(int j=0; j<size; j++)
			data[r][j] = UNDEF;
	}

	public void setUndefCol(int c){
		for(int i=1; i<size; i++)
			data[i][c] = UNDEF;
	}

	public void setUndefPos(int i, int j){
		data[i][j] = UNDEF;
	}

	private int getMinRow(int r){
		int min = data[r][0];
		for(int j=1; j<size; j++){
			if (data[r][j] < min)
				min = data[r][j];
		}
		return min;
	}

	private int getMinCol(int c){
		int min = data[0][c];
		for(int i=1; i<size; i++){
			if (data[i][c] < min)
				min = data[i][c];
		}
		return min;
	}

	private int reduceRow(int r){
		int min = getMinRow(r);
		int reduced = 0;
		if (min != UNDEF){
			reduced += min;
			for(int j=0; j<size; j++){
				if (data[r][j] != UNDEF){
					data[r][j] -= min;
				}
			}
		}
		return reduced;
	}

	private int reduceCol(int c){
		int min = getMinCol(c);
		int reduced = 0;
		if (min != UNDEF){
			reduced += min;
			for(int i=0; i<size; i++){
				if (data[i][c] != UNDEF)
					data[i][c] -= min;
			}
		}
		return reduced;
	}

	private int reduceAllRow(){
		int reduced = 0;
		for(int i=0; i<size; i++)
			reduced += reduceRow(i);
		return reduced;
	}

	private int reduceAllCol(){
		int reduced = 0;
		for(int j=0; j<size; j++)
			reduced += reduceCol(j);
		return reduced;
	}

	public int reduceAll(){
		return reduceAllRow() + reduceAllCol();
	}

	@SuppressWarnings("unchecked")
	public void tsp(){
		PriorityQueue<Triplet<MatrixGraph, Integer, Vector<Integer>>> pq = new
			PriorityQueue<Triplet<MatrixGraph, Integer, Vector<Integer>>>(1, new MatrixGraphTripletComparator());

		// insert first node to pq
		MatrixGraph mg = new MatrixGraph(this);
		Integer firstReduce = mg.reduceAll();
		Vector<Integer> firstSolution = new Vector<Integer>(1);
		firstSolution.add(FIRST_NODE);
		pq.add(new Triplet(mg, firstReduce, firstSolution));

		//System.out.println();

		// b&b
		do {
			Triplet<MatrixGraph, Integer, Vector<Integer>> head = pq.poll();
			int node = head.getThird().lastElement();

			for(int j=0; j<size; j++){
				if (head.getFirst().getData(node, j) != UNDEF){
					MatrixGraph branch = new MatrixGraph(head.getFirst());

					Integer cost = head.getSecond() + branch.getData(node, j);

					branch.setUndefRow(node);
					branch.setUndefCol(j);
					branch.setUndefPos(j, node);

					cost += branch.reduceAll();

					Vector<Integer> solution = new Vector(head.getThird());
					solution.add(j);

					pq.add(new Triplet(branch, cost, solution));

					/*branch.print(); System.out.println("cost:"+cost);
					System.out.println(solution.toString());*/
				}
			}
		} while (pq.peek().getThird().lastElement() != FIRST_NODE);

		System.out.println("Solusi: " + pq.peek().getThird().toString());
		System.out.println("Jarak Minimum: " + pq.peek().getSecond());
		
	}

}
