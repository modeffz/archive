#!/bin/bash

echo "Отсчет начался"

timer=${1:-5}
while (( $timer > 0 )); do
    echo "Осталось $timer"
    ((timer--))
    sleep 1
done
