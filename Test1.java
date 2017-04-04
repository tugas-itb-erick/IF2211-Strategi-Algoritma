/**
 * Created by asus on 4/4/2017.
 */

import org.graphstream.graph.*;
import org.graphstream.graph.implementations.*;

public class Test1 {
    public static void main(String args[]) {
        Graph graph = new SingleGraph("Tutorial 1");
        graph.addNode("A" );
        graph.addNode("B" );
        graph.addNode("C" );
        graph.addEdge("AB", "A", "B");
        graph.addEdge("BC", "B", "C");
        graph.addEdge("CA", "C", "A");
        /*
        graph.setStrict(false);
        graph.setAutoCreate( true );
        graph.addEdge( "AB", "A", "B" );
        graph.addEdge( "BC", "B", "C" );
        graph.addEdge( "CA", "C", "A" );
         */
        graph.display();
    }
}
