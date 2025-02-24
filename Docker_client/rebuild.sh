docker container prune -f
docker rmi chessimg
docker build -t chessimg .
xhost +
docker run --network host -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -e XDG_RUNTIME_DIR=/tmp/runtime-root --device /dev/dri  -it chessimg:latest bash