

INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1058,3,'p-ph','Personal Pepe/Hawai','Pepe/Hawai','Personal');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1059,3,'p-p3','Personal Pepe/3c','Pepe/3C','Personal');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1060,3,'p-pi','Personal Pepe/Ita','Pepe/Ita','Personal');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1061,3,'p-pm','Personal Pepe/Mex','Pepe/Mex','Personal');

UPDATE CatalogItem SET active = 'Y'  WHERE id >= 1058 and id <= 1061;
UPDATE CatalogItem SET value = 75 WHERE id >= 1058 and id <= 1061;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id >= 1058 and id <= 1061;
UPDATE CatalogItem SET type = 1  WHERE id >= 1058 and id <= 1061;
UPDATE CatalogItem SET station = 2  WHERE id >= 1058 and id <= 1061;

