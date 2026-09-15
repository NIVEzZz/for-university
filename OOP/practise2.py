import math

class Point3d:

    _total_points_count = 0

    def __init__ (self, x:float, y:float, z:float):
        self.x = x
        self.y = y
        self.z = z
        Point3d._total_points_count += 1
    def __str__ (self):
        return f"({self.x:.2f},{self.y:.2f},{self.z:.2f})"
    def __repr__ (self):
        return f"Point3d(x={self.x:.2f},y={self.y:.2f}, z={self.z:.2f})"

    def distance_to (self, other):
        return ( (other.x-self.x)**2 + (other.y-self.y)**2 + (other.z-self.z)**2)**0.5

    @classmethod
    def origin(cls):
        return cls(0.0,0.0, 0.0)

    @classmethod
    def clone(cls, point):
        return cls(point.x,point.y,point.z)

    @classmethod
    def from_polar(cls, r, theta_degrees):
        return cls(math.cos(math.radians(theta_degrees))*r,math.sin(math.radians(theta_degrees))*r)

    @staticmethod
    def distance_between(p1, p2):
        return ( (p1[0]-p2[0])**2 + (p1[1]-p2[1])**2 + (p1[2]-p2[2])**2 )**0.5

class Vector:
    def __init__ (self, x:float, y:float, z:float):
        self.x = x
        self.y = y
        self.z = z
    def __str__ (self):
        return f"({self.x:.2f},{self.y:.2f},{self.z:.2f})"
    def __repr__ (self):
        return f"Vector(x={self.x:.2f},y={self.y:.2f}, z={self.z:.2f})"

    @classmethod
    def from_points(cls, start:Point3d, end:Point3d):
        return cls(end.x-start.x, end.y-start.y, end.z-start.z)
    def __eq__(self, other):
        return (self.x == other.x and self.y == other.y and self.z == other.z)
    def __gt__(self, other):
        return ((self.x**2 + self.y**2 + self.z**2) > (other.x**2 + other.y**2 + other.z**2))
    def __lt__(self, other):
        return ((self.x**2 + self.y**2 + self.z**2) < (other.x**2 + other.y**2 + other.z**2))

    def __add__(self, other):
        if isinstance(other, (int, float)):
            return Vector(self.x + other, self.y + other, self.z + other)
        elif isinstance(other, Vector):
            return Vector(self.x + other.x, self.y + other.y, self.z + other.z)
        return f"Error"
    def __radd__(self, other):
        return self.__add__(other)

    def __sub__(self, other):
        if isinstance(other, (int, float)):
            return Vector(self.x - other, self.y - other, self.z - other)
        elif isinstance(other, Vector):
            return Vector(self.x - other.x, self.y - other.y, self.z - other.z)
        return f"Error"
    def __rsub__(self, other):
        if isinstance(other, (int, float)):
            return Vector(other - self.x, other - self.y, other - self.z)
        return f"Error"

    def __mul__(self, other):
        if isinstance(other, (int, float)):
            return Vector(self.x * other, self.y * other, self.z * other)
        elif isinstance(other, Vector):
            return Vector(self.x * other.x, self.y * other.y, self.z * other.z)
        return f"Error"
    def __rmul__(self, other):
        return self.__mul__(other)

    def __truediv__(self, other):
        if isinstance(other, (int, float)):
            return Vector(self.x / other, self.y / other, self.z / other)
        elif isinstance(other, Vector):
            return Vector(self.x / other.x, self.y / other.y, self.z / other.z)
        return f"Error"
    def __rtruediv__(self, other):
        if isinstance(other, (int, float)):
            return Vector(other / self.x, other / self.y, other / self.z)
        return f"Error"

    def __iadd__(self, other):
        if isinstance(other, (int, float)):
            self.x += other
            self.y += other
            self.z += other
        elif isinstance(other, Vector):
            self.x += other.x
            self.y += other.y
            self.z += other.z
        else:
            return f"Error"
        return self
    def __isub__(self, other):
        if isinstance(other, (int, float)):
            self.x -= other
            self.y -= other
            self.z -= other
        elif isinstance(other, Vector):
            self.x -= other.x
            self.y -= other.y
            self.z -= other.z
        else:
            return f"Error"
        return self
    def __imul__(self, other):
        if isinstance(other, (int, float)):
            self.x *= other
            self.y *= other
            self.z *= other
        elif isinstance(other, Vector):
            self.x *= other.x
            self.y *= other.y
            self.z *= other.z
        else:
            return f"Error"
        return self
    def __itruediv__(self, other):
        if isinstance(other, (int, float)):
            self.x /= other
            self.y /= other
            self.z /= other
        elif isinstance(other, Vector):
            self.x /= other.x
            self.y /= other.y
            self.z /= other.z
        else:
            return f"Error"
        return self

    def __matmul__(self, other):
        if isinstance(other, Vector):
            return Vector(
                self.y * other.z - self.z * other.y,
                self.z * other.x - self.x * other.z,
                self.x * other.y - self.y * other.x,
            )
        else:
            return f"Error"
    def __rmatmul__(self, other):
        if isinstance(other, Vector):
            return Vector(
                other.y * self.z - other.z * self.y,
                other.z * self.x - other.x * self.z,
                other.x * self.y - other.y * self.x,
            )
        else:
            return f"Error"
    @staticmethod
    def is_collinear(a,b):
        return a.x/b.x == a.y/b.y == a.z/b.z
    def is_complanar(a,b,c):
        delta = a.x*b.y*c.z + c.x*b.y*

a = Vector(1,2,3)
b = Vector(1,2,3)

p1 = Point3d(1,1,1)
p2 = Point3d(3,4,5)

c = Vector.from_points(p1,p2)
print(c)
print (a == b)
print (a == c)
print (a > b)
print (a > c)
print (a < c)

print (a + b)
print(a+3)
print(3+a)
print(a+"sf")

print (a - b)
print (a - 3)
print (3 - a)

print(a * b)
print(a * 3)
print(3 * a)

print (a / b)
print(a / 3)
print(3 / a)
a += b
print (a)
a -= b
print(a)
print(a@c)
print(c@a)
