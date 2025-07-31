ALTER SESSION SET "_ORACLE_SCRIPT"=TRUE;

CREATE CLUSTER GLPI_CERGY.user_cluster (user_id INT) TABLESPACE GLPI_CERGY_TABSPACE; 
CREATE CLUSTER GLPI_CERGY.ticket_cluster (ticket_id INT) TABLESPACE GLPI_CERGY_TABSPACE; 

CREATE CLUSTER GLPI_PAU.user_cluster (user_id INT) TABLESPACE GLPI_PAU_TABSPACE; 
CREATE CLUSTER GLPI_PAU.ticket_cluster (ticket_id INT) TABLESPACE GLPI_PAU_TABSPACE; 

-- Cr�ation d'index sur les clusters pour am�liorer les performances globales des requ�tes impliquant des op�rations sur les donn�es regroup�es dans ces clusters.

-- Index sur le cluster des utilisateurs pour am�liorer les performances des requ�tes courantes impliquant des op�rations sur les utilisateurs.
CREATE INDEX GLPI_PAU.idx_user_cluster ON CLUSTER GLPI_PAU.user_cluster;
CREATE INDEX GLPI_CERGY.idx_user_cluster ON CLUSTER GLPI_CERGY.user_cluster;

-- Index sur le cluster des tickets pour am�liorer les performances des requ�tes courantes impliquant des op�rations sur les tickets
CREATE INDEX GLPI_PAU.idx_ticket_cluster ON CLUSTER GLPI_PAU.ticket_cluster;
CREATE INDEX GLPI_CERGY.idx_ticket_cluster ON CLUSTER GLPI_CERGY.ticket_cluster;


COMMIT;
EXIT;
