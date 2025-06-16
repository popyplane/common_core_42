FROM debian:bullseye

# installing dependencies, giving them the right rights
RUN apt-get update && apt-get install -y mariadb-server gettext && \
    rm -rf /var/lib/apt/lists/* && \
    rm -rf /var/lib/mysql/* && \
    mkdir -p /var/run/mysqld && \
    chown -R mysql:mysql /var/run/mysqld && \
    chmod 777 /var/run/mysqld

# copying the template inside the containers file that launch them all at start
COPY init/ /docker-entrypoint-initdb.d/

# setting our own entrypoint and allox it to exec
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# specify port to receive requests
EXPOSE 3306

# specify where the database is stored
VOLUME /var/lib/mysql

# setting up our entrypoint
ENTRYPOINT ["/entrypoint.sh"]