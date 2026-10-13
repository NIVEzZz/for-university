from printer import Color, Printer, ANSI_CLEAR_SCREEN

#Чтоб буквы в буквы не въехали
print(ANSI_CLEAR_SCREEN, end="")

# Статический вызов
Printer.print(
    text="HI",
    color=Color.GREEN,
    position=(1, 1),
    symbol="*",
    font_path="font5.json",
)

#Экземпляр с фиксированным цветом и позицией 
with Printer(
    color=Color.CYAN,
    position=(1, 16),
    symbol="+",
    font_path="font7.json",
) as printer:
    printer.print("HI")
    printer.print("IH")

Printer.print(
    text="HIH\nIHI",
    color=Color.GREEN,
    position=(19, 30),
    symbol="*",
    font_path="font5.json",
)
