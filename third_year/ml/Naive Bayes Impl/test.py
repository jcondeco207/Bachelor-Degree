from NaiveBayes import NaiveBayesUevora

def main():
    print(" _   _       _           ____                        _   _ _____ ")
    print("| \ | | __ _(_)_   _____| __ )  __ _ _   _  ___  ___| | | | ____|")
    print("|  \| |/ _` | \ \ / / _ \  _ \ / _` | | | |/ _ \/ __| | | |  _|  ")
    print("| |\  | (_| | |\ V /  __/ |_) | (_| | |_| |  __/\__ \ |_| | |___ ")
    print("|_| \_|\__,_|_| \_/ \___|____/ \__,_|\__, |\___||___/\___/|_____|")
    print("                                     |___/                       ")


#---------------------------------------| Teste 1 |---------------------------------------#

    print("Teste 1:\n")
    col = -1
    test1 = NaiveBayesUevora("inputs/breast.cancer-train.csv")
    test1.loadFile()
    test1.setAlpha(1.0)
    test1.setColIndex(col)

    X, y = test1.separate()
    test1.fit(X, y)
    test1.readByLine()

    test1.setFileName("inputs/breast-cancer-test.csv")
    test1.loadFile()
    test1.setColIndex(col)
    X, y = test1.separate()
    print("Exatidão: " + str(test1.accuracy_score(X, y)))
    print("Precisão: " + str(test1.precision_score(X, y)))


# ---------------------------------------| Teste 2 |---------------------------------------#

    print("\nTeste 2:\n")

    test2 = NaiveBayesUevora("inputs/breast.cancer-train.csv")
    test2.loadFile()
    test2.setAlpha(1.0)

    X, y = test1.separate()
    test2.fit(X, y)
    test2.readByLine()

    query = ["no-recurrence-events","30-39","premeno","30-34","0-2","no",3,"left","left_low"]     #Answer:no
    print("Predict de ['no-recurrence-events','30-39','premeno','30-34','0-2','no',3,'left','left_low'] >> "
          + str(test2.predict(query)))


if __name__ == "__main__":
    main()