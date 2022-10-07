
-- MUPOSYS


--MIAS
INSERT INTO Entities(id) VALUES(1001);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1001,13,'ppp','Personal - Peperoni');
INSERT INTO Entities(id) VALUES(1002);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1002,13,'cpp','Chica - Peperoni');
INSERT INTO Entities(id) VALUES(1003);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1003,13,'mpp','Mediana - Peperoni');
INSERT INTO Entities(id) VALUES(1004);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1004,13,'gpp','Grande - Peperoni');
INSERT INTO Entities(id) VALUES(1005);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1005,13,'fpp','Familiar - Peperoni');


INSERT INTO Entities(id) VALUES(1006);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1006,13,'phw','Personal - Hawaina');
INSERT INTO Entities(id) VALUES(1007);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1007,13,'chw','Chica - Hawaina');
INSERT INTO Entities(id) VALUES(1008);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1008,13,'mhw','Mediana - Hawaina');
INSERT INTO Entities(id) VALUES(1009);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1009,13,'ghw','Grande - Hawaina');
INSERT INTO Entities(id) VALUES(1010);
INSERT INTO Cataloging(id,catalog,number_id,name) VALUES(1010,13,'fhw','Familiar - Hawaina');

UPDATE Cataloging SET active = 'Y'  WHERE id = 1001;
UPDATE Cataloging SET value = 75 WHERE id = 1001;
UPDATE Cataloging SET active = 'Y'  WHERE id = 1002;
UPDATE Cataloging SET value = 95 WHERE id = 1002;
UPDATE Cataloging SET active = 'Y'  WHERE id = 1003;
UPDATE Cataloging SET value = 135 WHERE id = 1003;
UPDATE Cataloging SET active = 'Y'  WHERE id = 1004;
UPDATE Cataloging SET value = 175 WHERE id = 1004;
UPDATE Cataloging SET active = 'Y'  WHERE id = 1005;
UPDATE Cataloging SET value = 195 WHERE id = 1005;


