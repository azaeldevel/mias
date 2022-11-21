

ALTER TABLE CatalogItem ADD COLUMN station TINYINT COMMENT 'Estación de producción';


ALTER TABLE Operation ADD COLUMN serie VARCHAR(5) COMMENT 'Serie de Fólio';
ALTER TABLE Operation ADD COLUMN number BIGINT COMMENT 'Número de Fólio';
ALTER TABLE Operation ADD COLUMN size TINYINT DEFAULT 6 COMMENT 'Número de Fólio';


CREATE TABLE MiasService (operation BIGINT NOT NULL, name VARCHAR(50) NOT NULL);
ALTER TABLE MiasService ADD CONSTRAINT pk_MiasService PRIMARY KEY(operation);
ALTER TABLE MiasService ADD CONSTRAINT fk_MiasService_operation_Operation_operation FOREIGN KEY(operation) REFERENCES Operation(operation);
ALTER TABLE MiasService ADD COLUMN step TINYINT DEFAULT 0 COMMENT 'Progreso actual del Servicio';
ALTER TABLE MiasService ADD COLUMN updated SMALLINT DEFAULT 0 COMMENT 'Indiucador de actualizacion';

CREATE TABLE ProgressLog(progress BIGINT PRIMARY KEY NOT NULL, FOREIGN KEY(progress) REFERENCES Progress(stocking));
ALTER TABLE ProgressLog ADD user BIGINT NOT NULL COMMENT 'Usuario que realiza la actualización progreso';
ALTER TABLE ProgressLog ADD CONSTRAINT fk_ProgressLog_user_User_user FOREIGN KEY(user) REFERENCES User(user);
