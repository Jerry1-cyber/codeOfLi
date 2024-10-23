class infor:
    def __init__(self):
        self._name = "丁俊豪"
        self._age = "18"
    def __str__(self):
         return self._name + " " + self._age
def main():
    myinfor = infor()
    print(myinfor)
    return 0
if __name__ == '__main__':
    main()
