package reversi;

public class Player {
	private char symbol;

	public Player(char pSymbol) {
		this.symbol = pSymbol;
	}

	public char getSymbol() {
		return this.symbol;
	}
	
	public char getRivalSymbol() {
		if (this.symbol == 'X') return 'O';
		return 'X';
	}
}
