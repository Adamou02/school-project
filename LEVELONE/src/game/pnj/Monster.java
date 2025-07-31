package game.pnj;

import java.util.Random;

import game.character.Player;
import game.inventory.Inventory;
import game.item.AbstractItem;
import game.map.Map;
import game.textures.Texture;
import javafx.animation.PauseTransition;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.geometry.BoundingBox;
import javafx.geometry.Bounds;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.util.Duration;

/**
 * Classe représentant les monstres du jeu.
 */
public class Monster extends AbstractPnj {
    private int health;
    private int strength;
    private int speed;
    private boolean hasVision;
    private ImageView imageView;
    //private AbstractItem itemOnDeath;
    private Timeline randomM;
    private Inventory inventory;
    private int x;
    private int y;
    private int newX;
    private int newY;

    /**
     * Constructeur de la classe Monster.
     *
     * @param name      Le nom du monstre.
     * @param health    La santé du monstre.
     * @param strength  La force du monstre.
     * @param hasVision Indique si le monstre a une vision.
     * @param image     La texture/image représentant le monstre.
     * @param drop      L'objet à droper lorsque le monstre est vaincu.
     * @param map       La carte du jeu.
     * @param x         La position en X du monstre sur la carte.
     * @param y         La position en Y du monstre sur la carte.
     */
    public Monster(String name, int health, int strength, boolean hasVision, Texture image, AbstractItem drop, Map map, int x, int y) {
        super(name, image, true);
        this.health = health;
        this.strength = strength;
        this.hasVision = hasVision;
        this.speed = 30;
        this.imageView = image.getImageView();
        this.imageView.setFitHeight(30);
        this.imageView.setFitWidth(30);
        //this.itemOnDeath = drop;
        this.inventory = new Inventory();
        this.inventory.push(drop);
        this.imageView.setUserData(this);

        this.x = x;
        this.y = y;
        this.newX = x;
        this.newY = y;
        this.randomM = new Timeline();
        this.randomM.getKeyFrames().add(new KeyFrame(Duration.seconds(1), event -> {
            this.randomMove(map);
        }));
        this.randomM.setCycleCount(Timeline.INDEFINITE);
    }

    /**
     * Getter pour l'inventaire du monstre.
     *
     * @return L'inventaire du monstre.
     */
    public Inventory getInventory() {
        return inventory;
    }

    /**
     * Setter pour l'inventaire du monstre.
     *
     * @param inventory L'inventaire du monstre.
     */
    public void setInventory(Inventory inventory) {
        this.inventory = inventory;
    }

    /**
     * Getter pour la timeline de déplacement aléatoire du monstre.
     *
     * @return La timeline de déplacement aléatoire du monstre.
     */
    public Timeline getRandomM() {
        return randomM;
    }

    /**
     * Setter pour la timeline de déplacement aléatoire du monstre.
     *
     * @param randomM La timeline de déplacement aléatoire du monstre.
     */
    public void setRandomM(Timeline randomM) {
        this.randomM = randomM;
    }

    /**
     * Getter pour l'ImageView du monstre.
     *
     * @return L'ImageView du monstre.
     */
    public ImageView getImageView() {
        return imageView;
    }

    /**
     * Setter pour l'ImageView du monstre.
     *
     * @param imageView L'ImageView du monstre.
     */
    public void setImageView(ImageView imageView) {
        this.imageView = imageView;
    }

    /**
     * Getter pour la santé du monstre.
     *
     * @return La santé du monstre.
     */
    public int getHealth() {
        return health;
    }

    /**
     * Setter pour la santé du monstre.
     *
     * @param health La santé du monstre.
     */
    public void setHealth(int health) {
        this.health = health;
    }

    /**
     * Getter pour la force du monstre.
     *
     * @return La force du monstre.
     */
    public int getStrength() {
        return strength;
    }

    /**
     * Getter pour la vitesse du monstre.
     *
     * @return La vitesse du monstre.
     */
    public int getSpeed() {
        return speed;
    }

    /**
     * Setter pour la vitesse du monstre.
     *
     * @param speed La vitesse du monstre.
     */
    public void setSpeed(int speed) {
        this.speed = speed;
    }

    /**
     * Setter pour la force du monstre.
     *
     * @param strength La force du monstre.
     */
    public void setStrength(int strength) {
        this.strength = strength;
    }

    /**
     * Vérifie si le monstre a une vision.
     *
     * @return true si le monstre a une vision, false sinon.
     */
    public boolean hasVision() {
        return hasVision;
    }

    /**
     * Setter pour la vision du monstre.
     *
     * @param hasVision Indique si le monstre a une vision.
     */
    public void setHasVision(boolean hasVision) {
        this.hasVision = hasVision;
    }

    /**
     * Getter pour la position en X du monstre sur la carte.
     *
     * @return La position en X du monstre sur la carte.
     */
    public int getX() {
        return x;
    }

    /**
     * Setter pour la position en X du monstre sur la carte.
     *
     * @param x La position en X du monstre sur la carte.
     */
    public void setX(int x) {
        this.x = x;
    }

    /**
     * Getter pour la position en Y du monstre sur la carte.
     *
     * @return La position en Y du monstre sur la carte.
     */
    public int getY() {
        return y;
    }

    /**
     * Setter pour la position en Y du monstre sur la carte.
     *
     * @param y La position en Y du monstre sur la carte.
     */
    public void setY(int y) {
        this.y = y;
    }

    /**
     * Getter pour la nouvelle position en X du monstre sur la carte.
     *
     * @return La nouvelle position en X du monstre sur la carte.
     */
    public int getNewX() {
        return newX;
    }

    /**
     * Setter pour la nouvelle position en X du monstre sur la carte.
     *
     * @param newX La nouvelle position en X du monstre sur la carte.
     */
    public void setNewX(int newX) {
        this.newX = newX;
    }

    /**
     * Getter pour la nouvelle position en Y du monstre sur la carte.
     *
     * @return La nouvelle position en Y du monstre sur la carte.
     */
    public int getNewY() {
        return newY;
    }

    /**
     * Setter pour la nouvelle position en Y du monstre sur la carte.
     *
     * @param newY La nouvelle position en Y du monstre sur la carte.
     */
    public void setNewY(int newY) {
        this.newY = newY;
    }

    /**
     * Fait tomber l'objet du monstre sur la carte.
     *
     * @param map la carte du jeu
     */
    public void drop(Map map) {
        // Récupération des coordonnées x et y
        int x = (int)this.getNewX();
        int y = (int)this.getNewY();
        
        // Arrêt de la timeline de déplacement aléatoire du monstre
        this.randomM.stop();
        
        // Suppression de l'image du monstre du conteneur parent
        map.getGridpanePnj().getChildren().remove(this.getImageView());
        
        // Suppression du monstre du tableau de monstres de la carte
        map.getTableauDeMonstres().remove(this);
        
        // Boucle sur les objets de l'inventaire du monstre
        for(AbstractItem item : this.getInventory().getItem()) {
            if(item != null) {
                // Ajout de l'image de l'objet à l'emplacement (x, y) du conteneur d'interaction de la carte
                map.getGridpaneInteract().add(item.getImageView(), x, y);
            }
        }
    }
    
    /**
     * Anime le monstre lorsqu'il subit des dégâts.
     * Le monstre clignote pendant une courte période pour indiquer qu'il est touché.
     */
    public void takingDamage() {
        // Création d'une timeline pour animer le monstre lorsqu'il subit des dégâts
        Timeline timeline = new Timeline(new KeyFrame(Duration.millis(200), event -> {
            this.getImageView().setVisible(!this.getImageView().isVisible());
        }));
        timeline.setCycleCount(Timeline.INDEFINITE);
        
        // Désactivation de la possibilité de subir des dégâts pendant l'animation
        this.setCanBeHurt(false);
        
        // Création d'une pause de 1 seconde
        PauseTransition pause = new PauseTransition(Duration.seconds(1));
        pause.setOnFinished(event -> {
            // Arrêt de l'animation et réapparition du monstre
            timeline.stop();
            this.getImageView().setVisible(true);
            
            // Réactivation de la possibilité de subir des dégâts
            this.setCanBeHurt(true);
        });
        
        // Lancement de l'animation et de la pause
        timeline.play();
        pause.play();
    }

    /**
     * Déplace le monstre dans une direction spécifiée.
     * 
     * @param direction la direction du déplacement (UP, DOWN, LEFT, RIGHT)
     * @param map la carte du jeu
     * @return true si le déplacement a été effectué, sinon false
     */
    public boolean move(String direction, Map map) {
        boolean hasMoved = false;

        switch(direction) {
            case "UP":
                hasMoved = this.moveIfPossible(map, 0, -1, "Up");
                break;
            case "DOWN":
                hasMoved = this.moveIfPossible(map, 0, 1, "Down");
                break;
            case "LEFT":
                hasMoved = this.moveIfPossible(map, -1, 0, "Left");
                break;
            case "RIGHT":
                hasMoved = this.moveIfPossible(map, 1, 0, "Right");
                break;
        }

        return hasMoved;
    }

    /**
     * Déplace le monstre dans une direction spécifiée si le déplacement est possible.
     * 
     * @param map la carte du jeu
     * @param newX la nouvelle position en x du monstre
     * @param newY la nouvelle position en y du monstre
     * @param direction la direction du déplacement (Up, Down, Left, Right)
     * @return true si le déplacement a été effectué, sinon false
     */
    private boolean moveIfPossible(Map map, int newX, int newY, String direction) {
        // Vérification des collisions avec les objets interactifs et les obstacles
        if (!PnjCollision.testCollision(this, map.getGridpaneInteract(), newX, newY, map, direction) && 
            !PnjCollision.testCollision(this, map.getGridpaneObstacle(), newX, newY, map, direction)) {
            
            // Animation du déplacement du monstre
            MonsterAnimation.animatedMove(map.getGridpanePnj(), this.getImageView(), direction, this.getX(), this.getY(), this.getNewX() + newX, this.getNewY() + newY);
            
            // Mise à jour des nouvelles coordonnées du monstre
            this.setNewX(this.getNewX() + newX);
            this.setNewY(this.getNewY() + newY);
            
            return true;
        }
        
        return false;
     }

    /**
     * Effectue un déplacement aléatoire du monstre sur la carte.
     * Si le monstre a déjà repéré le joueur, il ne se déplace pas.
     * Le déplacement est effectué en choisissant une direction aléatoire parmi les 4 possibles (haut, bas, gauche, droite).
     * Si le déplacement n'est pas possible dans la direction choisie, une nouvelle direction est sélectionnée jusqu'à ce que le déplacement soit possible.
     * @param map La carte du jeu.
     */
    public void randomMove(Map map) {
        this.playerInVision(map);
        if (this.hasVision()) {
            return;
        }

        boolean hasMoved;
        int direction;
        Random random = new Random();
        direction = random.nextInt(4);

        switch (direction) {
            case 0:
                hasMoved = this.moveIfPossible(map, 0, -1, "Up");
                break;
            case 1:
                hasMoved = this.moveIfPossible(map, -1, 0, "Left");
                break;
            case 2:
                hasMoved = this.moveIfPossible(map, 1, 0, "Right");
                break;
            case 3:
                hasMoved = this.moveIfPossible(map, 0, 1, "Down");
                break;
            default:
                hasMoved = false;
                break;
        }
        if(!hasMoved) {
            randomMove(map);
        }
    }

    /**
     * Vérifie si le monstre a repéré le joueur et effectue un déplacement dans la direction spécifiée si possible.
     * La vision du monstre est vérifiée en comparant les coordonnées du monstre avec celles du joueur.
     * Si le monstre a une vision claire du joueur (aucun obstacle), il se déplace vers le joueur dans la direction spécifiée.
     * @param sortX Coordonnée X du point supérieur gauche de la vision rapprochée du monstre.
     * @param sortY Coordonnée Y du point supérieur gauche de la vision rapprochée du monstre.
     * @param shortWidth Largeur de la vision rapprochée du monstre.
     * @param sortHeight Hauteur de la vision rapprochée du monstre.
     * @param longX Coordonnée X du point supérieur gauche de la vision éloignée du monstre.
     * @param longY Coordonnée Y du point supérieur gauche de la vision éloignée du monstre.
     * @param longWidth Largeur de la vision éloignée du monstre.
     * @param longHeight Hauteur de la vision éloignée du monstre.
     * @param playerBounds Les limites du joueur.
     * @param direction La direction dans laquelle le monstre doit se déplacer.
     * @param map La carte du jeu.
     * @return true si le monstre a pu effectuer le déplacement, sinon false.
     */
    private boolean checkVisionAndMoveIfPossible(double sortX, double sortY, double shortWidth, double sortHeight, double longX, double longY, double longWidth, double longHeight, Bounds playerBounds, String direction, Map map) {
        if (!PnjCollision.testVision(new BoundingBox(sortX,sortY,shortWidth,sortHeight), map) && playerBounds.intersects(longX, longY, longWidth, longHeight)) {
            this.setHasVision(true);
            return this.move(direction, map);
        }
        return false;
    }

    /**
     * Effectue le déplacement du monstre en fonction de la vision du joueur.
     * Cette méthode est appelée lorsque le monstre n'a pas encore repéré le joueur.
     * Le monstre vérifie différentes positions autour de lui pour détecter le joueur.
     * Si le joueur est détecté, le monstre se déplace dans la direction du joueur.
     * @param map La carte du jeu.
     */
    public void playerInVision(Map map) {
        this.setHasVision(false);
        Bounds playerBounds = map.getPlayer().getSprite().getBoundsInParent();
        Bounds monsterBounds = this.getImageView().getBoundsInParent();

        if (!checkVisionAndMoveIfPossible(monsterBounds.getMinX() - 30, monsterBounds.getMinY() - 30, monsterBounds.getWidth(), monsterBounds.getHeight() + 30, monsterBounds.getMinX() - 64, monsterBounds.getMinY() - 64, 64, 94, playerBounds, "LEFT", map)) {
            if (!checkVisionAndMoveIfPossible(monsterBounds.getMinX(), monsterBounds.getMinY() - 30, monsterBounds.getWidth() + 30, monsterBounds.getHeight(), monsterBounds.getMinX(), monsterBounds.getMinY() - 64, 94, 64, playerBounds, "UP", map)) {
                if (!checkVisionAndMoveIfPossible(monsterBounds.getMinX() + 30, monsterBounds.getMinY(), monsterBounds.getWidth(), monsterBounds.getHeight() + 30, monsterBounds.getMinX() + 30, monsterBounds.getMinY(), 64, 94, playerBounds, "RIGHT", map)) {
                    checkVisionAndMoveIfPossible(monsterBounds.getMinX() - 30, monsterBounds.getMinY() + 30, monsterBounds.getWidth() + 30, monsterBounds.getHeight(), monsterBounds.getMinX() - 64, monsterBounds.getMinY() + 30, 94, 64, playerBounds, "DOWN", map);
                }
            }
        }
    }

    /**
     * Effectue une attaque du monstre sur le joueur dans la direction spécifiée.
     * L'animation d'attaque du monstre est déclenchée.
     * La santé du joueur est réduite en fonction de la force du monstre.
     * Si la santé du joueur atteint 0 ou moins, l'image du joueur est changée pour indiquer qu'il est mort.
     * @param player Le joueur.
     * @param map La carte du jeu.
     * @param direction La direction de l'attaque.
     */
    public void attack(Player player, Map map, String direction) {
        MonsterAnimation.animatedAttack(this.getImageView(), direction);
        player.setHealth(player.getHealth() - this.getStrength(), map);

        // Le monstre vole un item au joueur quand il le frappe
        //this.getInventory().push(player.getInventory().getItem()[1]);
        //player.getInventory().remove(player.getInventory().getItem()[1], player, map);

        if(player.getHealth() <= 0) {
            player.getSprite().setImage(new Image("file:res/images/dead.png"));
        }
    }
}
