import json
from enum import Enum

# ANSI-команды
ANSI_ESC = "\033["
ANSI_RESET_COLOR = f"{ANSI_ESC}0m"
ANSI_SAVE_CURSOR_POSITION = f"{ANSI_ESC}s"
ANSI_CURSOR_POSITION = f"{ANSI_ESC}{{row}};{{column}}H"
ANSI_CLEAR_SCREEN = f"{ANSI_ESC}2J{ANSI_ESC}H"

class Color(Enum):
    BLACK = f"{ANSI_ESC}30m"
    RED = f"{ANSI_ESC}31m"
    GREEN = f"{ANSI_ESC}32m"
    YELLOW = f"{ANSI_ESC}33m"
    BLUE = f"{ANSI_ESC}34m"
    MAGENTA = f"{ANSI_ESC}35m"
    CYAN = f"{ANSI_ESC}36m"
    WHITE = f"{ANSI_ESC}37m"

#Шрифт + проверка json'а
class Font:
    def __init__(self, filename: str):
        with open(filename, "r", encoding="utf-8") as file:
            data = json.load(file)

        self.height: int = data["height"]
        self.glyphs: dict[str, list[str]] = data["glyphs"]

        if self.height <= 0:
            raise ValueError("Высота шрифта должна быть положительной.")
        if not self.glyphs:
            raise ValueError("В файле шрифта нет шаблонов букв.")

        widths = set()

        for character, rows in self.glyphs.items(): #Возвращает пары (ключ, значение).
            if len(rows) != self.height:
                raise ValueError(
                    f"Для символа {character} указано {len(rows)} строк, "
                    f"ожидалось {self.height}."
                )
            for row in rows:
                widths.add(len(row))
        if len(widths) != 1:
            raise ValueError("Все строки шаблонов должны иметь одинаковую ширину.")

        self.width = widths.pop()

#Это объект, который умеет перехватывать доступ к атрибуту класса.
class _PrintDispatcher:
    def __get__(self, instance, owner):
        if instance is None:
            return owner._print_at
        return instance._print


class Printer:
    print = _PrintDispatcher()

    def __init__(self, color: Color, position: tuple[int, int], symbol: str,font_path: str):
        self._validate_arguments(color, position, symbol)

        self.color = color
        self.position = position
        self.symbol = symbol
        self.font = Font(font_path)

    @staticmethod
    def _validate_arguments(color: Color, position: tuple[int, int], symbol: str) -> None:
        if not isinstance(color, Color):
            raise TypeError("color должен быть значением перечисления Color.")

        if (
            not isinstance(position, tuple)
            or len(position) != 2
            or any(not isinstance(value, int) for value in position)
        ):
            raise TypeError("position должен быть кортежем из двух целых чисел.")

        if position[0] < 1 or position[1] < 1:
            raise ValueError("Координаты ANSI-терминала начинаются с 1.")

        if len(symbol) != 1 or not symbol.isprintable(): #True - если символ в строке доступны для печати.
            raise ValueError("symbol должен быть одним печатным символом.")

    @classmethod
    def _print_at(cls, text: str, color: Color, position: tuple[int, int], symbol: str, font_path: str) -> None:
        cls._validate_arguments(color, position, symbol)
        font = Font(font_path)
        cls._draw(text, color, position, symbol, font)

    def _print(self, text: str) -> None:
        self.position = self._draw(text, self.color, self.position, self.symbol, self.font)

    @staticmethod
    def _draw(text: str, color: Color, position: tuple[int, int], symbol: str, font: Font) -> tuple[int, int]:
        start_row, start_column = position
        lines = text.upper().split("\n")

        for line_number, line in enumerate(lines):
            rows = [""] * font.height

            for character in line:
                if character == " ":
                    glyph = [" " * font.width] * font.height
                else:
                    try:
                        glyph = font.glyphs[character] #list[str]
                    except KeyError:
                        raise ValueError(f"Для символа {character} нет шаблона в файле шрифта.")

                for row_index, glyph_row in enumerate(glyph):
                    rows[row_index] += glyph_row.replace("*", symbol) + " " #Пробел чтоб буквы не склеило

            block_row = start_row + line_number * (font.height + 1) #+1 чтоб был отступ между строками

            for row_index, row_text in enumerate(rows):
                cursor = ANSI_CURSOR_POSITION.format(row = block_row + row_index,column = start_column)
                print(f"{cursor}{color.value}{row_text}{ANSI_RESET_COLOR}", end="")

        next_row = start_row + len(lines) * (font.height + 1)
        return next_row, start_column

    def __enter__(self):
        #print(ANSI_SAVE_CURSOR_POSITION, end="")
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        #print(ANSI_RESET_COLOR, end="")
        #print(ANSI_CURSOR_POSITION.format(row = self.position[0], column = 1), end="")
        return False
