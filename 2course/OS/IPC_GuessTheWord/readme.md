# Игра "Отгадай слово"
Сервер по запросу клиента предлагает отгадать слово (выбранное из базы данных сервера, возможно с комментарием), сообщает клиенту количество букв в слове. Клиент за один ход
может предложить одну букву или назвать слово целиком. Если буква содержится в слове, сервер указывает, на каких именно позициях она расположена, в противном случае сообщает об ошибке. Если слово, названное целиком, не совпадает с загаданным, игра прекращается. Количество попыток может быть ограничено. Клиент работает с пользователем-игроком в интерактивном режиме Взаимодействие между клиентом и сервером организовано с помощью сокетов.

# Сервер
По запросу клиента обращается к базе данных и выбирает слово, которое было выбрано меньше всего раз(коэффициент). Если таких слов несколько, то выбирается лексиграфически последнее. Сразу после выбора слова, его коэффициент увеличивается на 1(для выбора разных слов разным клиентам). Далее идёт описанная в условии игра. После окончания игры сервер обновляет базу данных, повторно увеличивая коэффициент выбранного слова в зависимости от результата игры(если игрок выиграл, то коэффициент увеличивается на 2, если проиграл, то на 1)
## База данных
Использована база данных _NoSQL_ - **MongoDB**. В базе данных хранятся слова и коэффициенты. Коэффициенты используются для выбора слова, которое будет загадано клиенту.
Для работы с базой данных используется официальный драйвер и самописный заголовочный файл `mongo.h`, который реализует функции для выбора слова и обновления коэффициентов.
## Сокеты
Для работы с сокетами используется библиотека `sys/socket.h`. Реализована схема 1 сервер - N клиентов. При подключении клиента создаётся новый поток, который обрабатывает запросы клиента. При отключении клиента поток завершается.

# Клиент
Клиент работает в интерактивном режиме. Клиент запускается с двумя аргументами - ip-адресом сервера и номером порта. После запуска клиент подключается к серверу и начинает игру. После окончания игры клиент предлагает пользователю начать новую игру или выйти из программы.
## Сокеты
Для работы с сокетами используется библиотека `sys/socket.h`. Клиент подключается к серверу и ждёт команды для начала игры от пользователя. Если пользователь ввёл команду `start`, то клиент отправляет запрос на сервер и начинает игру. Если пользователь ввёл команду `exit`, то клиент завершает работу.

# Сборка
В репозитории содержится `makefile`, который позволяет собрать проект с помощью команды `make`

# Запуск
Для запуска сервера необходимо выполнить команду `./server <port>`, где `<port>` - номер порта, на котором будет работать сервер.
Для запуска клиента необходимо выполнить команду `./client <ip> <port>`, где `<ip>` - ip-адрес сервера, `<port>` - номер порта, на котором работает сервер.