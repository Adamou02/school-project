CREATE PUBLIC DATABASE LINK 
LK_GLPI_PAU CONNECT TO glpi_pau_admin1 IDENTIFIED BY your_password USING '127.0.0.1:1521';
CREATE PUBLIC DATABASE LINK 
LK_GLPI_CERGY CONNECT TO glpi_cergy_admin1 IDENTIFIED BY your_password USING '127.0.0.1:1521';

COMMIT;
EXIT;
