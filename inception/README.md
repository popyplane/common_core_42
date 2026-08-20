# Inception

A small multi-container infrastructure built from scratch with Docker: NGINX, WordPress, and MariaDB, each running in a custom-built container with no pre-built images from Docker Hub. 42 School system administration project.

## Architecture

```
                 :443 (TLS only)
                     |
                 [ nginx ]
                     |  FastCGI :9000
              [ wordpress ]
                     |
               [ mariadb ] :3306
```

All three services run on a single custom bridge network. Two named volumes (bind-mounted to `~/data/mariadb` and `~/data/wordpress` on the host) persist the database and WordPress files across `docker-compose down`/`up` cycles.

## Services

**nginx**
Built on `debian:bullseye`. Generates a self-signed 4096-bit RSA certificate at build time, restricted to TLSv1.2/TLSv1.3 with a hardened cipher list. Only port 443 is exposed; HTTP is not served. `.php` requests are proxied to `wordpress:9000` over FastCGI. The entrypoint runs `nginx -t` to validate the config before starting.

**wordpress**
PHP-FPM 7.4 with the extensions WordPress needs (mysql, mbstring, gd, intl, xml, soap, zip), plus `wp-cli` for automation. On first boot, the entrypoint downloads WordPress core into the persistent volume, polls MariaDB until it's ready, then uses `wp-cli` to non-interactively configure `wp-config.php`, run the install, and create both an admin user and a second non-admin author, entirely from environment variables.

**mariadb**
Built on `debian:bullseye`, `mysqld` is started once with `--skip-networking` on a Unix socket to run first-time initialization (root password, `wordpress` database, application user) via a heredoc SQL script, gated by a sentinel file so it only runs once. It's then restarted in the foreground with networking enabled.

## Usage

```bash
make up      # creates host bind-mount directories, builds and starts everything
make down    # stops the stack
make re      # full clean rebuild
make fclean  # stops everything, wipes persisted data and images
```

## Known limitation

A `secrets/` directory exists in the repo (intended for Docker Secrets) but isn't currently wired into `docker-compose.yml`. Credentials are passed via a plain `.env` file instead. Documented here rather than silently left as-is: wiring up proper Docker Secrets is the natural next improvement.
