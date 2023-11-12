#include<iostream> 
#include<vector> 
#include<fstream> 
#include "GeneticAlgorithm.hpp"

int main(){
      /*La fonction checkup n'est pas bonne */
 
   std::string file = "Knapsack.txt";

   GeneticAlgorithm Genetique = GeneticAlgorithm(file,500,30);
   Genetique.resolve(10);






  




}
  






