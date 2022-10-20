
-- MUPOSYS


--MIAS
INSERT INTO Ente(id) VALUES(1001);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1001,7,'ppp','Peperoni - Personal');
INSERT INTO Ente(id) VALUES(1002);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1002,7,'cpp','Peperoni - Chica');
INSERT INTO Ente(id) VALUES(1003);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1003,7,'mpp','Peperoni - Mediana');
INSERT INTO Ente(id) VALUES(1004);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1004,7,'gpp','Peperoni - Grandes');
INSERT INTO Ente(id) VALUES(1005);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1005,7,'fpp','Peperoni - Familiar');

INSERT INTO Ente(id) VALUES(1006);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1006,7,'phw','Hawaina - Personal');
INSERT INTO Ente(id) VALUES(1007);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1007,7,'chw','Hawaina - Chica');
INSERT INTO Ente(id) VALUES(1008);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1008,7,'mhw','Hawaina - Mediana');
INSERT INTO Ente(id) VALUES(1009);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1009,7,'ghw','Hawaina - Grande');
INSERT INTO Ente(id) VALUES(1010);
INSERT INTO CatalogItem(item,catalog,number,brief) VALUES(1010,7,'fhw','Hawaina - Familiar');

UPDATE CatalogItem SET active = 'Y'  WHERE item = 1001;
UPDATE CatalogItem SET value = 75 WHERE item = 1001;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1001;
UPDATE CatalogItem SET active = 'Y'  WHERE item = 1002;
UPDATE CatalogItem SET value = 95 WHERE item = 1002;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1002;
UPDATE CatalogItem SET active = 'Y'  WHERE item = 1003;
UPDATE CatalogItem SET value = 135 WHERE item = 1003;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1003;
UPDATE CatalogItem SET active = 'Y'  WHERE item = 1004;
UPDATE CatalogItem SET value = 175 WHERE item = 1004;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1004;
UPDATE CatalogItem SET active = 'Y'  WHERE item = 1005;
UPDATE CatalogItem SET value = 195 WHERE item = 1005;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1005;

UPDATE CatalogItem SET active = 'Y'  WHERE item = 1006;
UPDATE CatalogItem SET value = 95 WHERE item = 1006;
UPDATE CatalogItem SET active = 'Y'  WHERE item = 1007;
UPDATE CatalogItem SET value = 115 WHERE item = 1007;
UPDATE CatalogItem SET active = 'Y'  WHERE item = 1008;
UPDATE CatalogItem SET value = 155 WHERE item = 1008;
UPDATE CatalogItem SET active = 'Y'  WHERE item = 1009;
UPDATE CatalogItem SET value = 195 WHERE item = 1009;
UPDATE CatalogItem SET active = 'Y'  WHERE item = 1010;
UPDATE CatalogItem SET value = 215 WHERE item = 1010;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1006;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1007;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1008;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1009;
UPDATE CatalogItem SET presentation = 'Pz' WHERE item = 1010;


