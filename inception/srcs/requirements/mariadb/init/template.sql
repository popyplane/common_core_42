CREATE DATABASE IF NOT EXISTS wordpress;

-- user -- user@host  --    % = all
-- This user is for WordPress to connect to the database
CREATE USER IF NOT EXISTS 'wpuser'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}'; -- Correct: uses db_user_password
GRANT ALL PRIVILEGES ON wordpress.* TO 'wpuser'@'%';

-- admin user (for your personal access to the database or for specific admin tasks if needed)
-- This user should ideally use a different password than wpuser for security,
-- and should ideally be the same password as the WordPress admin (which uses db_root_password.txt)
CREATE USER IF NOT EXISTS '${MYSQL_ADMIN_USER}'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}'; -- Changed: uses db_root_password
GRANT ALL PRIVILEGES ON wordpress.* TO '${MYSQL_ADMIN_USER}'@'%';

FLUSH PRIVILEGES;