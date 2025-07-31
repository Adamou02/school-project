package game.map;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import game.character.Player;
import game.item.AbstractItem;
import game.item.Items;
import game.pnj.Merchant;
import game.pnj.Monster;
import game.reader.CsvReader;
import game.textures.Constants;
import javafx.scene.Scene;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Region;
import javafx.scene.layout.StackPane;
import game.utils.Minuteur;

/**
 * Classe représentant une carte du jeu.
 * Cette classe contient les différentes grilles (background, obstacles, interactions) de la carte, ainsi que les éléments comme le joueur, les monstres et les items.
 */
public class Map {

	private int height;
	private int width;
	private GridPane gridpaneBackground;
	private GridPane gridpaneObstacle;
	private GridPane gridpaneInteract;
	private GridPane gridpanePnj;
	private GridPane gameInfo;
	private Pane pane;
	private StackPane stackpane;
	private Player player;
	private List<Monster> tableauDeMonstres = new ArrayList<>();

	/**
	 * Constructeur de la classe Map.
	 * 
	 * @param width  La largeur de la carte.
	 * @param height La hauteur de la carte.
	 */
	public Map(int width, int height) {
		this.width = width;
		this.height = height;
		this.gridpaneBackground = new GridPane();
		gridpaneBackground.setPrefSize(width, height);
		this.gridpaneObstacle = new GridPane();
		gridpaneObstacle.setPrefSize(width, height);
		this.gridpaneInteract = new GridPane();
		gridpaneInteract.setPrefSize(width, height);
		this.gameInfo = new GridPane();
		gameInfo.setPrefSize(width, height);
		this.gridpanePnj = new GridPane();
		gridpanePnj.setPrefSize(width, height);
		this.pane = new Pane();
		this.player = new Player("Julien", 20, 0, "file:res/images/perso.png", this);
		this.player.getSprite().setLayoutX(70);
		this.player.getSprite().setLayoutY(70);
		this.stackpane = new StackPane();
	}

	/**
	 * Retourne la grille d'arrière-plan de la carte.
	 * 
	 * @return La grille d'arrière-plan.
	 */
	public GridPane getGridpaneBackground() {
		return gridpaneBackground;
	}

	/**
	 * Définit la grille d'arrière-plan de la carte.
	 * 
	 * @param gridpaneBackground La grille d'arrière-plan.
	 */
	public void setGridpaneBackground(GridPane gridpaneBackground) {
		this.gridpaneBackground = gridpaneBackground;
	}

	/**
	 * Retourne la grille des obstacles de la carte.
	 * 
	 * @return La grille des obstacles.
	 */
	public GridPane getGridpaneObstacle() {
		return gridpaneObstacle;
	}

	/**
	 * Définit la grille des obstacles de la carte.
	 * 
	 * @param gridpaneObstacle La grille des obstacles.
	 */
	public void setGridpaneObstacle(GridPane gridpaneObstacle) {
		this.gridpaneObstacle = gridpaneObstacle;
	}

	/**
	 * Retourne la grille des interactions de la carte.
	 * 
	 * @return La grille des interactions.
	 */
	public GridPane getGridpaneInteract() {
		return gridpaneInteract;
	}

	/**
	 * Définit la grille des interactions de la carte.
	 * 
	 * @param gridpaneInteract La grille des interactions.
	 */
	public void setGridpaneInteract(GridPane gridpaneInteract) {
		this.gridpaneInteract = gridpaneInteract;
	}

	/**
	 * Retourne la grille des PNJ (personnages non joueurs) de la carte.
	 * 
	 * @return La grille des PNJ.
	 */
	public GridPane getGridpanePnj() {
		return gridpanePnj;
	}

	/**
	 * Définit la grille des PNJ (personnages non joueurs) de la carte.
	 * 
	 * @param gridpanePnj La grille des PNJ.
	 */
	public void setGridpanePnj(GridPane gridpanePnj) {
		this.gridpanePnj = gridpanePnj;
	}

	/**
	 * Retourne la grille des informations de jeu de la carte.
	 * 
	 * @return La grille des informations de jeu.
	 */
	public GridPane getGameInfo() {
		return gameInfo;
	}

	/**
	 * Définit la grille des informations de jeu de la carte.
	 * 
	 * @param gameInfo La grille des informations de jeu.
	 */
	public void setGameInfo(GridPane gameInfo) {
		this.gameInfo = gameInfo;
	}

	/**
	 * Retourne le conteneur principal de la carte.
	 * 
	 * @return Le conteneur principal de la carte.
	 */
	public Pane getPane() {
		return pane;
	}
	    
	/**
	 * Définit le conteneur de la carte.
	 * 
	 * @param pane Le conteneur de la carte.
	 */
	public void setPane(Pane pane) {
		this.pane = pane;
	}


	/**
	 * Retourne le conteneur empilé de la carte.
	 * 
	 * @return Le conteneur empilé de la carte.
	 */
	public StackPane getStackpane() {
		return stackpane;
	}

	/**
	 * Définit le conteneur empilé de la carte.
	 * 
	 * @param stackpane Le conteneur empilé de la carte.
	 */
	public void setStackpane(StackPane stackpane) {
		this.stackpane = stackpane;
	}

	/**
	 * Retourne la largeur de la carte.
	 * 
	 * @return La largeur de la carte.
	 */
	public int getWidth() {
		return width;
	}

	/**
	 * Définit la largeur de la carte.
	 * 
	 * @param width La largeur de la carte.
	 */
	public void setWidth(int width) {
		this.width = width;
	}

	/**
	 * Retourne la hauteur de la carte.
	 * 
	 * @return La hauteur de la carte.
	 */
	public int getHeight() {
		return height;
	}

	/**
	 * Définit la hauteur de la carte.
	 * 
	 * @param height La hauteur de la carte.
	 */
	public void setHeight(int height) {
		this.height = height;
	}

	/**
	 * Retourne le joueur de la carte.
	 * 
	 * @return Le joueur de la carte.
	 */
	public Player getPlayer() {
		return player;
	}

	/**
	 * Définit le joueur de la carte.
	 * 
	 * @param player Le joueur de la carte.
	 */
	public void setPlayer(Player player) {
		this.player = player;
	}

	/**
	 * Retourne la liste des monstres de la carte.
	 * 
	 * @return La liste des monstres de la carte.
	 */
	public List<Monster> getTableauDeMonstres() {
		return tableauDeMonstres;
	}

	/**
	 * Définit la liste des monstres de la carte.
	 * 
	 * @param tableauDeMonstres La liste des monstres de la carte.
	 */
	public void setTableauDeMonstres(List<Monster> tableauDeMonstres) {
		this.tableauDeMonstres = tableauDeMonstres;
	}


	/**
	 * Initializes the GridPane with images based on the given file name.
	 *
	 * @param nameFile  The name of the file.
	 * @param gridpane  The GridPane to initialize.
	 */
	public void InitGridpane(String nameFile, GridPane gridpane) {
	    HashMap<String, ImageView> imageMap = new HashMap<>();

	    // GridPane background
	    imageMap.put("black", Constants.black.getImageView());
	    imageMap.put("sol", Constants.sol.getImageView());

	    // GridPane Obstacles
	    imageMap.put("topLeftCorner", Constants.topLeftCorner.getImageView());
	    imageMap.put("topRightCorner", Constants.topRightCorner.getImageView());
	    imageMap.put("bottomLeftCorner", Constants.bottomLeftCorner.getImageView());
	    imageMap.put("bottomRightCorner", Constants.bottomRightCorner.getImageView());
	    imageMap.put("topBorder", Constants.topBorder.getImageView());
	    imageMap.put("bottomBorder", Constants.bottomBorder.getImageView());
	    imageMap.put("leftBorder", Constants.leftBorder.getImageView());
	    imageMap.put("rightBorder", Constants.rightBorder.getImageView());
	    imageMap.put("block", Constants.block.getImageView());

	    imageMap.put("verticalLine", Constants.verticalLine.getImageView());
	    imageMap.put("verticalLineBreak", Constants.verticalLineBreak.getImageView());
	    imageMap.put("bottomVerticalLine", Constants.bottomVerticalLine.getImageView());
	    imageMap.put("topVerticalLine", Constants.topVerticalLine.getImageView());
	    imageMap.put("horizontalLine", Constants.horizontalLine.getImageView());
	    imageMap.put("horizontalLineBreak", Constants.horizontalLineBreak.getImageView());
	    imageMap.put("leftHorizontalLine", Constants.leftHorizontalLine.getImageView());
	    imageMap.put("cornerLeft", Constants.cornerLeft.getImageView());
	    imageMap.put("cornerRight", Constants.cornerRight.getImageView());
	    imageMap.put("cornerLeftBottom", Constants.cornerLeftBottom.getImageView());
	    imageMap.put("cornerRightBottom", Constants.cornerRightBottom.getImageView());

	    // GridPane Interact
	    imageMap.put("door1", Constants.door1.getImageView());
	    imageMap.put("door2", Constants.door2.getImageView());
	    imageMap.put("door3", Constants.door3.getImageView());
	    imageMap.put("door4", Constants.door4.getImageView());

	    imageMap.put("doorOpen1", Constants.doorOpen1.getImageView());
	    imageMap.put("doorOpen2", Constants.doorOpen2.getImageView());
	    imageMap.put("doorOpen3", Constants.doorOpen3.getImageView());
	    imageMap.put("doorOpen4", Constants.doorOpen4.getImageView());

	    imageMap.put("flag", Constants.flag.getImageView());
	    imageMap.put("trap", Constants.trap.getImageView());

	    imageMap.put("potionRed", Constants.potionRed.getImageView());
	    imageMap.put("potionBlue", Constants.potionBlue.getImageView());
	    imageMap.put("potionGray", Constants.potionGray.getImageView());
	    imageMap.put("potionYellow", Constants.potionYellow.getImageView());
	    imageMap.put("potionPurple", Constants.potionPurple.getImageView());
	    imageMap.put("potionGreen", Constants.potionGreen.getImageView());

	    imageMap.put("diamond", Constants.diamond.getImageView());
	    imageMap.put("key", Constants.key.getImageView());
	    imageMap.put("hammerBoosted", Constants.hammerBoosted.getImageView());

	    // Iterate over the GridPane cells and add regions with preferred size
	    for (int col = 0; col < 38; col++) {
	        for (int row = 0; row < 22; row++) {
	            Region region = new Region();
	            region.setPrefSize(32, 32);
	            region.setMinSize(32, 32);
	            region.setMaxSize(32, 32);
	            gridpane.add(region, col, row);
	        }
	    }

	    // Read matrix from the CSV file
	    String[][] matrix = CsvReader.ReadFile("res/files/" + nameFile + ".csv");

	    // Iterate over the matrix and add images to the GridPane based on matrix values
	    for (int i = 0; i < 38; i++) {
	        for (int j = 0; j < 22; j++) {

	            switch (matrix[j][i]) {
	                case "pigKing":
	                    Items drop = new Items("key", "Permet d'ouvrir une porte", "Use");
	                    Monster pigKing = new Monster("pigKing", 4, 2, false, Constants.pigKing, (AbstractItem) drop, this, i, j);
	                    gridpane.add(pigKing.getImageView(), i, j);
	                    pigKing.getRandomM().play();
	                    tableauDeMonstres.add(pigKing);
	                    break;
	                case "pigMob":
	                    Items drop_pigMob = new Items("diamond", "beautiful diamond with a lot of utilities ;)", "Use With Merchant");
	                    Monster pigMob = new Monster("pigMob", 2, 1, false, Constants.pigMob, (AbstractItem) drop_pigMob, this, i, j);
	                    gridpane.add(pigMob.getImageView(), i, j);
	                    pigMob.getRandomM().play();
	                    tableauDeMonstres.add(pigMob);
	                    break;
	                case "merchant":
	                    Merchant Me = new Merchant("Merchant", Constants.merchant);
	                    gridpane.add(Me.getImageView(), i, j);
	                    break;
	                case "merchant2":
	                    Merchant Me2 = new Merchant("Merchant", Constants.merchant2);
	                    gridpane.add(Me2.getImageView(), i, j);
	                    break;
	                case "dialogPnj":
	                    Merchant DP = new Merchant("dialogPnj", Constants.dialogPnj);
	                    gridpane.add(DP.getImageView(), i, j);
	                    break;
	                case "nothing":
	                    break;
	                default:
	                    gridpane.add(new ImageView(imageMap.get(matrix[j][i]).getImage()), i, j);
	            }
	        }
	    }
	}

	/**
	 * Stops the random movement of all monsters.
	 */
	public void stopMonster() {
	    for (Monster monstre : tableauDeMonstres) {
	        monstre.getRandomM().stop();
	    }
	}

	/**
	 * Restarts the random movement of all monsters.
	 */
	public void playMonster() {
	    for (Monster monstre : tableauDeMonstres) {
	        monstre.getRandomM().play();
	    }
	}

	/**
	 * Updates the life indicators on the game info pane based on the player's health.
	 */
	public void majLife() {
	    int i;
	    for (i = 0; i < this.getPlayer().getHealth() / 2; i++) {
	        gameInfo.add(Constants.fullHeart.getImageView(), i, 0);
	    }
	    if (this.getPlayer().getHealth() % 2 == 1) gameInfo.add(Constants.semiHeart.getImageView(), i++, 0);
	    for (int a = i; a < 10; a++) {
	        gameInfo.add(Constants.emptyHeart.getImageView(), a, 0);
	    }
	}

	/**
	 * Initializes the GridPane for the game information.
	 *
	 * @param player The player object.
	 */
	public void InitGridpaneGameInfo(Player player) {
	    for (int col = 0; col < 22; col++) {
	        for (int row = 0; row < 38; row++) {
	            Region region = new Region();
	            region.setPrefSize(32, 32);
	            region.setMinSize(32, 32);
	            region.setMaxSize(32, 32);
	            gameInfo.add(region, row, col);
	        }
	    }
	    majLife();

	    Minuteur minuteur = new Minuteur(player);
	    gameInfo.add(minuteur, 36, 0);
	    GridPane.setColumnSpan(minuteur, 3);
	    minuteur.start(300);
	}

	/**
	 * Creates the scene with the map and game information.
	 *
	 * @return The created scene.
	 */
	public Scene createMap() {

	    InitGridpane("background", this.gridpaneBackground);
	    InitGridpane("obstacles", this.gridpaneObstacle);
	    InitGridpane("interact", this.gridpaneInteract);
	    InitGridpane("pnj", this.gridpanePnj);
	    InitGridpaneGameInfo(player);

	    // Stack the panes
	    stackpane.getChildren().add(gridpaneBackground);
	    stackpane.getChildren().add(gridpaneObstacle);
	    stackpane.getChildren().add(pane);
	    stackpane.getChildren().add(gridpaneInteract);
	    stackpane.getChildren().add(gridpanePnj);
	    stackpane.getChildren().add(gameInfo);
	    pane.getChildren().add(this.getPlayer().getSprite());

	    return new Scene(stackpane, width, height);
	}

    	
}
