package game.item;

/**
 * Classe représentant une potion dans le jeu.
 * Cette classe hérite de la classe abstraite AbstractItem.
 */
public class Potion extends AbstractItem {

	/**
	 * Constructeur de la classe Potion.
	 * 
	 * @param name        Le nom de la potion.
	 * @param description La description de la potion.
	 * @param btnText     Le texte affiché sur le bouton associé à la potion.
	 */
	public Potion(String name, String description, String btnText) {
		super(name, description, btnText);
	}
}
