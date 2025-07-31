package game.inventory;

import game.character.Player;
import game.item.AbstractItem;
import game.item.Weapon;
import game.map.Map;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Separator;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.Region;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import game.utils.Minuteur;

/**
 * Cette classe représente l'inventaire du joueur dans le jeu.
 */
public class Inventory {

    //instances de l'inventaire pour la partie graphique 
    private Stage stage;
    private BorderPane borderPane;
    private ImageView centre;

    //instances de l'inventaire pour la gestion des items
    protected AbstractItem[] items;
    protected int nbItem;

    /**
     * Constructeur de la classe Inventory.
     * Initialise les variables membres et crée la fenêtre d'inventaire.
     */
    public Inventory() {    
        this.nbItem = 0;
        this.items = new AbstractItem[24];

        for(int i = 0 ; i < 24; i++) {
            this.items[i] = null;
        }

        this.borderPane = new BorderPane();
        this.borderPane.setCenter(new GridPane());
        this.borderPane.setMaxSize(700, 400);
        this.stage = new Stage();
        this.stage.setTitle("Inventaire");
        this.stage.setScene(new Scene(this.borderPane));
        this.stage.setResizable(false);
        this.stage.initModality(Modality.APPLICATION_MODAL);
	    this.stage.initStyle(StageStyle.UNDECORATED);
    }
    
    
    /**
     * Met à jour l'affichage de l'inventaire dans la fenêtre.
     * 
     * @param player le joueur actuel
     * @param map la carte du jeu
     */
    public void updateStageInventory(Player player, Map map) {
    	
    	BorderPane bp = new BorderPane();
    	bp.setPrefSize(700, 350);
    	bp.setMaxSize(700, 350);
    	bp.setMinSize(700, 350);
    	bp.setStyle("-fx-padding: 5px; -fx-background-color: rgb(56,52,68);");
    	
    	//System.out.println("mise a jour de la gridpane inventory");
        HBox infoPlayer = new HBox();
        infoPlayer.setPrefHeight(50);
        infoPlayer.setPrefWidth(500);
        infoPlayer.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56,52,50);");
        
        Text PlayerName = new Text(player.getName());
        PlayerName.setFont(Font.font("Nom de la police", FontWeight.BOLD, 20));
        PlayerName.setFill(Color.YELLOW);
        HBox.setMargin(PlayerName, new Insets(0, 0, 0, 10));
        
        ImageView PlayerView = new ImageView(new Image("file:res/images/perso.png"));
        PlayerView.setFitHeight(50);
        PlayerView.setFitWidth(50);
        HBox.setMargin(PlayerView, new Insets(10, 10, 10, 10));
        
        Weapon actualweapon = player.getWeapon();
        ImageView WeaponView = new ImageView(actualweapon.getImageView().getImage());
        WeaponView.setFitHeight(32);
        WeaponView.setFitWidth(70);
        HBox.setMargin(WeaponView, new Insets(10, 10, 10, 100));
        
        VBox weaponDetails = new VBox();
        VBox.setMargin(weaponDetails, new Insets(10, 10, 10, 10));
        
        Text weaponName = new Text("Nom : " + actualweapon.getName());
        weaponName.setFont(Font.font("Nom de la police", 17));
        weaponName.setFill(Color.YELLOW);
        VBox.setMargin(weaponName, new Insets(10, 0, 0, 0));
        
        Text playerDamage = new Text("Dégats : " + actualweapon.getDamage());
        playerDamage.setFont(Font.font("Nom de la police", 17));
        playerDamage.setFill(Color.YELLOW);
        VBox.setMargin(playerDamage, new Insets(0, 0, 10, 0));
        
        weaponDetails.getChildren().add(weaponName);
        weaponDetails.getChildren().add(playerDamage);
        
        Region spacer = new Region();
        HBox.setHgrow(spacer, Priority.ALWAYS);
	    
        Button goBack = new Button("Go back");
		goBack.setStyle("-fx-background-color: rgb(56,52,68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");
		HBox.setMargin(goBack, new Insets(10, 10, 10, 10));

		goBack.setOnAction(event -> {
		//Ferme la Stage dialog quand on clique sur la croix rouge
		Minuteur.resume();
		this.stage.close();
        });
        
        infoPlayer.getChildren().add(PlayerView);
        infoPlayer.getChildren().add(PlayerName);
        infoPlayer.getChildren().add(WeaponView);
        infoPlayer.getChildren().add(weaponDetails);
        infoPlayer.getChildren().add(spacer);
    	infoPlayer.getChildren().add(goBack);
        infoPlayer.setAlignment(Pos.CENTER_LEFT);
        BorderPane.setMargin(infoPlayer, new Insets(0, 0, 10, 0));

        //CrÃƒÂ©ez la grille d'items
        GridPane gridPane = new GridPane();
        gridPane.setPadding(new Insets(10));
        gridPane.setHgap(10);
        gridPane.setVgap(10);
        gridPane.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56,52,50);");
        BorderPane.setMargin(gridPane, new Insets(0, 10, 0, 0));

        VBox ItemInfo = new VBox();
        ItemInfo.setPrefSize(300, 300);
        ItemInfo.setMaxSize(300, 300);
        ItemInfo.setStyle("-fx-border-width: 2px; -fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56,52,50);");

        int row = 0;
        int compteur = 0;
        for(AbstractItem item : items) {
            if (item != null) {
            	ImageView item_view = new ImageView(item.getImageView().getImage());
            	item_view.setPreserveRatio(true);
                item_view.setFitWidth(45);
                item_view.setFitHeight(45);
                StackPane itemBox = new StackPane(item_view);
                itemBox.setPrefWidth(50);
                itemBox.setPrefHeight(50);
                itemBox.setStyle("-fx-border-width: 2px;-fx-border-color: white; -fx-border-radius: 10; -fx-background-color: rgb(56,52,50);");
                
                
                itemBox.setOnMouseClicked(event ->{
                    ItemInfo.getChildren().clear();
                    Text itemName = new Text(item.getName());
                    itemName.setFont(Font.font("Nom de la police", FontWeight.BOLD, 15));
                    itemName.setFill(Color.WHITE);
                    HBox nameBox = new HBox();
                    nameBox.getChildren().add(itemName);
                    nameBox.setAlignment(Pos.CENTER);
                    ImageView itemView = new ImageView(item.getImageView().getImage());
                    HBox conteneur = new HBox();
                    conteneur.getChildren().add(itemView);
                    VBox.setMargin(conteneur, new Insets(5, 0, 5, 0));
                    conteneur.setAlignment(Pos.CENTER);
                    Text itemDescription = new Text(item.getDescription());
                    itemDescription.setFill(Color.WHITE);
                    StackPane descBox = new StackPane(itemDescription);
                    descBox.setStyle("-fx-border-width: 2px; -fx-border-color: rgb(56,52,50); -fx-border-radius: 10; -fx-background-color:  rgb(56,52,68);");
                    VBox.setMargin(descBox, new Insets(0, 0, 5, 0));
                    
                    UseButtonInventory itemBtn = new UseButtonInventory(item);
                    itemBtn.setStyle("-fx-background-color: rgb(56,52,68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");
                    
                    itemBtn.setOnAction(e -> {
                    	switch(item.getBtnText()) {
                    	case"Drink":
                    		itemBtn.pushButton(player,map);
                            this.remove(item, player,map);
                            this.stage.close();
                    		break;
                    	case "equip weapon":
                    		player.setWeapon((Weapon) item);
                    		player.getInventory().updateStageInventory(player, map);
                    	default:
                    		break;
                    	}
                    });
                    
                    Button dropItem = new Button("Drop");
                    
                    dropItem.setOnAction(e -> {
                    	if(! (item instanceof Weapon)) {
                    		player.getInventory().remove(item, player, map);    
                        	map.getGridpaneInteract().add(item.getImageView(),(int) (map.getPlayer().getSprite().getLayoutX() /32),(int) (map.getPlayer().getSprite().getLayoutY() /32)+1);   
                    	}});
                    
                    dropItem.setStyle("-fx-background-color: rgb(56,52,68); -fx-text-fill: white; -fx-border-color: white; -fx-border-width: 2px; -fx-border-radius: 5;");

                    HBox boutonsBox = new HBox();
                    boutonsBox.setSpacing(10);
                    boutonsBox.getChildren().addAll(itemBtn, dropItem);
                    itemView.setPreserveRatio(true);
                    itemView.setFitHeight(70);
                    boutonsBox.setAlignment(Pos.CENTER);
                    
                    Separator separator = new Separator();
                    separator.setPrefWidth(ItemInfo.getWidth());
                    separator.getStyleClass().add("-fx-border-style: solid; -fx-border-width: 0 0 1 0; -fx-border-color: white;");
                    
                    ItemInfo.getChildren().add(nameBox);
                    ItemInfo.getChildren().add(separator);
                    ItemInfo.getChildren().add(conteneur);
                    ItemInfo.getChildren().add(descBox);
                    ItemInfo.getChildren().add(boutonsBox);
                });
                gridPane.add(itemBox, compteur%6, row);
                compteur++;

                if(compteur%6 == 0) {
                    row++;
                }
            }

     }

        bp.setTop(infoPlayer);
        bp.setCenter(gridPane);
        bp.setRight(ItemInfo);
        
        this.borderPane=bp;
        this.stage.setScene(new Scene(bp));;
    }
	
    /**
	 * Renvoie le tableau d'items de l'inventaire.
	 * 
	 * @return Le tableau d'items de l'inventaire.
	 */
	public AbstractItem[] getItem() {
		return items;
	}
    
    /**
	 * Définit le tableau d'items de l'inventaire.
	 * 
	 * @param item Le nouveau tableau d'items de l'inventaire.
	 */
	public void setItem(AbstractItem[] item) {
		this.items = item;
	}

	/**
	 * Renvoie le nombre d'items dans l'inventaire.
	 * 
	 * @return Le nombre d'items dans l'inventaire.
	 */
	public int getNbItem() {
		return nbItem;
	}

	/**
	 * Définit le nombre d'items dans l'inventaire.
	 * 
	 * @param nbItem Le nouveau nombre d'items dans l'inventaire.
	 */
	public void setNbItem(int nbItem) {
		this.nbItem = nbItem;
	}

	/**
	 * Renvoie l'image centrale de l'inventaire.
	 * 
	 * @return L'image centrale de l'inventaire.
	 */
	public ImageView getCentre() {
		return centre;
	}

	/**
	 * Définit l'image centrale de l'inventaire.
	 * 
	 * @param centre La nouvelle image centrale de l'inventaire.
	 */
	public void setCentre(ImageView centre) {
		this.centre = centre;
	}
	
	/**
	 * Renvoie la fenêtre de l'inventaire.
	 * 
	 * @return La fenêtre de l'inventaire.
	 */
	public Stage getStage() {
		return stage;
	}

	/**
	 * Définit la fenêtre de l'inventaire.
	 * 
	 * @param stage La nouvelle fenêtre de l'inventaire.
	 */
	public void setStage(Stage stage) {
		this.stage = stage;
	}

	/**
	 * Renvoie le conteneur principal de l'interface graphique de l'inventaire.
	 * 
	 * @return Le conteneur principal de l'interface graphique de l'inventaire.
	 */
	public BorderPane getBorderPane() {
		return borderPane;
	}
	
	/**
	 * Définit le conteneur principal de l'interface graphique de l'inventaire.
	 * 
	 * @param borderPane Le nouveau conteneur principal de l'interface graphique de l'inventaire.
	 */
	public void setBorderPane(BorderPane borderPane) {
		this.borderPane = borderPane;
	}
	
	/**
	 * Ajoute un item à l'inventaire.
	 * 
	 * @param item L'item à ajouter à l'inventaire.
	 */
	public void push(AbstractItem item) {
		this.items[this.nbItem] = item;
		this.nbItem++;
		
		// Fin de la partie si, par exemple, il y a 3 diamants dans l'inventaire
		/*int cpt = 0;
		for(AbstractItem items : this.getItem()) {
			if (items != null && items.getName().equals("diamond")) {
				cpt++;
			}
		}
		if(cpt==3) {
			ActionEndGame.displayEndGame(true);
		}*/
	}
	
	/**
	 * Supprime un item de l'inventaire.
	 * 
	 * @param item   L'item à supprimer de l'inventaire.
	 * @param player Le joueur associé à l'inventaire.
	 * @param map    La carte associée à l'inventaire.
	 */
	public void remove(AbstractItem item, Player player, Map map) {
		int compteur = 0;
		
		for(AbstractItem itemIn : this.items) {
			if (itemIn == item) {
				for(int i = compteur; i < this.getNbItem();i++) {
					this.getItem()[i] = this.getItem()[i+1];
				}
			}
			compteur++;
		}
		this.nbItem--;
		this.updateStageInventory(player, map);
	}
	
	/**
	 * Affiche le contenu de l'inventaire.
	 */
	public void afficheInventory() {
		System.out.println("Voici le contenu de l'inventaire :");
		for(int i = 0 ; i < this.nbItem; i++) {
			System.out.println(items[i].getName());
		}
	}
	
	/**
	 * Supprime le premier diamant trouvé dans l'inventaire.
	 * 
	 * @param player Le joueur associé à l'inventaire.
	 * @param map    La carte associée à l'inventaire.
	 */
	public void removeDiam(Player player, Map map) {
		for(int i = 0 ; i < this.nbItem; i++) {
			if(items[i].getName().equals("diamond")) {
				this.remove(items[i], player, map);
				break;
			}
		}
	}

}
