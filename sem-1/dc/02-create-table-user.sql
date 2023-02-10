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
