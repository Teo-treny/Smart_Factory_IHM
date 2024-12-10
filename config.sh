#! /bin/sh

sudo apt install -y $(cat packages.txt)
sudo cp res/FreeSans.ttf /usr/share/fonts/
