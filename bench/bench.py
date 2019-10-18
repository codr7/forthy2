from timeit import Timer

def bench(reps, setup, test):
    return int(Timer(test, setup).timeit(reps) * 1000)
