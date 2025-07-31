package game.pnj;

import game.textures.Texture;

/**
 * Classe abstraite représentant un personnage non-joueur (PNJ) dans le jeu.
 */
public abstract class AbstractPnj {
	protected String name;
	protected boolean isMoving;
	protected boolean canBeHurt;	
	
	
	 /**
     * Constructeur de la classe AbstractPnj.
     *
     * @param name     Le nom du PNJ.
     * @param image    La texture représentant le PNJ.
     * @param hurt     Indique si le PNJ peut être blessé.
     */
	public AbstractPnj(String name, Texture image, boolean hurt) {
		this.name = name;
		this.isMoving = false;
		this.canBeHurt = hurt;
	}

	/**
     * Retourne le nom du PNJ.
     *
     * @return Le nom du PNJ.
     */
	public String getName() {
		return name;
	}

	/**
     * Modifie le nom du PNJ.
     *
     * @param name Le nouveau nom du PNJ.
     */
	public void setName(String name) {
		this.name = name;
	}

	/**
     * Vérifie si le PNJ est en mouvement.
     *
     * @return true si le PNJ est en mouvement, false sinon.
     */
	public boolean isMoving() {
		return isMoving;
	}

	/**
     * Définit si le PNJ est en mouvement.
     *
     * @param isMoving true pour indiquer que le PNJ est en mouvement, false sinon.
     */
	public void setMoving(boolean isMoving) {
		this.isMoving = isMoving;
	}

	/**
     * Vérifie si le PNJ peut être blessé.
     *
     * @return true si le PNJ peut être blessé, false sinon.
     */
	public boolean CanBeHurt() {
		return canBeHurt;
	}

	/**
     * Définit si le PNJ peut être blessé.
     *
     * @param canBeHurt true pour indiquer que le PNJ peut être blessé, false sinon.
     */
	public void setCanBeHurt(boolean canBeHurt) {
		this.canBeHurt = canBeHurt;
	}
	
	

}
