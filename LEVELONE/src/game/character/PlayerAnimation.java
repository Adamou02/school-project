package game.character;

import game.map.Map;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.scene.image.Image;
import javafx.util.Duration;

/**
 * Classe utilitaire pour gérer les animations du joueur.
 */
public class PlayerAnimation {
	
	/**
	 * Anime le déplacement du personnage du joueur.
	 *
	 * @param player    Le joueur.
	 * @param direction La direction du déplacement ("RIGHT", "LEFT", "UP" ou "DOWN").
	 * @param map       La carte du jeu.
	 * @return L'objet Timeline représentant l'animation.
	 */
	public static Timeline animateCharacterMovement(Player player, String direction, Map map) {
	    
		// Chargement des images d'animation pour le déplacement du personnage
		Image[] moveAnimation = new Image[8];
	    for (int i = 0; i < moveAnimation.length; i++) {
	    	moveAnimation[i] = new Image("file:res/images/move" + direction + i + ".png");
	    }

		if (direction.equals("RIGHT")) {
			final Timeline animationTimeline = new Timeline();
			animationTimeline.getKeyFrames().add(new KeyFrame(Duration.millis(50), event -> {
				boolean collision = false;

				// Vérification des collisions avec les obstacles
				if (!player.isInvisible() && PlayerCollision.testCollision(map.getPlayer(), map.getGridpaneObstacle(), 5, 0, map)) {
					collision = true;
				}

				// Vérification des collisions avec les éléments interactifs
				if (PlayerCollision.testCollision(map.getPlayer(), map.getGridpaneInteract(), 5, 0, map)) {
					collision = true;
					player.stopAnimation();
				}

				// Vérification des collisions avec les PNJ
				if (PlayerCollision.testCollision(map.getPlayer(), map.getGridpanePnj(), 5, 0, map)) {
					collision = true;
				}

				//Si pas de collision, lance le deplacement
				if (!collision) {
					int etape = (int) ((System.currentTimeMillis() / 100) % 8);
					double x = map.getPlayer().getSprite().getLayoutX() + map.getPlayer().getSpeed();
					map.getPlayer().getSprite().setImage(moveAnimation[etape]);
					map.getPlayer().getSprite().setLayoutX(x);
					map.getPlayer().setX(x);
				}
			}));

			animationTimeline.setCycleCount(Timeline.INDEFINITE);
			return animationTimeline;

		}
		if (direction.equals("LEFT")) {
			final Timeline animationTimeline = new Timeline();
			animationTimeline.getKeyFrames().add(new KeyFrame(Duration.millis(50), event -> {
				boolean collision = false;

				// Vérification des collisions avec les obstacles
				if (!player.isInvisible() && PlayerCollision.testCollision(map.getPlayer(), map.getGridpaneObstacle(), -5, 0, map)) {
					collision = true;
				}

				// Vérification des collisions avec les éléments interactifs
				if (PlayerCollision.testCollision(map.getPlayer(), map.getGridpaneInteract(), -5, 0, map)) {
					collision = true;
					player.stopAnimation();
				}

				// Vérification des collisions avec les PNJ
				if (PlayerCollision.testCollision(map.getPlayer(), map.getGridpanePnj(), -5, 0, map)) {
					collision = true;
				}

				//Si pas de collision, lance le deplacement
				if (!collision) {
					int etape = (int) ((System.currentTimeMillis() / 100) % 8);
					double x = map.getPlayer().getSprite().getLayoutX() - map.getPlayer().getSpeed();
					map.getPlayer().getSprite().setImage(moveAnimation[etape]);
					map.getPlayer().getSprite().setLayoutX(x);
					map.getPlayer().setX(x);
				}
			}));

			animationTimeline.setCycleCount(Timeline.INDEFINITE);
			return animationTimeline;
		}
		if (direction.equals("UP")) {
			final Timeline animationTimeline = new Timeline();
			animationTimeline.getKeyFrames().add(new KeyFrame(Duration.millis(50), event -> {
				boolean collision = false;

				// Vérification des collisions avec les obstacles
				if (!player.isInvisible() && PlayerCollision.testCollision(map.getPlayer(), map.getGridpaneObstacle(), 0, -5, map)) {
					collision = true;
				}

				// Vérification des collisions avec les éléments interactifs
				if (PlayerCollision.testCollision(map.getPlayer(), map.getGridpaneInteract(), 0, -5, map)) {
					collision = true;
					player.stopAnimation();
				}

				// Vérification des collisions avec les PNJ
				if (PlayerCollision.testCollision(map.getPlayer(), map.getGridpanePnj(), 0, -5, map)) {
					collision = true;
				}

				//Si pas de collision, lance le deplacement
				if (!collision) {
					int etape = (int) ((System.currentTimeMillis() / 100) % 8);
					double y = map.getPlayer().getSprite().getLayoutY() - map.getPlayer().getSpeed();
					map.getPlayer().getSprite().setImage(moveAnimation[etape]);
					map.getPlayer().getSprite().setLayoutY(y);
					map.getPlayer().setX(y);
				}
			}));

			animationTimeline.setCycleCount(Timeline.INDEFINITE);
			return animationTimeline;
		}
		if (direction.equals("DOWN")) {
			final Timeline animationTimeline = new Timeline();
			animationTimeline.getKeyFrames().add(new KeyFrame(Duration.millis(50), event -> {
				boolean collision = false;

				// Vérification des collisions avec les obstacles
				if (!player.isInvisible() && PlayerCollision.testCollision(map.getPlayer(), map.getGridpaneObstacle(), 0, 5, map)) {
					collision = true;
				}

				// Vérification des collisions avec les éléments interactifs
				if (PlayerCollision.testCollision(map.getPlayer(), map.getGridpaneInteract(), 0, 5, map)) {
					collision = true;
					player.stopAnimation();
				}

				// Vérification des collisions avec les PNJ
				if (PlayerCollision.testCollision(map.getPlayer(), map.getGridpanePnj(), 0, 5, map)) {
					collision = true;
				}

				//Si pas de collision, lance le deplacement
				if (!collision) {
					int etape = (int) ((System.currentTimeMillis() / 100) % 8);
					double y = map.getPlayer().getSprite().getLayoutY() + map.getPlayer().getSpeed();
					map.getPlayer().getSprite().setImage(moveAnimation[etape]);
					map.getPlayer().getSprite().setLayoutY(y);
					map.getPlayer().setX(y);
				}
			}));

			animationTimeline.setCycleCount(Timeline.INDEFINITE);
			return animationTimeline;
		}

		return null;
	}

	/**
	 * Anime l'attaque du personnage du joueur.
	 *
	 * @param player    Le joueur.
	 * @param direction La direction de l'attaque ("RIGHT", "LEFT", "UP" ou "DOWN").
	 * @param map       La carte du jeu.
	 * @return L'objet Timeline représentant l'animation.
	 */
	public static Timeline animateCharacterAttack(Player player, String direction, Map map) {
	    
		// Chargement des images d'animation pour l'attaque du personnage
		Image[] attackAnimation = new Image[6];
	    for (int i = 0; i < attackAnimation.length; i++) {
	    	attackAnimation[i] = new Image("file:res/images/attack" + direction + i + ".png");
	    }
	    
	    //Animation de l'attaque du joueurs
		final Timeline animationTimeline = new Timeline();
		animationTimeline.getKeyFrames().add(new KeyFrame(Duration.millis(50), event -> {
			player.setAttackAnimation(true);
    		int etape = (int) ((System.currentTimeMillis() / 100) % 6);
    		map.getPlayer().getSprite().setScaleX(2.5);
    		map.getPlayer().getSprite().setScaleY(2.5);
		    map.getPlayer().getSprite().setImage(attackAnimation[etape]);
	   	}));
		
		//Fin de l'animation d'attaque
		animationTimeline.setOnFinished(event -> {
			map.getPlayer().getSprite().setScaleX(1);
			map.getPlayer().getSprite().setScaleY(1);
			map.getPlayer().getSprite().setImage(new Image("file:res/images/move" + direction + "0.png"));
			player.setAttackAnimation(false);
		});
		
		animationTimeline.setCycleCount(6);
	    return animationTimeline;
	}
}
