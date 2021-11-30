import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import java.util.Arrays;

public class Puzzle {
    private final int n;
    private final char[] tiles;
    private int empty;

    private int row(int p) {
        return (int) Math.ceil((double)p/(double)n);
    }

    private int col(int p) {
        if (p % n == 0) return n;
        return p % n;
    }

    public Puzzle(int[][] tiles) {
        n = tiles.length;
        this.tiles = new char[n*n];
        int k = 0 ;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                this.tiles[k] = (char) tiles[i][j];
                if (tiles[i][j] == 0) empty = k;
                k ++;
            }
        }
    }


    public int hamming() {
        int hamming = 0;
        for (int k = 0, ans = 1; k < n * n; k++, ans++) {
            if (tiles[k] == 0) continue;
            if (tiles[k] != ans) hamming++;
        }
        return hamming;
    }

    public int manhattan() {
        int manhattan = 0;
        for (int k = 0; k < n*n; k++) {
            if (tiles[k] == 0) continue;
            int rowdiff = Math.abs(row(tiles[k]) - row(k+1));
            int coldiff = Math.abs(col(tiles[k]) - col(k+1));
            manhattan = manhattan + rowdiff + coldiff;
        }
        return manhattan;
    }

    public boolean isGoal() {
        for (int k = 0 ; k < n * n - 2; k++) {
            if (tiles[k] > tiles[k + 1]) return false;
        }
        return true;
    }
    public int dimension() {
    	return n;
    }

    public Puzzle twin() {
        boolean swapSuccess = false;
        char[] twin = tiles.clone();
        int k = 0;
        do {
            k=StdRandom.uniform(n*n);
        } while (tiles[k] == 0);
        while (swapSuccess == false) {
            int choice = StdRandom.uniform(4);
            switch(choice) {
                case 0 :
                    if(row(k+1) == 1) swapSuccess = false;
                    else if(twin[k-n] == 0) swapSuccess = false;
                    else {
                        swapAbove(twin,k);
                        swapSuccess = true;
                    }
                    break;
                case 1 :
                    if(row(k+1) == n) swapSuccess = false;
                    else if(twin[k+n] == 0) swapSuccess = false;
                    else {
                        swapBelow(twin,k);
                        swapSuccess = true;
                    }
                    break;
                case 2 :
                    if(col(k+1) == 1) swapSuccess = false;
                    else if(twin[k-1] == 0) swapSuccess = false;
                    else {
                        swapLeft(twin,k);
                        swapSuccess = true;
                    }
                    break;
                case 3 :
                    if(col(k+1) == n) swapSuccess = false;
                    else if(twin[k+1] == 0) swapSuccess = false;
                    else {
                        swapRight(twin,k);
                        swapSuccess = true;
                    }
                    break;
            }
        }
        Puzzle twinPuzzle = new Puzzle(toTwoDarray(twin));
        return twinPuzzle;
    }

    public boolean equals(Object y) {
        if (y == this) return true;
        if (y == null) return false;
        if (y.getClass() != this.getClass()) return false;
        Puzzle that = (Puzzle) y;
        if (!Arrays.equals(this.tiles, that.tiles)) return false;
        return true;
    }

    public Iterable<Puzzle> neighbors() {
        Stack<Puzzle> stackNeighbors = new Stack<Puzzle>();
        char[] neighbor;
        if(row(empty+1) != 1) {
            neighbor = tiles.clone();
            swapAbove(neighbor,empty);
            Puzzle neighborPuzzle = new Puzzle(toTwoDarray(neighbor));
            stackNeighbors.push(neighborPuzzle);
        }
        if(row(empty+1) != n) {
            neighbor = tiles.clone();
            swapBelow(neighbor,empty);
            Puzzle neighborPuzzle = new Puzzle(toTwoDarray(neighbor));
            stackNeighbors.push(neighborPuzzle);
        }
        if(col(empty+1) != 1) {
            neighbor = tiles.clone();
            swapLeft(neighbor,empty);
            Puzzle neighborPuzzle = new Puzzle(toTwoDarray(neighbor));
            stackNeighbors.push(neighborPuzzle);
        }
        if(col(empty+1) != n) {
            neighbor = tiles.clone();
            swapRight(neighbor,empty);
            Puzzle neighborPuzzle = new Puzzle(toTwoDarray(neighbor));
            stackNeighbors.push(neighborPuzzle);
        }
        return stackNeighbors;
    }

    public String toString() {
        String s = new String();
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                s += (String.format("%2d ", (int)tiles[k]));
                k++;
            }
            s += ("\n");
        }
        return s.toString();
    }

    private void swapAbove(char[] oneDarray, int k) {
        char temp = oneDarray[k];
        oneDarray[k] = oneDarray[k - n];
        oneDarray[k - n] = temp;
    }
    private void swapBelow(char[] oneDarray, int k) {
        char temp = oneDarray[k];
        oneDarray[k] = oneDarray[k + n];
        oneDarray[k + n] = temp;
    }
    private void swapLeft(char[] oneDarray, int k) {
        char temp = oneDarray[k];
        oneDarray[k] = oneDarray[k - 1];
        oneDarray[k - 1] = temp;
    }
    private void swapRight(char[] oneDarray, int k) {
        char temp = oneDarray[k];
        oneDarray[k] = oneDarray[k + 1];
        oneDarray[k + 1] = temp;
    }

    private int[][] toTwoDarray(char[] oneDarray) {
        int k = 0 ;
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
            tiles[i][j] = oneDarray[k];
            k++;
        }
        return tiles;
    }

    public static void main(String[] args) {
        In in = new In("15puzzle.txt");
        int n = in.readInt();
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            tiles[i][j] = in.readInt();
        Puzzle initial = new Puzzle(tiles);
    }
}