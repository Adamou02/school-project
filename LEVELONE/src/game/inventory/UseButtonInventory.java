package game.inventory;

import game.character.Player;
import game.item.AbstractItem;
import game.map.Map;
import game.pnj.Monster;
import javafx.scene.control.Button;
import javafx.scene.effect.ColorAdjust;
import javafx.scene.layout.GridPane;
import game.utils.Minuteur;
import game.utils.MinuteurInvincibility;
import game.utils.MinuteurInvisibility;
import game.utils.MinuteurMonsterStop;

/**
 * Classe représentant un bouton d'utilisation d'un item dans l'inventaire.
 */
public class UseButtonInventory extends Button {
	
	private String itemName;
	
	/**
	 * Constructeur de la classe UseButtonInventory.
	 * 
	 * @param item L'item associé au bouton.
	 */
	public UseButtonInventory(AbstractItem item) {
		this.itemName = item.getName();
		this.setText(item.getBtnText());
	}
	
	/**
	 * Méthode appelée lorsqu'on appuie sur le bouton.
	 * Effectue l'action correspondante à l'item associé au bouton.
	 * 
	 * @param player Le joueur associé à l'inventaire.
	 * @param map    La carte associée à l'inventaire.
	 */
	public void pushButton(Player player, Map map) {
		switch(this.itemName) {
		case("potionBlue"):
			player.getWeapon().setDamage(player.getWeapon().getDamage()+1);
			break;
		case("potionRed"):
			if(player.getHealth()+2>20) {
				player.setHealth(20, map);
			}else {
				player.setHealth(player.getHealth()+4,map);
			}
			break;
		case("potionGreen"):
			Minuteur.addTime(+50);
			break;
		case("potionPurple"):
			MinuteurMonsterStop minuteur2 = new MinuteurMonsterStop(map);
    		map.getGameInfo().add(minuteur2,34,0);
    		GridPane.setColumnSpan(minuteur2,3);
    		minuteur2.start(20);
    		for(Monster monster : map.getTableauDeMonstres()) {
    			ColorAdjust colorAdjust = new ColorAdjust();
    			colorAdjust.setHue(0.8333);
    			colorAdjust.setSaturation(1); 
    			monster.getImageView().setEffect(colorAdjust);
    		}
			break;
		case("potionYellow"):
			MinuteurInvincibility minuteurInvicibility = new MinuteurInvincibility(map);
			map.getGameInfo().add(minuteurInvicibility,32,0);
			GridPane.setColumnSpan(minuteurInvicibility,3);
			minuteurInvicibility.start(15);
			
			ColorAdjust colorAdjustInvicibility = new ColorAdjust();
			colorAdjustInvicibility.setHue(0.8888);
			colorAdjustInvicibility.setSaturation(1); 
			player.getSprite().setEffect(colorAdjustInvicibility);
			break;
		case("potionGray"):
			MinuteurInvisibility minuteurInvisibility = new MinuteurInvisibility(map);
			map.getGameInfo().add(minuteurInvisibility,29,0);
			GridPane.setColumnSpan(minuteurInvisibility,3);
			minuteurInvisibility.start(15);
		 
			player.setInvisible(true);
			player.getSprite().setOpacity(0.6);
			break;
		default:
			break;
		}
	}
}
