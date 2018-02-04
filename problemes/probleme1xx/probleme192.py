from decimal import Decimal, getcontext
from fractions import Fraction

getcontext().prec = 60

def get_den(x):
    fr = Fraction.from_decimal(Decimal(x).sqrt())
    return fr.limit_denominator(1000000000000).denominator

print(sum(get_den(i) for i in range(2, 100001) if int(i ** 0.5) ** 2 != i))
