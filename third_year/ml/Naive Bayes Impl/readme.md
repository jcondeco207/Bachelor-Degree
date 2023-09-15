# Naive Bayes Implementation
### Machine Learning 2022/2023 - Évora University

This practical work aims to reconcile the knowledge acquired in the Machine Learning course to implement a class that allows the use of the Naive Bayes algorithm with nominal data type in the scikit-learn environment, with a smoothed estimator, and evaluate the classifier using accuracy and precision metrics.

The code includes two classes: Element and interElement, and the NaiveBayesUevora class that contains the main implementation of the algorithm.

The Element class represents the classes to be predicted, and it has attributes such as the number of occurrences of each class, the total number of samples, the alpha value used for Laplace smoothing, and the number of possible values for each feature. The updateProb method updates the probability of the class given a new observation, and the calcProb method calculates the probability of the class.

The interElement class represents the intersection of a feature value and a class, and it has attributes such as the number of occurrences of the intersection, the class it belongs to, the number of possible values for the feature, and the number of occurrences of the class. The calcProb method calculates the probability of the intersection given an alpha value for Laplace smoothing.

The NaiveBayesUevora class has methods to set the alpha value and the file name to read data from. The fit method trains the model using the data provided, and the predict method predicts the class for a new observation. The findOcurrencies method finds the number of occurrences of a given class, findObject finds a class given its name, and findInterObject finds an intersection given its name.

This work was elaborated by João Rodrigo Condeço, Joana Carrasqueira and Diogo Mestre.