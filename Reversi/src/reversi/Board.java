package reversi;

public class Board {
	private char [][] board;
	public Board(int size) {
		board = new char[size][size];
		init();
	}
	
	public void init() {
		int i, j;
		int length = this.board.length;
		for (i = 0; i < length; i++) {
			for (j = 0; j < length; j++) {
				this.board[i][j] = ' ';
			}
		}
		this.board[(length / 2) - 1][(length / 2) - 1] = 'X';
		this.board[length / 2][length / 2] = 'X';
		this.board[length / 2][(length / 2) - 1] = 'O';
		this.board[(length / 2) - 1][length / 2] = 'O';
	}
	
	public char[][] getBoardCells() {
		return this.board ;
	}
	
	public int getSize() {
		return this.board.length;
	}
	
}
