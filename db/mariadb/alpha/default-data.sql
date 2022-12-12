
-- MUPOSYS


--MIAS
--INSERT INTO Ente(id) VALUES(1001);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1001,3,'ppp','Peperoni - Personal');
--INSERT INTO Ente(id) VALUES(1002);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1002,3,'cpp','Peperoni - Chica');
--INSERT INTO Ente(id) VALUES(1003);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1003,3,'mpp','Peperoni - Mediana');
--INSERT INTO Ente(id) VALUES(1004);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1004,3,'gpp','Peperoni - Grandes');
--INSERT INTO Ente(id) VALUES(1005);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1005,3,'fpp','Peperoni - Familiar');

--INSERT INTO Ente(id) VALUES(1006);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1006,3,'phw','Hawaina - Personal');
--INSERT INTO Ente(id) VALUES(1007);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1007,3,'chw','Hawaina - Chica');
--INSERT INTO Ente(id) VALUES(1008);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1008,3,'mhw','Hawaina - Mediana');
--INSERT INTO Ente(id) VALUES(1009);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1009,3,'ghw','Hawaina - Grande');
--INSERT INTO Ente(id) VALUES(1010);
INSERT INTO CatalogItem(id,catalog,number,brief) VALUES(1010,3,'fhw','Hawaina - Familiar');

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

UPDATE CatalogItem SET type = 'service'  WHERE id >= 1001 and id <= 1010;
UPDATE CatalogItem SET station=1  WHERE id >= 1001 and id <= 1010;


--INSERT INTO Ente(id) VALUES(1011);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1011,3,'p3c','Tres Carnes - Personal','Y',115,'Pz');
--INSERT INTO Ente(id) VALUES(1012);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1012,3,'c3c','Tres Carnes - Chica','Y',135,'Pz');
--INSERT INTO Ente(id) VALUES(1013);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1013,3,'m3c','Tres Carnes - Mediana','Y',175,'Pz');
--INSERT INTO Ente(id) VALUES(1014);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1014,3,'g3c','Tres Carnes - Grandes','Y',215,'Pz');
--INSERT INTO Ente(id) VALUES(1015);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1015,3,'f3c','Tres Carnes - Familiar','Y',235,'Pz');

--INSERT INTO Ente(id) VALUES(1016);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1016,3,'pit','Italiana - Personal','Y',135,'Pz');
--INSERT INTO Ente(id) VALUES(1017);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1017,3,'cit','Italiana - Chica','Y',155,'Pz');
--INSERT INTO Ente(id) VALUES(1018);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1018,3,'mit','Italiana - Mediana','Y',195,'Pz');
--INSERT INTO Ente(id) VALUES(1019);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1019,3,'git','Italiana - Grandes','Y',235,'Pz');
--INSERT INTO Ente(id) VALUES(1020);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1020,3,'fit','Italiana - Familiar','Y',275,'Pz');

--INSERT INTO Ente(id) VALUES(1021);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1021,3,'pmx','Mexicana - Personal','Y',135,'Pz');
--INSERT INTO Ente(id) VALUES(1022);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1022,3,'cmx','Mexicana - Chica','Y',155,'Pz');
--INSERT INTO Ente(id) VALUES(1023);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1023,3,'mmx','Mexicana - Mediana','Y',195,'Pz');
--INSERT INTO Ente(id) VALUES(1024);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1024,3,'gmx','Mexicana - Grandes','Y',235,'Pz');
--INSERT INTO Ente(id) VALUES(1025);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1025,3,'fmx','Mexicana - Familiar','Y',275,'Pz');

--INSERT INTO Ente(id) VALUES(1026);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1026,3,'pcb','Combinada - Personal','Y',0,'Pz');
--INSERT INTO Ente(id) VALUES(1027);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1027,3,'ccb','Combinada - Chica','Y',0,'Pz');
--INSERT INTO Ente(id) VALUES(1028);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1028,3,'mcb','Combinada - Mediana','Y',0,'Pz');
--INSERT INTO Ente(id) VALUES(1029);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1029,3,'gcb','Combinada - Grandes','Y',0,'Pz');
--INSERT INTO Ente(id) VALUES(1030);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1030,3,'fcb','Combinada - Familiar','Y',0,'Pz');

--INSERT INTO Ente(id) VALUES(1031);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1031,3,'pe','Especial - Personal','Y',0,'Pz');
--INSERT INTO Ente(id) VALUES(1032);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1032,3,'ce','Especial - Chica','Y',0,'Pz');
--INSERT INTO Ente(id) VALUES(1033);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1033,3,'me','Especial - Mediana','Y',0,'Pz');
--INSERT INTO Ente(id) VALUES(1034);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1034,3,'ge','Especial - Grandes','Y',0,'Pz');
--INSERT INTO Ente(id) VALUES(1035);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1035,3,'fe','Especial - Familiar','Y',0,'Pz');

--INSERT INTO Ente(id) VALUES(1036);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1036,3,'c1b-bbq','Boneless - Combo 1','Y',60,'Pz');
--INSERT INTO Ente(id) VALUES(1037);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1037,3,'c2b-bbq','Boneless - Combo 2','Y',130,'Pz');

--INSERT INTO Ente(id) VALUES(1038);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1038,3,'c1b-buf','Boneless - Combo 1','Y',60,'Pz');
--INSERT INTO Ente(id) VALUES(1039);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1039,3,'c2b-buf','Boneless - Combo 2','Y',130,'Pz');


--INSERT INTO Ente(id) VALUES(1040);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1040,3,'c1a-bbq','Alitas - Combo 1','Y',70,'Pz');
--INSERT INTO Ente(id) VALUES(1041);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1041,3,'c2a-bbq','Alitas - Combo 2','Y',145,'Pz');

--INSERT INTO Ente(id) VALUES(1042);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1042,3,'c1a-buf','Alitas - Combo 1','Y',70,'Pz');
--INSERT INTO Ente(id) VALUES(1043);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1043,3,'c2a-buf','Alitas - Combo 2','Y',145,'Pz');

--INSERT INTO Ente(id) VALUES(1044);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1044,3,'ces-reg','Espagueti Regualar- Chico','Y',45,'Pz');
--INSERT INTO Ente(id) VALUES(1045);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1045,3,'ges-reg','Espagueti Regualar - Grande','Y',85,'Pz');

--INSERT INTO Ente(id) VALUES(1046);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1046,3,'ces-cm','Espagueti Camaron - Chico','Y',65,'Pz');
--INSERT INTO Ente(id) VALUES(1047);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1047,3,'ges-cm','Espagueti Camaron - Grande','Y',115,'Pz');

--INSERT INTO Ente(id) VALUES(1048);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1048,3,'cen-vg','Ensalada Vegetariana - Chico','Y',55,'Pz');
--INSERT INTO Ente(id) VALUES(1049);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1049,3,'gen-vg','Ensalada Vegetariana - Grande','Y',75,'Pz');

--INSERT INTO Ente(id) VALUES(1050);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1050,3,'cen-gr','Ensalada Griega - Chico','Y',55,'Pz');
--INSERT INTO Ente(id) VALUES(1051);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1051,3,'gen-gr','Ensalada Griega - Grande','Y',75,'Pz');

--INSERT INTO Ente(id) VALUES(1052);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1052,3,'cen-po','Ensalada Pollo - Chico','Y',70,'Pz');
--INSERT INTO Ente(id) VALUES(1053);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1053,3,'gen-po','Ensalada Pollo - Grande','Y',95,'Pz');

--INSERT INTO Ente(id) VALUES(1054);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1054,3,'ing-pp','Pepperoni','Y',20,'Pz');
--INSERT INTO Ente(id) VALUES(1055);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1055,3,'ing-qs','Queso','Y',20,'Pz');
--INSERT INTO Ente(id) VALUES(1056);
INSERT INTO CatalogItem(id,catalog,number,brief,active,value,presentation) VALUES(1056,3,'ing-sl','Salami','Y',20,'Pz');

UPDATE CatalogItem SET type = 'service'  WHERE id >= 1011 and id <= 1035;
UPDATE CatalogItem SET station=1  WHERE id >= 1011 and id <= 1035;

UPDATE CatalogItem SET type = 'service'  WHERE id >= 1036 and id <= 1047;
UPDATE CatalogItem SET station=2  WHERE id >= 1036 and id <= 1047;

--INSERT INTO Ente(id) VALUES(1059);
--INSERT INTO Ente(id) VALUES(1060);
INSERT INTO Person(id,name1,name3) VALUES(1059,'Ana','V.');
--INSERT INTO UserManagement(um) VALUES(1060);
INSERT INTO User(id,person,name) VALUES(1060,1059,'ana');
UPDATE User SET pwdtxt='ana' WHERE id = 1060;
UPDATE User SET status='autorizado' WHERE id = 1060;

--INSERT INTO Ente(id) VALUES(1061);
--INSERT INTO Ente(id) VALUES(1062);
INSERT INTO Person(id,name1,name3) VALUES(1061,'Joana','R.');
--INSERT INTO UserManagement(um) VALUES(1062);
INSERT INTO User(id,person,name) VALUES(1062,1061,'cesia');
UPDATE User SET pwdtxt='cesia' WHERE id = 1062;
UPDATE User SET status='autorizado' WHERE id = 1062;

INSERT INTO UserPermission(user,permission) VALUES(1060,1);
INSERT INTO UserPermission(user,permission) VALUES(1062,1);

--INSERT INTO Ente(id) VALUES(1063);
--INSERT INTO Ente(id) VALUES(1064);
INSERT INTO Person(id,name1,name3) VALUES(1063,'Beto','X');
--INSERT INTO UserManagement(um) VALUES(1064);
INSERT INTO User(id,person,name) VALUES(1064,1063,'beto');
UPDATE User SET pwdtxt='beto' WHERE id = 1064;
UPDATE User SET status='autorizado' WHERE id = 1064;

--INSERT INTO Ente(id) VALUES(1065);
--INSERT INTO Ente(id) VALUES(1066);
INSERT INTO Person(id,name1,name3) VALUES(1065,'Maria','X');
--INSERT INTO UserManagement(um) VALUES(1066);
INSERT INTO User(id,person,name) VALUES(1066,1065,'maria');
UPDATE User SET pwdtxt='maria' WHERE id = 1066;
UPDATE User SET status='autorizado' WHERE id = 1066;

INSERT INTO UserPermission(user,permission) VALUES(1064,1);
INSERT INTO UserPermission(user,permission) VALUES(1066,1);

--INSERT INTO Ente(id) VALUES(1067);
--INSERT INTO Ente(id) VALUES(1068);
INSERT INTO Person(id,name1,name3) VALUES(1067,'Azael','R.');
--INSERT INTO UserManagement(um) VALUES(1068);
INSERT INTO User(id,person,name) VALUES(1068,1067,'azael');
UPDATE User SET pwdtxt='azael' WHERE id = 1068;
UPDATE User SET status='autorizado' WHERE id = 1068;

INSERT INTO UserPermission(user,permission) VALUES(1068,1);




--INSERT INTO Ente(id) VALUES(2000);
