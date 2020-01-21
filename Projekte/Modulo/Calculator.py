


class Calculator:
    __result = np.zeros([1, 6])

    def __init__(self, total_old, cost):

        self.total_old = total_old
        self.cost = cost



    def getResult(self):
        return self.result

# print((round((333.4-0.1-0.3),1))%1.5)
# np.set_printoptions(suppress=True)
# c = Calculator(333.4, 1.5)
# c.calculate()
# print(c.result)
# c.cost = 2.5
# c.total_old = 138.7
# c.calculate()
# print(c.result)
# c.total_old = 678.8
# c.cost = 1.5
# c.calculate()
# print(c.result)
