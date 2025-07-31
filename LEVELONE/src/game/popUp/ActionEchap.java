package game.popUp;

import game.Game;
import game.PrimaryStageHolder;
import game.map.Map;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import game.utils.Minuteur;

/**
 * La classe ActionEchap affiche une boîte de dialogue pour la pause du jeu.
 */
public class ActionEchap {
    private static boolean isOpen = false;

    /**
     * Affiche la boîte de dialogue de pause du jeu.
     *
     * @param map La carte du jeu.
     */
    public static void displayPause(Map map) {
        map.getPlayer().stopAnimation();
        Minuteur.pause();

        Button goBack = createStyledButton("Continue");
        Button restartGame = createStyledButton("Restart");
        Button exitGame = createStyledButton("Exit");

        BorderPane borderPane = new BorderPane();
        borderPane.setStyle("-fx-padding: 10px; -fx-background-color: rgb(56, 52, 68);");

        VBox vBox = new VBox(10);
        vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56, 52, 50);");
        vBox.setAlignment(Pos.CENTER);

        HBox hBox = new HBox(10, goBack, restartGame, exitGame);
        hBox.setAlignment(Pos.CENTER);

        vBox.getChildren().addAll(hBox);

        borderPane.setCenter(vBox);

        Scene dialogScene = new Scene(borderPane, 300, 200);

        Stage dialog = new Stage();
        dialog.initStyle(StageStyle.UNDECORATED);
        dialog.setScene(dialogScene);
        dialog.setTitle("Pause");

        dialog.setOnCloseRequest(event -> event.consume());

        goBack.setOnAction(event -> {
            isOpen = false;
            Minuteur.resume();
            map.playMonster();
            dialog.close();
        });

        restartGame.setOnAction(event -> {
            System.out.println("Restart game");
            dialog.close();
            Stage actualStage = PrimaryStageHolder.getPrimaryStage();
            try {
                actualStage.close();
                isOpen = false;
                Game newGame = new Game();
                Stage newPrimaryStage = new Stage();
                newGame.start(newPrimaryStage);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });

        exitGame.setOnAction(event -> {
            System.out.println("Exit game");
            System.exit(0);
        });

        if (!isOpen) {
            dialog.initModality(Modality.APPLICATION_MODAL);
            Platform.runLater(() -> dialog.showAndWait());
            isOpen = true;
        }
    }

    private static Button createStyledButton(String text) {
        Button button = new Button(text);
        button.setStyle("-fx-background-color: rgb(56, 52, 68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");
        return button;
    }
}