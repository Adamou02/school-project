package game.utils;

import game.map.Map;
import game.pnj.Monster;
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
 * La classe MinuteurMonsterStop représente un minuteur pour arrêter temporairement les monstres du jeu.
 * Il affiche un compte à rebours et arrête les monstres pendant cette période.
 */
public class MinuteurMonsterStop extends GridPane {
	private static Timeline timeline;
    private static Label timeLabel;
    
    /**
     * Construit un objet MinuteurMonsterStop.
     *
     * @param map La carte associée au minuteur.
     */
    public MinuteurMonsterStop(Map map) {
        // Créer un label pour afficher le temps
        timeLabel = new Label();
        timeLabel.setFont(new Font("Arial", 24));
        timeLabel.setTextFill(Paint.valueOf("#FFF")); // définit la couleur du texte en rouge
        timeLabel.setTextFill(Color.web("#FF00FF"));
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
                int remainingTime = Integer.parseInt(timeLabel.getText()) - 1;
                map.stopMonster();
                timeLabel.setText(Integer.toString(remainingTime));

                // Arrêter le minuteur si le temps est écoulé
                if (remainingTime <= 0) {
                	for(Monster monster : map.getTableauDeMonstres()) {
                		monster.getImageView().setEffect(null);
            		}
                	map.playMonster();
                	timeline.stop(); // Arrêter la timeline lorsque le temps est écoulé
                    getChildren().remove(timeLabel); 
                }
            }
        }));
    }
    
    /**
     * Démarre le minuteur d'arrêt des monstres avec la durée spécifiée en secondes.
     *
     * @param durationInSeconds La durée d'arrêt des monstres en secondes.
     */
    public void start(int durationInSeconds) {
        timeLabel.setText(Integer.toString(durationInSeconds));
        timeline.playFromStart();
    }
}
