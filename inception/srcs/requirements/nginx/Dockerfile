FROM	debian:bullseye

RUN		apt-get update && \
		apt-get install -y nginx openssl curl && \
		apt-get clean

RUN		mkdir -p /etc/nginx/ssl
RUN		openssl req -x509 -nodes -days 365 -newkey rsa:4096 -sha256 \
			-out /etc/nginx/ssl/bvieilhe.crt \
			-keyout /etc/nginx/ssl/bvieilhe.key \
			-subj "/C=FR/ST=Paris/L=Paris/O=42 School/OU=bvieilhe/CN=bvieilhe.42.fr/"

COPY	./conf/nginx.conf /etc/nginx/conf.d/default.conf

EXPOSE	443

CMD ["nginx", "-g", "daemon off;"]