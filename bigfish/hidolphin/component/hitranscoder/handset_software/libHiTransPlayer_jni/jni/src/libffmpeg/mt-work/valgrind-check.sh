#!/bin/bash

valgrind --track-origins=yes --leak-check=full ./ffmpeg -threads 1 -vsync 0 -y -t 30 -i "$1" -an -f null /dev/null

valgrind --track-origins=yes --leak-check=full ./ffmpeg -threads 3 -vsync 0 -y -t 30 -i "$1" -an -f null /dev/null
