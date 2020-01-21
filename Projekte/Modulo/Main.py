from tkinter import *
import numpy as np
from matplotlib import pyplot as plt


res = []
total_old = 0
cost = 0


def mymod(c, x, m, o):
    ret = round((c + o - x * 0.3), 2)
    ret = round(ret % m, 2)
    ret = round(ret % m, 2)
    return ret


def calculate(total_old, cost):
    result = np.zeros([1, 6])
    first = 1
    for x in range(0, 51):
        if first == 1 and mymod(total_old, x, cost, 0) == 0:
            first = 0
            offset = 0
            bes = x
            t_bes = bes * 0.3
            t_prog = total_old - t_bes + offset
            prog = t_prog / cost
            total_new = t_bes + t_prog
            result[0][0] = bes
            result[0][1] = t_bes
            result[0][2] = prog
            result[0][3] = t_prog
            result[0][4] = total_new
            result[0][5] = offset
            result = result
            continue
        if first == 0 and mymod(total_old,x,cost,0) == 0:
            offset = 0
            bes = x
            t_bes = bes * 0.3
            t_prog = total_old - t_bes + offset
            prog = t_prog / cost
            total_new = t_bes + t_prog
            temp = np.array([bes, t_bes, prog, t_prog, total_new, offset])
            temp = temp.reshape((1, 6))
            # print(temp)
            result = np.vstack((result, temp))
            result = result
    if not result.any():
        for x in range(0, 51):
            if first == 1 and mymod(total_old,x,cost,-0.1) == 0:
                first = 0
                offset = -0.1
                bes = x
                t_bes = bes * 0.3
                t_prog = total_old - t_bes + offset
                prog = t_prog / cost
                total_new = t_bes + t_prog
                result[0][0] = bes
                result[0][1] = t_bes
                result[0][2] = prog
                result[0][3] = t_prog
                result[0][4] = total_new
                result[0][5] = offset
                result = result
                continue
            if first == 0 and mymod(total_old,x,cost,-0.1) == 0:
                offset = -0.1
                bes = x
                t_bes = bes * 0.3
                t_prog = total_old - t_bes + offset
                prog = t_prog / cost
                total_new = t_bes + t_prog
                temp = np.array([bes, t_bes, prog, t_prog, total_new, offset])
                temp = temp.reshape((1, 6))
                # print(temp)
                result = np.vstack((result, temp))
                result = result
    if not result.any():
        for x in range(0, 51):
            if first == 1 and mymod(total_old,x,cost,0.1) == 0:
                first = 0
                offset = 0.1
                bes = x
                t_bes = bes * 0.3
                t_prog = total_old - t_bes + offset
                prog = t_prog / cost
                total_new = t_bes + t_prog
                result[0][0] = bes
                result[0][1] = t_bes
                result[0][2] = prog
                result[0][3] = t_prog
                result[0][4] = total_new
                result[0][5] = offset
                result = result
                continue
            if first == 0 and mymod(total_old,x,cost,0.1) == 0:
                offset = 0.1
                bes = x
                t_bes = bes * 0.3
                t_prog = total_old - t_bes + offset
                prog = t_prog / cost
                total_new = t_bes + t_prog
                temp = np.array([bes, t_bes, prog, t_prog, total_new, offset])
                temp = temp.reshape((1, 6))
                # print(temp)
                result = np.vstack((result, temp))
                result = result
    return result


def window():
    window = Tk()
    window.title("Test1")
    lbl_total = Label(window, text="Gesamtbetrag")
    lbl_total.grid(row=0, column=0)
    lbl_cost = Label(window, text="Kosten pro Programm")
    lbl_cost.grid(row=1, column=0)
    txt_total = Entry(window, width=10)
    txt_total.grid(row=0, column=1)
    txt_cost = Entry(window, width=10)
    txt_cost.grid(row=1, column=1)

    def get_value():
        total_old = float(txt_total.get().replace(",", "."))
        cost = float(txt_cost.get().replace(",", "."))
        res = calculate(total_old, cost)
        # plt.matshow(res)
        # plt.show()
        fig, axs = plt.subplots(1,1)
        collabel = ("Besetzungszettel", "Gesamt", "Programme", "Gesamt", "Einnahmen", "Offset")
        axs.axis('tight')
        axs.axis('off')
        print(res)
        res2 = tab_2 = [['%.2f' % j for j in i] for i in res]
        the_table = axs.table(cellText=res2, colLabels=collabel, loc='center')
        plt.show()

    btn_enter = Button(window, text="Eingabe", command=get_value)
    btn_enter.grid(row=2, column=1)
    btn_quit = Button(window, text="Exit", command=window.destroy)
    btn_quit.grid(row=2, column=0)

    window.mainloop()


np.set_printoptions(suppress=True)

window()
