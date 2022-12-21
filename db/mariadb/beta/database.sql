

ALTER TABLE CatalogItem ADD COLUMN station SMALLINT COMMENT 'Estación de producción';
ALTER TABLE CatalogItem ADD COLUMN name VARCHAR(30) COMMENT 'Tipo de pizza';
ALTER TABLE CatalogItem ADD COLUMN size VARCHAR(30) COMMENT 'Tamaño de la pizza';


ALTER TABLE Operation ADD COLUMN serie VARCHAR(5) COMMENT 'Serie de Fólio';
ALTER TABLE Operation ADD COLUMN number BIGINT COMMENT 'Número de Fólio';
ALTER TABLE Operation ADD COLUMN size SMALLINT DEFAULT 6 COMMENT 'Número de Fólio';


CREATE TABLE MiasService (operation BIGINT NOT NULL, name VARCHAR(50) NOT NULL);
ALTER TABLE MiasService ADD CONSTRAINT pk_MiasService PRIMARY KEY(operation);
ALTER TABLE MiasService ADD CONSTRAINT fk_MiasService_operation_Operation_operation FOREIGN KEY(operation) REFERENCES Operation(id);
ALTER TABLE MiasService ADD COLUMN step SMALLINT DEFAULT 0 COMMENT 'Progreso actual del Servicio';
ALTER TABLE MiasService ADD COLUMN updated SMALLINT DEFAULT 0 COMMENT 'Indicador de actualizacion';

CREATE TABLE ProgressLog(progress BIGINT PRIMARY KEY DEFAULT 11, FOREIGN KEY(progress) REFERENCES Progress(id)) COMMENT = 'Registra el progreso de las opoeracion operaciones';
ALTER TABLE ProgressLog ADD worker BIGINT NOT NULL COMMENT 'Usuario que realiza la actualización progreso';
ALTER TABLE ProgressLog ADD CONSTRAINT fk_ProgressLog_user_User_user FOREIGN KEY(worker) REFERENCES User(id);

--ALTER TABLE Progress ADD worker BIGINT DEFAULT 11 COMMENT 'Usuario que realiza la actualización progreso';
--ALTER TABLE Progress ADD CONSTRAINT fk_Progress_worker_User_user FOREIGN KEY(worker) REFERENCES User(id);

CREATE TABLE StockingCombined(id BIGINT NOT NULL, stocking BIGINT NOT NULL, pizza1 BIGINT NOT NULL, pizza2 BIGINT NOT NULL);
ALTER TABLE StockingCombined MODIFY id BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY;
ALTER TABLE StockingCombined ADD CONSTRAINT fk_Stocking_stocking_Stocking_id FOREIGN KEY(stocking) REFERENCES Stocking(id);
ALTER TABLE StockingCombined ADD CONSTRAINT fk_StockingCombined_pizza1_CatalogItem_id FOREIGN KEY(pizza1) REFERENCES CatalogItem(id);
ALTER TABLE StockingCombined ADD CONSTRAINT fk_StockingCombined_pizza2_CatalogItem_id FOREIGN KEY(pizza2) REFERENCES CatalogItem(id);
