FROM debian:bullseye

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

RUN mkdir -p /run/php && chown -R www-data:www-data /run/php

COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf

WORKDIR /tmp

RUN mkdir -p /var/www/html && \
    curl -O https://wordpress.org/latest.tar.gz && \
    tar -xzf latest.tar.gz && \
    cp -r wordpress/* /var/www/html && \
    chown -R www-data:www-data /var/www/html && \
    rm -rf wordpress latest.tar.gz

EXPOSE 9000
    
VOLUME /var/www/html

CMD ["php-fpm7.4", "-F"]