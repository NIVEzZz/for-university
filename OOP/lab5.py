import json
from collections.abc import Sequence
from dataclasses import asdict, dataclass, field
from typing import Any, Generic, Protocol, TypeVar

T = TypeVar("T")


# 1, 2, 3. Класс User
@dataclass
class User:
    id: int
    name: str
    login: str
    password: str = field(repr=False)  # Нет в str() и repr()
    email: str | None = None
    address: str | None = None

    def __lt__(self, other) -> bool:
        if not isinstance(other, User):
            return NotImplemented
        return self.name.lower() < other.name.lower()


# 4. Протокол для системы CRUD = Create, Read, Update, Delete для произвольного типа данных
class DataRepositoryProtocol(Protocol[T]):
    def get_all(self) -> Sequence[T]: ...
    def get_by_id(self, id: int) -> T | None: ...
    def add(self, item: T) -> None: ...
    def update(self, item: T) -> None: ...
    def delete(self, item: T) -> None: ...


# 5. Протокол для взаимодействия с типом данных User
#                                    чтоб тоже был протоколом ↓
class UserRepositoryProtocol(DataRepositoryProtocol[User], Protocol):
    def get_by_login(self, login: str) -> User | None: ...


# 6. JSON-файл
class JsonDataRepository(Generic[T]):
    def __init__(self, file_path: str, model_cls: type[T]) -> None:
        self._file_path = file_path
        self._model_cls = model_cls
        self._items: list[T] = self._load()

    def _load(self) -> list[T]:
        try:
            with open(self._file_path, "r", encoding="utf-8") as f:
                raw_data: list[dict[str, Any]] = json.load(f)
                return [self._model_cls(**item) for item in raw_data]
        except (FileNotFoundError, json.JSONDecodeError, TypeError):
            return []

    def _save(self) -> None:
        with open(self._file_path, "w", encoding="utf-8") as f:
            json.dump(
                [asdict(item) for item in self._items],
                f,
                ensure_ascii=False, #Для русских букв
                indent=4, #Табуляция
            )
    #Read
    def get_all(self) -> Sequence[T]:
        return list(self._items)

    #Read
    def get_by_id(self, id: int) -> T | None:
        return next((item for item in self._items if getattr(item, "id") == id), None)

    #Create
    def add(self, item: T) -> None:
        if self.get_by_id(getattr(item, "id")) is not None:
            raise ValueError(f"Объект с id={getattr(item, 'id')} уже существует.")
        self._items.append(item)
        self._save()

    #Update
    def update(self, item: T) -> None:
        item_id = getattr(item, "id")
        for idx, existing in enumerate(self._items):
            if getattr(existing, "id") == item_id:
                self._items[idx] = item
                self._save()
                return
        raise ValueError(f"Объект с id={item_id} не найден для обновления.")

    #Delete
    def delete(self, item: T) -> None:
        item_id = getattr(item, "id")
        initial_len = len(self._items)
        self._items = [i for i in self._items if getattr(i, "id") != item_id]
        if len(self._items) == initial_len:
            raise ValueError(f"Объект с id={item_id} не найден для удаления.")
        self._save()


# 7. Реп пользователя
class UserRepository(JsonDataRepository[User]):
    def __init__(self, file_path: str = "users.json") -> None:
        #Конструктор родителя
        super().__init__(file_path, User)

    def get_by_login(self, login: str) -> User | None:
        return next((u for u in self._items if u.login == login), None)


# 8. Протокол
class AuthServiceProtocol(Protocol):
    def sign_in(self, user: User) -> None: ...
    def sign_out(self, user: User) -> None: ...

    @property
    def is_authorized(self) -> bool: ...

    @property
    def current_user(self) -> User | None: ...


# 9. Реализация
class FileAuthService:
    def __init__(
        self,
        user_repo: UserRepositoryProtocol,
        session_file: str = "session.json",
    ) -> None:
        self._user_repo = user_repo
        self._session_file = session_file
        self._current_user: User | None = None
        self._restore_session()


    def _clear_session_file(self) -> None:
        with open(self._session_file, "w", encoding="utf-8") as f:
            json.dump({}, f)

    def _restore_session(self) -> None:
        #Автоматическая авторизация
        try:
            with open(self._session_file, "r", encoding="utf-8") as f:
                data = json.load(f)
                user_id = data.get("user_id")
                if user_id is not None:
                    user = self._user_repo.get_by_id(user_id)
                    if user is not None:
                        self._current_user = user
                    else:
                        self._clear_session_file()
        except (FileNotFoundError, json.JSONDecodeError, OSError, AttributeError):
            self._clear_session_file()

    def _save_session_file(self, user_id: int) -> None:
        with open(self._session_file, "w", encoding="utf-8") as f:
            json.dump({"user_id": user_id}, f, indent=4)

    def sign_in(self, user: User) -> None:
        stored_user = self._user_repo.get_by_login(user.login)
        if stored_user is None or stored_user.password != user.password:
            raise PermissionError("Неверный логин или пароль.")

        self._current_user = stored_user
        self._save_session_file(stored_user.id)

    def sign_out(self, user: User) -> None:
        if self._current_user and self._current_user.id == user.id:
            self._current_user = None
            self._clear_session_file()

    @property
    def is_authorized(self) -> bool:
        return self._current_user is not None

    @property
    def current_user(self) -> User | None:
        return self._current_user


# 10. Демо
users_file = "demo_users.json"
session_file = "demo_session.json"

# Очистка файлов от предыдущих тестов
with open(users_file, "w", encoding="utf-8") as f:
    json.dump([], f)
with open(session_file, "w", encoding="utf-8") as f:
    json.dump({}, f)

print("=== 1. Инициализация и добавление пользователей ===")
user_repo: UserRepositoryProtocol = UserRepository(users_file)
auth_service: AuthServiceProtocol = FileAuthService(user_repo, session_file)

u1 = User(id=1, name="Иван", login="ivan", password="secret_password_1", email="ivan@gmail.ru")
u2 = User(id=2, name="Анна", login="anna", password="secret_password_2", address="Москва")
u3 = User(id=3, name="Борис", login="boris", password="secret_password_3")

user_repo.add(u1)
user_repo.add(u2)
user_repo.add(u3)

print("Добавлен пользователь (пароля не видно):", u1)

sorted_users = sorted(user_repo.get_all())
print("Отсортированный список по имени:", [u.name for u in sorted_users])


print("\n=== 2. Редактирование свойств пользователя ===")
u1.address = "Калининград, ул. Невского"
u1.name = "Иван Алексеевич"
user_repo.update(u1)
print("Обновленный пользователь из БД:", user_repo.get_by_id(1))


print("\n=== 3. Авторизация пользователя ===")
print("Статус до входа:", auth_service.is_authorized)
auth_service.sign_in(u1)
print("Статус после входа:", auth_service.is_authorized)
print("Текущий пользователь:", auth_service.current_user)

print("\n=== 4. Смена текущего пользователя ===")
auth_service.sign_out(u1)
print("После выхода Иван авторизован?:", auth_service.is_authorized)
auth_service.sign_in(u2)
print("Новый текущий пользователь:", auth_service.current_user)

print("\n=== 5. Имитация перезапуска программы (авто авторизация) ===")
# очистка оперативки
del auth_service
del user_repo

new_user_repo: UserRepositoryProtocol = UserRepository(users_file)
new_auth_service: AuthServiceProtocol = FileAuthService(new_user_repo, session_file)

print("Автоматически авторизован при запуске?:", new_auth_service.is_authorized)
print("Восстановленный пользователь:", new_auth_service.current_user)
