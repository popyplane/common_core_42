#!/bin/bash

# Log a message to show the script is starting
echo "[NGINX ENTRYPOINT] Starting..."

# Ensure the web root exists and has correct permissions
# Even if mounted, sometimes mkdir -p can help with initial creation/permissions if not existing on host
mkdir -p /var/www/html
#chown -R www-data:www-data /var/www/html
#chmod -R 755 /var/www/html

# Check for Nginx config syntax before starting
echo "[NGINX ENTRYPOINT] Testing Nginx configuration syntax..."
nginx -t
if [ $? -ne 0 ]; then
    echo "[NGINX ENTRYPOINT] Nginx configuration syntax test failed! Exiting."
    exit 1
fi
echo "[NGINX ENTRYPOINT] Nginx configuration syntax test successful."

# Finally, execute Nginx in the foreground
echo "[NGINX ENTRYPOINT] Executing Nginx in foreground mode..."
exec nginx -g "daemon off;"