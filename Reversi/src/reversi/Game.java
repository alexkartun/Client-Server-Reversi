package reversi;

import java.util.Stack;

public class Game {
	private Logic logic;
	public enum status {
	     End, NoMove, Move, BadInput
	}
	Stack<Player> players;
	
	public Game(int boardSize) {
		players = new Stack<Player>();
		players.push(new Player('O'));
		players.push(new Player('X'));
		this.logic = new Logic(new Board(boardSize));
	}
	
	public char[][] getBoard() {
		return this.logic.getBoard().getBoardCells();
	}
 
	public status makeTurn(Move m) {
		Player turnPlayer = players.peek();
		this.logic.setPossibleMoves(turnPlayer);
		if (this.logic.getPossibleMoves().isEmpty()) {
			switchTurns();
			Player rival = players.peek();
			this.logic.setPossibleMoves(rival);
			if(this.logic.getPossibleMoves().isEmpty()) {    //END OF GAME. BOTH CANT PLAY //TODO::END GAME
				return status.End;    //END GAME.
			} else {
				return status.NoMove;
			}
		} else {
			if (this.logic.isMoveValid(m)) {
				this.logic.updateBoard(m.getRow() - 1, m.getCol() - 1, turnPlayer);
			} else {
				return status.BadInput;
			}
		}
		switchTurns();
		return status.Move;
	}

	public String WhiteScore() {
		return Integer.toString(countScore('O'));
	}
	
	public String BlackScore() {
		return Integer.toString(countScore('X'));
	}
	
	public int countScore(char player) {
		int count = 0;
		char[][] endingBoard = this.logic.getBoard().getBoardCells();
		for (int i = 0 ; i < this.logic.getBoard().getSize(); i++) {
			for (int j = 0; j < this.logic.getBoard().getSize(); j++) {
				if (endingBoard[i][j] == player) {
					count++;
				}
			}
		}
		return count;
	}
	public void switchTurns() {
		Player p1 = players.peek();
		this.logic.clearPossibleMoves();
		players.pop();
		Player p2 = players.peek();
	    players.pop();
		players.push(p1);
		players.push(p2);
	}

	public String whoWin() {
		int countO = 0, countX = 0;
		countO = countScore('O');
		countX = countScore('X');
		if (countO > countX) {
			return "Player 'O' wins!";
		}
		else if (countO < countX) {
			return "Player 'X' wins!";
		}
		else {
			return "It's a tie.";
		}
	}
}

