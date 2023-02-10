USE bloggle;

CREATE TABLE `UserRole` (
`userId` BIGINT NOT NULL,
`roleName` ENUM('WRITER', 'MANAGER', 'ADMIN') NOT NULL,
PRIMARY KEY (`userId`, `roleName`)
) ENGINE = InnoDB;
