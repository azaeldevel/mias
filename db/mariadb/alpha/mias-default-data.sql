
-- MUPOSYS


--MIAS
INSERT INTO Ente(id) VALUES(1001);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1001,7,'ppp','Peperoni - Personal');
INSERT INTO Ente(id) VALUES(1002);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1002,7,'cpp','Peperoni - Chica');
INSERT INTO Ente(id) VALUES(1003);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1003,7,'mpp','Peperoni - Mediana');
INSERT INTO Ente(id) VALUES(1004);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1004,7,'gpp','Peperoni - Grandes');
INSERT INTO Ente(id) VALUES(1005);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1005,7,'fpp','Peperoni - Familiar');

INSERT INTO Ente(id) VALUES(1006);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1006,7,'phw','Hawaina - Personal');
INSERT INTO Ente(id) VALUES(1007);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1007,7,'chw','Hawaina - Chica');
INSERT INTO Ente(id) VALUES(1008);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1008,7,'mhw','Hawaina - Mediana');
INSERT INTO Ente(id) VALUES(1009);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1009,7,'ghw','Hawaina - Grande');
INSERT INTO Ente(id) VALUES(1010);
INSERT INTO Catalog_Item(id,catalog,number,name) VALUES(1010,7,'fhw','Hawaina - Familiar');

UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1001;
UPDATE Catalog_Item SET value = 75 WHERE id = 1001;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1001;
UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1002;
UPDATE Catalog_Item SET value = 95 WHERE id = 1002;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1002;
UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1003;
UPDATE Catalog_Item SET value = 135 WHERE id = 1003;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1003;
UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1004;
UPDATE Catalog_Item SET value = 175 WHERE id = 1004;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1004;
UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1005;
UPDATE Catalog_Item SET value = 195 WHERE id = 1005;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1005;

UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1006;
UPDATE Catalog_Item SET value = 95 WHERE id = 1006;
UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1007;
UPDATE Catalog_Item SET value = 115 WHERE id = 1007;
UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1008;
UPDATE Catalog_Item SET value = 155 WHERE id = 1008;
UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1009;
UPDATE Catalog_Item SET value = 195 WHERE id = 1009;
UPDATE Catalog_Item SET active = 'Y'  WHERE id = 1010;
UPDATE Catalog_Item SET value = 215 WHERE id = 1010;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1006;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1007;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1008;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1009;
UPDATE Catalog_Item SET presentation = 'Pz' WHERE id = 1010;


