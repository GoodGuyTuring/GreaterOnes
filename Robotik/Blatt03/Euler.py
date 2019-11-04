import numpy as np

R = np.array([[1/np.sqrt(2),0,1/np.sqrt(2)],[-1/2,1/np.sqrt(2),1/2],[-1/2,-1/np.sqrt(2),1/2]])

print(R)
Theta1 = -1/np.sin(R[2,0])
Theta2 = np.pi - Theta1
print(Theta1)
Psi1 = np.arctan2(R[2,1]/np.cos(Theta1),R[2,2]/np.cos(Theta1))
Psi2 = np.arctan2(R[2,1]/np.cos(Theta2),R[2,2]/np.cos(Theta2))
Phi1 = np.arctan2(R[1,0]/np.cos(Theta1),R[0,0]/np.cos(Theta1))
Phi2 = np.arctan2(R[1,0]/np.cos(Theta2),R[0,0]/np.cos(Theta2))
Euler1 = np.array([Phi1,Psi1,Theta1])
Euler2 = np.array([Phi1,Psi2,Theta2])
print(Euler1, Euler2, sep="\n")
Euler1 = (Euler1[::1]*180)/np.pi
Euler2 = (Euler2*180)/np.pi
print(Euler1)
print(Euler2)

e4 = (1/2)*np.sqrt(1+R[0,0]+R[1,1]+R[2,2])
e3 = (R[1,0]-R[0,1])/4e4
e2 = (R[0,2]-R[2,0])/4e4
e1 = (R[2,1]-R[1,2])/4e4
print(e1,e2,e3,e4,sep="\n")
ep4 = np.cos(Psi1/2)*np.cos((Phi1+Theta1)/2)
ep3 = np.cos(Psi1/2)*np.sin((Phi1+Theta1)/2)
ep2 = np.sin(Psi1/2)*np.sin((Phi1+Theta1)/2)
ep1 = np.sin(Psi1/2)*np.cos((Phi1+Theta1)/2)
print(ep1, ep2, ep3, ep4,sep="\n")

