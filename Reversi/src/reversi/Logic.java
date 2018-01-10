package reversi;

import java.util.ArrayList;
import reversi.Board;

public class Logic {
	private Board board;
	private ArrayList<Move> possibleMoves;
	
	public Logic(Board board) {
		this.board = board;
		this.possibleMoves = new ArrayList<Move>();
	}
	
	public Board getBoard() {
		return this.board;
	}
	
	public ArrayList<Move> getPossibleMoves() {
		return this.possibleMoves;
	}
	
	public void addPossibleMove(Move m) {
		possibleMoves.add(m);
	}

	public void clearPossibleMoves() {
		possibleMoves.clear();
	}
	
	public void setPossibleMoves(Player p) {
		int i, j;
		for (i = 0; i < board.getSize(); i++) {
			for (j = 0; j < board.getSize(); j++) {
				if (board.getBoardCells()[i][j] == ' ') {
					if (checkAllSides(i, j, p, false)) {
						Move m = new Move(i + 1, j + 1);
						addPossibleMove(m);
					}
				}
			}
		}
	}
	
	
	public boolean isCellInBorder(int n, int border) {
		if (n >= 0 && n < border) {
			return true;
		}
		return false;
	}

	public boolean isMoveValid(Move m) {
		for (int i = 0; i < possibleMoves.size(); i++) {
			if (m.getRow() == possibleMoves.get(i).getRow() && m.getCol() == possibleMoves.get(i).getCol()) {
				return true;
			}
		}
		return false;
	}
	
	public boolean checkMoveInLine(int row, int col, int rowDelta, int colDelta, Player p) {
		char currBoard[][] = board.getBoardCells();
		while (currBoard[row][col] == p.getRivalSymbol() &&
				isCellInBorder(row + rowDelta, board.getSize()) &&
				isCellInBorder(col + colDelta, board.getSize())) {
			row += rowDelta;
			col += colDelta;
		}
		if (currBoard[row][col] == p.getSymbol()) {
			return true;
		}
		return false;

	}

	public void flipRivalsCells(int row, int col,
		int rowDelta, int colDelta, Player p) {
		char currBoard[][] = board.getBoardCells();
		while (currBoard[row][col] == p.getRivalSymbol() &&
				isCellInBorder(row + rowDelta, board.getSize()) &&
				isCellInBorder(col + colDelta, board.getSize())) {
			row += rowDelta;
			col += colDelta;
		}
		if (currBoard[row][col] == p.getSymbol()) {
			row -= rowDelta;
			col -= colDelta;
			while (currBoard[row][col] == p.getRivalSymbol()) {
				currBoard[row][col] = p.getSymbol();
				row -= rowDelta;
				col -= colDelta;
			}
		}
	}

	public boolean checkAllSides (int row, int col, Player p, boolean toUpdate) {
		char[][] currBoard = board.getBoardCells();
		// Check right.
		if (isCellInBorder(col+1, board.getSize())) {
			if (currBoard[row][col+1] == p.getRivalSymbol()) {
				if (!toUpdate) {
					if (checkMoveInLine(row, col+1, 0, 1, p)) {
						return true;
					}
				}
				else {
					flipRivalsCells(row, col+1, 0, 1, p);
				}
			}
		}

		// Check left.
		if (isCellInBorder(col-1, board.getSize())) {
			if (currBoard[row][col-1] == p.getRivalSymbol()) {
				if (!toUpdate) {
					if (checkMoveInLine(row, col-1, 0, -1, p)) {
						return true;
					}
				}
				else {
					flipRivalsCells(row, col-1, 0, -1, p);
				}
			}
		}

		// Check down.
		if (isCellInBorder(row+1, board.getSize())) {
			if (currBoard[row+1][col] == p.getRivalSymbol()) {
				if (!toUpdate) {
					if (checkMoveInLine(row+1, col, 1, 0, p)) {
						return true;
					}
				}
				else {
					flipRivalsCells(row+1, col, 1, 0, p);
				}
			}

		}

		// Check up.
		if (isCellInBorder(row-1, board.getSize())) {
			if (currBoard[row-1][col] == p.getRivalSymbol()) {
				if (!toUpdate) {
					if (checkMoveInLine(row-1, col, -1, 0, p)) {
						return true;
					}
				}
				else {
					flipRivalsCells(row-1, col, -1, 0, p);
				}
			}

		}

		// Check up-right
		if (isCellInBorder(row-1, board.getSize()) &&
				isCellInBorder(col+1, board.getSize())) {
			if (currBoard[row-1][col+1] == p.getRivalSymbol()) {
				if (!toUpdate) {
					if (checkMoveInLine(row-1, col+1, -1, 1, p)) {
						return true;
					}
				}
				else {
					flipRivalsCells(row-1, col+1, -1, 1, p);
				}
			}

		}

		// Check up-left.
		if (isCellInBorder(row-1, board.getSize()) &&
					isCellInBorder(col-1, board.getSize())) {
			if (currBoard[row-1][col-1] == p.getRivalSymbol()) {
				if (!toUpdate) {
					if (checkMoveInLine(row-1, col-1, -1, -1, p)) {
						return true;
					}
				}
				else {
					flipRivalsCells(row-1, col-1, -1, -1, p);
				}
			}

		}

		// Check down-right
		if (isCellInBorder(row+1, board.getSize()) &&
						isCellInBorder(col+1, board.getSize())) {
			if (currBoard[row+1][col+1] == p.getRivalSymbol()) {
				if (!toUpdate) {
					if (checkMoveInLine(row+1, col+1, 1, 1, p)) {
						return true;
					}
				}
				else {
					flipRivalsCells(row+1, col+1, 1, 1, p);
				}
			}

		}

		//Check down-left
		if (isCellInBorder(row+1, board.getSize()) &&
							isCellInBorder(col-1, board.getSize())) {
			if (currBoard[row+1][col-1] == p.getRivalSymbol()) {
				if (!toUpdate) {
					if (checkMoveInLine(row+1, col-1, 1, -1, p)) {
							return true;
					}
				}
				else {
					flipRivalsCells(row+1, col-1, 1, -1, p);
				}
			}
		}

		return false;
	}

	public void updateBoard(int row, int col, Player p) {
		char currBoard[][] = board.getBoardCells();
		currBoard[row][col] = p.getSymbol();
		checkAllSides(row, col, p, true);
	}
}
