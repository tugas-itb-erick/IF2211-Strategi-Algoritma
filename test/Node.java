import java.util.*;
import java.awt.*;
import java.util.*;
import java.io.*;
public class Node implements Comparable, Serializable {
 // Fields
 private int lowerBound;
 private int size; // Number of cities in partial tour
 private byte [] cities; // Stores partial tour
 private boolean [] blocked = new boolean[TSP.numRows + 1];
 private int level; // The level in the tree
 // Constructor
 public Node (byte [] cities, int size) {
 this.size = size;
 this.cities = cities;
 }
 // Commands
 public void computeLowerBound () {
 lowerBound = 0;
 if (size == 1) {
 for (int i = 1; i <= TSP.numRows; i++) {
 lowerBound += minimum(i);
 }
 } else {
 // Obtain fixed portion of bound
 for (int i = 2; i <= size; i++) {
 blocked[cities[i]] = true;
 lowerBound += TSP.c.cost(cities[i - 1], cities[i]);
 }
 blocked[1] = true;
 lowerBound += minimum(cities[size]);
 blocked[1] = false;
 blocked[cities[size]] = true;
 for (int i = 2; i <= TSP.numRows; i++) {
 if (!blocked[i]) {
 lowerBound += minimum(i);
 }
 }
 }
 }
 public void setLevel (int level) {
 this.level = level;
 }
 public void setCities (byte[] cities) {
 this.cities = cities;
 }
 // Queries
 public int size () {
 return size;
 } 

 public byte [] cities() {
 return cities;
 }
 public int level () {
 return level;
 }
 public int lowerBound() {
 return lowerBound;
 }
 public int compareTo (Object obj) {
 if (this == obj) {
 return 0;
 }
 Node other = (Node) obj;
 if (size < other.size) {
 return 1;
 } else if (size > other.size) {
 return -1;
 } else if (size == other.size) {
 if (lowerBound < other.lowerBound) {
 return -1;
 } else if (lowerBound > other.lowerBound) {
 return 1;
 } else if (lowerBound == other.lowerBound) {
 // Add up the sum of the cities
 int sumThis = 0;
 for (int i = 1; i <= size; i++) {
 sumThis += cities[i];
 }
 int sumOther = 0;
 for (int i = 1; i <= size; i++) {
 sumOther += other.cities[i];
 }
 if (sumThis <= sumOther) {
 return -1;
 } else if (sumThis > sumOther) {
 return 1;
 }
 }
 }
 return 100;
 }

 public boolean equals (Object obj) {
 return this.compareTo(obj) == 0;
 }
 public String toString () {
 String result = "<";
 for (int i = 1; i < cities.length; i++) {
 result += cities[i] + " ";
 }
 if (cities.length == TSP.numRows) {
 for (int i = 2; i <= TSP.numRows; i++) {
 if (!present((byte) i, cities)) { 
 result += i + " ";
 break;
 }
 }
 result += "1>";
 } else {
 result += ">";
 }
 return result;
 }
 private int minimum (int index) {
 int smallest = Integer.MAX_VALUE;
 for (int col = 1; col <= TSP.numRows; col++) {
 if (!blocked[col] && col != index &&
 TSP.c.cost(index, col) < smallest) {
 smallest = TSP.c.cost(index, col);
 }
 }
 return smallest;
 }
 private boolean present (byte city, byte [] cities) {
 for (int i = 1; i <= cities.length - 1; i++) {
 if (cities[i] == city) {
 return true;
 }
 }
 return false;
 }
} 
