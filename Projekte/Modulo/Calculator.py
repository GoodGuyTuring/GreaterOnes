import numpy as np


class Calculator:
    __result = np.zeros([1, 6])

    def __init__(self, total_old, cost):

        self.total_old = total_old
        self.cost = cost
        np.set_printoptions(suppress=True)

    def calculate(self):
        self.result = np.zeros([1, 6])
        first = 1
        for x in range(0, 51):
            if first == 1 and (self.total_old - x * 0.3) % self.cost == 0:
                first = 0
                result = self.result
                offset = 0
                bes = x
                t_bes = bes * 0.3
                t_prog = self.total_old - t_bes + offset
                prog = t_prog / self.cost
                total_new = t_bes + t_prog
                result[0][0] = bes
                result[0][1] = t_bes
                result[0][2] = prog
                result[0][3] = t_prog
                result[0][4] = total_new
                result[0][5] = offset
                self.result = result
                continue
            if first == 0 and (self.total_old - x * 0.3) % self.cost == 0:
                result = self.result
                offset = 0
                bes = x
                t_bes = bes * 0.3
                t_prog = self.total_old - t_bes + offset
                prog = t_prog / self.cost
                total_new = t_bes + t_prog
                temp = np.array([bes, t_bes, prog, t_prog, total_new, offset])
                temp = temp.reshape((1, 6))
                # print(temp)
                result = np.vstack((result, temp))
                self.result = result
            if x == 50:
                print()
        if not self.result.any():
            for x in range(0, 51):
                if first == 1 and round((self.total_old - 0.1 - x * 0.3), 1) % self.cost == 0:
                    first = 0
                    result = self.result
                    offset = -0.1
                    bes = x
                    t_bes = bes * 0.3
                    t_prog = self.total_old - t_bes + offset
                    prog = t_prog / self.cost
                    total_new = t_bes + t_prog
                    result[0][0] = bes
                    result[0][1] = t_bes
                    result[0][2] = prog
                    result[0][3] = t_prog
                    result[0][4] = total_new
                    result[0][5] = offset
                    self.result = result
                    continue
                if first == 0 and round((self.total_old - 0.1 - x * 0.3), 1) % self.cost == 0:
                    result = self.result
                    offset = -0.1
                    bes = x
                    t_bes = bes * 0.3
                    t_prog = self.total_old - t_bes + offset
                    prog = t_prog / self.cost
                    total_new = t_bes + t_prog
                    temp = np.array([bes, t_bes, prog, t_prog, total_new, offset])
                    temp = temp.reshape((1, 6))
                    # print(temp)
                    result = np.vstack((result, temp))
                    self.result = result
                if x == 50:
                    print()
        if not self.result.any():
            for x in range(0, 51):
                if first == 1 and round((self.total_old + 0.1 - x * 0.3), 1) % self.cost == 0:
                    first = 0
                    result = self.result
                    offset = 0.1
                    bes = x
                    t_bes = bes * 0.3
                    t_prog = self.total_old - t_bes + offset
                    prog = t_prog / self.cost
                    total_new = t_bes + t_prog
                    result[0][0] = bes
                    result[0][1] = t_bes
                    result[0][2] = prog
                    result[0][3] = t_prog
                    result[0][4] = total_new
                    result[0][5] = offset
                    self.result = result
                    continue
                if first == 0 and round((self.total_old + 0.1 - x * 0.3), 1) % self.cost == 0:
                    result = self.result
                    offset = 0.1
                    bes = x
                    t_bes = bes * 0.3
                    t_prog = self.total_old - t_bes + offset
                    prog = t_prog / self.cost
                    total_new = t_bes + t_prog
                    temp = np.array([bes, t_bes, prog, t_prog, total_new, offset])
                    temp = temp.reshape((1, 6))
                    # print(temp)
                    result = np.vstack((result, temp))
                    self.result = result
                if x == 50:
                    print()

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
