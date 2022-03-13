from os import system
from math import *
from random import *
#system("g++ std.cpp -o std -O2 -std=c++11")
def exp10(a):
	b=[]
	for i in a:
		b.append(i*10)
	return b
def expand(a):
	b=[]
	for i in a:
		for j in range(0,i[1]):
			b.append(i[0])
	return b

# Write here
T=[5,5,20,20,20,20,20,20,20]
N=[5,100,1000,1000,1000,1000,1000,1000,1000,1000,1000,1000]
S=["","","A","B","","","B","C","D"]
Id=[0,1,2,2,3,4,4,4,4,4,4,4,4,4]
def Main(_t,F):
	n=N[_t]
	if S[_t]=="B" and n%2==0:
		n=n-1
	print(n,file=F)
	p=list(range(2,n+1))
	shuffle(p)
	p=[1]+p
	if S[_t]=="B":
		P=[[]]
		while len(P[-1])!=n-1:
			x,y=randint(0,len(P)-1),randint(0,len(P)-1)
			while len(P[x])+len(P[y])+2>=n:
				x,y=randint(0,len(P)-1),randint(0,len(P)-1)
#			print(x,y,P[x],P[y])
			X,Y=list(P[x]),list(P[y])
			for i in range(0,len(X)):
				X[i]=X[i]+1
			for i in range(0,len(Y)):
				Y[i]=Y[i]+1+len(X)+1
			X=[1]+X
			Y=[1]+Y
			P.append(X+Y)
#			if(len(P)>=4):
#				for i in P:
#					print(i)
#				exit(0)
#		print(P[-1],p)
		f=[]
		for i in range(1,n):
			f.append(0)
		for i in range(2,n+1):
			f[p[i-1]-2]=p[P[-1][i-2]-1]
		print(f,file=F)
		return()
	w,r,R=[],0,0.
	if S[_t]=="C":
		r=randint(1,n/2)
		R=[0.001,0.01,0.1,0.2,0.5][randint(0,4)]
	if S[_t]=="D":
		r=randint(1,[2,10,100][randint(0,2)])
		R=[0.1,0.2,0.5,1][randint(0,3)]
	for j in range(0,n):
		if S[_t]=="A":
			w.append(2)
		else:
			w.append(n)
	f=[]
	for i in range(2,n+1):
		f.append(0)
	for i in range(2,n+1):
		j=0
		if S[_t]=="C" and i>r and random()<R:
			j=r
		if S[_t]=="D" and random()<R:
			j=i-randint(1,r)
		while j<=0 or w[j-1]==0:
			j=randint(1,i-1)
		w[j-1]=w[j-1]-1
		f[p[i-1]-2]=p[j-1]
	print(f,file=F)
	f.sort()
	if S[_t]=="A":
		for i in range(0,n-3):
			if f[i]==f[i+2]:
				exit(1)
	if S[_t]=="C":
		print(r,p[r-1],R)
	if S[_t]=="D":
		print(r,R)


print(T,"tests will be generated.")
id=0
for i in range(0,len(T)):
#	system("mkdir "+str(i))
	for j in range(0,T[i]):
		id=id+1
		f=open("d"+str(id)+".in",mode="w")
		Main(i,f)
		f.close()
		system("copy _"+str(Id[i])+".out d"+str(id)+".out")
#system("del std.exe")