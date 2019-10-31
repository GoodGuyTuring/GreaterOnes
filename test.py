# Aufgabe 1
# 1.a)
#test


import numpy as np
import sympy as sp
from scipy.linalg import null_space




def ComputeSVD(A):

    AT = np.transpose(A)
    AAT = np.matmul(A,AT)
    #print(AAT)
    ATA = np.matmul(AT,A)
    #print(ATA)
    ew, ev = np.linalg.eig(AAT)
    #print("Ew len: ", len(ew))
    for i in range(A.shape[1]-len(ew)):
        ew = np.concatenate((ew,[0]))
    #print("ew=", ew)
    #input()
    ew = np.abs(ew)
    ew = np.around(ew, 10)
    ew = np.sort(ew)
    ew = ew[::-1]
    sv = np.sqrt(ew)
    #todo unten nullen entfernen
    #sv = sv[sv != 0]
    #print("sv = ",sv)

    #print(ew)
    T1 = ATA - (ew[0]*(np.identity(ATA.shape[0])))
    #print(T1)
    #T2 = sp.Matrix(T1)
    #T2 = T2.rref()[0]
    #T3 = np.array(T2)
    #print(T3)
    V = []
    for i in range(len(ew)):
        T = ATA - ew[i]*np.identity(ATA.shape[0])
        if len(V) == 0:
            V = np.around(null_space(T),15)
            continue
        #print("V=",V)
        V = np.hstack((V,np.around(null_space(T),15)))

    #print("V nach Schleife", V)
    #V1 = np.around(null_space(T1),15)
    #print(V1)
    #T2 = ATA - (ew[1]*(np.identity(ATA.shape[0])))
    #V2 = np.around(null_space(T2),15)
    #V3 = np.around(null_space(ATA),15)
    #print(V1)
    #print(V2)
    #print(V3)
    #V = np.hstack((V1,V2,V3))
    VT = np.transpose(V)
    #print(VT)
    #input()
    S = np.diag(sv[sv!=0])
    #print(S.shape)
    Z = np.zeros((S.shape[0],1))
    while S.shape[1] < A.shape[1]:
        S = np.hstack((S,Z))
    #print(S)

    U = []
    for i in range(len(sv[sv!=0])):
        U_tmp = ( 1 / sv[i] * np.matmul(A, V[:,i]))
        #print("U tmp: ",U_tmp)
        if len(U) == 0:
            U =np.reshape(U_tmp, (len(U_tmp),1))
            continue
        U = np.hstack((U, np.reshape(U_tmp, (len(U_tmp),1))))

    U = np.around(U,15)
    #TT1 = np.matmul(A,V[:,0])
    #print(V)
    #print(TT1)
    #TT2 = (1/sv[0])*TT1
    #TT2 = np.reshape(TT2,(2,1))
    #print(TT2)
    #TT3 = np.matmul(A,V[:,1])
    #TT4 = (1/sv[1]*TT3)
    #TT4 = np.reshape(TT4,(2,1))
    #print(TT4)
    #U = np.hstack((TT2,TT4))
    #print("U: ", U, U.shape, S.shape, VT.shape)
    #input()
    AP = np.matmul(U,np.matmul(S,VT))
    AP = np.around(AP,15)
    #print(AP)
    return U, S, V

def pseudoinverse(U,S,V):
    S_stern = np.reciprocal(S)
    S_plus = np.transpose(S_stern)
    U_stern = np.transpose(U.conj())
    return np.matmul(V, np.matmul(S_plus, U_stern))

A = np.array([[3,2,2], [2,3,-2]])
B = np.array([[4, 0], [3, -5]])
#print("A = ", A)
#print("B = ", B)
U1, S1, V1 = ComputeSVD(A)
U2, S2, V2 = ComputeSVD(B)
print(U1,S1,V1,U2,S2,V2,sep="\n")
PS = pseudoinverse(U1, S1, V1)
print(PS)


"""
    # at = transposed A
    at = np.transpose(A)
    # ata = A^T * A
    ata = np.matmul(at, A)
    aat = np.matmul(A,at)

    # Get Eigenvalue(ev) and Eigenvector(ev) from A^T * A
    ew, ev = np.linalg.eig(ata)
    # Calculate Singularevalues SV = squareroot of absolute value of ordered Eigenvalues
    print(ew)
    sv = np.abs(ew)
    sv = np.around(sv,10)
    print(sv)
    sv = np.sort(sv)
    sv = sv[::-1]
    sv[sv==0] = 1
    print(sv)
    sv = np.sqrt(sv)
    print(sv)
    # Calculate Diagonalmatrix S from Singularvalues
    s = np.diag(sv)
    # Calculate SI = Inverse of S
    si = np.linalg.inv(s)
    evt = np.transpose(ev)                 #Need for ap
    # Calculate SVD U from A*EV*SI
    u = np.matmul(A, np.matmul(ev, si))
    ap = np.matmul(u,np.matmul(s,evt))     #Proof that u is correct
    print(ap)
"""
