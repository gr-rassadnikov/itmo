USE bloggle;

INSERT INTO `User` (`login`, `passwordHash`, `name`, `creationTime`) VALUES ('system', NULL, 'System', NOW());

INSERT INTO `User` (`login`, `passwordHash`, `name`, `creationTime`) VALUES ('mikemirzayanov', NULL, 'Mike Mirzayanov', NOW());
UPDATE User SET passwordHash=SHA2(CONCAT(id, 'bac54d5221048f7a', 'qwerty'), 256) WHERE login='mikemirzayanov'; 

INSERT INTO `User` (`login`, `passwordHash`, `name`, `creationTime`) VALUES ('andrewzta', NULL, 'Andrew Stankevich', NOW());
UPDATE User SET passwordHash=SHA2(CONCAT(id, 'bac54d5221048f7a', 'qwerty'), 256) WHERE login='andrewzta'; 

INSERT INTO `User` (`login`, `passwordHash`, `name`, `creationTime`) VALUES ('tourist', NULL, 'Gennady Korotkevich', NOW());
UPDATE User SET passwordHash=SHA2(CONCAT(id, 'bac54d5221048f7a', 'qwerty'), 256) WHERE login='tourist'; 

INSERT INTO `User` (`login`, `passwordHash`, `name`, `creationTime`) VALUES ('pashka', NULL, 'Pavel Mavrin', NOW());
UPDATE User SET passwordHash=SHA2(CONCAT(id, 'bac54d5221048f7a', 'qwerty'), 256) WHERE login='pashka'; 
