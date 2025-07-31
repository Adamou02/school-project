package game.popUp;

import game.character.Player;
import game.map.Map;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

/**
 * La classe ActionDialogPnj affiche une boîte de dialogue pour interagir avec un PNJ.
 */
public class ActionDialogPnj {
    private static boolean isOpen = false;

    /**
     * Affiche la boîte de dialogue pour interagir avec un marchand.
     *
     * @param node        Le nœud associé à la boîte de dialogue.
     * @param player      Le joueur qui interagit avec le marchand.
     * @param gridpane    Le GridPane contenant les éléments du jeu.
     * @param map         La carte du jeu.
     */
    public static void displayActionMerchant(Node node, Player player, GridPane gridpane, Map map) {
        player.stopAnimation();
        Button next = createStyledButton("Next");
        Button next2 = createStyledButton("Next");
        Button exit = createStyledButton("Exit");

        BorderPane borderPane = new BorderPane();
        borderPane.setStyle("-fx-padding: 10px; -fx-background-color: rgb(56, 52, 68);");

        VBox vBox = new VBox(10);
        vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56, 52, 50);");
        vBox.setAlignment(Pos.CENTER);

        HBox hBox = new HBox(10, next);
        hBox.setAlignment(Pos.CENTER);

        HBox hBox2 = new HBox(10, next2);
        hBox2.setAlignment(Pos.CENTER);

        Label endMessage = createStyledLabel("Hello Julien, today you will have to retrieve my treasure that the monsters have taken from me. To do this, you will have access to various special items and different quests to complete.");

        vBox.getChildren().addAll(
                endMessage,
                hBox
        );

        borderPane.setCenter(vBox);

        Scene dialogScene = new Scene(borderPane, 400, 200);

        Stage dialog = new Stage();
        dialog.initStyle(StageStyle.UNDECORATED);
        dialog.setScene(dialogScene);
        dialog.setTitle("Your quest!");

        dialog.setOnCloseRequest(event -> {
            isOpen = false;
        });

        next.setOnAction(event -> {
            hBox.getChildren().clear();
            hBox.getChildren().add(next2);
            endMessage.setText("To move around, you can use the keys Z, Q, S, and D. To open the inventory, click on I and use it with the left mouse click.");
            hBox.setAlignment(Pos.CENTER);
        });

        next2.setOnAction(event -> {
            hBox.getChildren().clear();
            hBox.getChildren().add(exit);
            endMessage.setText("Be careful, if you lose all your health points or if you don't finish within the allotted time, then the game will be lost. Good luck!");
            hBox.setAlignment(Pos.CENTER);
        });

        exit.setOnAction(event -> {
            dialog.close();
            isOpen = false;
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

    private static Label createStyledLabel(String text) {
        Label label = new Label(text);
        label.setStyle("-fx-text-fill: white; -fx-font-size: 14px; -fx-padding: 0 10px 10px 10px;");
        label.setWrapText(true);
        return label;
    }
}