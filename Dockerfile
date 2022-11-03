FROM gcc:latest

WORKDIR /home/

CMD ["/bin/bash"]

# docker build -t gcc:latest .
# docker run --name vs-gcc -it --rm -v ${PWD}:/home/ gcc:latest
# docker exec -it vs-gcc /bin/bash