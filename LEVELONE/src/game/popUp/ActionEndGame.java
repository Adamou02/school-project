package game.popUp;

import game.Game;
import game.PrimaryStageHolder;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import game.utils.Minuteur;

/**
 * La classe ActionEndGame affiche une fenêtre contextuelle à la fin du jeu, indiquant si le joueur a gagné ou perdu.
 */
public class ActionEndGame {

    private static boolean isOpen = false;

    /**
     * Affiche la fenêtre contextuelle de fin de jeu.
     * 
     * @param victory Indique si le joueur a gagné (true) ou perdu (false).
     */
    public static void displayEndGame(Boolean victory) {

        Minuteur.pause();
        Button restartGame = createStyledButton("Restart");

        Button exitGame = createStyledButton("Exit");

        BorderPane borderPane = new BorderPane();
        borderPane.setStyle("-fx-padding: 5px; -fx-background-color: rgb(56, 52, 68);");

        VBox vBox = new VBox(10);
        vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56, 52, 50);");
        vBox.setAlignment(Pos.CENTER);

        HBox hBox = new HBox(10, restartGame, exitGame);
        hBox.setAlignment(Pos.CENTER);

        Label endMessage;
        if (victory) {
            endMessage = new Label("Congrats, it's a win!");
        } else {
            endMessage = new Label("Ohh you lost! :(");
        }
        endMessage.setStyle("-fx-text-fill: white; -fx-margin-bottom: 10px;");

        vBox.getChildren().addAll(
                endMessage,
                hBox
        );

        borderPane.setCenter(vBox);

        Scene dialogScene = new Scene(borderPane, 300, 200);

        Stage dialog = new Stage();
        dialog.initStyle(StageStyle.UNDECORATED);
        dialog.setScene(dialogScene);
        dialog.setTitle("End Game!");

        dialog.setOnCloseRequest(event -> {
            event.consume();
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

    /**
     * Crée et retourne un bouton avec un style personnalisé.
     * 
     * @param text Texte du bouton.
     * @return Le bouton avec le style personnalisé.
     */
    private static Button createStyledButton(String text) {
        Button button = new Button(text);
        button.setStyle("-fx-background-color: rgb(56, 52, 68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");
        return button;
    }
}