from bench import bench

print(bench(100000, '''
def fib(n):
  a, b = 0, 1

  for _ in range(n - 1):
    a, b = b, a
    b += a

  return b
''', '''
fib(20)
'''))
