#这个窗口解决的是超几何分布的

#定义一个阶乘的函数
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
    s_space = int(input("样本空间的大小"))
    l_space = int(input("样本空间的分布"))
    r_space = s_space - l_space
    p_space = int(input("你想要抽取的数量"))
    dict = {}
    for X in range(0,p_space+1 if p_space <= l_space else l_space+1):
        #X使我们在一个区间中抽取的元素的个数
        if X <= l_space and p_space - X <= r_space:
            dict[f"X={X}"] = (combinationSize(l_space,X) * combinationSize(r_space,p_space-X)) / combinationSize(s_space,p_space)
    print(dict)
    sum = 0
    for dic in dict.values():
        sum += dic

    print(sum)
    return 0
    
if __name__ == '__main__':
    main()
