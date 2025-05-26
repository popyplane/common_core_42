NAME = inception

SHELL := /bin/bash
COMPOSE = docker-compose
COMPOSE_FILE = srcs/docker-compose.yml

up:
	$(COMPOSE) -f $(COMPOSE_FILE) up -d --build

down:
	$(COMPOSE) -f $(COMPOSE_FILE) down

re: fclean up

fclean:
	$(COMPOSE) -f $(COMPOSE_FILE) down --volumes --remove-orphans
	docker system prune -af
	docker volume prune -f
	docker network prune -f

.PHONY: up down re fclean
