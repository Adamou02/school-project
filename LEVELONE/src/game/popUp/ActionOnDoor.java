package game.popUp;

import java.util.ArrayList;
import java.util.List;

import game.character.Player;
import game.item.AbstractItem;
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
 * La classe ActionOnDoor affiche une fenêtre contextuelle lorsqu'un joueur interagit avec une porte,
 * permettant de choisir une action à effectuer.
 */
public class ActionOnDoor {
    private static boolean isOpen = false;

    /**
     * Affiche la fenêtre contextuelle pour choisir une action à effectuer sur une porte.
     * 
     * @param node    Le nœud sur lequel le joueur a cliqué pour interagir avec la porte.
     * @param player  Le joueur.
     * @param gridpane La grille où se trouve la porte.
     * @param map     La carte du jeu.
     */
    public static void displayActionDoorChoice(Node node, Player player, GridPane gridpane, Map map) {
        player.stopAnimation();

        for (AbstractItem item : player.getInventory().getItem()) {
            if (item != null && item.getName().equals("key")) {
                Button useKeyButton = createStyledButton("Use your Key!");

                Button goBack = createStyledButton("Go back");

                BorderPane borderPane = new BorderPane();
                borderPane.setStyle("-fx-padding: 10px; -fx-background-color: rgb(56, 52, 68);");

                VBox vBox = new VBox(10);
                vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56, 52, 50);");
                vBox.setAlignment(Pos.CENTER);

                Label itm_name = new Label(item.getName());
                itm_name.setStyle("-fx-text-fill: white; -fx-margin-bottom: 10px;");

                HBox hBox = new HBox(10, useKeyButton);
                hBox.setAlignment(Pos.CENTER);

                HBox hBox2 = new HBox(10, goBack);
                hBox2.setAlignment(Pos.CENTER);

                vBox.getChildren().addAll(
                        itm_name,
                        item.getImageView(),
                        hBox,
                        hBox2
                );

                borderPane.setCenter(vBox);

                Scene dialogScene = new Scene(borderPane, 300, 200);

                Stage dialog = new Stage();
                dialog.initStyle(StageStyle.UNDECORATED);
                dialog.setScene(dialogScene);
                dialog.setTitle("Pick Up Items Decision");

                dialog.setOnCloseRequest(event -> {
                    isOpen = false;
                    dialog.close();
                });

                goBack.setOnAction(event -> {
                    isOpen = false;
                    dialog.close();
                });

                useKeyButton.setOnAction(event -> {
                    List<Node> nodesToRemove = new ArrayList<>();

                    for (Node nodet : gridpane.getChildren()) {
                        if (nodet instanceof ImageView) {
                            Image obstacleImage = ((ImageView) nodet).getImage();
                            String obstacleImagePath = obstacleImage.getUrl();
                            if (obstacleImagePath.contains("door")) {
                                nodesToRemove.add(nodet);
                            }
                        }
                    }

                    for (Node nodeToRemove : nodesToRemove) {
                        gridpane.getChildren().remove(nodeToRemove);
                    }
                    
                    player.getInventory().remove(item, player, map);

                    isOpen = false;
                    dialog.close();
                });

                if (!isOpen) {
                    dialog.initModality(Modality.APPLICATION_MODAL);
                    Platform.runLater(() -> dialog.showAndWait());
                    isOpen = true;
                }
                break;
            }
        }

        Button exitButton = createStyledButton("Exit");

        BorderPane borderPane = new BorderPane();
        borderPane.setStyle("-fx-padding: 10px; -fx-background-color: rgb(56, 52, 68);");

        VBox vBox = new VBox(10);
        vBox.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56, 52, 50);");
        vBox.setAlignment(Pos.CENTER);

        Label itm_name = new Label("Hmmm.. You need a special item!");
        itm_name.setStyle("-fx-text-fill: white; -fx-margin-bottom: 10px;");

        HBox hBox = new HBox(10, exitButton);
        hBox.setAlignment(Pos.CENTER);

        vBox.getChildren().addAll(
                itm_name,
                hBox
        );

        borderPane.setCenter(vBox);

        Scene dialogScene = new Scene(borderPane, 300, 200);

        Stage dialog = new Stage();
        dialog.initStyle(StageStyle.UNDECORATED);
        dialog.setScene(dialogScene);
        dialog.setTitle("Tips: You have to fight");

        dialog.setOnCloseRequest(event -> {
            isOpen = false;
            dialog.close();
        });

        exitButton.setOnAction(event -> {
            isOpen = false;
            dialog.close();
        });

        if (!isOpen) {
            dialog.initModality(Modality.APPLICATION_MODAL);
            Platform.runLater(() -> dialog.showAndWait());
            isOpen = true;
        }
    }

    /**
     * Crée un bouton avec un style personnalisé.
     * 
     * @param text Le texte affiché sur le bouton.
     * @return Le bouton avec le style personnalisé.
     */
    private static Button createStyledButton(String text) {
        Button button = new Button(text);
        button.setStyle("-fx-background-color: rgb(56, 52, 68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");
        return button;
    }
}