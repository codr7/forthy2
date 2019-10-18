from bench import bench

print(bench(10, '''
def fib(n):
  if n < 2: return n
  return fib(n-1) + fib(n-2)
''', '''
fib(20)
'''))
