from enum import Enum
from typing import Protocol
import re
import socket

import logging # Для SyslogHandler
from logging.handlers import SysLogHandler as PythonSysLogHandler #SyslogHandler

#from ftplib import FTP
#from io import BytesIO

from datetime import datetime

# 1.
class LogLevel(Enum):
    INFO = "INFO"
    WARN = "WARN"
    ERROR = "ERROR"

# 2.
class LogFilterProtocol(Protocol):
    def match(self, log_level: LogLevel, text: str) -> bool:
        ...

# 3.
class SimpleLogFilter:
    def __init__(self, pattern: str) -> None:
        self.pattern = pattern

    def match(self, log_level: LogLevel, text: str) -> bool:
        return self.pattern in text


class ReLogFilter:
    def __init__(self, pattern: str) -> None:
        self.regular_expressions = re.compile(pattern)

    def match(self, log_level: LogLevel, text: str) -> bool:
        return self.regular_expressions.search(text) is not None


class LevelFilter:
    def __init__(self, level: LogLevel) -> None:
        self.level = level

    def match(self, log_level: LogLevel, text: str) -> bool:
        return log_level == self.level


# 4.
class LogHandlerProtocol(Protocol):
    def handle(self, log_level: LogLevel, text: str) -> None:
        ...


# 5.
class FileHandler:
    def __init__(self, filename: str) -> None:
        self.filename = filename

    def handle(self, log_level: LogLevel, text: str) -> None:
        with open(self.filename, "a", encoding="utf-8") as file:
            file.write(text + "\n")


class SocketHandler:
    def __init__(self, host: str, port: int, timeout: float = 5.0) -> None:
        self.host = host
        self.port = port
        self.timeout = timeout

    def handle(self, log_level: LogLevel, text: str) -> None:
        message = (text + "\n").encode("utf-8")

        with socket.create_connection(
            (self.host, self.port),
            timeout=self.timeout,
        ) as connection:
            connection.sendall(message)


class ConsoleHandler:
    def handle(self, log_level: LogLevel, text: str) -> None:
        print(text)


class SyslogHandler:
    def __init__(self, address=None) -> None:
        if address is None:
            address = ("127.0.0.1", 514)

        self.handler = PythonSysLogHandler(address=address)

# facility × 8 + severity
# severity: INFO → 6, WARN → 4, ERROR → 3
    def handle(self, log_level: LogLevel, text: str) -> None:
        python_levels = {
            LogLevel.INFO: logging.INFO,
            LogLevel.WARN: logging.WARNING,
            LogLevel.ERROR: logging.ERROR,
        }

        record = logging.LogRecord(
            name="application",
            level=python_levels[log_level],
            pathname="",
            lineno=0,
            msg=text,
            args=(),
            exc_info=None,
        )
        self.handler.emit(record)

    def close(self) -> None:
        self.handler.close()


class FtpHandler:
     def __init__(
         self,
         host: str,
         username: str,
         password: str,
         remote_path: str,
         port: int = 21,
         timeout: float = 10.0,
     ) -> None:
         self.host = host
         self.username = username
         self.password = password
         self.remote_path = remote_path
         self.port = port
         self.timeout = timeout

     def handle(self, log_level: LogLevel, text: str) -> None:
         print(
             f"[FtpHandler] вызван метод handle() "
             f"-> загрузка на ftp://{self.host}/{self.remote_path}: {text}"
         )
         # data = BytesIO((text + "\n").encode("utf-8"))
    #
    #     with FTP() as ftp:
    #         ftp.connect(self.host, self.port, timeout=self.timeout)
    #         ftp.login(self.username, self.password)
    #         ftp.storbinary(f"APPE {self.remote_path}", data)


# 6.
class LogFormatterProtocol(Protocol):
    def format(self, log_level: LogLevel, text: str) -> str:
        ...


# 7.
class TimestampFormatter:
    def format(self, log_level: LogLevel, text: str) -> str:
        timestamp = datetime.now().strftime("%Y.%m.%d %H:%M:%S")
        return f"[{log_level.value}] [{timestamp}] {text}"

# 8.
class Logger:
    def __init__(
        self,
        #... означает, что кортеж может содержать любое количество элементов указанного типа
        filters: tuple[LogFilterProtocol, ...] = (),
        formatters: tuple[LogFormatterProtocol, ...] = (),
        handlers: tuple[LogHandlerProtocol, ...] = (),
    ) -> None:
        self.filters = tuple(filters)
        self.formatters = tuple(formatters)
        self.handlers = tuple(handlers)

    def log(self, log_level: LogLevel, text: str) -> None:
        for log_filter in self.filters:
            if not log_filter.match(log_level, text):
                return

        formatted_text = text
        for formatter in self.formatters:
            formatted_text = formatter.format(log_level, formatted_text)

        for handler in self.handlers:
            handler.handle(log_level, formatted_text)

    def log_info(self, text: str) -> None:
        self.log(LogLevel.INFO, text)

    def log_warn(self, text: str) -> None:
        self.log(LogLevel.WARN, text)

    def log_error(self, text: str) -> None:
        self.log(LogLevel.ERROR, text)
