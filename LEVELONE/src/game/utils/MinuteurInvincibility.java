package game.utils;

import game.character.Player;
import game.map.Map;
import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.text.Font;
import javafx.util.Duration;

/**
 * La classe MinuteurInvincibility représente un minuteur pour l'invincibilité du joueur.
 * Il affiche un compte à rebours et rend le joueur invincible pendant cette période.
 */
public class MinuteurInvincibility extends GridPane{
	private static Timeline timeline;
    private static Label timeLabel;
    
    /**
     * Construit un objet MinuteurInvincibility.
     *
     * @param map La carte associée au minuteur.
     */
    public MinuteurInvincibility(Map map) {
    	Player player = map.getPlayer();
        // Créer un label pour afficher le temps
        timeLabel = new Label();
        timeLabel.setFont(new Font("Arial", 24));
        timeLabel.setTextFill(Paint.valueOf("#FFF")); // définit la couleur du texte en rouge
        timeLabel.setTextFill(Color.web("#FFFF00"));
        timeLabel.setAlignment(Pos.CENTER);
        timeLabel.setPrefSize(64,32);

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
            	player.setCanBeHurt(false);
                int remainingTime = Integer.parseInt(timeLabel.getText()) - 1;
                timeLabel.setText(Integer.toString(remainingTime));
                if (remainingTime <= 0) {
                	player.setCanBeHurt(true);
                	player.getSprite().setEffect(null);
                	timeline.stop(); // Arrêter la timeline lorsque le temps est écoulé
                	getChildren().remove(timeLabel); 
                }
            }
        }));
    }
    
    /**
     * Démarre le minuteur d'invincibilité avec la durée spécifiée en secondes.
     *
     * @param durationInSeconds La durée de l'invincibilité en secondes.
     */
    public void start(int durationInSeconds) {
        timeLabel.setText(Integer.toString(durationInSeconds));
        timeline.playFromStart();
    }
}
