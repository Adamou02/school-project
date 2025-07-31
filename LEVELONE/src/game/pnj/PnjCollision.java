package game.pnj;

import game.character.Player;
import game.map.Map;
import javafx.geometry.Bounds;
import javafx.scene.Node;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;

/**
 * The PnjCollision class provides methods for testing collisions between monsters and players, as well as visibility checks.
 */
public class PnjCollision {
	
	/**
	 * Tests collision between a monster and the game obstacles or the player.
	 *
	 * @param monster   The monster involved in the collision.
	 * @param gridpane  The GridPane representing the game board.
	 * @param diffX     The X difference for the monster's position.
	 * @param diffY     The Y difference for the monster's position.
	 * @param map       The Map object containing the player and obstacles.
	 * @param direction The direction in which the collision is being tested.
	 * @return true if a collision is detected, false otherwise.
	 */
	public static boolean testCollision(Monster monster, GridPane gridpane, double diffX, double diffY, Map map, String direction) {		
		Player player = map.getPlayer();
		monster.getImageView().setLayoutX(monster.getImageView().getLayoutX() + diffX * 32);
		monster.getImageView().setLayoutY(monster.getImageView().getLayoutY() + diffY * 32);

		Bounds monsterBounds = monster.getImageView().getBoundsInParent();

		monster.getImageView().setLayoutX(monster.getImageView().getLayoutX() - diffX * 32);
		monster.getImageView().setLayoutY(monster.getImageView().getLayoutY() - diffY * 32);
		
		for (Node obstacle : gridpane.getChildren()) {
			if (obstacle instanceof ImageView) {
				// Create bounds for the obstacle and the player to check for collisions
				Bounds obstacleBounds = obstacle.getBoundsInParent();

				// Check for collision
				if (obstacleBounds.intersects(monsterBounds)) {
					// Get the image URL of the obstacle
					Image obstacleImage = ((ImageView) obstacle).getImage();
					String obstacleImagePath = obstacleImage.getUrl();
					
					// Switch based on the obstacle image name (using the URL)
					switch(obstacleImagePath.substring(16)) {
						case "diamond.png":   
							return false;
						case "épée.png":   
							return false;
						case "potionBlue.png":
							return false;
						case "potionRed.png":
							return false;
						case "key.png":
							return false;
						default:
							break;
					}
					return true;
				}
			}
		}
		
		Bounds playerBounds = player.getSprite().getBoundsInParent();
		
		if (playerBounds.intersects(monsterBounds)) {
			if (player.canBeHurt()) {
				monster.attack(player, map, direction);
				player.takingDamage();
			}		    	
			return true;
		}
		
		return false;
	}
	
	/**
	 * Tests if there is an obstacle obstructing the vision of the player.
	 *
	 * @param bound The bounds of the player's vision.
	 * @param map   The Map object containing the obstacles.
	 * @return true if an obstacle obstructs the vision, false otherwise.
	 */
	public static boolean testVision(Bounds bound, Map map) {	
		for (Node obstacle : map.getGridpaneObstacle().getChildren()) {
			if (obstacle instanceof ImageView) {
				// Check if the player is adjacent to a wall, in which case the vision is blocked
				Bounds obstacleBounds = obstacle.getBoundsInParent();
				if (obstacleBounds.intersects(bound)) {
					return true;
				}
			}
		}
		
		return false;
	}
}
