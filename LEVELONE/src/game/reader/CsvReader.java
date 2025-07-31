package game.reader;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

/**
 * Classe utilitaire pour lire un fichier CSV.
 */
public class CsvReader {
	
    /**
     * Lit un fichier CSV et renvoie une matrice de chaînes de caractères représentant les données.
     *
     * @param filePath Chemin du fichier CSV à lire.
     * @return Matrice de chaînes de caractères représentant les données du fichier CSV.
     */
    public static String[][] ReadFile(String filePath) {
        String line;
        String cvsSplitBy = ",";

        String[][] matrix = new String[22][38];

        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {

            int row = 0;
            while ((line = br.readLine()) != null && row < matrix.length) {

                // Utiliser la virgule comme séparateur pour diviser la ligne en valeurs individuelles
                String[] values = line.split(cvsSplitBy);
            	
            	for(int col = 0 ; col < 38; col++) {
            		matrix[row][col] = values[col];
            	}
            	row++;

            }

        } catch (IOException e) {
            e.printStackTrace();
        }
        return matrix;
    }
}
