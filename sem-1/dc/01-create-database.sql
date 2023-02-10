CREATE DATABASE bloggle CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE bloggle;

CREATE TABLE `User` (
`id` BIGINT NOT NULL AUTO_INCREMENT,
`login` VARCHAR(255) NOT NULL,
`passwordHash` VARCHAR(255) NULL,
`name` VARCHAR(255) NOT NULL,
`creationTime` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY (`id`),
INDEX `index_User_name` (`name`),
INDEX `index_User_creationTime` (`creationTime`),
UNIQUE `unique_User_login` (`login`)
) ENGINE = InnoDB;

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

USE bloggle;

CREATE TABLE `Post` (
`id` BIGINT NOT NULL AUTO_INCREMENT,
`userId` BIGINT NOT NULL,
`title` VARCHAR(255) NOT NULL,
`text` LONGTEXT NOT NULL,
`creationTime` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
PRIMARY KEY (`id`),
INDEX `index_Post_creationTime` (`creationTime`)
) ENGINE = InnoDB;

ALTER TABLE `Post` ADD CONSTRAINT `fk_Post_userId` FOREIGN KEY (`userId`) REFERENCES `User` (`id`);

USE bloggle;

INSERT INTO `Post` (`userId`, `title`, `text`, `creationTime`) VALUES
(4, 'TCO 2021 Algo Semi 2', 'Topcoder Open 2021 Algorithm Semifinal 2 is right around the corner, starting in less than 5 minutes!\r\n\r\nThe competitors are Benq aka bqi343, Petr, scott_wu, neal aka neal_wu, SpyCheese, maroonrk aka maroon_kuri, krijgertje, and Heltion.\r\n\r\nThe top 4 advance to the Finals. The advancers from Semi 1 are ecnerwala, tourist, Um_nik, and ACRush.\r\n\r\nWatch the live broadcast on YouTube and Twitch, featuring Pena, Egor, tourist, and ksun48!\r\n', '2021-11-04 12:00:00'),
(2, 'C++20 Is Released', 'Hello, Codeforces.\r\n\r\nPlease, welcome c++20 support on Codeforces. Yes, it is 64-bit. Thanks to Brecht Sanders: I used his distribution GCC-11.2.0-64 from https://winlibs.com/.\r\n\r\nIf you have installed PBOX, you can add this compiler with the line pbox install gcc11-64-winlibs. Probably, a good idea is to add C:\\Programs\\gcc11-64-winlibs\\bin into the PATH. More about PBOX you can read here.\r\n\r\nI use the compilation command line similar to other GCC installations: g++ -Wall -Wextra -Wconversion -static -DONLINE_JUDGE -Wl,--stack=268435456 -O2 -std=c++20 <source>. The only differences are -std=c++20 and -Wall -Wextra -Wconversion (I plan to use somehow such warnings in Polygon to suggest fixes in uploaded files).\r\n\r\nNow you can use c++20 in your solutions. I\'m not sure there are many features useful in competitive programming. Probably, I\'m wrong. For example, now you can write vector v{vector{1, 2}}; instead of vector<vector<int>> v{vector<int>{1, 2}};. What else is useful? Please, if you are good with modern C++ then write.\r\n\r\nYou might be interested in looking at such a table. Before implementation, I always test every C++ distribution for the efficiency of reading and writing large amounts of data. For example, the latest GCC compiler from MSYS2 is terribly slow in some cases. I don\'t want to use it here. Also, it happens that some specifiers like lld or Lf work unexpectedly. In the table by reference, the second line is the added compiler. The columns correspond to different tests. The cell contains the time of the test execution. If I have time, I will someday publish scripts for testing c++ compiler installations.\r\n\r\nBye for now,\r\n— Mike\r\n', '2021-12-07 16:16:49'),
(4, 'TCO 2021 Algo Semi 1', 'Topcoder Open 2021 Algorithm Semifinal 1 is right around the corner, starting in less than 5 minutes!\r\n\r\nThe competitors are tourist, ecnerwala aka ecnerwal, ACRush, hos.lyric aka lyrically, Um_nik, ko_osaga aka gs14004, PavelKunyavskiy aka kuniavski, and never_giveup aka grumpy_gordon.\r\n\r\nWatch the live broadcast on YouTube and Twitch, featuring scott_wu, Petr, and krijgertje!\r\n', '2021-12-07 18:50:55'),
(4, 'Codeforces Global Round 5', 'It is the fifth round of a new series of Codeforces Global Rounds supported by XTX Markets. The rounds are open for everybody, the rating will be updated for everybody.', '2021-12-09 21:41:52'),
(2, 'Codeforces Global Rounds 2021: Current Results (GR13-GR17)', 'In 2021 (as in 2019 and 2020), with the support of XTX Markets, 6 rounds of the new Codeforces Global Rounds are held: common rounds for both divisions of 7–9 problems each. The duration of the rounds is 2-3 hours, depending on the number and complexity of the problems. All such rounds are rated for all participants. At each such round, 50 brand T-shirts are handed out, and we are happy to give T-shirts to all problem authors.', '2021-12-09 23:50:55'),
(3, 'NEERC-2016 Site in Almaty', 'In 2016 teams form Middle Asia are invited to Almaty to take part in NEERC. The contest will take place in Kazakh-British Technical University. See contact information at http://neerc.ifmo.ru/information/contacts.html#almaty.', '2021-12-11 18:50:55');


USE bloggle;

CREATE TABLE `Role` (
`name` ENUM('WRITER', 'MANAGER', 'ADMIN') NOT NULL,
`canWritePost` BOOLEAN NOT NULL DEFAULT FALSE,
`canViewUsers` BOOLEAN NOT NULL DEFAULT FALSE,
PRIMARY KEY (`name`)
) ENGINE = InnoDB;


USE bloggle;

INSERT INTO `Role` (`name`, `canWritePost`, `canViewUsers`) VALUES
    ('WRITER', TRUE, FALSE),
    ('MANAGER', FALSE, TRUE),
    ('ADMIN', TRUE, TRUE);



USE bloggle;

CREATE TABLE `UserRole` (
`userId` BIGINT NOT NULL,
`roleName` ENUM('WRITER', 'MANAGER', 'ADMIN') NOT NULL,
PRIMARY KEY (`userId`, `roleName`)
) ENGINE = InnoDB;


USE bloggle;

INSERT INTO `UserRole` (`userId`, `roleName`) VALUES
    (2, 'ADMIN'),
    (3, 'MANAGER'),
    (4, 'WRITER'),
    (5, 'WRITER'),
    (5, 'MANAGER');
