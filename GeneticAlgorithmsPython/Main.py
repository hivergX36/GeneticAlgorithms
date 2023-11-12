from GeneticAlgorithm import GeneticAlgorithm
import random
import os


fileName = "knapsack.txt"
os.chdir("GeneticAlgorithmsPython")
print(os.getcwd()) 


geneticAlgorithme = GeneticAlgorithm(50,20)
geneticAlgorithme.parseKnapsack(fileName)
geneticAlgorithme.resolve(10)