# EspIot
Designed for 2086, control client app for ESP8266/32

Полная инструкция по установке:

-------------------------------------------------------------------------------------------------
В репозитории есть 2 файла: скетч для ESP и программа на Python 3

Скетч заливается на ESP, в нем необходимо указать:
1) SSID и пароль Вашей WiFi сети
2) Имя для вашей ESP (это переменная esp_id, имя не слишком длинное, на латинице)
3) Тоже на латинице тип датчика (RH, TEMP и т.д.)

Что касается мобильного приложения:
1) В Play Market нужно скачать приложение Termux, по сути это просто командная строка на базе Linux
2) В ней нужно выполнить следующие команды для корректной работы:
    pkg update -y && pkg upgrade -y (Обновление пакетов)
    pkg install git cowsay figlet python -y (обе эти команды выполняются около 2 минут, зависит от ситуации)
    git clone https://github.com/brestyck/EspIot && cd EspIot (Скачивает сам репозиторий)
Эти команды выполняются один раз, далее можно спокойно пользоватся приложением

После установки всех пакетов лучше перезапустить Termux.
Важно! Чтобы его закрыть, нужно в панели уведомлений найти его уведомление и прямо на нём нажать Exit.

После перезапуска нужно зайти в Termux и написать там команду: python EspIot/main.py

Если всё было сделано корректно, появится надпись ESPIOT.

Приложение всё сделает автоматически, не нужна никакая настройка.
Сразу после запуска приложение скажет есть ли доступные устройства.

Затем данные будут выводится циклично каждые 20 секунд.
