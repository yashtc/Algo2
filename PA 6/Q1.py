'''
Question 1
In this assignment you will implement one or more algorithms for the 2SAT problem. Here are 6 different 2SAT instances: #1 #2 #3 #4 #5 #6.

The file format is as follows.
In each instance, the number of variables and the number of clauses is the same, and this number is specified on the first line of the file.
Each subsequent line specifies a clause via its two literals, with a number denoting the variable and a "-" sign denoting logical "not".
For example, the second line of the first data file is "-16808 75250", which indicates the clause ¬x16808 V x75250.

Your task is to determine which of the 6 instances are satisfiable, and which are unsatisfiable.
In the box below, enter a 6-bit string, where the ith bit should be 1 if the ith instance is satisfiable, and 0 otherwise.
For example, if you think that the first 3 instances are satisfiable and the last 3 are not, then you should enter the string 111000 in the box below.

DISCUSSION: This assignment is deliberately open-ended, and you can implement whichever 2SAT algorithm you want.
For example, 2SAT reduces to computing the strongly connected components of a suitable graph (with two vertices per variable and two directed edges per clause, you should think through the details).
This might be an especially attractive option for those of you who coded up an SCC algorithm for Part I of this course.
Alternatively, you can use Papadimitriou's randomized local search algorithm. (The algorithm from lecture might be too slow; but perhaps there are some simple ways to ensure that it doesn't run too long?).
A third approach is via backtracking. In lecture we mentioned this approach only in passing; see the DPV book, for example, for more details.
'''
import random
import math
def main():
	f=open("2sat1.txt","r")
	num_vars=int(f.readline())
	inst={}
	choices=[True, False]
	tclauses={}
	for i in range(1,num_vars+1):
		tclauses[i]=[]
	for i in range(1,num_vars+1):
		s=f.readline().rstrip()
		variables=s.split(' ')
		if int(variables[0])<0: tclauses[0-int(variables[0])].append(variables)
		else: tclauses[int(variables[0])].append(variables)
		if variables[0]!=variables[1]:
			if int(variables[1])<0: tclauses[0-int(variables[1])].append(list(reversed(variables)))
			else: tclauses[int(variables[1])].append(list(reversed(variables)))
		inst[str(i)]=random.choice(choices)
	f.close()
	for i in range(1,num_vars+1):
		if len(tclauses[i])==0: del tclauses[i]
	oldnum=num_vars+1
	newnum=num_vars
	while oldnum>newnum:
		oldnum=newnum
		for tc in tclauses.keys():
			if len(tclauses[tc])==0:
				del tclauses[tc]
			else:
				first=tclauses[tc][0][0]
				sameSign=True
				for i in tclauses[tc]:
					if i[0]!=first:
						sameSign=False
						break
				if sameSign:
					for tcc in tclauses[tc]:
						var1=tcc[0]
						var2=tcc[1]
						if int(var1)<0: var1=str(0-int(var1))
						if int(var2)<0: var2=str(0-int(var2))
						var11=True
						var22=True
						if int(tcc[0])<0:
							if inst[str(0-int(tcc[0]))]: var11=False
							else: var11=True
						else: var11=inst[tcc[0]]
						if int(tcc[1])<0:
							if inst[str(0-int(tcc[1]))]: var22=False
							else: var22=True
						else: var22=inst[tcc[1]]
						if not(var11 or var22):
							inst[var1]=not inst[var1]
						if tcc[0]!=tcc[1]:
							tclauses[int(var2)].remove(list(reversed(tcc)))
						tclauses[tc].remove(tcc)
						if len(tclauses[tc])==0:
							del tclauses[tc]
						newnum-=1
	flag=False
	for varc in tclauses.keys():
			if len(tclauses[varc])==0: del tclauses[varc]
			else:
				for c in tclauses[varc]:
					var1=c[0]
					var2=c[1]
					if int(var1)<0: var1=str(0-int(var1))
					if int(var2)<0: var2=str(0-int(var2))
					if c[0]!=c[1]:
						tclauses[int(var2)].remove(list(reversed(c)))
	for i in range(0,int(math.log(num_vars,2))+1):
		j=1
		while (not flag) and j<(2*num_vars*num_vars):
			flag=True
			for varc in tclauses.keys():
				for c in tclauses[varc]:
					var1=c[0]
					var2=c[1]
					if int(var1)<0: var1=str(0-int(var1))
					if int(var2)<0: var2=str(0-int(var2))
					var11=True
					var22=True
					if int(c[0])<0:
						if inst[str(0-int(c[0]))]: var11=False
						else: var11=True
					else: var11=inst[c[0]]
					if int(c[1])<0:
						if inst[str(0-int(c[1]))]: var22=False
						else: var22=True
					else: var22=inst[c[1]]
					if not(var11 or var22):
						if random.choice([1,2])==1: inst[var1]=not inst[var1]
						else: inst[var2]=not inst[var2]
						flag=False
						break
			if flag:
				print "Satisfiable"
				break
			j=j+1
	if not flag: print "Unsatisfiable"

if __name__ == '__main__':
	main()
