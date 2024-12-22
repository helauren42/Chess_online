FROM ubuntu:22.04

USER root

RUN apt-get update && apt-get install -y \
    libxcb-xinerama0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxkbcommon-x11-0 \
    libstdc++6 \
    libc6 \
    libgcc-s1 \
    libzstd1 \
    libxcb1 \
    libx11-6 \
    libxkbcommon0 \
    libpoco-dev \
    libfontconfig1 \
    libfreetype6 \
    libegl1 \
    libgl1-mesa-glx \
    libglib2.0-0 \
    && apt-get clean

RUN ldconfig

WORKDIR /app

# Copy necessary files# Copy all libraries from the host to the container
COPY chessApp.AppDir/usr/lib /usr/lib
COPY Qt/build/Desktop_Qt_6_8_1-Release/a.out /app/2/3/a.out
COPY styles.css /app/FrontEnd/styles.css
COPY IMG /app/IMG

# Set environment variables for Qt
ENV QT_PLUGIN_PATH=/usr/lib/qt6/plugins
ENV QT_QPA_PLATFORM_PLUGIN_PATH=/usr/lib/qt6/plugins/platforms
ENV LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/poco:$LD_LIBRARY_PATH

# Run the application
CMD ["/app/2/3/a.out"]
