package reversi;

import java.io.IOException;
import java.util.ArrayList;

import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import reversi.Game.status;

public class ReversiBoard extends GridPane {
	private Game game;
	private Label current_player, white_score, black_score;
	public ReversiBoard(Game game, Label current_player, Label white_score, Label black_score) {
		this.game = game;
		this.current_player = current_player;
		this.white_score = white_score;
		this.black_score = black_score;
		
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ReversiBoard.fxml"));
		fxmlLoader.setRoot(this);
		fxmlLoader.setController(this);
	    try {
	    	fxmlLoader.load();
	    	this.setOnMouseClicked(event -> {
				 double x = event.getSceneX();
				 double y = event.getSceneY();
				 Move chosenMove = convertClickToMove(x, y);
				 if (this.game.makeTurn(chosenMove)) {    //Player did Move.
					 updateGameStatus();
				 }    //Move input was wrong.
			 });

		} catch (IOException exception) {
			 throw new RuntimeException(exception);
	    }
	}
	
	public void showEndGameStatus() {
		Alert alert = new Alert(AlertType.INFORMATION);
		alert.setTitle("Game Over");
		alert.setHeaderText(null);
		alert.setContentText(this.game.whoWin());
		alert.showAndWait();
	}
	    	
	public void updateGameStatus() {
		flipPlayers();
		this.white_score.setText(this.game.WhiteScore());
		this.black_score.setText(this.game.BlackScore());
		draw();
		status status_game= this.game.checkStatusGame();
		if (status_game == status.End) {    //Check if game now is finished.
			 showEndGameStatus();
		 }
		 if (status_game == status.NoMove) {    //Check if other player have move.
			 flipPlayers();
			 showNoMoveStatus();
		 }
	}
	
	public void showNoMoveStatus() {
		Alert alert = new Alert(AlertType.INFORMATION);
		alert.setTitle("Player's status");
		alert.setHeaderText(null);
		alert.setContentText("No possible move. Turn passes to other player");
		alert.showAndWait();
	}
	
	public void flipPlayers() {
		if (this.current_player.getText().equals("Black")) {
			this.current_player.setText("White");
		} else {
			this.current_player.setText("Black");
		}
	}
	
	public Move convertClickToMove(double x, double y) {
		char board[][] = this.game.getBoard();
		int size = board.length;
		
		int j = (int) ( x /((this.getPrefHeight() / size)));
		int i = (int) ( y /((this.getPrefWidth() / size)));
		
		return new Move(i + 1, j + 1);
	}
	
	public void drawPossibleMoves(int cellWidth, int cellHeight, int length) {
		game.clearPossibleMoves();
		game.setPossibleMoves();
		ArrayList<Move> possible_moves = game.getPossibleMoves();
		
		for (int i = 0; i < length; i++) {
			 for (int j = 0; j < length; j++) {
				 Move m = new Move(i + 1, j + 1);
				 Tile tile;
				 if (possible_moves.contains(m)) {
					 tile = new Tile(cellHeight, cellWidth, Color.RED);
				 } else {
					 tile = new Tile(cellHeight, cellWidth, Color.LIGHTYELLOW);
				 }
				 tile.setTranslateX(j * cellWidth);
				 tile.setTranslateY(i * cellHeight);
				 this.getChildren().add(tile);
			 }
		 }
	}

	public void draw() {
		 this.getChildren().clear();
		 
		 char board[][] = this.game.getBoard();
		 int length = board.length;
		 
		 int height = (int) this.getPrefHeight();
		 int width = (int) this.getPrefWidth();
		 
		 int cellHeight = height / length;
		 int cellWidth = width / length;
		 
		 drawPossibleMoves(cellWidth, cellHeight, length);
		 
		 double radius = cellWidth / 2 - 10;    //TODO:: GAP = 10
		 
		 for (int i = 0; i < length; i++) {
			 for (int j = 0; j < length; j++) {
				 Circle circle = new Circle(radius);
				 circle.setStroke(Color.BLACK);
				 circle.setTranslateX(j * cellWidth + 10);
				 circle.setTranslateY(i * cellHeight);
				 circle.setRadius(radius);
				 if (board[i][j] == 'X') {
			 	 	 circle.setFill(Color.BLACK);
			 	 	 this.getChildren().add(circle);
				 }
				 if (board[i][j] == 'O') {
				 	 circle.setFill(Color.WHITE);
				 	 this.getChildren().add(circle);
				 }
			 }
		 }
    }
	
	private class Tile extends StackPane {
		public Tile(int cellHeight, int cellWidth, Color color) {
			Rectangle border = new Rectangle(cellHeight, cellWidth);
			border.setFill(color);
			border.setStroke(Color.BLACK);
			
			setAlignment(Pos.CENTER);
			this.getChildren().add(border);
		}
	}
}
