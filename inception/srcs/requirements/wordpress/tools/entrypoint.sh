#!/bin/bash

# Export environment variables for wp-cli and other commands
# Renamed to match wp-cli's expected environment variable names for DB connection
export DB_NAME="${MYSQL_DATABASE}"    # Renamed from MYSQL_DATABASE
export DB_USER="${MYSQL_USER}"        # Renamed from MYSQL_USER
# DB_PASSWORD will be read from secret later, so no need to export it from .env directly
export DOMAIN_NAME="${DOMAIN_NAME}"
export WP_TITLE="${WP_TITLE}"
export WP_ADMIN_USER="${MYSQL_ADMIN_USER}" # Renamed from MYSQL_ADMIN_USER for clarity in WP context
export WP_ADMIN_EMAIL="${WP_ADMIN_EMAIL}"

# --- Wait for MariaDB to be ready ---
echo "[ENTRYPOINT] Waiting for MariaDB to be ready..."
while ! nc -z mariadb 3306; do
    sleep 1
done
echo "[ENTRYPOINT] MariaDB is ready!"

WP_PATH="/var/www/html"
WP_CONFIG_FILE="${WP_PATH}/wp-config.php"

# Read passwords from secrets files
DB_USER_PASSWORD=$(cat /run/secrets/db_user_password)
DB_ROOT_PASSWORD=$(cat /run/secrets/db_root_password) # Used for WP admin password during core install

# --- wp-config.php creation ---
# Check if wp-config.php exists. If not, create it using environment variables.
if [ ! -f "$WP_CONFIG_FILE" ]; then
    echo "[ENTRYPOINT] Creating wp-config.php using environment variables..."
    # wp config create will automatically pick up DB_NAME, DB_USER, DB_HOST from environment
    # DB_PASSWORD still needs to be passed via --dbpass as it's from a secret file, not a simple env var
    wp config create \
        --allow-root \
        --dbname="${DB_NAME}" \
        --dbuser="${DB_USER}" \
        --dbhost="mariadb" \
        --dbpass="${DB_USER_PASSWORD}" \
        --dbcharset="utf8" \
        --dbcollate="utf8_general_ci" \
        --path="$WP_PATH"
    echo "[ENTRYPOINT] wp-config.php created."

    echo "[ENTRYPOINT] Generating WordPress security keys..."
    wp config shuffle-salts --allow-root --path="$WP_PATH"
    echo "[ENTRYPOINT] WordPress security keys set."
else
    echo "[ENTRYPOINT] wp-config.php already exists. Skipping creation."
fi


# --- WordPress core installation logic ---
# Check if WordPress is already installed in the database
# This is the most reliable check for a complete WordPress setup
# Passwords for --dbuser and --dbpass in 'is-installed' command are needed if not in wp-config.php or env
if ! wp core is-installed --allow-root --path="$WP_PATH"; then
    echo "[ENTRYPOINT] WordPress is not installed. Proceeding with core installation."

    # Perform core installation, creating the initial admin user
    wp core install \
        --allow-root \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${DB_ROOT_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --path="${WP_PATH}"
    echo "[ENTRYPOINT] WordPress core installation complete!"

    # Create the standard WordPress user ONLY if they don't exist
    echo "[ENTRYPOINT] Checking for and creating standard WordPress user '${MYSQL_USER}'..."
    # Note: Use MYSQL_USER from .env for the standard user as this doesn't conflict with WP_ADMIN_USER
    if ! wp user get "${MYSQL_USER}" --field=ID --allow-root --path="$WP_PATH" &>/dev/null; then
        wp user create "${MYSQL_USER}" "${WP_ADMIN_EMAIL}" \
            --allow-root \
            --user_pass="${DB_USER_PASSWORD}" \
            --role=author \
            --path="${WP_PATH}"
        echo "[ENTRYPOINT] Standard WordPress user '${MYSQL_USER}' created."
    else
        echo "[ENTRYPOINT] Standard WordPress user '${MYSQL_USER}' already exists. Skipping creation."
    fi

else
    echo "[ENTRYPOINT] WordPress is already installed. Skipping core installation and user creation."
fi

echo "[ENTRYPOINT] Starting PHP-FPM..."
# Start PHP-FPM in the foreground
exec /usr/sbin/php-fpm7.4 -F