USE bloggle;

INSERT INTO `Role` (`name`, `canWritePost`, `canViewUsers`) VALUES
    ('WRITER', TRUE, FALSE),
    ('MANAGER', FALSE, TRUE),
    ('ADMIN', TRUE, TRUE);
