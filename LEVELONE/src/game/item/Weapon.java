package game.item;

/**
 * Classe représentant une arme dans le jeu.
 * Cette classe hérite de la classe abstraite AbstractItem.
 */
public class Weapon extends AbstractItem {
	private int damage;
	
	/**
	 * Constructeur de la classe Weapon.
	 * 
	 * @param name        Le nom de l'arme.
	 * @param damage      Les dégâts infligés par l'arme.
	 * @param description La description de l'arme.
	 * @param btnText     Le texte affiché sur le bouton associé à l'arme.
	 */
	public Weapon(String name, int damage, String description, String btnText) {
		super(name, description, btnText);
		this.damage = damage;
	}

	/**
	 * Retourne les dégâts infligés par l'arme.
	 * 
	 * @return Les dégâts infligés par l'arme.
	 */
	public int getDamage() {
		return damage;
	}

	/**
	 * Définit les dégâts infligés par l'arme.
	 * 
	 * @param damage Les nouveaux dégâts infligés par l'arme.
	 */
	public void setDamage(int damage) {
		this.damage = damage;
	}
}
