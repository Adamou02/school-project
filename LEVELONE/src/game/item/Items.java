package game.item;

/**
 * Classe représentant un item spécifique du jeu.
 * Cette classe hérite de la classe abstraite AbstractItem.
 */
public class Items extends AbstractItem {

	/**
	 * Constructeur de la classe Items.
	 * 
	 * @param name        Le nom de l'item.
	 * @param description La description de l'item.
	 * @param btnText     Le texte affiché sur le bouton associé à l'item.
	 */
	public Items(String name, String description, String btnText) {
		super(name, description, btnText);
	}
}
