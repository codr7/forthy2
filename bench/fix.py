from bench import bench

print(bench(10, '''
from decimal import Decimal
''', '''
x = Decimal(0)

for _ in range(100000):
  x += Decimal(1) / Decimal(3)
'''))

print(bench(10, '', '''
x = 0.0
for _ in range(1000000): x += 0.1
'''))
