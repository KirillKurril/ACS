from numpy import exp, sin, cos, arange, prod, abs

a = 1
b = 1
h = 1
precision = 0.00000001

def factorial(n):
    arr = arange(1, n+1)
    return prod(arr)

# def Y(x):
#     result = exp(cos(x)) * cos(sin(x))
#     return result

# def S(x, n):
#     result = 0
#     for i in range(1, n+1):
#         result += cos(i * x) / factorial(i)
#     return result

def Y(x):
    result = sin(x)
    return result

def S(x, n):
    result = 0
    for i in range(1, n+1):
        result += ((-1)**(i-1))*(x**(2*i-1))/factorial(2*i - 1)
    return result


counter = 1
y = Y(a)
s = S(a, counter)

while True:
    if abs(y - s) < precision:
        break
    print(f"----------------->intermediate calculation result:\nY = {y}\nS = {s}\nCounter = {counter}\n")
    counter +=1
    y = Y(a)
    s = S(a, counter)

print(f"final counter result: {counter}")




