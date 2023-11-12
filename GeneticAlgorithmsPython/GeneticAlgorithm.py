import random 
import math 


class Solution: 
  def __init__(self, nbVariable,nbconstraint,listConstraint):
        self.solution = [0 for i in range(nbVariable)]
        self.SumConstraint = [0 for i in range(nbconstraint)]
        self.fitnessValue = 0
        valid = True 
        fitnessCalculated = False; 
        self.NbVariable = nbVariable
        self.Nbconstraint = nbconstraint
        self.listConstraint = listConstraint
        self.admissible = True
        

  def sumconstraint(self, matrix):
       self.SumConstraint = [sum([matrix[ind1][ind2] * self.solution[ind2] for ind2 in range(self.NbVariable)])for ind1 in range(self.Nbconstraint)]
       
  def calculatefitnessvalue(self,Price):
        self.fitnessValue = sum([Price[i] * self.solution[i] for i in range(self.NbVariable)]) 
       

  
  def CheckIndividual(self):
        check = True
        for k in range(self.Nbconstraint):
              print(self.SumConstraint[k])
              if(self.SumConstraint[k] > self.listConstraint[k] or self.SumConstraint[k] == 0):
                    check = False
                    break
        if check == False:
              print("La solution n'est pas admissible")
              self.admissible = False
        else:
              "La solution est admissible"  
              self.admissible = True


        
  def addmutation(self):
        indlistadd = [i for i in range(self.NbVariable) if self.solution[i] == 0]
        indice = random.choice(indlistadd)
        self.solution[indice] = 1
        
  def repaire(self):
        indlistadd = [i for i in range(self.NbVariable) if self.solution[i] == 1]
        indice = random.choice(indlistadd)
        self.solution[indice] = 0
        
  def checkandrepaire(self,compteur):
        check = True
        for k in range(self.Nbconstraint):
              print(self.SumConstraint[k])
              if(self.SumConstraint[k] > self.listConstraint[k] or self.SumConstraint[k] == 0):
                    check = False
                    compteur += 1 
                    if(compteur < 1):
                          self.repaire()
                          self.checkandrepaire(compteur)
                    break
        if check == False:
              print("La solution n'est pas admissible")
              self.admissible = False
        else:
              "La solution est admissible"  
              self.admissible = True
        
        
   
        
        
        

        
              
      

        
       

        
        

class GeneticAlgorithm(Solution):
    
  def __init__(self, NbPop,NbInd):
        """Constructeur de notre classe"""
        self.NbInd = NbInd
        self.NbPop = NbPop
        self.NbVariable = 0 
        self.NbConstraint = 0 
        self.Population = []
        self.Sample = [] 
        self.PriceVariable = []
        self.Constraint = []
        self.MatrixConstraint = []
        
  def checknumber(self,lignes,indice):
        ParsedList = []
        compteur1 = 0
        compteur2 = 0
        while(lignes[indice][compteur1] != '\n' and lignes[indice][compteur2] != '\n'):
              while(lignes[indice][compteur2] != " " and lignes[indice][compteur2] != '\n'):
                    compteur2 += 1
              ParsedList.append(int(lignes[indice][compteur1:compteur2]))
              compteur1 = compteur2 + 1
              compteur2 = compteur1

   
              if compteur1 > len(lignes[indice]) - 1:
                    break
        return ParsedList
 
  
  def parseKnapsack(self,text):
      fichier = open(text, "r",encoding="utf8")
      lignes = fichier.readlines()
      tab = [self.checknumber(lignes,indice) for indice in range(len(lignes) - 1)]
      self.NbVariable = tab[0][0]
      self.NbConstraint = tab[0][1]
      self.PriceVariable = [tab[1][ind] for ind in range(self.NbVariable)]
      self.MatrixConstraint = [[tab[2 + ind][j] for j in range(self.NbVariable)] for ind in range(self.NbConstraint)]
      self.constraint = [tab[-1][ind] for ind in range(self.NbConstraint)]
      
 
    
  def initPopulation(self):
      self.Population = [Solution(self.NbVariable,self.NbConstraint,self.constraint) for i in range(self.NbPop)]
      for i in range(self.NbPop):
            
            self.Population[i].solution = [random.randrange(0,2) for i in range(self.NbVariable)]
            self.Population[i].sumconstraint(self.MatrixConstraint)
            self.Population[i].CheckIndividual()
            while(self.Population[i].admissible == False):
                  self.Population[i].solution = [random.randrange(0,2) for i in range(self.NbVariable)]
                  self.Population[i].sumconstraint(self.MatrixConstraint)
                  self.Population[i].CheckIndividual()
            self.Population[i].calculatefitnessvalue(self.PriceVariable)
            
            


                  
                   
  def displayPopulation(self):
        print("The population is: ")
        for i in range(self.NbPop):
              print(self.Population[i].solution)
              
                      
  def displaySample(self):
        print("The sample is: ")
        for i in range(self.NbInd):
              print(self.Sample[i].solution)
              print(self.Sample[i].fitnessValue)

              
              
  def tounament(self):
        
        self.Sample = []


        compteur = 0
        while(compteur < self.NbInd):
              AddList = []
              for i in range(self.NbInd):
                    randomIndividual = random.randrange(0,self.NbPop)
                    AddList.append(self.Population[randomIndividual])
              AddList.sort(key = lambda x: x.fitnessValue, reverse = True )      
              self.Sample.append(AddList[0])
              compteur+=1
              
  def CrossoverMutation(self):
        ind_Parent1 = random.randrange(0,self.NbInd)
        ind_Parent2 = random.randrange(0,self.NbInd)
        ind_crossover = random.randrange(0,self.NbVariable); 
        children1 = Solution(self.NbVariable,self.NbConstraint,self.constraint)
        children2 = Solution(self.NbVariable,self.NbConstraint,self.constraint)
        children1.solution = [0 for i in range(self.NbVariable)]
        children2.solution = [0 for i in range(self.NbVariable)]
        for i in range(ind_crossover):
              children1.solution[i] = self.Sample[ind_Parent1].solution[i]
              children2.solution[i] = self.Sample[ind_Parent2].solution[i]
        for j in range(ind_crossover, self.NbVariable):

              children1.solution[j] = self.Sample[ind_Parent2].solution[j]
              children2.solution[j] = self.Sample[ind_Parent1].solution[j]

        

        Getmuted = random.randrange(3)
        print("choixmutation: ", Getmuted)
        if Getmuted > 0:
              children1.addmutation()
              children2.addmutation()
              children1.sumconstraint(self.MatrixConstraint)
              children2.sumconstraint(self.MatrixConstraint)
              children1.checkandrepaire(0)
              children2.checkandrepaire(0)
              if children1.admissible == True:
                    self.Sample[ind_Parent1] = children1
                    self.Sample[ind_Parent1].calculatefitnessvalue()
              if children2.admissible == True:
                    self.Sample[ind_Parent2] = children2
                    self.Sample[ind_Parent2].calculatefitnessvalue()
                    
                    
                    

  def UpdateEllitismPopulation(self):
        self.Population.sort(key = lambda x: x.fitnessValue, reverse = True)     

        for i in range(self.NbInd):

            self.Population[self.NbPop - i - 1].solution = self.Sample[i].solution; 

        
        
        for i in range(self.NbPop):
               self.Population[i].calculatefitnessvalue(self.PriceVariable)
              
        self.Population.sort(key = lambda x: x.fitnessValue, reverse = True)     




   

  def UpdateFusionPopulation(self):
        Newlist = [self.Population[i] for i in range(self.NbPop)]
        for i in range(self.NbInd):
              Newlist.append(self.Sample[i])
        Newlist.sort(key = lambda x: x.fitnessValue, reverse = True) 
        self.Population = [Newlist[i] for i in range(self.NbPop)]
        
  def resolve(self, Nbgen):
        self.initPopulation()
        self.displayPopulation()
        for i in range(Nbgen):
              self.tounament()
              NbMutation = random.randrange(self.NbInd)
              for j in range(NbMutation):
                    self.CrossoverMutation()
              self.UpdateFusionPopulation()
        self.Population.sort(key = lambda x: x.fitnessValue, reverse = True)
        self.displayPopulation()     

        
            
              

   




    
      




        


              
              
         
         




        
        
            
      



     

 
    

           
    
    

        
  
        
  
        

      
             
        
             
             
            
             
            



             
            
            

            
             
          
            

        
        
        




     






    
      
        

