FROM gcc:latest

WORKDIR /home/

CMD ["/bin/bash"]

# docker build -t gcc:latest .
# docker run -it --rm -v ${PWD}:/home/ gcc:latest