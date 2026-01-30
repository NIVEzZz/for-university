def check_user_access(user,resource):
    if user is None:
        return "Пользователь не найден"
    if not user.is_active:
        return "Пользователь не активен"
    if not user.has_permission(resource):
        return "Недостаточно прав"
    if resource.is_maintenance:
        return "Ресурс на техническом обсулживании"
    return "Доступ разрешен"

def calculate_discount(order):
    if order.total_amount <= 0:
        return 0
    if order.customer_type != ("VIP" or "REGULAR"):
        return 0
    if order.customer_type == "VIP":
        if order.total_amount > 10_000:
            return order.total_amount * 0.20
        return order.total_amount * 0.15
    if order.customer_type == "REGULAR":
        if order.total_amount > 5_000:
            return order.total_amount * 0.10
        return order.total_amount * 0.05

def process_payment(transaction):
    if transaction.amount <= 0:
        return {"status": "error", "message": "Сумма должна быть положительной"}
    if not transaction.is_valid():
        return {"status": "error", "message": "Невалидная транзакция"}
    if not transaction.sender.has_funds(transaction.amount):
        return {"status": "error", "message": "Недостаточно стредств"}
    if not transaction.receiver.can_receive_payment():
        return {"status": "error", "message": "Получатель не может принять платеж"}
    transaction.execute()
    return {"status": "error", "message": "Платеж выполнен"}



def calculate_delivery_cost(order, customer, address, weight):
    #1.Базовая проверка данных
    if order is None:
        return {"success": False, "cost": 0.0, "message": "Заказ не существует"}
    if address is None:
        return {"success": False, "cost": 0.0, "message": "Адрес не указан"}
    if order.weight <= 0:
        return {"success": False, "cost": 0.0, "message": "Вес заказа должен быть положительным числом"}

    #3.Логика расчета
    if order.self_delivery:
        return order.total_amount
    if address.in_town:
        if weight < 5:
            return order.total_amount + 300
        if 5 <= weight <= 10:
            return order.total_amount + 500
        if weight > 10:
            return order.total_amount + 500 + 50 * (weight - 10)
    if not address.in_town:
        return

    #2.Специальные условия
    if customer.type == "VIP" and order.total_amount >= 5_000:
        return {"success": True, "cost": order.total_amount, "message": ""}
    if customer.type == "NEW":


    return {
    "success": bool,
    "cost": float,
    "message": str
}
