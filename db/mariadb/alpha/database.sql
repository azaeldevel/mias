

ALTER TABLE CatalogItem ADD COLUMN station SMALLINT COMMENT 'Estación de producción';


ALTER TABLE Operation ADD COLUMN serie VARCHAR(5) COMMENT 'Serie de Fólio';
ALTER TABLE Operation ADD COLUMN number BIGINT COMMENT 'Número de Fólio';
ALTER TABLE Operation ADD COLUMN size SMALLINT DEFAULT 6 COMMENT 'Número de Fólio';


CREATE TABLE MiasService (operation BIGINT NOT NULL, name VARCHAR(50) NOT NULL);
ALTER TABLE MiasService ADD CONSTRAINT pk_MiasService PRIMARY KEY(operation);
ALTER TABLE MiasService ADD CONSTRAINT fk_MiasService_operation_Operation_operation FOREIGN KEY(operation) REFERENCES Operation(operation);
ALTER TABLE MiasService ADD COLUMN step SMALLINT DEFAULT 0 COMMENT 'Progreso actual del Servicio';
ALTER TABLE MiasService ADD COLUMN updated SMALLINT DEFAULT 0 COMMENT 'Indiucador de actualizacion';

CREATE TABLE ProgressLog(progress BIGINT PRIMARY KEY DEFAULT 11, FOREIGN KEY(progress) REFERENCES Progress(stocking)) COMMENT = 'Registra el progreso de las opoeracion operaciones';
ALTER TABLE ProgressLog ADD worker BIGINT NOT NULL COMMENT 'Usuario que realiza la actualización progreso';
ALTER TABLE ProgressLog ADD CONSTRAINT fk_ProgressLog_user_User_user FOREIGN KEY(worker) REFERENCES UserManagement(um);

ALTER TABLE Progress ADD worker BIGINT DEFAULT 11 COMMENT 'Usuario que realiza la actualización progreso';
ALTER TABLE Progress ADD CONSTRAINT fk_Progress_worker_User_user FOREIGN KEY(worker) REFERENCES UserManagement(user);

