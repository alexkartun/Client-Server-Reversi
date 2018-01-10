package reversi;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Rectangle;
import reversi.Game.status;

public class ReversiBoard extends GridPane {
	private Game game;
	private Label current_player, white_score, black_score, win_game;
	public ReversiBoard(Game game, Label current_player, Label white_score, Label black_score, Label win_game) {
		this.game = game;
		this.current_player = current_player;
		this.white_score = white_score;
		this.black_score = black_score;
		this.win_game = win_game;
		
		FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("ReversiBoard.fxml"));
		fxmlLoader.setRoot(this);
		fxmlLoader.setController(this);
	    try {
	    	fxmlLoader.load();
	    	this.setOnMouseClicked(event -> {
				 double x = event.getSceneX();
				 double y = event.getSceneY();
				 Move chosenMove = convertClickToMove(x, y);
				 status status_of_turn = this.game.makeTurn(chosenMove);
				 if (status_of_turn == status.Move || status_of_turn == status.NoMove) {
					 updateGameStatus();
				     draw();
				 }
				 if (status_of_turn == status.End) {
					 updateEndGameStatus();
				 }
			 });

		} catch (IOException exception) {
			 throw new RuntimeException(exception);
	    }
	}
	
	public void updateEndGameStatus() {
		this.win_game.setText(game.whoWin());
	}
	    	
	public void updateGameStatus() {
		if (current_player.getText().equals("Black")) {
			current_player.setText("White");
		} else {
			current_player.setText("Black");
		}
		this.white_score.setText(game.WhiteScore());
		this.black_score.setText(game.BlackScore());
	}
	
	public Move convertClickToMove(double x, double y) {
		char board[][] = this.game.getBoard();
		int size = board.length;
		
		int j = (int) ( x /((this.getPrefHeight() / size)));
		int i = (int) ( y /((this.getPrefWidth() / size)));
		
		return new Move(i + 1, j + 1);
	}

	public void draw() {
		 this.getChildren().clear();
		 
		 char board[][] = this.game.getBoard();
		 int length = board.length;
		 
		 int height = (int) this.getPrefHeight();
		 int width = (int) this.getPrefWidth();
		 
		 int cellHeight = height / length;
		 int cellWidth = width / length;
		 
		 for (int i = 0; i < length; i++) {
			 for (int j = 0; j < length; j++) {
				 Tile tile = new Tile(cellHeight, cellWidth);
				 tile.setTranslateX(j * cellWidth);
				 tile.setTranslateY(i * cellHeight);
				 this.getChildren().add(tile);
			 }
		 }
		 
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
		public Tile(int cellHeight, int cellWidth) {
			Rectangle border = new Rectangle(cellHeight, cellWidth);
			border.setFill(Color.LIGHTYELLOW);
			border.setStroke(Color.BLACK);
			
			setAlignment(Pos.CENTER);
			this.getChildren().add(border);
		}
	}
}
