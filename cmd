docker build -t chess-online-app .


docker run --rm -it \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -e DISPLAY=$DISPLAY \
    chess-online-app

# debuggin
docker run --rm -it chess-online-app bash

