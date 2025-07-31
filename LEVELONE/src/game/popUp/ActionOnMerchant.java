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
 * The ActionOnMerchant class represents a popup window for interacting with a merchant in the game.
 * It allows the player to trade items and receive rewards.
 */
public class ActionOnMerchant {
    private static boolean isOpen = false;

    /**
     * Displays the merchant interaction window.
     *
     * @param node   The JavaFX node associated with the popup window.
     * @param player The player object.
     * @param gridpane The gridpane object representing the game map.
     * @param map    The map object representing the game map.
     */
    public static void displayActionMerchant(Node node, Player player, GridPane gridpane, Map map) {
        int nbrDiamond = 0;
        player.stopAnimation();

        // Count the number of diamonds in the player's inventory
        for (AbstractItem item : player.getInventory().getItem()) {
            if (item != null && item.getName().equals("diamond")) {
                nbrDiamond++;
            }
        }

        if (nbrDiamond >= 1) {
            Button takeButton2 = createStyledButton("Trade 1 diamond for a gift? (red potion)");
            Button goBack = createStyledButton("Go back");

            BorderPane borderPane = new BorderPane();
            borderPane.setStyle("-fx-padding: 5px; -fx-background-color: rgb(56, 52, 68);");

            VBox vBox = new VBox(10);
            vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56, 52, 50);");
            vBox.setAlignment(Pos.CENTER);

            Label itmName = new Label("It's time to trade!");
            itmName.setStyle("-fx-text-fill: white; -fx-margin-bottom: 10px;");

            HBox hBox = new HBox(10, takeButton2);
            hBox.setAlignment(Pos.CENTER);

            HBox hBox2 = new HBox(10, goBack);
            hBox2.setAlignment(Pos.CENTER);

            ImageView trade = new ImageView(new Image("file:res/images/tradeDiamondPotionRed.png"));
            trade.setFitHeight(50);
            trade.setFitWidth(100);

            vBox.getChildren().addAll(
                    itmName,
                    trade,
                    hBox,
                    hBox2
            );

            borderPane.setCenter(vBox);

            Scene dialogScene = new Scene(borderPane, 300, 200);

            Stage dialog = new Stage();
            dialog.setScene(dialogScene);
            dialog.setTitle("Merchant Interaction");

            dialog.setOnCloseRequest(event -> {
                isOpen = false;
                dialog.close();
            });

            takeButton2.setOnAction(event -> {
                // Remove the diamond from the player's inventory
                player.getInventory().removeDiam(player, map);
                isOpen = false;
                dialog.close();

                // Create a red potion item and add it to the player's inventory
                Items redPotion = new Items("potionRed", "Give you 1 more life to destroy enemies", "Drink");
                player.getInventory().push(redPotion);
            });

            goBack.setOnAction(event -> {
                isOpen = false;
                dialog.close();
            });

            if (!isOpen) {
                dialog.initModality(Modality.APPLICATION_MODAL);
                dialog.initStyle(StageStyle.UNDECORATED);
                Platform.runLater(() -> dialog.showAndWait());
                isOpen = true;
            }
        } else {
            Button takeButton2 = createStyledButton("Go back to fight");

            BorderPane borderPane = new BorderPane();
            borderPane.setStyle("-fx-padding: 5px; -fx-background-color: rgb(56, 52, 68);");

            VBox vBox = new VBox(10);
            vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56, 52, 50);");
            vBox.setAlignment(Pos.CENTER);

            Label itmName = new Label("Hmmm... Sorry... You don't have enough items. Need more money?!");
            itmName.setStyle("-fx-text-fill: white; -fx-margin-bottom: 10px;");

            HBox hBox = new HBox(10, takeButton2);
            hBox.setAlignment(Pos.CENTER);

            vBox.getChildren().addAll(
                    itmName,
                    hBox
            );

            borderPane.setCenter(vBox);

            Scene dialogScene = new Scene(borderPane, 300, 200);

            Stage dialog = new Stage();
            dialog.setScene(dialogScene);
            dialog.setTitle("Tips: You have to fight... AGAIN!");

            dialog.setOnCloseRequest(event -> {
                isOpen = false;
                dialog.close();
            });

            takeButton2.setOnAction(event -> {
                isOpen = false;
                dialog.close();
            });

            if (!isOpen) {
                dialog.initModality(Modality.APPLICATION_MODAL);
                dialog.initStyle(StageStyle.UNDECORATED);
                Platform.runLater(() -> dialog.showAndWait());
                isOpen = true;
            }
        }
    }

    /**
     * Creates a styled button with the given text.
     *
     * @param text The text to be displayed on the button.
     * @return The styled button.
     */
    private static Button createStyledButton(String text) {
        Button button = new Button(text);
        button.setStyle("-fx-background-color: rgb(56, 52, 68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");
        return button;
    }
}