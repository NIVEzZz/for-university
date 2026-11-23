from typing import Protocol, TypeVar, Generic, Any


# Базовый класс-маркер для аргументов событий
class EventArgs:
    pass

# 1. Протокол для обработки события

TEventArgs = TypeVar("TEventArgs", bound=EventArgs)

class EventHandler(Protocol[TEventArgs]):
    def handle(self, sender: object, args: TEventArgs) -> None:
        ...


# 2. Обобщенный класс события
# Механизм подписки и отписки от события, а также оповещение всех подписантов.

# Python 3.10
class Event(Generic[TEventArgs]):
    def __init__(self) -> None:
        self._handlers: list[EventHandler[TEventArgs]] = []

    def __iadd__(self, handler: EventHandler[TEventArgs]) -> "Event[TEventArgs]":
        if handler not in self._handlers:
            self._handlers.append(handler)
        return self

    def __isub__(self, handler: EventHandler[TEventArgs]) -> "Event[TEventArgs]":
        if handler in self._handlers:
            self._handlers.remove(handler)
        return self

    def invoke(self, sender: object, args: TEventArgs) -> None:
        for handler in list(self._handlers):
            handler.handle(sender, args)


# 3. Просто структура Лол
#                 |ed|
class PropertyChangedEventArgs(EventArgs):
    def __init__(self, property_name: str) -> None:
        self.property_name = property_name


# 4. Обработчик событий и выводильщик информации в консоль
class ConsoleLoggerHandler:
    def handle(self, sender: object, args: PropertyChangedEventArgs) -> None:
        new_value = getattr(sender, args.property_name, "<значение не найдено>")
        print(
            f"[LOG] Объект {sender.__class__.__name__} ({sender}) "
            f"изменил свойство '{args.property_name}' на '{new_value}'."
        )


# 5. Опять структура Лол
#                 |ing|
class PropertyChangingEventArgs(EventArgs):
    def __init__(
        self, property_name: str, old_value: Any, new_value: Any, can_change: bool = True
        ) -> None:
        self.property_name = property_name
        self.old_value = old_value
        self.new_value = new_value
        self.can_change = can_change


# 6. Валидаторы
class UserValidator:
    def handle(self, sender: object, args: PropertyChangingEventArgs) -> None:
        if args.property_name == "age":
            if not isinstance(args.new_value, int) or not (0 <= args.new_value <= 120):
                print(f"[ВАЛИДАЦИЯ ОТКЛОНЕНА] Некорректный возраст: {args.new_value}")
                args.can_change = False
        elif args.property_name == "username":
            if not isinstance(args.new_value, str) or len(args.new_value.strip()) < 3:
                print(f"[ВАЛИДАЦИЯ ОТКЛОНЕНА] Имя пользователя слишком короткое: '{args.new_value}'")
                args.can_change = False
        elif args.property_name == "email":
            if not isinstance(args.new_value, str) or "@" not in args.new_value:
                print(f"[ВАЛИДАЦИЯ ОТКЛОНЕНА] Некорректный email: '{args.new_value}'")
                args.can_change = False


class ProductValidator:
    def handle(self, sender: object, args: PropertyChangingEventArgs) -> None:
        if args.property_name == "price":
            if not isinstance(args.new_value, (int, float)) or args.new_value <= 0:
                print(f"[ВАЛИДАЦИЯ ОТКЛОНЕНА] Цена должна быть больше 0 (передано: {args.new_value})")
                args.can_change = False
        elif args.property_name == "stock":
            if not isinstance(args.new_value, int) or args.new_value < 0:
                print(f"[ВАЛИДАЦИЯ ОТКЛОНЕНА] Остаток не может быть отрицательным (передано: {args.new_value})")
                args.can_change = False
        elif args.property_name == "title":
            if not isinstance(args.new_value, str) or not args.new_value.strip():
                print("[ВАЛИДАЦИЯ ОТКЛОНЕНА] Название товара не может быть пустым")
                args.can_change = False


# 7.
# Чтоб не писать по 100 раз
class Obj:
    def __init__(self) -> None:
        self.property_changing = Event[PropertyChangingEventArgs]()
        self.property_changed = Event[PropertyChangedEventArgs]()

    def _set_property(self, attr_name: str, prop_name: str, new_value: Any) -> None:
        old_value = getattr(self, attr_name)

        if old_value == new_value:
            return

        changing_args = PropertyChangingEventArgs(prop_name, old_value, new_value)
        self.property_changing.invoke(self, changing_args)

        if not changing_args.can_change:
            return

        setattr(self, attr_name, new_value)

        changed_args = PropertyChangedEventArgs(prop_name)
        self.property_changed.invoke(self, changed_args)


# Два целевых класса (3 поля в каждом)
class User(Obj):
    def __init__(self, username: str, age: int, email: str) -> None:
        super().__init__()
        self._username = username
        self._age = age
        self._email = email

    @property
    def username(self) -> str:
        return self._username

    @username.setter
    def username(self, value: str) -> None:
        self._set_property("_username", "username", value)

    @property
    def age(self) -> int:
        return self._age

    @age.setter
    def age(self, value: int) -> None:
        self._set_property("_age", "age", value)

    @property
    def email(self) -> str:
        return self._email

    @email.setter
    def email(self, value: str) -> None:
        self._set_property("_email", "email", value)

    def __str__(self) -> str:
        return f"User(username='{self._username}', age={self._age}, email='{self._email}')"


class Product(Obj):
    def __init__(self, title: str, price: float, stock: int) -> None:
        super().__init__()
        self._title = title
        self._price = price
        self._stock = stock

    @property
    def title(self) -> str:
        return self._title

    @title.setter
    def title(self, value: str) -> None:
        self._set_property("_title", "title", value)

    @property
    def price(self) -> float:
        return self._price

    @price.setter
    def price(self, value: float) -> None:
        self._set_property("_price", "price", value)

    @property
    def stock(self) -> int:
        return self._stock

    @stock.setter
    def stock(self, value: int) -> None:
        self._set_property("_stock", "stock", value)

    def __str__(self) -> str:
        return f"Product(title='{self._title}', price={self._price}, stock={self._stock})"


# 8. Демо
if __name__ == "__main__":
    # Создание
    user = User(username="Alex", age=25, email="alex@gmail.com")
    laptop = Product(title="Ноутбук", price=75000.0, stock=10)

    c_logger = ConsoleLoggerHandler()
    user_validator = UserValidator()
    product_validator = ProductValidator()

    # Подписка
    user.property_changing += user_validator
    user.property_changed += c_logger

    laptop.property_changing += product_validator
    laptop.property_changed += c_logger

    print("=== 1. УСПЕШНЫЕ ИЗМЕНЕНИЯ ===")
    user.age = 26
    user.username = "Alexander"
    laptop.price = 72000.0
    print(f"Итоговое состояние user: {user}")
    print(f"Итоговое состояние laptop: {laptop}\n")

    print("=== 2. НЕУДАЧНЫЕ ИЗМЕНЕНИЯ ===")
    user.age = -5             # возраст < 0
    user.email = "bad-email"  # нет @
    laptop.stock = -3         # отрицательный остаток
    print(f"Состояние user не изменилось: {user}")
    print(f"Состояние laptop не изменилось: {laptop}\n")

    print("=== 3. ОТПИСКА ОТ СОБЫТИЙ И ПОВТОРНОЕ ИЗМЕНЕНИЕ ===")
    # Без валидки
    user.property_changing -= user_validator
    print("-> Отписали user_validator от user.property_changing")
    user.age = -99
    print(f"Итоговое состояние user: {user}\n")
    # Без логгера
    laptop.property_changed -= c_logger
    print("-> Отписали logger от laptop.property_changed")
    laptop.stock = 5
    print(f"Итоговое состояние laptop: {laptop}")
