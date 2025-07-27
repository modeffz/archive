#!/bin/bash

echo "Обновление пакетов"
timer=${1:-5}
while (( timer > 0)); do
    echo "$timer..."
    sleep 1
    ((timer--))
done

sudo pacman -Suy

echo "Готово"
