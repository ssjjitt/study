SELECT name, open_mode, restricted FROM v$pdbs;

ALTER PLUGGABLE DATABASE orclpdb OPEN;

CREATE USER mwrep IDENTIFIED BY 1234;

GRANT DBA TO mwrep;

