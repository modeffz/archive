#!/bin/bash

echo "Имя пользователя"
read userName

if [[ $userName == "modeffz" || $userName == "Modeffz" ]]; then
    echo "Владелец"
else
    echo "Ну и кто ты?"
    read guestName
    echo "Пошел отсюда, $guestName"
fi
