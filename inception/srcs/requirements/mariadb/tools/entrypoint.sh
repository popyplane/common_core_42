#!/bin/bash

# load environment variables
MYSQL_ROOT_PASSWORD=${MYSQL_ROOT_PASSWORD}
MYSQL_PASSWORD=${MYSQL_PASSWORD}
MYSQL_DATABASE=${MYSQL_DATABASE}
MYSQL_USER=${MYSQL_USER}
MYSQL_ADMIN_USER=${MYSQL_ADMIN_USER}

# paths
MARIADB_DATA_DIR="/var/lib/mysql"
INIT_FLAG="${MARIADB_DATA_DIR}/.db_initialized"
MYSQL_SOCKET="/run/mysqld/mysqld.sock"

if [ ! -f "$INIT_FLAG" ]; then
    echo "[entrypoint] First-time database initialization..."

    echo "[entrypoint] Initializing the MariaDB database using mysql_install_db..."
    mysql_install_db --datadir="${MARIADB_DATA_DIR}" --user=mysql --skip-test-db

    echo "[entrypoint] Starting MariaDB in background for initialization..."
    /usr/sbin/mysqld --datadir="${MARIADB_DATA_DIR}" --skip-networking --socket="${MYSQL_SOCKET}" &
    MYSQLD_PID=$! # Get PID of mysqld

    echo "[entrypoint] Waiting for MariaDB to be ready for initialization (via socket)..."
    for i in $(seq 1 60); do
        if mysqladmin -u root -S "${MYSQL_SOCKET}" ping >/dev/null 2>&1; then
            break
        fi
        sleep 1
    done

    if ! mysqladmin -u root -S "${MYSQL_SOCKET}" ping >/dev/null 2>&1; then
        echo "[entrypoint] MariaDB did not become ready for initialization after 60 seconds. Exiting."
        kill ${MYSQLD_PID}
        exit 1
    fi
    echo "[entrypoint] MariaDB is ready for initialization."

    echo "[entrypoint] Generating and executing initial SQL script..."

    cat <<EOF > /tmp/init.sql
-- Set root password
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
FLUSH PRIVILEGES;

-- Create database
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;

-- Create and grant privileges for wordpress user
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';

-- Create and grant privileges for admin user
CREATE USER IF NOT EXISTS '${MYSQL_ADMIN_USER}'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_ADMIN_USER}'@'%';

FLUSH PRIVILEGES;
EOF

    mysql -u root -S "${MYSQL_SOCKET}" < /tmp/init.sql

    if [ $? -ne 0 ]; then
        echo "[entrypoint] ERROR: SQL initialization script failed. Check /tmp/init.sql for syntax issues or MariaDB logs for errors."
        rm -f /tmp/init.sql # cleanup the temporary file
        kill ${MYSQLD_PID}  # stop mariaDB process
        exit 1
    fi

    rm -f /tmp/init.sql # cleanup the temporary file
    echo "[entrypoint] SQL initialization complete."

    echo "[entrypoint] Shutting down MariaDB after initialization..."
    mysqladmin -u root -p"${MYSQL_ROOT_PASSWORD}" -S "${MYSQL_SOCKET}" shutdown
    wait ${MYSQLD_PID} # Wait for mysqld to truly exit
    echo "[entrypoint] MariaDB shut down cleanly."

    touch "$INIT_FLAG"
    echo "[entrypoint] Initialization flag created: $INIT_FLAG"

else
    echo "[entrypoint] Database already initialized. Skipping setup."
fi

# start mariaDB in foreground mode
echo "[entrypoint] Starting MariaDB in foreground mode for regular operation..."
exec /usr/sbin/mysqld --datadir="${MARIADB_DATA_DIR}" --bind-address=0.0.0.0 --default-authentication-plugin=mysql_native_password