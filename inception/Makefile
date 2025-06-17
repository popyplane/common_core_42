NAME = inception

SHELL := /bin/bash
COMPOSE = docker-compose
COMPOSE_FILE = srcs/docker-compose.yml

up: setup-dirs
	$(COMPOSE) -f $(COMPOSE_FILE) up -d --build

setup-dirs:
	@mkdir -p $(HOME)/data/mariadb
	@mkdir -p $(HOME)/data/wordpress
	
down:
	$(COMPOSE) -f $(COMPOSE_FILE) down

re: fclean up

fclean:
	@echo "--- Starting fclean process ---"
	
	@echo "1. Stopping Docker containers and removing related resources..."
	@$(COMPOSE) -f $(COMPOSE_FILE) down --remove-orphans 2>/dev/null || true

	@echo "2. Cleaning project-specific data directories on the host (bind mounts)..."
	@rm -rf $(HOME)/data/mariadb/* $(HOME)/data/mariadb/.db_initialized 2>/dev/null || true
	@rm -rf $(HOME)/data/wordpress/* $(HOME)/data/wordpress/.wordpress_initialized 2>/dev/null || true # Add for WordPress too, if you use a similar flag
	@rmdir $(HOME)/data/mariadb 2>/dev/null || true
	@rmdir $(HOME)/data/wordpress 2>/dev/null || true

	@echo "3. Attempting to remove project-specific Docker named volumes (if any were created)..."
	@docker volume rm $(notdir $(shell pwd))_mariadb_data 2>/dev/null || true
	@docker volume rm $(notdir $(shell pwd))_wordpress_data 2>/dev/null || true

	@echo "4. Cleaning up local Docker images..."
	@docker rmi $(shell docker images -q --filter "label=com.docker.compose.project=$(notdir $(shell pwd))") 2>/dev/null || true
	@docker rmi $(shell docker images -q --filter "dangling=true") 2>/dev/null || true

	@echo "--- Fclean process complete ---"

.PHONY: up down re fclean
