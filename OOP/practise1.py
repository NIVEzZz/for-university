import math

class Point2D:

    _total_points_count = 0

    def __init__ (self, x:float, y:float):
        if not(x is float or x is int) or not(y is float or y is int):
            return f"Ошибка, данные не корректны"
        self.x = x
        self.y = y
        Point2D._total_points_count += 1
    def __str__ (self):
        return f"({self.x:.2f},{self.y:.2f})"
    def __repr__ (self):
        return f"Point2D(x={self.x:.2f},y={self.y:.2f})"

    def distance_to (self, other):
        return ( (other.x-self.x)**2 + (other.y-self.y)**2 )**0.5

    @classmethod
    def origin(cls):
        return cls(0.0,0.0)

    @classmethod
    def clone(cls, point):
        return cls(point.x,point.y)

    @classmethod
    def from_polar(cls, r, theta_degrees):
        return cls(math.cos(math.radians(theta_degrees))*r,math.sin(math.radians(theta_degrees))*r)

    @staticmethod
    def distance_between(p1, p2):
        return ( (p1[0]-p2[0])**2 + (p1[1]-p2[1])**2 )**0.5

point_view = Point2D(1.555, 5.8888)
point_a = Point2D(10,10)
point_b = Point2D(13,14)
print(Point2D._total_points_count)

print(str(point_view))
print(repr(point_view))
print(point_a.distance_to(point_b))
print(Point2D.origin())
print(Point2D._total_points_count)

print(Point2D.clone(point_view))
print(Point2D._total_points_count)

print(Point2D.from_polar(9,30))
print(Point2D._total_points_count)

print(Point2D.distance_between((10,10),(13,14)))



