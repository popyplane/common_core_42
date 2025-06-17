FROM debian:bullseye

# Install necessary packages and PHP extensions
RUN apt-get update && apt-get install -y \
    php7.4 \
    php7.4-fpm \
    php7.4-mysql \
    php7.4-mbstring \
    php7.4-gd \
    php7.4-intl \
    php7.4-xml \
    php7.4-soap \
    php7.4-zip \
    wget \
    curl \
    mariadb-client \
    # Install WP-CLI (if not already in a cached layer)
    && curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp \
    && rm -rf /var/lib/apt/lists/* # Clean up apt cache

# Create the PHP-FPM socket directory
RUN mkdir -p /run/php && chown -R www-data:www-data /run/php

# Copy PHP-FPM configuration
COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# Set the working directory to where WordPress will be installed
WORKDIR /var/www/html

# --- REMOVE THESE LINES FROM YOUR DOCKERFILE ---
# RUN curl -O https://wordpress.org/latest.tar.gz && \
#     tar -xzf latest.tar.gz -C /var/www/html --strip-components=1 && \
#     rm latest.tar.gz && \
#     chown -R www-data:www-data /var/www/html
# If you have `VOLUME /var/www/html` also REMOVE IT

# Copy and set permissions for your entrypoint script
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Expose the PHP-FPM port
EXPOSE 9000

# Define the entrypoint and default command
ENTRYPOINT ["/entrypoint.sh"]
CMD ["php-fpm7.4", "-F"]