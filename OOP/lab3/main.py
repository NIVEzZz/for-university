import tempfile
from log import *
# match()
print("SimpleLogFilter:", SimpleLogFilter("disk").match(LogLevel.INFO, "disk space low"))
print("SimpleLogFilter:", SimpleLogFilter("пев").match(LogLevel.INFO, "disk space low"))

print("ReLogFilter:", ReLogFilter(r"ERROR|WARN").match(LogLevel.WARN, "WARN: slow response"))
print("ReLogFilter:", ReLogFilter(r"ERROR|INFO").match(LogLevel.WARN, "WARN: slow response"))

print("LevelFilter:", LevelFilter(LogLevel.ERROR).match(LogLevel.ERROR, "something failed"))
print("LevelFilter:", LevelFilter(LogLevel.INFO).match(LogLevel.ERROR, "something failed"))

# Время
formatter = TimestampFormatter()
print("TimestampFormatter:", formatter.format(LogLevel.INFO, "Пример сообщения"))

# консоль + файл + часть logger
with tempfile.TemporaryDirectory() as directory:
    filename = f"{directory}/demo.log"

    logger = Logger(
        formatters=(TimestampFormatter(),),
        handlers=(ConsoleHandler(), FileHandler(filename)),
    )

    logger.log_info("Приложение запущено")
    logger.log_warn("Заканчивается место на диске")
    logger.log_error("Не удалось сохранить данные")

    print("\nСодержимое файла:")
    with open(filename, encoding="utf-8") as file:
        print(file.read(), end="")

# фильтр logger
error_logger = Logger(
    filters=(LevelFilter(LogLevel.ERROR),),
    formatters=(TimestampFormatter(),),
    handlers=(ConsoleHandler(),),
)
error_logger.log_info("Это сообщение будет отфильтровано")
print()
error_logger.log_error("Это сообщение будет выведено")


# TCP (Socket)
socket_logger = Logger(
    formatters=(TimestampFormatter(),),
    handlers=(SocketHandler("127.0.0.1", 5515),),
)
socket_logger.log_info("Проверка TCP")

# FTP
ftp_handler = FtpHandler(
    host="ftp.example.com",
    username="user",
    password="password",
    remote_path="/logs/app.log",
)
ftp_handler.handle(LogLevel.INFO, "Тестовое FTP-сообщение")

# Syslog
syslog_handler = SyslogHandler(address=("127.0.0.1", 5514))
syslog_handler.handle(LogLevel.INFO, "Проверка syslog")
syslog_handler.close()
print("\nСообщение передано обработчику syslog.")
