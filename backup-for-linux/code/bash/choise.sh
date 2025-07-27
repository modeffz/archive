#!/bin/bash

echo "Имя"
read name

select choise in "Поздороваться" "Комплимент" "Выйти"; do
    case $REPLY in
        1)
            echo "Приветствую, $name!"
            ;;
        2)
            echo "$name, ты лучший из тех кого я знаю"
            ;;
        3)
            echo "Ну вот и все :("
            break
            ;;
        *)
            echo "Странно..."
            ;;
    esac
done
