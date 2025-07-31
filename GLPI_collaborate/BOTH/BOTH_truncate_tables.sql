-- Vidage des donn�es de la table de liaison entre les tickets et les utilisateurs (observateurs)
TRUNCATE TABLE GLPI_PAU.OBSERVERS;

-- Vidage des donn�es de la table de liaison entre les tickets et les utilisateurs (responsables)
TRUNCATE TABLE GLPI_PAU.ASSIGNED_TO;

-- Vidage des donn�es de la table de liaison entre les commentaires et les ressources
TRUNCATE TABLE GLPI_PAU.COMMENT_RESSOURCES;

-- Vidage des donn�es de la table de liaison entre les tickets et les ressources
TRUNCATE TABLE GLPI_PAU.TICKET_RESSOURCES;

-- Vidage des donn�es de la table qui stocke les ressources disponibles
TRUNCATE TABLE GLPI_PAU.RESSOURCES;

-- Vidage des donn�es de la table qui stocke les commentaires associ�s � chaque ticket
TRUNCATE TABLE GLPI_PAU.COMMENTS;

-- Vidage des donn�es de la table principale qui contient les d�tails de chaque ticket de support
TRUNCATE TABLE GLPI_PAU.TICKETS;

-- Vidage des donn�es de la table qui stocke les informations sur les utilisateurs de l'outil de ticketing
TRUNCATE TABLE GLPI_PAU.USERS;

-- Vidage des donn�es de la table qui stocke les d�tails sur le mat�riel concern� par les tickets
TRUNCATE TABLE GLPI_PAU.HARDWARES;

-- Vidage des donn�es de la table qui stocke les d�tails sur les emplacements physiques associ�s aux tickets
TRUNCATE TABLE GLPI_PAU.LOCATIONS;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de groupes pour les tickets
TRUNCATE TABLE GLPI_PAU.REF_GROUP;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de r�les pour les tickets
TRUNCATE TABLE GLPI_PAU.REF_ROLE;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de types pour les tickets
TRUNCATE TABLE GLPI_PAU.REF_TYPE;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de cat�gories pour les tickets
TRUNCATE TABLE GLPI_PAU.REF_CATEGORY;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de statuts pour les tickets
TRUNCATE TABLE GLPI_PAU.REF_STATUS;

-- Vidage des donn�es de la table de r�f�rence contient une liste pr�d�finie de valeurs pour les priorit�s des commentaires
TRUNCATE TABLE GLPI_PAU.REF_PRIORITY;

-- Vidage des donn�es de la table de liaison entre les tickets et les utilisateurs (observateurs)
TRUNCATE TABLE GLPI_CERGY.OBSERVERS;

-- Vidage des donn�es de la table de liaison entre les tickets et les utilisateurs (responsables)
TRUNCATE TABLE GLPI_CERGY.ASSIGNED_TO;

-- Vidage des donn�es de la table de liaison entre les commentaires et les ressources
TRUNCATE TABLE GLPI_CERGY.COMMENT_RESSOURCES;

-- Vidage des donn�es de la table de liaison entre les tickets et les ressources
TRUNCATE TABLE GLPI_CERGY.TICKET_RESSOURCES;

-- Vidage des donn�es de la table qui stocke les ressources disponibles
TRUNCATE TABLE GLPI_CERGY.RESSOURCES;

-- Vidage des donn�es de la table qui stocke les commentaires associ�s � chaque ticket
TRUNCATE TABLE GLPI_CERGY.COMMENTS;

-- Vidage des donn�es de la table principale qui contient les d�tails de chaque ticket de support
TRUNCATE TABLE GLPI_CERGY.TICKETS;

-- Vidage des donn�es de la table qui stocke les informations sur les utilisateurs de l'outil de ticketing
TRUNCATE TABLE GLPI_CERGY.USERS;

-- Vidage des donn�es de la table qui stocke les d�tails sur le mat�riel concern� par les tickets
TRUNCATE TABLE GLPI_CERGY.HARDWARES;

-- Vidage des donn�es de la table qui stocke les d�tails sur les emplacements physiques associ�s aux tickets
TRUNCATE TABLE GLPI_CERGY.LOCATIONS;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de groupes pour les tickets
TRUNCATE TABLE GLPI_CERGY.REF_GROUP;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de r�les pour les tickets
TRUNCATE TABLE GLPI_CERGY.REF_ROLE;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de types pour les tickets
TRUNCATE TABLE GLPI_CERGY.REF_TYPE;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de cat�gories pour les tickets
TRUNCATE TABLE GLPI_CERGY.REF_CATEGORY;

-- Vidage des donn�es de la table de r�f�rence qui permet de d�finir une liste pr�d�finie de statuts pour les tickets
TRUNCATE TABLE GLPI_CERGY.REF_STATUS;

-- Vidage des donn�es de la table de r�f�rence contient une liste pr�d�finie de valeurs pour les priorit�s des commentaires
TRUNCATE TABLE GLPI_CERGY.REF_PRIORITY;

COMMIT;
EXIT;
