ALTER SESSION SET "_ORACLE_SCRIPT"=TRUE;

-- Suppression des tablespaces et des utilisateurs pour GLPI_PAU
DROP USER GLPI_PAU CASCADE;
DROP TABLESPACE GLPI_PAU_TABSPACE INCLUDING CONTENTS AND DATAFILES;
DROP TABLESPACE GLPI_PAU_TABSPACE_TEMP INCLUDING CONTENTS AND DATAFILES;

-- Suppression des tablespaces et des utilisateurs pour GLPI_CERGY
DROP USER GLPI_CERGY CASCADE;
DROP TABLESPACE GLPI_CERGY_TABSPACE INCLUDING CONTENTS AND DATAFILES;
DROP TABLESPACE GLPI_CERGY_TABSPACE_TEMP INCLUDING CONTENTS AND DATAFILES;

-- -- Suppression des tablespaces pour les rôles GLPI
-- DROP TABLESPACE GLPI_OBSERVER_TS INCLUDING CONTENTS AND DATAFILES;
-- DROP TABLESPACE GLPI_OBSERVER_TEMP_TS INCLUDING CONTENTS AND DATAFILES;
-- DROP TABLESPACE GLPI_ANALYST_TS INCLUDING CONTENTS AND DATAFILES;
-- DROP TABLESPACE GLPI_ANALYST_TEMP_TS INCLUDING CONTENTS AND DATAFILES;
-- DROP TABLESPACE GLPI_DEV_TS INCLUDING CONTENTS AND DATAFILES;
-- DROP TABLESPACE GLPI_DEV_TEMP_TS INCLUDING CONTENTS AND DATAFILES;
-- DROP TABLESPACE GLPI_ADMIN_TS INCLUDING CONTENTS AND DATAFILES;
-- DROP TABLESPACE GLPI_ADMIN_TEMP_TS INCLUDING CONTENTS AND DATAFILES;

COMMIT;
EXIT;
