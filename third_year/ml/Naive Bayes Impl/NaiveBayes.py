import pandas as pd
from collections import Counter

# Classe que armazena dados relativos às classes a prever
class Element:
    def __init__(self, name, ocurrencias, total, alfa, nVals):
        self.ocurrencias = ocurrencias
        self.name = name
        self.total = total
        self.prob = 0
        self.totalProb = 0
        self.alfa = alfa
        self.nVals = nVals

    # Função responsável por atualizar a probabilidade da classe
    def updateProb(self, prob):
        if (self.prob == 0):
            self.totalProb = self.calcProb()
        self.totalProb *= prob

    # Função que calcula a probabilidade
    def calcProb(self):
        self.prob = (self.ocurrencias + self.alfa) / (self.total + self.alfa * self.nVals)
        return self.prob

    # Função que reinicia a probabilidade
    def resetProb(self):
        self.totalProb = self.prob

# Classe que armazena dados relativos às classes do X
class interElement:
    def __init__(self, name, obj, nValues, motherOcurrencias):
        self.name = name
        self.ocurrencias = 0
        self.obj = obj                                          # Classe a prever
        self.objName = obj.name                                 
        self.nValues = nValues                                  # Número de tipos de variáveis diferentes
        self.motherOcurrencias = motherOcurrencias              # Número de ocorrências da classe a prever

    def increment(self):
        self.ocurrencias += 1

    # Função que retorna o nome da classe
    def getName(self):
        return self.name

    # Função que calcula a probabilidade
    def calcProb(self, alfa):
        return (self.ocurrencias + alfa) / (self.motherOcurrencias + alfa * self.nValues)


class NaiveBayesUevora:
    alfa = 0.0
    colIndex = -1

    def __init__(self, fileName):
        self.fileName = fileName
        self.objects = []
        self.intersections = []
        self.nValues = {}
        self.toPredic = None

    def setAlpha(self, alfa):
        self.alfa = alfa

    def setFileName(self, fileName):
        self.fileName = fileName

    def findOcurrencies(self, name):
        for obj in self.objects:
            if (name == obj.name):
                return obj.ocurrencias
        return None

    def findObject(self, name):
        for obj in self.objects:
            if (name == obj.name):
                return obj
        return None

    def findInterObject(self, name):
        for obj in self.intersections:
            if (name == obj.name):
                return obj
        return None

    def fit(self, X, y):
        contagem = Counter(y)
        self.toPredic = y.name
        for el in contagem:
            self.objects.append(Element(el, contagem[el], len(y), self.alfa, len(contagem)))

        for name in X:
            col = X.loc[:, name]
            contagemCol = Counter(col)
            nValues = len(contagemCol)
            self.nValues[name.strip()] = len(contagemCol)
            for interName in contagemCol:
                for obj in self.objects:
                    className = obj.name
                    interObj = self.findInterObject(str(interName) + "|" + str(className))
                    if (interObj == None):
                        self.intersections.append(interElement((str(interName) + "|" + str(className)), self.findObject(className), nValues, obj.ocurrencias))
                        interObj = self.findInterObject(str(interName) + "|" + str(className))

            for i in range(len(col)):
                className = y[i]
                interObj = self.findInterObject(str(col[i]) + "|" + str(className))
                interObj.increment()

    def readByLine(self):
        file = pd.read_csv(self.fileName)
        X = file.drop([file.columns[self.colIndex]], axis=1)
        y = file[file.columns[self.colIndex]]
        res = []
        arr = []
        nValues = len(X.columns)

        for line in range(len(X)):
            content = X.loc[line]

            for i in content:
                arr.append(i)
            res.append(self.predict(arr))
            arr = []

    def predict(self, x):
        maxClass = None
        maxValue = 0

        if(self.colIndex == -1):
            toAdd = len(x)
        else:
            toAdd = self.colIndex

        x.insert(toAdd, ' ')

        for classObj in self.objects:
            className = classObj.name

            for i in range(len(self.data.columns)):
                if str(self.data.columns[i]).strip() == str(self.toPredic).strip():
                    continue

                valueName = x[i]
                interName = str(valueName) + "|" + str(className)

                obj = self.findInterObject(str(valueName) + "|" + str(className))

                if obj == None:
                    self.intersections.append(interElement(interName, self.findObject(className), self.nValues[str(self.data.columns[i]).strip()],classObj.ocurrencias))
                    obj = self.findInterObject(interName)



                classObj.updateProb(obj.calcProb(self.alfa))
            if maxValue < classObj.totalProb:
                maxValue = classObj.totalProb
                maxClass = classObj.name

        for resetObj in self.objects:
            resetObj.resetProb()

        return maxClass

    def separate(self):
        X = self.data.drop([self.data.columns[self.colIndex]], axis=1)
        y = self.data[self.data.columns[self.colIndex]]
        return X, y

    def loadFile(self):
        self.data = pd.read_csv(self.fileName)

    def accuracy_score(self, X, y):
        res = []
        arr = []
        score = []
        nValues = len(X.columns)
        for line in range(len(X)):
            content = X.loc[line]
            for i in content:
                arr.append(i)
            res.append(self.predict(arr))
            arr = []

        for i in range(len(y)):
            score.append(res[i] == y[i])

        count = Counter(score)

        return count[True] / (count[True] + count[False])

    def precision_score(self, X, y):
        res = []

        arr = []
        precisions = []

        for line in range(len(X)):
            content = X.loc[line]
            for i in content:
                arr.append(i)
            res.append(self.predict(arr))
            arr = []

        for o in self.objects:
            positive = o.name
            vn = []
            vp = []
            fn = []
            fp = []
            for i in range(len(y)):

                if res[i] == y[i] and str(y[i]) == positive:
                    vp.append(True)
                elif res[i] == y[i] and str(y[i]) != positive:
                    vn.append(False)
                elif res[i] != y[i] and str(res[i]) == positive:
                    fp.append(False)
                elif res[i] != y[i] and str(res[i]) != positive:
                    fn.append(False)

            if (len(vp) + len(fp)) == 0:
                precision = 0
            else:
                precision = len(vp) / (len(vp) + len(fp))

            precisions.append(precision)

        return sum(precisions) / len(precisions)

    def setColIndex(self, colIndex):
        self.colIndex = colIndex