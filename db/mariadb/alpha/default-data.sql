
-- MUPOSYS


--MIAS
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1001,3,'ppp','Peperoni - Personal','Peperoni','Personal');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1002,3,'cpp','Peperoni - Chica','Peperoni','Chica');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1003,3,'mpp','Peperoni - Mediana','Peperoni','Mediana');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1004,3,'gpp','Peperoni - Grandes','Peperoni','Grande');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1005,3,'fpp','Peperoni - Familiar','Peperoni','Familiar');

INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1006,3,'phw','Hawaina - Personal','Hawaina','Personal');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1007,3,'chw','Hawaina - Chica','Hawaina','Chica');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1008,3,'mhw','Hawaina - Mediana','Hawaina','Mediana');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1009,3,'ghw','Hawaina - Grande','Hawaina','Grande');
INSERT INTO CatalogItem(id,catalog,number,brief,name,size) VALUES(1010,3,'fhw','Hawaina - Familiar','Hawaina','Familiar');

UPDATE CatalogItem SET active = 'Y'  WHERE id = 1001;
UPDATE CatalogItem SET value = 75 WHERE id = 1001;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1001;
UPDATE CatalogItem SET active = 'Y'  WHERE id = 1002;
UPDATE CatalogItem SET value = 95 WHERE id = 1002;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1002;
UPDATE CatalogItem SET active = 'Y'  WHERE id = 1003;
UPDATE CatalogItem SET value = 135 WHERE id = 1003;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1003;
UPDATE CatalogItem SET active = 'Y'  WHERE id = 1004;
UPDATE CatalogItem SET value = 175 WHERE id = 1004;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1004;
UPDATE CatalogItem SET active = 'Y'  WHERE id = 1005;
UPDATE CatalogItem SET value = 195 WHERE id = 1005;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1005;

UPDATE CatalogItem SET active = 'Y'  WHERE id = 1006;
UPDATE CatalogItem SET value = 95 WHERE id = 1006;
UPDATE CatalogItem SET active = 'Y'  WHERE id = 1007;
UPDATE CatalogItem SET value = 115 WHERE id = 1007;
UPDATE CatalogItem SET active = 'Y'  WHERE id = 1008;
UPDATE CatalogItem SET value = 155 WHERE id = 1008;
UPDATE CatalogItem SET active = 'Y'  WHERE id = 1009;
UPDATE CatalogItem SET value = 195 WHERE id = 1009;
UPDATE CatalogItem SET active = 'Y'  WHERE id = 1010;
UPDATE CatalogItem SET value = 215 WHERE id = 1010;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1006;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1007;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1008;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1009;
UPDATE CatalogItem SET presentation = 'Pz' WHERE id = 1010;

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1011,3,'p3c','Tres Carnes - Personal','Y',115,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1012,3,'c3c','Tres Carnes - Chica','Y',135,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1013,3,'m3c','Tres Carnes - Mediana','Y',175,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1014,3,'g3c','Tres Carnes - Grandes','Y',215,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1015,3,'f3c','Tres Carnes - Familiar','Y',235,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1016,3,'pit','Italiana - Personal','Y',135,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1017,3,'cit','Italiana - Chica','Y',155,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1018,3,'mit','Italiana - Mediana','Y',195,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1019,3,'git','Italiana - Grandes','Y',235,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1020,3,'fit','Italiana - Familiar','Y',275,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1021,3,'pmx','Mexicana - Personal','Y',135,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1022,3,'cmx','Mexicana - Chica','Y',155,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1023,3,'mmx','Mexicana - Mediana','Y',195,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1024,3,'gmx','Mexicana - Grandes','Y',235,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1025,3,'fmx','Mexicana - Familiar','Y',275,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1026,3,'pcb','Combinada - Personal','Y',0,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1027,3,'ccb','Combinada - Chica','Y',0,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1028,3,'mcb','Combinada - Mediana','Y',0,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1029,3,'gcb','Combinada - Grandes','Y',0,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1030,3,'fcb','Combinada - Familiar','Y',0,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1031,3,'pe','Especial - Personal','Y',0,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1032,3,'ce','Especial - Chica','Y',0,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1033,3,'me','Especial - Mediana','Y',0,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1034,3,'ge','Especial - Grandes','Y',0,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1035,3,'fe','Especial - Familiar','Y',0,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1036,3,'c1b-bbq','Boneless - Combo 1','Y',60,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1037,3,'c2b-bbq','Boneless - Combo 2','Y',130,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1038,3,'c1b-buf','Boneless - Combo 1','Y',60,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1039,3,'c2b-buf','Boneless - Combo 2','Y',130,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1040,3,'c1a-bbq','Alitas - Combo 1','Y',70,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1041,3,'c2a-bbq','Alitas - Combo 2','Y',145,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1042,3,'c1a-buf','Alitas - Combo 1','Y',70,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1043,3,'c2a-buf','Alitas - Combo 2','Y',145,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1044,3,'ces-reg','Espagueti Regualar- Chico','Y',45,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1045,3,'ges-reg','Espagueti Regualar - Grande','Y',85,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1046,3,'ces-cm','Espagueti Camaron - Chico','Y',65,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1047,3,'ges-cm','Espagueti Camaron - Grande','Y',115,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1048,3,'cen-vg','Ensalada Vegetariana - Chico','Y',55,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1049,3,'gen-vg','Ensalada Vegetariana - Grande','Y',75,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1050,3,'cen-gr','Ensalada Griega - Chico','Y',55,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1051,3,'gen-gr','Ensalada Griega - Grande','Y',75,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1052,3,'cen-po','Ensalada Pollo - Chico','Y',70,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1053,3,'gen-po','Ensalada Pollo - Grande','Y',95,'Pz');

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1054,3,'ing-pp','Pepperoni','Y',20,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1055,3,'ing-qs','Queso','Y',20,'Pz');
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1056,3,'ing-sl','Salami','Y',20,'Pz');

UPDATE CatalogItem SET type = 1  WHERE id >= 1001 and id <= 1010;
UPDATE CatalogItem SET station=1  WHERE id >= 1001 and id <= 1010;

UPDATE CatalogItem SET type = 1  WHERE id >= 1011 and id <= 1035;
UPDATE CatalogItem SET station=1  WHERE id >= 1011 and id <= 1035;

UPDATE CatalogItem SET type = 1  WHERE id >= 1036 and id <= 1047;
UPDATE CatalogItem SET station = 2  WHERE id >= 1036 and id <= 1047;

INSERT INTO Person(id,name1,name3) VALUES(2,'Ana','V.');
INSERT INTO UserManagement(id) VALUES(3);
INSERT INTO User(id,person,name) VALUES(3,2,'ana');
UPDATE User SET pwdtxt = 'ana' WHERE id = 3;
UPDATE User SET status = 3 WHERE id = 3;
INSERT INTO UserPermission(user,permission) VALUES(3,1);

INSERT INTO Person(id,name1,name3) VALUES(3,'Joana','R.');
INSERT INTO UserManagement(id) VALUES(4);
INSERT INTO User(id,person,name) VALUES(4,3,'cesia');
UPDATE User SET pwdtxt = 'cesia' WHERE id = 4;
UPDATE User SET status=3 WHERE id = 4;
INSERT INTO UserPermission(user,permission) VALUES(4,1);

INSERT INTO Person(id,name1,name3) VALUES(4,'Beto','X');
INSERT INTO UserManagement(id) VALUES(5);
INSERT INTO User(id,person,name) VALUES(5,4,'beto');
UPDATE User SET pwdtxt = 'beto' WHERE id = 5;
UPDATE User SET status=3 WHERE id = 5;
INSERT INTO UserPermission(user,permission) VALUES(5,1);

INSERT INTO Person(id,name1,name3) VALUES(5,'Maria','X');
INSERT INTO UserManagement(id) VALUES(6);
INSERT INTO User(id,person,name) VALUES(6,5,'maria');
UPDATE User SET pwdtxt = 'maria' WHERE id = 6;
UPDATE User SET status = 3 WHERE id = 6;
INSERT INTO UserPermission(user,permission) VALUES(6,1);

INSERT INTO Person(id,name1,name3) VALUES(6,'Azael','R.');
INSERT INTO UserManagement(id) VALUES(7);
INSERT INTO User(id,person,name) VALUES(7,6,'azael');
UPDATE User SET pwdtxt = 'azael' WHERE id = 7;
UPDATE User SET status = 3 WHERE id = 7;
INSERT INTO UserPermission(user,permission) VALUES(7,1);

INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation,station) VALUES(1057,3,'be-600','Bebida 600mL','Y',22,'Pz',0);
--INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1058,3,'co-la-255','Coca de lata 255mL','Y',22,'Pz');

--INSERT INTO Ente(id) VALUES(2000);
