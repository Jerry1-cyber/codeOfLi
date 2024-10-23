#这个文件用于处理几何分布的实现
print("当前你正处于几何分布的路径下面")

def main():
    s_space = (input("你的样本的空间"))
    s_space = int(s_space)
    every_true= input("一次为真的概率")
    every_true = float(every_true)
    pos_true = input("你希望第几次为真")
    pos_true = int(pos_true)
    output = pow(1-every_true,pos_true-1)*every_true
    print(f"在第{pos_true}的概率是:{output}")
    return 0
if __name__ == '__main__':
    main()
