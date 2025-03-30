# ИНСТРУКЦИЯ К ЗАПУСКУ ТЕСТОВ

## НАДО УСТАНОВИТЬ ЛИБУ check.h 

**установка либы инструкция от некоего Фони**
#### если линуха там просто

`sudo apt update`
`sudo apt install check`

`ls /usr/include/check.h` проверить если либа 
доступность можно чекнуть `ldconfig -p | grep check`

#### для установки чек на школьный мак
сначала ставишь brew
https://21-school-by-students.notion.site/Homebrew-goinfre-af3acfc9cfee424481a8a08c204ff272

потом это
`curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh`

потом

`brew install check`

`brew install gcc` // если вопрос зачем gcc я хз, взял из чатика в волне 22, без этого установить не пробовал

`brew install pkg-config`

`pkg-config --cflags --libs check` **вообще полезная вещь, на убунте имба**

эта команда тебе что-то выводит. один путь с флагом I, другой с флагом L 

дальше заходишь в .zshrc (я делал через vim, можно через нано)

`nano .zshrc` (в главной папке) 

и вставляешь две строки

`export C_INCLUDE_PATH= export C_INCLUDE_PATH=` то, что было в той команде после I

`export LIBRARY_PATH=` то, что было в той команде после L


пример:
export C_INCLUDE_PATH=/opt/goinfre/asleyter/homebrew/Cellar/check/0.15.2/include
export LIBRARY_PATH=/opt/goinfre/asleyter/homebrew/Cellar/check/0.15.2/lib



дальше вводим в терминал:
`source .zshrc`


перезапустить терминал 
(не забыть после этого прописать 3 команды для homebrew, если не сделали z.профиль)
вы восхитительны c:

## чтобы запускать gcov_report
- установите 
`gcov`
`lcov`
`genhtml`

## дальше в мейке смотрите по целям и запускайте

# P.S. 
- основные функции должны распологаться в `src`
- ну или пути в мейке поменяйте как вам по кайфу