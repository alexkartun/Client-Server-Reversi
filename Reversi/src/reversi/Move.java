package reversi;

public class Move {
	private int row;
	private int col;

	public Move(int r, int c) {
		this.row = r;
		this.col = c;
	}
	
	public void setRow(int r) {
		this.row = r;
	}
	
	public void setCol(int c) {
		this.col = c;
	}
	
	public int getRow() {
		return this.row;
	}
	
	public int getCol() {
		return this.col;
	}
}
