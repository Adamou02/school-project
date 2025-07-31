package game.pnj;

import game.textures.Texture;
import javafx.scene.image.ImageView;

/**
 * Classe représentant un PNJ marchand.
 */
public class Merchant extends AbstractPnj {
	private ImageView imageView;

	/**
	 * Constructeur de la classe Merchant.
	 *
	 * @param name  Nom du marchand.
	 * @param image Texture/image représentant le marchand.
	 */
	public Merchant(String name, Texture image) {
		super(name, image, false);
		this.imageView = image.getImageView();
		this.imageView.setFitHeight(30);
		this.imageView.setFitWidth(30);
		this.imageView.setUserData(this);
	}

	/**
	 * Retourne l'objet ImageView associé au marchand.
	 *
	 * @return L'objet ImageView représentant le marchand.
	 */
	public ImageView getImageView() {
		return imageView;
	}

	/**
	 * Modifie l'objet ImageView associé au marchand.
	 *
	 * @param imageView Le nouvel objet ImageView représentant le marchand.
	 */
	public void setImageView(ImageView imageView) {
		this.imageView = imageView;
	}
}
