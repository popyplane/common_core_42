#!/bin/bash

WP_PATH="/var/www/html"
WP_CONFIG_FILE="${WP_PATH}/wp-config.php"

mkdir -p "${WP_PATH}"
chown -R www-data:www-data "${WP_PATH}"

# check if wordpress is already installed
if [ ! -f "${WP_CONFIG_FILE}" ]; then
    echo "[entrypoint] WordPress not found in volume. Starting fresh installation..."

    cd /tmp

    # download wordpress
    echo "[entrypoint] Downloading WordPress..."
    wget -q https://wordpress.org/latest.tar.gz

    # extract to the volume
    echo "[entrypoint] Extracting WordPress to ${WP_PATH}..."
    tar -xzf latest.tar.gz -C "${WP_PATH}" --strip-components=1

    # cleanup
    rm latest.tar.gz
    cd "${WP_PATH}"
    echo "[entrypoint] WordPress files extracted."

    # --- wait for mariaDB to be ready ---
    echo "[entrypoint] Waiting for MariaDB (host: mariadb) to be ready..."
    MAX_RETRIES=60
    COUNT=0
    
    while ! mariadb -h mariadb -u ${MYSQL_USER} -p${MYSQL_PASSWORD} -e "SELECT 1;" > /dev/null 2>&1; do
        sleep 1
        COUNT=$((COUNT+1))
        if [ $COUNT -ge $MAX_RETRIES ]; then
            echo "[entrypoint] MariaDB did not become ready after ${MAX_RETRIES} seconds. Exiting WordPress setup."
            exit 1
        fi
    done
    echo "[entrypoint] MariaDB is ready."

    # --- configure and install wordpress ---
    echo "[entrypoint] Configuring wp-config.php..."
    wp config create \
        --allow-root \
        --dbname=${MYSQL_DATABASE} \
        --dbuser=${MYSQL_USER} \
        --dbpass=${MYSQL_PASSWORD} \
        --dbhost=mariadb \
        --path="${WP_PATH}"

    echo "[entrypoint] Installing WordPress core..."
    wp core install \
        --allow-root \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user=${WP_ADMIN_USER} \
        --admin_password=${WP_ADMIN_PASSWORD} \
        --admin_email=${WP_ADMIN_EMAIL} \
        --path="${WP_PATH}"

    echo "[entrypoint] Creating a regular WordPress user..."
    wp user create \
        --allow-root \
        ${WP_USER} ${WP_USER_EMAIL} \
        --user_pass=${WP_USER_PASSWORD} \
        --role=author \
        --path="${WP_PATH}"

    echo "[entrypoint] WordPress installation and configuration complete."

else
    echo "[entrypoint] WordPress already installed in volume. Skipping setup."
fi

echo "[entrypoint] Setting final permissions for ${WP_PATH}..."
chown -R www-data:www-data "${WP_PATH}"

echo "[entrypoint] Starting php-fpm..."
exec "$@" # (php-fpm7.4 -F)