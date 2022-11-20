
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

UPDATE CatalogItem SET type = 'service'  WHERE item >= 1001 and item <= 1010;
UPDATE CatalogItem SET station=1  WHERE item >= 1001 and item <= 1010;


INSERT INTO Ente(id) VALUES(1011);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1011,7,'p3c','Tres Carnes - Personal','Y',115,'Pz');
INSERT INTO Ente(id) VALUES(1012);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1012,7,'c3c','Tres Carnes - Chica','Y',135,'Pz');
INSERT INTO Ente(id) VALUES(1013);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1013,7,'m3c','Tres Carnes - Mediana','Y',175,'Pz');
INSERT INTO Ente(id) VALUES(1014);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1014,7,'g3c','Tres Carnes - Grandes','Y',215,'Pz');
INSERT INTO Ente(id) VALUES(1015);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1015,7,'f3c','Tres Carnes - Familiar','Y',235,'Pz');

INSERT INTO Ente(id) VALUES(1016);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1016,7,'pit','Italiana - Personal','Y',135,'Pz');
INSERT INTO Ente(id) VALUES(1017);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1017,7,'cit','Italiana - Chica','Y',155,'Pz');
INSERT INTO Ente(id) VALUES(1018);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1018,7,'mit','Italiana - Mediana','Y',195,'Pz');
INSERT INTO Ente(id) VALUES(1019);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1019,7,'git','Italiana - Grandes','Y',235,'Pz');
INSERT INTO Ente(id) VALUES(1020);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1020,7,'fit','Italiana - Familiar','Y',275,'Pz');

INSERT INTO Ente(id) VALUES(1021);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1021,7,'pmx','Mexicana - Personal','Y',135,'Pz');
INSERT INTO Ente(id) VALUES(1022);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1022,7,'cmx','Mexicana - Chica','Y',155,'Pz');
INSERT INTO Ente(id) VALUES(1023);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1023,7,'mmx','Mexicana - Mediana','Y',195,'Pz');
INSERT INTO Ente(id) VALUES(1024);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1024,7,'gmx','Mexicana - Grandes','Y',235,'Pz');
INSERT INTO Ente(id) VALUES(1025);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1025,7,'fmx','Mexicana - Familiar','Y',275,'Pz');

INSERT INTO Ente(id) VALUES(1026);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1026,7,'pcb','Combinada - Personal','Y',0,'Pz');
INSERT INTO Ente(id) VALUES(1027);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1027,7,'ccb','Combinada - Chica','Y',0,'Pz');
INSERT INTO Ente(id) VALUES(1028);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1028,7,'mcb','Combinada - Mediana','Y',0,'Pz');
INSERT INTO Ente(id) VALUES(1029);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1029,7,'gcb','Combinada - Grandes','Y',0,'Pz');
INSERT INTO Ente(id) VALUES(1030);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1030,7,'fcb','Combinada - Familiar','Y',0,'Pz');

INSERT INTO Ente(id) VALUES(1031);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1031,7,'pe','Especial - Personal','Y',0,'Pz');
INSERT INTO Ente(id) VALUES(1032);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1032,7,'ce','Especial - Chica','Y',0,'Pz');
INSERT INTO Ente(id) VALUES(1033);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1033,7,'me','Especial - Mediana','Y',0,'Pz');
INSERT INTO Ente(id) VALUES(1034);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1034,7,'ge','Especial - Grandes','Y',0,'Pz');
INSERT INTO Ente(id) VALUES(1035);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1035,7,'fe','Especial - Familiar','Y',0,'Pz');

INSERT INTO Ente(id) VALUES(1036);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1036,7,'c1b-bbq','Boneless - Combo 1','Y',60,'Pz');
INSERT INTO Ente(id) VALUES(1037);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1037,7,'c2b-bbq','Boneless - Combo 2','Y',130,'Pz');

INSERT INTO Ente(id) VALUES(1038);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1038,7,'c1b-buf','Boneless - Combo 1','Y',60,'Pz');
INSERT INTO Ente(id) VALUES(1039);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1039,7,'c2b-buf','Boneless - Combo 2','Y',130,'Pz');


INSERT INTO Ente(id) VALUES(1040);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1040,7,'c1a-bbq','Alitas - Combo 1','Y',70,'Pz');
INSERT INTO Ente(id) VALUES(1041);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1041,7,'c2a-bbq','Alitas - Combo 2','Y',145,'Pz');

INSERT INTO Ente(id) VALUES(1042);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1042,7,'c1a-buf','Alitas - Combo 1','Y',70,'Pz');
INSERT INTO Ente(id) VALUES(1043);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1043,7,'c2a-buf','Alitas - Combo 2','Y',145,'Pz');

INSERT INTO Ente(id) VALUES(1044);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1044,7,'ces-reg','Espagueti Regualar- Chico','Y',45,'Pz');
INSERT INTO Ente(id) VALUES(1045);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1045,7,'ges-reg','Espagueti Regualar - Grande','Y',85,'Pz');

INSERT INTO Ente(id) VALUES(1046);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1046,7,'ces-cm','Espagueti Camaron - Chico','Y',65,'Pz');
INSERT INTO Ente(id) VALUES(1047);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1047,7,'ges-cm','Espagueti Camaron - Grande','Y',115,'Pz');

INSERT INTO Ente(id) VALUES(1048);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1048,7,'cen-vg','Ensalada Vegetariana - Chico','Y',55,'Pz');
INSERT INTO Ente(id) VALUES(1049);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1049,7,'gen-vg','Ensalada Vegetariana - Grande','Y',75,'Pz');

INSERT INTO Ente(id) VALUES(1050);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1050,7,'cen-gr','Ensalada Griega - Chico','Y',55,'Pz');
INSERT INTO Ente(id) VALUES(1051);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1051,7,'gen-gr','Ensalada Griega - Grande','Y',75,'Pz');

INSERT INTO Ente(id) VALUES(1052);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1052,7,'cen-po','Ensalada Pollo - Chico','Y',70,'Pz');
INSERT INTO Ente(id) VALUES(1053);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1053,7,'gen-po','Ensalada Pollo - Grande','Y',95,'Pz');


INSERT INTO Ente(id) VALUES(1054);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1054,7,'ing-pp','Pepperoni','Y',20,'Pz');
INSERT INTO Ente(id) VALUES(1055);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1055,7,'ing-qs','Queso','Y',20,'Pz');
INSERT INTO Ente(id) VALUES(1056);
INSERT INTO CatalogItem(item,catalog,number,brief,active,value,presentation) VALUES(1056,7,'ing-sl','Salami','Y',20,'Pz');

UPDATE CatalogItem SET type = 'service'  WHERE item >= 1011 and item <= 1035;
UPDATE CatalogItem SET station=1  WHERE item >= 1011 and item <= 1035;

UPDATE CatalogItem SET type = 'service'  WHERE item >= 1036 and item <= 1047;
UPDATE CatalogItem SET station=2  WHERE item >= 1036 and item <= 1047;





INSERT INTO Ente(id) VALUES(2000);
