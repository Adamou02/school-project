package game.utils;

import game.character.Player;
import game.popUp.ActionEndGame;
import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Paint;
import javafx.scene.text.Font;
import javafx.util.Duration;

/**
 * La classe Minuteur représente un minuteur dans le jeu.
 * Il affiche un compte à rebours et exécute des actions lorsque le temps s'écoule.
 */
public class Minuteur extends GridPane {
    private static Timeline timeline;
    private static Label timeLabel;

    /**
     * Construit un objet Minuteur.
     *
     * @param player Le joueur associé au minuteur.
     */
    public Minuteur(Player player) {
        // Créer un label pour afficher le temps
        timeLabel = new Label();
        timeLabel.setFont(new Font("Arial", 24));
        timeLabel.setTextFill(Paint.valueOf("#FFF")); // définit la couleur du texte en rouge

        timeLabel.setAlignment(Pos.CENTER);
        timeLabel.setPrefSize(64, 32);

        // Ajouter le label à la GridPane
        this.add(timeLabel, 0, 0);

        // Configurer la GridPane
        this.setAlignment(Pos.CENTER);
        this.setPadding(new Insets(10));
        this.setHgap(10);

        // Créer la timeline pour le minuteur
        timeline = new Timeline();
        timeline.setCycleCount(Animation.INDEFINITE);

        // Ajouter une KeyFrame toutes les secondes
        timeline.getKeyFrames().add(new KeyFrame(Duration.seconds(1), new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                // Mettre à jour le label avec le temps restant
                int remainingTime = Integer.parseInt(timeLabel.getText()) - 1;
                timeLabel.setText(Integer.toString(remainingTime));

                // Arrêter le minuteur si le temps est écoulé
                if (remainingTime <= 0) {
                    timeline.stop();
                    timeLabel.setText("Temps écoulé !");
                    player.getAnimationDown().stop();
                    player.getAnimationLeft().stop();
                    player.getAnimationRight().stop();
                    player.getAnimationUp().stop();
                    ActionEndGame.displayEndGame(false);
                }
            }
        }));
    }

    /**
     * Met en pause le minuteur.
     */
    public static void pause() {
        timeline.pause();
    }

    /**
     * Reprend l'exécution du minuteur après une pause.
     */
    public static void resume() {
        timeline.play();
    }

    /**
     * Ajoute du temps au minuteur.
     *
     * @param time Le temps à ajouter en secondes.
     */
    public static void addTime(int time) {
        int currentTime = Integer.parseInt(timeLabel.getText());
        int newTime = currentTime + time;
        timeLabel.setText(Integer.toString(newTime));
    }

    /**
     * Démarre le minuteur avec la durée spécifiée en secondes.
     *
     * @param durationInSeconds La durée du minuteur en secondes.
     */
    public void start(int durationInSeconds) {
        // Définir la durée du minuteur en secondes
        timeLabel.setText(Integer.toString(durationInSeconds));

        // Démarrer la timeline
        timeline.playFromStart();
    }
}
