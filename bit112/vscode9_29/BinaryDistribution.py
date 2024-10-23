#这里是进行二项分布
s_space= int(input("这里是样本空间的大小"))
prob = float(input("单次抽取的概率"))
def combinationSize(n,x):
    sum = 1
    for i in range(1,n+1):
        sum *= i
    for i in range(1,x+1):
        sum /= i
    for i in range(1,n-x+1):
        sum /= i
    return sum
def main():
    diction = {}
    for X in range(0,s_space+1):
        diction[f"X={X}"] = combinationSize(s_space,X) * pow(prob,X) * pow(1-prob,s_space-X)
    print(diction)
    sum = 0

if __name__ == '__main__':
    main()