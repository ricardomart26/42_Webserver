
IMAGE_NAME = nginx_img
CONTAINER_NAME = nginx_con

all: build run

build: 
	docker build -t $(IMAGE_NAME) .

run:
	docker run -it -d -p 800:80 --name=$(CONTAINER_NAME) $(IMAGE_NAME)

exec:
	docker exec -it $(CONTAINER_NAME) bash

stop:
	docker stop $(CONTAINER_NAME)

rm:
	docker rm $(CONTAINER_NAME)


clean: stop rm

fclean: clean
	docker image rm $(IMAGE_NAME)

re: clean all

