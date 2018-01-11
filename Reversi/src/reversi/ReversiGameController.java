package reversi;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

public class ReversiGameController implements Initializable {
	@FXML
	private HBox root;
	@FXML
	private Label current_player;
	@FXML
	private Label black_score;
	@FXML
	private Label white_score;
	
	int size = 4;
	int WIDTH = 400;
	int HEIGHT = 400;

	@FXML
	protected void exit() {
		Stage stage = (Stage) root.getScene().getWindow();
	    stage.close();
	}

	@Override
	public void initialize(URL location, ResourceBundle resources) {
		Game game = new Game(size);
		current_player.setText("Black");
		white_score.setText("2");
		black_score.setText("2");
		
		ReversiBoard reversi_board = new ReversiBoard(game, current_player, white_score, black_score); 
	
		reversi_board.setPrefWidth(WIDTH);
		reversi_board.setPrefHeight(HEIGHT);
		
		root.getChildren().add(0, reversi_board);
		
		reversi_board.draw();
	}
}
