#!/bin/sh

# === Load sensitive values from secrets and store them in environment variables ===
export MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
export MYSQL_PASSWORD=$(cat /run/secrets/db_user_password)
export MYSQL_USER=wpuser
export MYSQL_ADMIN_USER=superboss

envsubst < /docker-entrypoint-initdb.d/template.sql > /docker-entrypoint-initdb.d/init.sql
rm -f /docker-entrypoint-initdb.d/template.sql

cat /docker-entrypoint-initdb.d/init.sql

# === Initialize the database if it hasn't been initialized yet ===
if [ ! -f /var/lib/mysql/.db_initialized ]; then
    echo "[entrypoint] First-time database initialization..."

    # Create internal system tables (mysql.*, performance_schema, etc.)
    mysql_install_db --user=mysql --ldata=/var/lib/mysql

    mysqld_safe --skip-networking &
    sleep 5

    mysql -uroot < /docker-entrypoint-initdb.d/init.sql

    mysqladmin shutdown

    touch /var/lib/mysql/.db_initialized
else
    echo "[entrypoint] Database already initialized. Skipping setup."
fi

sed -i "s/^bind-address\s*=.*/bind-address = 0.0.0.0/" /etc/mysql/mariadb.conf.d/50-server.cnf

# === Start MariaDB server in foreground ===
echo "[entrypoint] Starting MariaDB in foreground mode..."
exec mysqld_safe --console
