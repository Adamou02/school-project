package game.popUp;

import game.character.Player;
import game.item.AbstractItem;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import game.utils.Minuteur;

/**
 * La classe ActionChoice affiche une boîte de dialogue pour permettre au joueur de choisir
 * s'il souhaite prendre ou ne pas prendre un objet.
 */
public class ActionChoice {

    private static boolean isOpen = false;

    /**
     * Affiche la boîte de dialogue pour le choix d'action.
     *
     * @param node       Le nœud associé à la boîte de dialogue.
     * @param player     Le joueur qui interagit avec la boîte de dialogue.
     * @param gridpane   Le GridPane contenant les éléments du jeu.
     * @param items      L'objet à prendre ou ne pas prendre.
     * @param imageView  L'ImageView de l'objet à afficher dans la boîte de dialogue.
     */
    public static void displayActionChoice(Node node, Player player, GridPane gridpane,AbstractItem items, ImageView imageView) {

        player.stopAnimation();
        Minuteur.pause();
        Button takeButton = createStyledButton("Take");
        Button dontTakeButton = createStyledButton("Don't Take");

        BorderPane borderPane = new BorderPane();
        borderPane.setStyle("-fx-padding: 5px; -fx-background-color: rgb(56, 52, 68);");

        VBox vBox = new VBox(10);
        vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56, 52, 50);");
        vBox.setAlignment(Pos.CENTER);

        Label itemName = new Label(items.getName());
        itemName.setStyle("-fx-text-fill: white; -fx-margin-bottom: 10px;");

        HBox hBox = new HBox(10, takeButton, dontTakeButton);
        hBox.setAlignment(Pos.CENTER);

        Text itemDescription = new Text(items.getDescription());
        itemDescription.setFill(Color.WHITE);
        StackPane descBox = new StackPane(itemDescription);

        vBox.getChildren().addAll(
                itemName,
                imageView,
                descBox,
                hBox
        );

        borderPane.setCenter(vBox);

        Scene dialogScene = new Scene(borderPane, 300, 200);

        Stage dialog = new Stage();
        dialog.setScene(dialogScene);
        dialog.setTitle("Pick Up Items Decision");

        dialog.setOnCloseRequest(event -> {
            isOpen = false;
            dialog.close();
        });

        takeButton.setOnAction(event -> {
            gridpane.getChildren().remove(node);
            player.getInventory().push(items);
            isOpen = false;
            Minuteur.resume();
            dialog.close();
        });

        dontTakeButton.setOnAction(event -> {
            isOpen = false;
            Minuteur.resume();
            dialog.close();
        });

        if (!isOpen) {
            dialog.initModality(Modality.APPLICATION_MODAL);
            dialog.initStyle(StageStyle.UNDECORATED);
            Platform.runLater(() -> dialog.showAndWait());
            isOpen = true;
        }
    }

    /**
     * Crée un bouton stylisé avec le texte spécifié.
     *
     * @param text  Le texte à afficher sur le bouton.
     * @return      Le bouton stylisé.
     */
    private static Button createStyledButton(String text) {
        Button button = new Button(text);
        button.setStyle("-fx-background-color: rgb(56, 52, 68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");
        return button;
    }
}