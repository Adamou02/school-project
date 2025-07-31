package game;

import javafx.stage.Stage;

/**
 * Classe utilitaire pour stocker la référence de la fenêtre principale de l'application.
 */
public class PrimaryStageHolder {
    private static Stage primaryStage;

    /**
     * Définit la fenêtre principale.
     *
     * @param stage La fenêtre principale à définir.
     */
    public static void setPrimaryStage(Stage stage) {
        primaryStage = stage;
    }

    /**
     * Récupère la référence de la fenêtre principale.
     *
     * @return La référence de la fenêtre principale.
     */
    public static Stage getPrimaryStage() {
        return primaryStage;
    }
}
