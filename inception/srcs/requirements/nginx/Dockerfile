FROM    debian:bullseye

# Install dependencies and delete cache
RUN     apt-get update && \
        apt-get install -y nginx openssl curl && \
        service nginx stop || true && \
        update-rc.d nginx disable || true && \
        apt-get clean

# Creating a folder to store ssl key and certificate
RUN     mkdir -p /etc/nginx/ssl
RUN     openssl req -x509 -nodes -days 365 -newkey rsa:4096 -sha256 \
            -out /etc/nginx/ssl/bvieilhe.crt \
            -keyout /etc/nginx/ssl/bvieilhe.key \
            -subj "/C=FR/ST=Paris/L=Paris/O=42 School/OU=bvieilhe/CN=bvieilhe.42.fr/"

# Copying our own conf
COPY    ./conf/nginx.conf /etc/nginx/conf.d/default.conf

# --- ADD THESE LINES FOR THE NEW ENTRYPOINT SCRIPT ---
COPY    tools/entrypoint.sh /entrypoint.sh
RUN     chmod +x /entrypoint.sh
# ----------------------------------------------------

# Specify which port to connect
EXPOSE  443

# Change CMD to ENTRYPOINT to execute our script
ENTRYPOINT ["/entrypoint.sh"]
# Remove the old CMD line, it's replaced by ENTRYPOINT
# CMD echo "Attempting to start NGINX now..." && nginx -g "daemon off;"