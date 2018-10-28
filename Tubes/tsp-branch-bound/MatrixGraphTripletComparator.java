/* NIM/Nama : 13515057 / Erick Wijaya           */
/* File     : MatrixGraphTripletComparator.java */

import java.io.*;
import java.util.*;

public class MatrixGraphTripletComparator implements Comparator< Triplet<MatrixGraph, Integer, Vector<Integer>> > {
	public int compare(Triplet<MatrixGraph, Integer, Vector<Integer>> a, Triplet<MatrixGraph, Integer, Vector<Integer>> b){
		return a.getSecond() - b.getSecond();
	}
}
