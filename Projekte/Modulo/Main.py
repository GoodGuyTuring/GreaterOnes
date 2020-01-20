from Calculator import *

class Main:
    cost = 1.5
    total = 634.8
    C = Calculator(total, cost)
    C.calculate()
    print(C.getResult())
    print(C.result[7][1])

