import math
import sys

#0
TWO_PI = 2 * math.pi
EPS = sys.float_info.epsilon

def _norm_rad(x: float) -> float:
    x = float(x) % TWO_PI
    if abs(x - TWO_PI) < EPS:
        return 0.0
    else:
        return x

def _as_rad(x) -> float:
    if isinstance(x, Angle):
        return x.get_radians()
    if isinstance(x, (int, float)):
        return float(x)
    raise TypeError(f"TypeError x={type(x)}")


class Angle:
    #1
    def __init__(self, radians: float):
        self._rad = float(radians)

    #2
    @classmethod
    #Можно воткнуть вместо "Angle" Self, но у меня питон 3.10
    def from_radians(cls, radians: float) -> "Angle":
        return cls(radians)

    @classmethod
    def from_degrees(cls, degrees: float) -> "Angle":
        return cls(math.radians(degrees))

    #3
    def __str__(self) -> str:
        return f"Angle({self._rad:.3f} rad, {self.get_degrees():.3g} deg)"

    def __repr__(self) -> str:
        return f"Angle(_rad={self._rad:.3f})"

    #4
    def get_radians(self) -> float:
        return self._rad

    def set_radians(self, radians: float) -> None:
        self._rad = float(radians)

    def get_degrees(self) -> float:
        return math.degrees(self._rad)

    def set_degrees(self, degrees: float) -> None:
        self._rad = math.radians(degrees)

    #5
    def __eq__(self, other) -> bool:
        if not isinstance(other, (Angle, int, float)):
            return NotImplemented
        a = _norm_rad(self.get_radians())
        b = _norm_rad(_as_rad(other))
        return abs(a - b) < EPS

    def __ne__(self, other) -> bool:
        result = self.__eq__(other)
        if result == NotImplemented:
            return NotImplemented
        return not result

    def __lt__(self, other) -> bool:
        if not isinstance(other, (Angle, int, float)):
            return NotImplemented
        a = _norm_rad(self.get_radians())
        b = _norm_rad(_as_rad(other))
        return a + EPS < b

    def __le__(self, other) -> bool:
        if not isinstance(other, (Angle, int, float)):
            return NotImplemented
        a = _norm_rad(self.get_radians())
        b = _norm_rad(_as_rad(other))
        return a + EPS < b or abs(a - b) < EPS

    def __gt__(self, other) -> bool:
        if not isinstance(other, (Angle, int, float)):
            return NotImplemented
        return not self.__le__(other)

    def __ge__(self, other) -> bool:
        if not isinstance(other, (Angle, int, float)):
            return NotImplemented
        return not self.__lt__(other)

    #6
    def __float__(self) -> float:
        return float(self._rad)

    def __int__(self) -> int:
        return int(self._rad)

    #7
    def __add__(self, other) -> "Angle":
        if isinstance(other, (Angle, int, float)):
            return Angle(self.get_radians() + _as_rad(other))
        return NotImplemented

    def __radd__(self, other) -> "Angle":
        return self.__add__(other)

    def __sub__(self, other) -> "Angle":
        if isinstance(other, (Angle, int, float)):
            return Angle(self.get_radians() - _as_rad(other))
        return NotImplemented

    def __rsub__(self, other) -> "Angle":
        if isinstance(other, (Angle, int, float)):
            return Angle(_as_rad(other) - self.get_radians())
        return NotImplemented

    def __mul__(self, other) -> "Angle":
        if isinstance(other, (int, float)):
            return Angle(self.get_radians() * float(other))
        return NotImplemented

    def __rmul__(self, other) -> "Angle":
        return self.__mul__(other)

    def __truediv__(self, other) -> "Angle":
        if isinstance(other, (int, float)):
            return Angle(self.get_radians() / float(other))
        return NotImplemented


class AngleRange:
    #1,2
    def __init__(self, start, end, include_start=True, include_end=True):
        if _as_rad(end) + EPS < _as_rad(start):
            raise ValueError("start must be smaller than end")
        self.start = Angle.from_radians(_as_rad(start))
        self.end = Angle.from_radians(_as_rad(end))
        self.include_start = bool(include_start)
        self.include_end = bool(include_end)

    #3
    def __eq__(self, other) -> bool:
        if not isinstance(other, AngleRange):
            return NotImplemented
        a_start = self.start.get_radians()
        a_end = self.end.get_radians()
        b_start = other.start.get_radians()
        b_end = other.end.get_radians()

        return (
            self.include_start == other.include_start
            and self.include_end == other.include_end
            and abs(a_start - b_start) < EPS
            and abs(a_end - b_end) < EPS
        )

    #4
    def __str__(self) -> str:
        open = "[" if self.include_start else "("
        close = "]" if self.include_end else ")"
        return f"{open}{self.start.get_degrees():.3g}°, {self.end.get_degrees():.3g}°{close}"

    def __repr__(self) -> str:
        return f"AngleRange(start={self.start.get_radians():.3f}, end={self.end.get_radians():.3f}, include_start={self.include_start}, include_end={self.include_end})"

    #5
    def __abs__(self) -> float:
        return abs(self.end.get_radians() - self.start.get_radians())

    #6
    def __lt__(self, other) -> bool:
        if not isinstance(other, AngleRange):
            return NotImplemented
        return abs(self) + EPS < abs(other)

    def __le__(self, other) -> bool:
        if not isinstance(other, AngleRange):
            return NotImplemented
        len_a = abs(self)
        len_b = abs(other)
        return (len_a + EPS < len_b) or (abs(len_a - len_b) < EPS)

    def __gt__(self, other) -> bool:
        if not isinstance(other, AngleRange):
            return NotImplemented
        return not self.__le__(other)

    def __ge__(self, other) -> bool:
        if not isinstance(other, AngleRange):
            return NotImplemented
        return not self.__lt__(other)

    #7
    def __contains__(self, item) -> bool:
        if not isinstance(item, (AngleRange, Angle, int, float)):
            return NotImplemented
        start = self.start.get_radians()
        end = self.end.get_radians()
        if isinstance(item, (Angle, int, float)):
            item = _as_rad(item) #float
            on_edge = False
            if self.include_start:
                on_edge = abs(item - start) < EPS
            if self.include_end and on_edge == False:
                on_edge = abs(item - end) < EPS
            return (start + EPS < item) and (item + EPS < end) or on_edge

        if item == self:
            return True
        if (item.start.get_radians() - start) < EPS and (item.end.get_radians() - end) < EPS and item.include_start == False and self.include_end == True:
            return True
        return (start + EPS < item.start.get_radians()) and (item.end.get_radians() + EPS < end)

    #8
    def __add__(self, other):
        if not isinstance(other, AngleRange):
            return NotImplemented

        if abs(self) == 0 and not (self.include_start or self.include_end):
            return other
        if abs(other) == 0 and not (other.include_start or other.include_end):
            return self

        if other in self:
            return self
        if self in other:
            return other

        if other.start in self:
            return AngleRange(self.start, other.end, self.include_start, other.include_end)
        if other.end in self:
            return AngleRange(other.start, self.end, other.include_start, self.include_end)

        if self.start < other.start:
            return str(other), str(self)
        if other.start < self.start:
            return str(self), str(other)

    def __sub__(self, other):
        if not isinstance(other, AngleRange):
            return NotImplemented

        if other == self:
            return AngleRange(0, 0, False, False)

        if abs(self) == abs(other) and self.include_start == False and self.include_end == False and other.include_start == True and other.include_end == True:
            return AngleRange(0, 0, False, False)

        if abs(self) == abs(other) and other.include_start == False and other.include_end == False:
            first = AngleRange(self.start, self.start, self.include_start, self.include_start)
            second = AngleRange(self.end, self.end, self.include_end, self.include_end)
            return str(first), str(second)

        if self.end < other.start:
            return self
        if other.end < self.start:
            return self

        if other.start < self.start and self.end < other.end:
            return AngleRange(0, 0, False, False)

        if other in self:
            first = AngleRange(self.start, other.start, self.include_start, not other.include_start)
            second = AngleRange(other.end, self.end, not other.include_end, self.include_end)
            return str(first), str(second)

        if abs(self) == 0 and not (self.include_start or self.include_end):
            return other
        if abs(other) == 0 and not (other.include_start or other.include_end):
            return self

        if other.start in self:
            return AngleRange(self.start, other.start, self.include_start, not other.include_start)
        if other.end in self:
            return AngleRange(other.end, self.end, not other.include_end, self.include_end)


if __name__ == "__main__":
    a = Angle.from_degrees(90)
    b = Angle.from_radians(math.pi / 2)
    c = Angle.from_radians(5 * math.pi / 2)

    print(f"90° (str) {a}")
    print(f"90° (repr) {repr(a)}")
    print(f"PI/2 радиан (str) {b}")
    print(f"5*PI/2 радиан (str) {c}")
    print(f"a == b {a == b}")
    print(f"a == c {a == c}")
    print(f"float(b) {float(b)}")
    print(f"int(с) {int(c)}")
    print(f"c + PI {c + math.pi}")
    print(f"c * 2 {c * 2}")
    print(f"c / 2 {c / 2}")
    print(f"a - 4.8 {a - 4.8}")
    print(f"4.8 - a {4.8 - a}")

    r1 = AngleRange(math.pi, TWO_PI) #[PI, TWO_PI]
    r2 = AngleRange(Angle.from_degrees(180), Angle.from_degrees(360)) #[PI, TWO_PI]
    r3 = AngleRange(math.pi / 2, 3 * math.pi / 4) #[90, 90+45]
    r4 = AngleRange(0, math.pi) #[0, PI]
    r5 = AngleRange(math.pi, TWO_PI, False, False) #(PI, TWO_PI)
    r6 = AngleRange(-math.pi/2, math.pi / 4) #[-90,45]

    print("="*30)
    print(f"TWO_PI={TWO_PI}")
    print(f"r1 {r1}")
    print(f"r2 {r5}")
    print(f"repr(r1) {repr(r1)}")
    print(f"r1 == r2 {r1 == r2}")
    print(f"r1 len {abs(r1)}")
    print()

    print("PI*5/4 in r1:", math.pi*5/4 in r1)
    print("PI in r1:", math.pi in r1)
    print("TWO_PI in r1:", TWO_PI in r1)
    print()

    print("PI*5/4 in r5:", math.pi*5/4 in r5)
    print("PI in r5:", math.pi in r5)
    print("TWO_PI in r5:", TWO_PI in r5)
    print()

    print("r1 in r5:", r1 in r5)
    print("r5 in r1:", r5 in r1)
    print("r1 in r2:", r1 in r2)
    print("r3 in r4:", r3 in r4,)
    print()

    print("r1 < r2:", r1 < r2)
    print("r1 <= r1:", r1 <= r1)
    print("r3 < r2:", r3 < r2)
    print()

    print("r3 + r4:", r3 + r4)
    print("r4 + r1:", r4 + r1)
    print("r6 + r4:", r6 + r4)
    print("r4 + r6:", r4 + r6)
    print("r6 + r3:", r6 + r3)
    print("r3 + r6:", r3 + r6)
    print("r5 + r1:", r5 + r1)
    print()

    print("r2 - r1:", r2 - r1)
    print("r3 - r6:", r3 - r6)
    print("r6 - r3:", r6 - r3)
    print("r1 - r5:", r1 - r5)
    print("r5 - r1:", r5 - r1)
    print("r4 - r3:", r4 - r3)
    print("r3 - r4:", r3 - r4)
