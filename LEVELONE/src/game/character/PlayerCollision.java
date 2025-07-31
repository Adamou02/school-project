package game.character;

import game.item.Items;
import game.item.Potion;
import game.item.Weapon;
import game.map.Map;
import game.pnj.Monster;
import game.popUp.ActionChoice;
import game.popUp.ActionDialogPnj;
import game.popUp.ActionEndGame;
import game.popUp.ActionOnDoor;
import game.popUp.ActionOnMerchant;
import game.popUp.ActionOnMerchant2;
import game.textures.Constants;
import javafx.geometry.BoundingBox;
import javafx.geometry.Bounds;
import javafx.scene.Node;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;

/**
 * Cette classe contient les méthodes pour tester les collisions entre le joueur et les différents éléments du jeu.
 */
public class PlayerCollision {

    /**
     * Teste la collision entre le joueur et les éléments d'une grille donnée.
     *
     * @param player   Le joueur.
     * @param gridpane La grille contenant les éléments.
     * @param diffX    La différence en X à appliquer au joueur.
     * @param diffY    La différence en Y à appliquer au joueur.
     * @param map      La carte du jeu.
     * @return {@code true} s'il y a une collision, {@code false} sinon.
     */
    public static boolean testCollision(Player player, GridPane gridpane, double diffX, double diffY, Map map) {

        for (Node obstacle : gridpane.getChildren()) {

            // Vérifier si l'élément est un obstacle
            if (obstacle instanceof ImageView) {

                // Création des bounds de l'obstacle et du joueur pour vérifier les collisions
                Bounds obstacleBounds = obstacle.getBoundsInParent();

                player.getSprite().setLayoutX(player.getSprite().getLayoutX() + diffX);
                player.getSprite().setLayoutY(player.getSprite().getLayoutY() + diffY);

                //Test si le joueur es ta la limite de la stage
                if (map.getPlayer().OutOfArea()) {
                    player.getSprite().setLayoutX(player.getSprite().getLayoutX() - diffX);
                    player.getSprite().setLayoutY(player.getSprite().getLayoutY() - diffY);
                    return true;
                }

                Bounds playerBounds = player.getSprite().getBoundsInParent();

                player.getSprite().setLayoutX(player.getSprite().getLayoutX() - diffX);
                player.getSprite().setLayoutY(player.getSprite().getLayoutY() - diffY);

                // S'il y a collision
                if (obstacleBounds.intersects(playerBounds)) {

                    // Récupération de l'URL de l'image de l'obstacle
                    Image obstacleImage = ((ImageView) obstacle).getImage();
                    String obstacleImagePath = obstacleImage.getUrl();

                    //Test si collision avec des monstres
                    if (obstacleImagePath.substring(16).contains("pigKing")) {
                        if (player.canBeHurt()) {
                            Monster pigKing = (Monster) obstacle.getUserData();
                            player.setHealth(player.getHealth() - pigKing.getStrength(), map);
                            player.takingDamage();
                        }
                        return false;
                    }

                    if (obstacleImagePath.substring(16).contains("pigMob")) {
                        if (player.canBeHurt()) {
                            Monster pigMob = (Monster) obstacle.getUserData();
                            player.setHealth(player.getHealth() - pigMob.getStrength(), map);
                            player.takingDamage();
                        }
                        return false;
                    }

                    // Switch selon le nom de l'image (via l'URL), et lance un pop up de demande de prise de decision
                    switch (obstacleImagePath.substring(16)) {
                        case "diamond.png":
                            Items D = new Items("diamond", "beautiful diamond wit a lot of utilities ;)", "Use With Merchant");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, D, Constants.diamond.getImageView());
                            break;
                        case "potionBlue.png":
                            Potion B = new Potion("potionBlue", "Your weapon w'll have 1 more damage", "Drink");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, B, Constants.potionBlue.getImageView());
                            break;
                        case "potionRed.png":
                        	Potion R = new Potion("potionRed", "Give you 1 more life to destroy enemy", "Drink");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, R, Constants.potionRed.getImageView());
                            break;
                        case "potionGreen.png":
                        	Potion G = new Potion("potionGreen", "Add 50s More to finish the game!", "Drink");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, G, Constants.potionGreen.getImageView());
                            break;
                        case "potionPurple.png":
                        	Potion P = new Potion("potionPurple", "Temporarily immobilizes monsters for 20 seconds", "Drink");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, P, Constants.potionPurple.getImageView());
                            break;
                        case "potionYellow.png":
                        	Potion Y = new Potion("potionYellow", "Invincibility for 15 seconds", "Drink");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, Y, Constants.potionYellow.getImageView());
                            break;
                        case "potionGray.png":
                        	Potion Gr = new Potion("potionGray", "special ability, hmm...", "Drink");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, Gr, Constants.potionGray.getImageView());
                            break;
                        case "key.png":
                            Items K = new Items("key", "Permet d'ouvrir une porte", "Use next to a door");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, K, Constants.key.getImageView());
                            break;
                        case "door1.png":
                            ActionOnDoor.displayActionDoorChoice(obstacle, player, gridpane, map);
                            break;
                        case "door3.png":
                            ActionOnDoor.displayActionDoorChoice(obstacle, player, gridpane, map);
                            break;
                        case "door2.png":
                            ActionOnDoor.displayActionDoorChoice(obstacle, player, gridpane, map);
                            break;
                        case "door4.png":
                            ActionOnDoor.displayActionDoorChoice(obstacle, player, gridpane, map);
                            break;
                        case "flag.png":
                            player.stopAnimation();
                            ActionEndGame.displayEndGame(true);
                            break;
                        case "trap.png":
                            player.stopAnimation();
                            if (!player.isAttackAnimation()) {
                                player.setHealth(0, map);
                            }
                            break;
                        case "merchant.png":
                            ActionOnMerchant.displayActionMerchant(obstacle, player, gridpane, map);
                            break;
                        case "merchant2.png":
                            ActionOnMerchant2.displayActionMerchant(obstacle, player, gridpane, map);
                            break;
                        case "dialogPnj.png":
                            ActionDialogPnj.displayActionMerchant(obstacle, player, gridpane, map);
                            break;
                        case "hammer.png":
                            Weapon H = new Weapon("hammer", 1, "Able to hit", "equip weapon");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, H, Constants.hammer.getImageView());
                            break;
                        case "hammerBoosted.png":
                            Weapon HB = new Weapon("hammerBoosted", 2, "Able to hit more", "equip weapon");
                            ActionChoice.displayActionChoice(obstacle, player, gridpane, HB, Constants.hammerBoosted.getImageView());
                            break;
                        default:

                            break;
                    }

                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Vérifie s'il y a une collision entre le joueur et un monstre lors d'une attaque.
     * 
     * @param player    le joueur
     * @param gridpane  le conteneur de monstres
     * @return le monstre avec lequel le joueur est en collision, ou null s'il n'y a pas de collision
     */
    public static Monster attackCollision(Player player, GridPane gridpane) {

        for (Node enemy : gridpane.getChildren()) {

            //Vérifier si le joueur est en collision avec l'obstacle
            if (enemy instanceof ImageView) {
                //creation des bounds de l'obstacle et du player our verif les collisions
                Bounds obstacleBounds = enemy.getBoundsInParent();
                Bounds playerBounds = player.getSprite().getBoundsInParent();

                // on prend la zone de collision du personnage à laquelle on ajoute artificiellement 10px de chaque côté
                double x = playerBounds.getMinX() - 32;
                double y = playerBounds.getMinY() - 32;
                double width = playerBounds.getWidth() + 96;
                double height = playerBounds.getHeight() + 96;
                Bounds areaBounds = new BoundingBox(x, y, width, height);

                if (obstacleBounds.intersects(areaBounds)) {
                    if (enemy.getUserData().getClass().toString().equals("class game.pnj.Monster")) {
                        Monster monster = (Monster) enemy.getUserData();
                        return monster;
                    }
                }
            }
        }
        return null;
    }

    /**
     * Checks if the player can break a wall.
     * If the player is in collision with a wall obstacle and has a "hammerBoosted" weapon equipped,
     * the wall is removed from the gridpane.
     *
     * @param player    The player object.
     * @param gridpane  The gridpane containing the game elements.
     */
    public static void TestWallBreak(Player player, GridPane gridpane) {

        for (Node wall : gridpane.getChildren()) {

            // Check if the player is in collision with the obstacle
            if (wall instanceof ImageView) {
                // Create bounds for the obstacle and the player to check collisions
                Bounds obstacleBounds = wall.getBoundsInParent();
                Bounds playerBounds = player.getSprite().getBoundsInParent();

                // Create a collision area for the player, with an additional 10px on each side
                double x = playerBounds.getMinX() - 16;
                double y = playerBounds.getMinY() - 16;
                double width = playerBounds.getWidth() + 48;
                double height = playerBounds.getHeight() + 48;
                Bounds areaBounds = new BoundingBox(x, y, width, height);

                //Test sir attaque un mur cassable
                if (obstacleBounds.intersects(areaBounds)) {
                    Image obstacleImage = ((ImageView) wall).getImage();
                    String obstacleImagePath = obstacleImage.getUrl();
                    if (obstacleImagePath.contains("Break") && player.getWeapon().getName().equals("hammerBoosted")) {
                        gridpane.getChildren().remove(wall);
                        return;
                    }

                }
            }
        }
    }

	
	
}