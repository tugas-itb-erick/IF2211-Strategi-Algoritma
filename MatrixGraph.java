/* NIM/Nama : 13515057 / Erick Wijaya */
/* File     : MatrixGraph.java        */

import java.io.*;
import java.util.*;

public class MatrixGraph {
	private int[][] data;
	private int size;
	private static final int UNDEF = Integer.MAX_VALUE;
	private static final int FIRST_NODE = 0;

  /* PUBLIC FUNCTION & CTOR */
	public MatrixGraph(Scanner in) {
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

	public MatrixGraph(MatrixGraph in) {
		size = in.getSize();
		data = new int[size][size];
		for(int i=0; i<size; i++){
			for(int j=0; j<size; j++){
				data[i][j] = in.getData(i,j);
			}
		}
	}

	public void read(Scanner in) {
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

	public void print() {
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

	public int getData(int i, int j) {
		return data[i][j];
	}

	public void tsp1() {
		PriorityQueue<Triplet<MatrixGraph, Integer, Vector<Integer>>> pq = new
			PriorityQueue<Triplet<MatrixGraph, Integer, Vector<Integer>>>(1, new MatrixGraphTripletComparator());

		// insert first node to pq
		MatrixGraph mg = new MatrixGraph(this);
		Integer firstReduce = mg.reduceAll();
		Vector<Integer> firstSolution = new Vector<Integer>(1);
		firstSolution.add(FIRST_NODE);
		pq.add(new Triplet<MatrixGraph, Integer, Vector<Integer>>(mg, firstReduce, firstSolution));

		// b&b
		while (pq.peek().getThird().size() < size) {
			Triplet<MatrixGraph, Integer, Vector<Integer>> head = pq.poll();
			int node = head.getThird().lastElement();

			for(int j=0; j<size; j++){
				if (head.getFirst().getData(node, j) != UNDEF){
					// Create Matrix, Cost, and Vector from head of PQ
					MatrixGraph branch = new MatrixGraph(head.getFirst());
					Integer cost = head.getSecond() + branch.getData(node, j);
					Vector<Integer> solution = new Vector<Integer>(head.getThird());

					//System.out.println("before: " + head.getThird().toString()); branch.print();

					// set to UNDEF to prevent subtour
					branch.setUndefRow(node);
					branch.setUndefCol(j);
					for(int i=0; i<solution.size(); i++){
						branch.setUndefPos(j, solution.get(i));
					}

					solution.add(j);

					cost += branch.reduceAll();

					//System.out.println("add: " + solution.toString());
					//System.out.println("cost: " + cost);
					//branch.print();System.out.println();

					pq.add(new Triplet<MatrixGraph, Integer, Vector<Integer>>(branch, cost, solution));

					/*branch.print(); System.out.println("cost:"+cost);
					System.out.println(solution.toString());*/
				}
			}
		}
		pq.peek().getThird().add(FIRST_NODE);

		System.out.println("Solusi: " + pq.peek().getThird().toString());
		System.out.println("Jarak Minimum: " + pq.peek().getSecond());
	}

	public void tsp2() {
		PriorityQueue<Pair<Integer, Vector<Integer>>> pq = new
			PriorityQueue<Pair<Integer, Vector<Integer>>>();

		// insert first node to pq
		Vector<Integer> firstSolution = new Vector<Integer>(1);
		firstSolution.add(FIRST_NODE);
		pq.add(new Pair<Integer, Vector<Integer>>(countSumOfTwoMinAllRow(), firstSolution));

		// b&b
		while (pq.peek().getSecond().size() < size){
			Pair<Integer, Vector<Integer>> head = pq.poll();

			for(int i=0; i<size; i++){

			}
		}

	}

	/* PRIVATE FUNCTION FOR TSP1 AND TSP2 */
	private void setUndefRow(int r) {
		for(int j=0; j<size; j++)
			data[r][j] = UNDEF;
	}

	private void setUndefCol(int c) {
		for(int i=1; i<size; i++)
			data[i][c] = UNDEF;
	}

	private void setUndefPos(int i, int j) {
		data[i][j] = UNDEF;
	}

	private int getMinRow(int r) {
		int min = data[r][0];
		for(int j=1; j<size; j++){
			if (data[r][j] < min)
				min = data[r][j];
		}
		return min;
	}

	private int getMinCol(int c) {
		int min = data[0][c];
		for(int i=1; i<size; i++){
			if (data[i][c] < min)
				min = data[i][c];
		}
		return min;
	}

	private int getFirstMinRow(int r) {
		return getMinRow(r);
	}

	private int getFirstMinCol(int c) {
		return getMinCol(c);
	}

	private int countSumOfTwoMinRow(int r) {
		int first, second;
		first = second = Integer.MAX_VALUE;
		for(int j=0; j<size; j++){
			if (data[r][j] < first){
				second = first;
				first = data[r][j];
			}
			else if ((data[r][j] >= first) && (data[r][j] < second)){
				second = data[r][j];
			}
		}
		return first + second;
	}

	private int countSumOfTwoMinAllRow() {
		int sum = 0;
		for(int i=0; i<size; i++){
			sum += countSumOfTwoMinRow(i);
		}
		return sum;
	}

	private int getSecondMinCol(int c) {
		int first, second;
		first = second = Integer.MAX_VALUE;
		for(int i=0; i<size; i++){
			if (data[i][c] < first){
				second = first;
				first = data[i][c];
			}
			else if ((data[i][c] >= first) && (data[i][c] < second)){
				second = data[i][c];
			}
		}
		return second;
	}

	private int reduceRow(int r) {
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

	private int reduceCol(int c) {
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

	private int reduceAllRow() {
		int reduced = 0;
		for(int i=0; i<size; i++)
			reduced += reduceRow(i);
		return reduced;
	}

	private int reduceAllCol() {
		int reduced = 0;
		for(int j=0; j<size; j++)
			reduced += reduceCol(j);
		return reduced;
	}

	private int reduceAll() {
		return reduceAllRow() + reduceAllCol();
	}

}
