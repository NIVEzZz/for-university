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



def calculate_delivery_cost(order, address, customer_type, weight, total_amount, self_delivery, in_town, far_rg):
    delivery_cost = 0.0
    #1.Базовая проверка данных
    if order is None:
        return {"success": False, "cost": delivery_cost, "message": "Заказ не существует"}
    if address is None:
        return {"success": False, "cost": delivery_cost, "message": "Адрес не указан"}
    if weight <= 0:
        return {"success": False, "cost": delivery_cost, "message": "Вес заказа должен быть положительным числом"}

    #4.Акции и ограничения:
    if weight > 50:
        return {"success": False, "cost": delivery_cost, "message": "Максимальный вес для доставки: 50 кг"}
    if total_amount < 1_000:
        return {"success": False, "cost": delivery_cost, "message": "Минимальная стоимость заказа для доставки: 1000 рублей" }
    if self_delivery:
        return {"success": True, "cost": delivery_cost, "message": "Успешно, самовывоз"}
    if total_amount >= 10_000 and not far_rg:
        return {"success": True, "cost": delivery_cost, "message": "Бесплатная доставка при заказе от 10000 рублей (кроме отдаленных регионов)"}

    #3.Логика расчета
    if in_town:
        if weight < 5:
            delivery_cost += 300
        if 5 <= weight <= 10:
            delivery_cost += 500
        if weight > 10:
            delivery_cost = 500 + 50 * (weight - 10)
    if not in_town:
        delivery_cost = 1_000 + 100 * weight

    #2.Специальные условия
    if customer_type == "VIP" and total_amount >= 5_000:
        delivery_cost = 0.0
        return {"success": True, "cost": delivery_cost, "message": "Для VIP клиентов: бесплатная доставка при заказе от 5000 рублей"}
    if customer_type == "NEW":
        delivery_cost *= 0.85
    if far_rg:
        delivery_cost *= 1.2

    return {"success": True, "cost": delivery_cost, "message": "Доставка оформлена"}

#Тесты
# 1. есть ли заказ, есть ли адрес, тип зазазчика, вес, стоимость товара, есть ли самовывоз, есть ли в городе
print("1.", calculate_delivery_cost(1,1,"",0,5_000, 0, 0, 0))
print("2.",calculate_delivery_cost(1,1,"",10,5_000, 1, 0, 0))
print("3.",calculate_delivery_cost(1,1,"VIP",10,5_000, 0, 0, 0))
print("4.",calculate_delivery_cost(1,1,"NEW",10,5_000, 0, 1, 0))
print("5.",calculate_delivery_cost(1,1,"",10,5_000, 0, 0, 1))
print("6.",calculate_delivery_cost(1,1,"",10,10_000, 0, 1, 0))
print("7.",calculate_delivery_cost(1,1,"",51,10_000, 0, 1, 0))
print("8.",calculate_delivery_cost(1,1,"",10,999, 0, 1, 0))

