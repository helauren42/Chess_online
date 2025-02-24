FROM fedora:latest

WORKDIR /app

COPY BackEnd/ BackEnd/
COPY FrontEnd/ FrontEnd/
COPY MyCppLib/ MyCppLib/ 
COPY launch.sh .

RUN chmod u+x launch.sh

RUN dnf update -y \
        && dnf upgrade -y \
        && dnf install qt6-qtbase-devel -y \
        && dnf install qt6-qtcharts-devel -y \
        && dnf install qt6-qttools-devel -y \
        && dnf install qt6-qtmultimedia-devel -y \
        && dnf install qt6-qtwebsockets-devel -y \
        && dnf install kvantum -y \
        && dnf install poco-devel -y \
        && dnf install nlohmann-json-devel -y

ENV QT_STYLE_OVERRIDE=kvantum

CMD [ "launch.sh" ]
