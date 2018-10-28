/* NIM/Nama : 13515057 / Erick Wijaya        */
/* File     : MatrixGraphPairComparator.java */

import java.io.*;
		import java.util.*;

public class MatrixGraphPairComparator implements Comparator< Pair<Integer, Vector<Integer>> > {
	public int compare(Pair<Integer, Vector<Integer>> a, Pair<Integer, Vector<Integer>> b){
		return a.getFirst() - b.getFirst();
	}
}
