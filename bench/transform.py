from bench import bench

print(bench(10000, '', '''
list(map(lambda x: x+1, filter(lambda x: x > 48, range(100))))
'''))

print(bench(10000, '', '''
[x+1 for x in range(100) if x > 48]
'''))
