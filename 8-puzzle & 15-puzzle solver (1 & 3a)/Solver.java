import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;

public class Solver {
    private MinPQ<SearchNode> pq;
    private MinPQ<SearchNode> pqTwin;
    private int n;
    private Puzzle initial;
    private Puzzle goal;

    private class SearchNode implements Comparable<SearchNode> {
        private Puzzle puzzle;
        private int nummoves;
        private int priority;
        private SearchNode prevNode;

        public SearchNode(Puzzle puzzle, int nummoves, SearchNode prevNode) {
            this.puzzle = puzzle;
            this.nummoves = nummoves;
            priority = nummoves + puzzle.manhattan();
            this.prevNode = prevNode;
        }

        public int compareTo(SearchNode that) {
            return (this.priority - that.priority);
        }
    }

    public Solver(Puzzle initial) {
        if(initial == null) throw new  NullPointerException();

        this.initial = initial;
        n = initial.dimension();
        pq = new MinPQ<SearchNode>();
        pqTwin = new MinPQ<SearchNode>();

        int[][] tiles = new int[n][n];
        int k = 1 ;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
            tiles[i][j] = k;
            k++;
        }
        tiles[n-1][n-1] = 0;
        goal = new Puzzle(tiles);

        SearchNode lowNode;
        SearchNode lowNodeTwin;
        pq.insert(new SearchNode(initial, 0, null));
        pqTwin.insert(new SearchNode(initial.twin(), 0, null));
        while(!pq.min().puzzle.equals(goal) && !pqTwin.min().puzzle.equals(goal)) {
            lowNode = pq.min();
            lowNodeTwin = pqTwin.min();
            pq.delMin();
            pqTwin.delMin();
            for (Puzzle neighbor: lowNode.puzzle.neighbors()) {
                if (lowNode.nummoves == 0) {
                    pq.insert(new SearchNode(neighbor, lowNode.nummoves+1, lowNode));
                }
                else if (!neighbor.equals(lowNode.prevNode.puzzle)) {
                    pq.insert(new SearchNode(neighbor, lowNode.nummoves+1, lowNode));
                }
            }

            for (Puzzle neighbor: lowNodeTwin.puzzle.neighbors()) {
                if (lowNodeTwin.nummoves == 0) {
                    pqTwin.insert(new SearchNode(neighbor, lowNodeTwin.nummoves+1, lowNodeTwin));
                }
                else if (!neighbor.equals(lowNodeTwin.prevNode.puzzle)) {
                    pqTwin.insert(new SearchNode(neighbor, lowNodeTwin.nummoves+1, lowNodeTwin));
                }
            }
        }
    }

    public boolean isSolvable() {
        if (pq.min().puzzle.equals(goal)) {
            return true;
        }
        if (pqTwin.min().puzzle.equals(goal)) {
            return false;
        }
        return false;
    }

    public int nummoves() {
        if(!isSolvable()) return -1;
        return pq.min().nummoves;
    }

    public Iterable<Puzzle> solution() {
        if(!isSolvable()) return null;
        Stack<Puzzle> stackSolution = new Stack<Puzzle>();
        SearchNode current = pq.min();
        while (current.prevNode!=null) {
            stackSolution.push(current.puzzle);
            current = current.prevNode;
        }
        stackSolution.push(initial);
        return stackSolution;
    }

    public static void main(String[] args) {
        In in = new In("15puzzle.txt");
        int n = in.readInt();
        int state = 0;
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            tiles[i][j] = in.readInt();
        Puzzle initial = new Puzzle(tiles);

        Solver solver = new Solver(initial);

        if (!solver.isSolvable())
        	System.out.println("The Puzzle is not solvable.");
        else {
        	System.out.println("Minimum number of moves = " + solver.nummoves());
        	System.out.println();
            for (Puzzle puzzle : solver.solution())
            {
            	System.out.println("State " + state);
                System.out.print(puzzle);
                System.out.println("The Hamming distance of this puzzle is: " + puzzle.hamming());
                System.out.println("The Manhattan distance of this puzzle is: " + puzzle.manhattan());
                System.out.println();
                state++;
            }
        }
    }
}