package game.popUp;

import game.character.Player;
import game.item.AbstractItem;
import game.item.Items;
import game.map.Map;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

/**
 * Affiche l'interaction avec le marchand2.
 */
public class ActionOnMerchant2 {
    private static boolean isOpen = false;

    /**
     * Affiche l'interaction avec le marchand.
     *
     * @param node    Le nœud parent de la fenêtre.
     * @param player  Le joueur.
     * @param gridpane La grille du jeu.
     * @param map     La carte du jeu.
     */
    public static void displayActionMerchant(Node node, Player player, GridPane gridpane, Map map) {

        int nbrDiamond = 0;
        player.stopAnimation();

        for (AbstractItem item : player.getInventory().getItem()) {
            if (item != null && item.getName().equals("diamond")) {
                nbrDiamond++;
            }
        }

        if (nbrDiamond >= 5) {
            // Interaction lorsque le joueur a suffisamment de diamants

            Button takeButton2 = new Button("Trade 5 diamonds for a special potion ?");
            takeButton2.setStyle("-fx-background-color: rgb(56,52,68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");

            Button goBack = new Button("Go back");
            goBack.setStyle("-fx-background-color: rgb(56,52,68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");

            BorderPane borderPane = new BorderPane();
            borderPane.setStyle("-fx-padding: 5px; -fx-background-color: rgb(56,52,68);");

            VBox vBox = new VBox(10);
            vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56,52,50);");
            vBox.setAlignment(Pos.CENTER);

            Label itm_name = new Label("It's time to get out ! ");
            itm_name.setStyle("-fx-text-fill: white; -fx-margin-bottom: 10px;");

            HBox hBox = new HBox(10, takeButton2);
            hBox.setAlignment(Pos.CENTER);

            HBox hBox2 = new HBox(10, goBack);
            hBox2.setAlignment(Pos.CENTER);

            ImageView trade = new ImageView(new Image("file:res/images/tradeDiamondPotionGray.png"));
            trade.setFitHeight(50);
            trade.setFitWidth(100);

            vBox.getChildren().addAll(itm_name, trade, hBox, hBox2);

            borderPane.setCenter(vBox);

            Scene dialogScene = new Scene(borderPane, 300, 200);

            Stage dialog = new Stage();
            dialog.setScene(dialogScene);
            dialog.setTitle("Merchant Interaction");

            dialog.setOnCloseRequest(event -> {
                // Ferme la Stage dialog quand on clique sur la croix rouge
                isOpen = false;
                dialog.close();
            });

            takeButton2.setOnAction(event -> {
                // Échange des diamants contre une potion spéciale
                for (int i = 0; i < 5; i++) {
                    player.getInventory().removeDiam(player, map);
                }
                Items Gr = new Items("potionGray", "special ability, hmm...", "Drink");
                player.getInventory().push(Gr);
                isOpen = false;
                dialog.close();
            });

            goBack.setOnAction(event -> {
                // Ferme la Stage dialog quand on clique sur le bouton "Go back"
                isOpen = false;
                dialog.close();
            });

            if (isOpen == false) {
                dialog.initModality(Modality.APPLICATION_MODAL);
                dialog.initStyle(StageStyle.UNDECORATED);
                Platform.runLater(() -> dialog.showAndWait());
                isOpen = true;
            }

        } else {
            // Interaction lorsque le joueur n'a pas suffisamment de diamants

            Button takeButton2 = new Button("Go back to Fight");
            takeButton2.setStyle("-fx-background-color: rgb(56,52,68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");

            BorderPane borderPane = new BorderPane();
            borderPane.setStyle("-fx-padding: 5px; -fx-background-color: rgb(56,52,68);");

            VBox vBox = new VBox(10);
            vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56,52,50);");
            vBox.setAlignment(Pos.CENTER);

            Label itm_name = new Label("Hmmm.. Sorry... You don't have enough item, more money ?!");
            itm_name.setStyle("-fx-text-fill: white; -fx-margin-bottom: 10px;");

            HBox hBox = new HBox(10, takeButton2);
            hBox.setAlignment(Pos.CENTER);

            vBox.getChildren().addAll(itm_name, hBox);

            borderPane.setCenter(vBox);

            Scene dialogScene = new Scene(borderPane, 300, 200);

            Stage dialog = new Stage();
            dialog.setScene(dialogScene);
            dialog.setTitle("Tips : You a to fight... AGAIN !");

            dialog.setOnCloseRequest(event -> {
                // Ferme la Stage dialog quand on clique sur la croix rouge
                isOpen = false;
                dialog.close();
            });

            takeButton2.setOnAction(event -> {
                isOpen = false;
                dialog.close();
            });

            if (isOpen == false) {
                dialog.initModality(Modality.APPLICATION_MODAL);
                dialog.initStyle(StageStyle.UNDECORATED);
                Platform.runLater(() -> dialog.showAndWait());
                isOpen = true;
            }
        }
    }
}