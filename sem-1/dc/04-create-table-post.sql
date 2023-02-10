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

CREATE TABLE `Comment` (
`id` BIGINT NOT NULL AUTO_INCREMENT, 
`postId` BIGINT NOT NULL , 
`userId` BIGINT NOT NULL , 
`text` LONGTEXT NOT NULL , 
`creationTime` DATETIME NOT NULL ,
 PRIMARY KEY (`id`),
INDEX `index_Post_creationTime` (`creationTime`)
) ENGINE = InnoDB;

ALTER TABLE `Comment` ADD CONSTRAINT `fk_Comment_userId` FOREIGN KEY (`userId`) REFERENCES `User` (`id`);

ALTER TABLE `Comment` ADD CONSTRAINT `fk_Comment_postId` FOREIGN KEY (`postId`) REFERENCES `Post` (`id`);