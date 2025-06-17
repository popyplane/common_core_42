#!/bin/bash

echo "[NGINX ENTRYPOINT] Starting..."

mkdir -p /var/www/html

echo "[NGINX ENTRYPOINT] Testing Nginx configuration syntax..."
nginx -t
if [ $? -ne 0 ]; then
    echo "[NGINX ENTRYPOINT] Nginx configuration syntax test failed! Exiting."
    exit 1
fi
echo "[NGINX ENTRYPOINT] Nginx configuration syntax test successful."

echo "[NGINX ENTRYPOINT] Executing Nginx in foreground mode..."
exec nginx -g "daemon off;"