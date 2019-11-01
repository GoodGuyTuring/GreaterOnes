# Aufgabe 1
# 1.a)
#test


import numpy as np
import sympy as sp
from scipy.linalg import null_space





def ComputeSVD(A):

    #AT ist die transponierte Matrix A
    AT = np.transpose(A)
    AAT = np.matmul(A,AT)

    ATA = np.matmul(AT,A)

    #gibt die Eigenwerte (ew) und die dazugehörigen Eigenvektoren (ev)
    # von der Matrix A mal A transponiert zurück
    ew, ev = np.linalg.eig(AAT)

    for i in range(A.shape[1]-len(ew)):
        ew = np.concatenate((ew,[0]))
    #nimmt den Betrag, rundet auf zehn Stellen, sortiert die Eigenwerte absteigend
    #dem Array sv werden die Quadratwurzeln der Eigenwerte übergeben
    ew = np.abs(ew)
    ew = np.around(ew, 10)
    ew = np.sort(ew)
    ew = ew[::-1]
    sv = np.sqrt(ew)

    #todo unten nullen entfernen
    #sv = sv[sv != 0]
    #print("sv = ",sv)

    #print(ew)

    #Die Matrix V (orthonormale Spaltenvektoren) wird erstellt und transponiert

    V = []
    for i in range(len(ew)):
        T = ATA - ew[i]*np.identity(ATA.shape[0])
        if len(V) == 0:
            V = np.around(null_space(T),15)
            continue

        V = np.hstack((V,np.around(null_space(T),15)))

    VT = np.transpose(V)

    #Die Matrix Sigma (S) wird erstellt mit allen Singulärwerten != 0

    S = np.diag(sv[sv!=0])

    #passt die Dimension von S an
    Z = np.zeros((S.shape[0],1))
    while S.shape[1] < A.shape[1]:
        S = np.hstack((S,Z))

    # U wird erstellt und die Werte auf 15 Stellen gerundet
    U = []
    for i in range(len(sv[sv!=0])):
        U_tmp = ( 1 / sv[i] * np.matmul(A, V[:,i]))

        if len(U) == 0:
            U =np.reshape(U_tmp, (len(U_tmp),1))
            continue
        U = np.hstack((U, np.reshape(U_tmp, (len(U_tmp),1))))

    U = np.around(U,15)

    #Die Matrix AP = A (zur Kontrolle)

    AP = np.matmul(U,np.matmul(S,VT))
    AP = np.around(AP,15)
    #print(AP)
    # U, S und V werden zurückgegeben
    return U, S, V

#Teilaufgabe b)

def pseudoinverse(U,S,V):

    #berechnet S+
    S_stern = S.copy()
    S_stern[S_stern != 0] = np.reciprocal(S[S != 0])
    S_plus = np.transpose(S_stern)

    #berechnet das komplex konjugierte und transponierte der Matrix U
    U_stern = np.transpose(U.conj())

    #gibt V mal S+ mal U* zurück
    return np.matmul(V, np.matmul(S_plus, U_stern))

#Teilaufgabe c)

def LinearSolve(A,b):
    #berechnet die SVD für A
    u, s, v = ComputeSVD(A)
    #gibt die Matrix A+ für A aus
    a_plus = pseudoinverse(u, s, v)
    #laut Skript löst A+*b das lineare Ausgleichsproblem
    x = np.matmul(a_plus, b)

    return x

#kurzer Testcode

A = np.array([[3,2,2], [2,3,-2]])
B = np.array([[4, 0], [3, -5]])
#print("A = ", A)
#print("B = ", B)
U1, S1, V1 = ComputeSVD(A)
U2, S2, V2 = ComputeSVD(B)
print(U1,S1,V1,U2,S2,V2,sep="\n")
PS = pseudoinverse(U1, S1, V1)
print(LinearSolve(A,[2,3])),
print(PS),