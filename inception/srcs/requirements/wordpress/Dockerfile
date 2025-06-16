FROM debian:bullseye

# installing dependencies
RUN apt-get update && apt-get install -y \
    php7.4 \
    php7.4-fpm \
    php7.4-mysql \
    php7.4-gd \
    php7.4-xml \
    php7.4-mbstring \
    php7.4-curl \
    php7.4-zip \
    php7.4-intl \
    curl \
    netcat \
    tar && \
    apt-get clean

# providing proper environment and permissions to php-fpm
RUN mkdir -p /run/php && chown -R www-data:www-data /run/php

# copying our own conf
COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

# setting a new temporary working dir
WORKDIR /tmp

# downloading wordpress and install it
RUN mkdir -p /var/www/html && \
    curl -O https://wordpress.org/latest.tar.gz && \
    tar -xzf latest.tar.gz && \
    cp -r wordpress/* /var/www/html && \
    chown -R www-data:www-data /var/www/html && \
    rm -rf wordpress latest.tar.gz

# downloading wp-cli
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

# copying our entry script and enable execution
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# specify port to send requests
EXPOSE 9000
        
# specify web content storage
VOLUME /var/www/html
    
# executing entrypoint to start container
ENTRYPOINT ["/entrypoint.sh"]