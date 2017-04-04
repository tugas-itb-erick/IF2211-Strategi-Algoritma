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

		long startTime = System.nanoTime();

		// insert first node to pq
		MatrixGraph mg = new MatrixGraph(this);
		Integer firstReduce = mg.reduceAll();
		Vector<Integer> firstSolution = new Vector<Integer>(1);
		firstSolution.add(FIRST_NODE);
		pq.add(new Triplet<MatrixGraph, Integer, Vector<Integer>>(mg, firstReduce, firstSolution));

		int liveNode = 1;

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

					++liveNode;
					pq.add(new Triplet<MatrixGraph, Integer, Vector<Integer>>(branch, cost, solution));

					/*branch.print(); System.out.println("cost:"+cost);
					System.out.println(solution.toString());*/
				}
			}
		}
		pq.peek().getThird().add(FIRST_NODE);
		long endTime = System.nanoTime();

		System.out.println("Solusi: " + pq.peek().getThird().toString());
		System.out.println("Bobot: " + pq.peek().getSecond());
		System.out.println("Jumlah Simpul Hidup: " + liveNode);
		System.out.printf("Waktu Eksekusi: %.2fms\n", (double)(endTime - startTime) / 1000000);
	}

	public void tsp2() {
		PriorityQueue<Pair<Integer, Vector<Integer>>> pq = new
			PriorityQueue<Pair<Integer, Vector<Integer>>>(1, new MatrixGraphPairComparator());

		long startTime = System.nanoTime();

		// insert first node to pq
		Vector<Integer> firstSolution = new Vector<Integer>(1);
		firstSolution.add(FIRST_NODE);
		pq.add(new Pair<Integer, Vector<Integer>>(countSumOfTwoMinAllRow(), firstSolution));

		int liveNode = 1;
		// b&b
		while (pq.peek().getSecond().size() < size){
			Pair<Integer, Vector<Integer>> head = pq.poll();

			for(int j=0; j<size; j++){
				boolean isExist = false;
				for(int i=0; i<head.getSecond().size(); i++){
					if (j == head.getSecond().get(i))
						isExist = true;
				}

				if ((data[head.getSecond().lastElement()][j] != UNDEF) && !isExist){
					Vector<Integer> solution = new Vector<Integer>(head.getSecond());

					// add next node to solution
					solution.add(j);

					int completeTour = 0;
					// loop to count completeTour value
					for(int i=0; i<size; i++){
						int ifound = 0;
						while ((ifound < solution.size()) && (solution.get(ifound) != i))
							++ifound;

						if (ifound < solution.size()){ // found at...
							//System.out.println(solution.toString());
							//System.out.println("found at vector i="+ifound+" with size="+solution.size());
							if (ifound == 0){ // beginning, x = (reserved)i1 + i2
								int reserved = data[solution.get(ifound)][solution.get(ifound+1)];
								completeTour += reserved + getMinRowAfterX(i, reserved);
							}
							else if (ifound == solution.size()-1){ // end, x = (reserved)i1 + i2
								int reserved = data[solution.get(ifound)][solution.get(ifound-1)];
								completeTour += reserved + getMinRowAfterX(i, reserved);
							}
							else{ // middle, x = (reserved)i1 + (reserved)i2
								int reserved1 = data[solution.get(ifound)][solution.get(ifound+1)];
								int reserved2 = data[solution.get(ifound)][solution.get(ifound-1)];
								completeTour += reserved1 + reserved2;
							}
						}
						else{
							completeTour += countSumOfTwoMinRow(i); // x = i1 + i2
						}

					}

					++liveNode;
					pq.add(new Pair<Integer, Vector<Integer>>(completeTour, solution));
				}
			}
		}
		pq.peek().getSecond().add(FIRST_NODE);
		long endTime = System.nanoTime();

		System.out.println("Solusi: " + pq.peek().getSecond().toString());
		System.out.println("Bobot: " + pq.peek().getFirst()/2);
		System.out.println("Jumlah Simpul Hidup: " + liveNode);
		System.out.printf("Waktu Eksekusi: %.2fms\n", (double)(endTime - startTime) / 1000000);
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

	private int getMinRowAfterX(int r, int x) {
		int min = Integer.MAX_VALUE;
		boolean firstOcc = false;
		for(int j=0; j<size; j++){
			if ((data[r][j] == x) && !firstOcc){
				firstOcc = true;
			}
			else{
				if (data[r][j] < min)
					min = data[r][j];
			}
		}
		return min;
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
