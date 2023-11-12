#include<vector> 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>  
#include <algorithm>
struct Solution{
    
    std::vector<int> *solution;
    std::vector<float> * SumConstraint; 
    float FitnessValue;
    bool valid;
    bool fitnessCalculated;

    Solution(){
        solution = new std::vector<int>;
        SumConstraint = new std::vector<float>;
        FitnessValue = 0;
         valid = true;
         fitnessCalculated = false; 
    

    }

    float operator()(Solution ind1, Solution ind2) { return ind1.FitnessValue > ind2.FitnessValue; }





    ~Solution(){

    }


};



struct GeneticAlgorithm: Solution{

    int NbVariable;
    int NbConstraints;
    int IndCandidat;
    int NbPop;
    int Nbind; 


    /* Price function */
    std::vector<int> * Price;
    /* Utility function */

    /*Matrix of constraint*/
    std::vector<float>*CostMatrix;
    /*Vector of solution*/





    std::vector<float> * constraint;
    std::vector<Solution> * Population; 
    std::vector<Solution> * Echantillon; 




 
    GeneticAlgorithm(std::string name, int nbpop, int nbind){

        int k = 0;
        int number;
        int candidat; 
        Nbind = nbind;
        NbPop = nbpop;  
        Population = new std::vector<Solution>;
        

            std::ifstream fichier(name);
                if(fichier){

                   

                     fichier >> NbVariable;
                     fichier >> NbConstraints; 

                     std::cout << NbVariable << std::endl;

             


                     Price = new std::vector<int>; 
                     CostMatrix = new std::vector<float>[NbConstraints];
                     constraint = new std::vector<float>[NbConstraints]; 

                     



                     while(k < NbVariable){
                        fichier >> number; 
                        Price[0].push_back(number);
                        k++;
                        };


                     for(int i = 0; i < NbConstraints; i++){
                        k = 0;

                        while(k < NbVariable){
                            fichier >> number; 
                            CostMatrix[i].push_back(number);
                            k++;
                        }
                     }


              
                        for(int i = 0; i < NbConstraints; i++){
                        fichier >> number;
                        std::cout << "la contrainte est: " << number << std::endl;
                        constraint[i].push_back(number);

                     } 
                     
                }
    }


 

    
    void sumconstraint(Solution & individual){
        float addconstraint;
        for(int j = 0;j < NbConstraints; j++){
            addconstraint = 0;
            for(int i = 0; i < NbVariable; i++){
               addconstraint += CostMatrix[j][i] * individual.solution[0][i];


            }
            individual.SumConstraint->push_back(addconstraint);
                std::cout <<  individual.SumConstraint[0][j] << std::endl;  
        }
    }

    void checkPopindividual(Solution & individual, int & compteur){
        bool check = true;

        for(int i = 0; i < NbConstraints; i++){
            std::cout << "La contrainte est: " << constraint[i][0] << std::endl;
            if( individual.SumConstraint[0][i] > constraint[i][0] || individual.SumConstraint[0][i] == 0){
             
                check = false;
                break;
            }
        }

        std::cout << "le booléen est: " << check << std::endl;

        if(check == false){
            std::cout << "La solution n'est pas admissible" << std::endl; 

        }else{

        std::cout << "La solution est admissible" << std::endl; 
        Population->push_back(individual);
        compteur++; 

        }
   


        }
        

    


    void initPopulation(){
        int compteur = 0; 
        int nbrandomseeds;
        int indice; 
        int value;
 while(compteur < NbPop)
            {
           Solution individual; 
            for(int k = 0; k < NbVariable; k++){
                 individual.solution->push_back(0);
            }
            nbrandomseeds = rand() %  NbVariable;
            std::cout << nbrandomseeds << std::endl;  
            for(int j = 0; j < nbrandomseeds; j++){
                indice = rand() % NbVariable ;
                value = rand() % 2;
                if(value > 0){

                  individual.solution[0][indice] = 1; 


                }

            }
            sumconstraint( individual);
            displayIndividual(individual);
            checkPopindividual(individual,compteur);
    }

    }

    void displayIndividual(Solution & individual){

        std::cout << "La solution créée est: "; 
        for(int i = 0; i < NbVariable; i ++){

            std::cout << " " << individual.solution[0][i];

        }

        std::cout << std::endl; 

        std::cout << "Les contraintes sont: "; 
        for (int j = 0; j < NbConstraints; j++){

            std::cout << " " << individual.SumConstraint[0][j]; 

        }
        std::cout << std::endl;
    }


    void displayPopulation(){
        std::cout << "La population est: " << std::endl; 
        for(int i = 0;i < NbPop; i++){
            std::cout << "individu_" << i + 1 << " : ";
            for(int j = 0; j < NbVariable; j++){

                std::cout << Population[0][i].solution[0][j] << " ";
            }

            std::cout << std::endl;


        }

      

    }

      void displayEchantillon(){
        std::cout << "L'Echantillon est: " << std::endl; 
        for(int i = 0;i < Nbind; i++){
            std::cout << "individu_" << i + 1 << " : ";
            for(int j = 0; j < NbVariable; j++){

                std::cout << Echantillon[0][i].solution[0][j] << " ";
            }

            std::cout << std::endl;


        }
      }
                
                



    

    void displayCostMatrix(){
        for(int i = 0; i < NbConstraints; i++){
            for(int j = 0; j < NbVariable; j++)
            {
                std::cout << CostMatrix[i][j] << " ";

        }

        std::cout << std::endl;
        }
    }


    void fitnessValuePop(/*std::vector<Solution> & Echantillon, int dim*/){
        float fitnessvalue; 
        int compteur = 0;
        while(compteur < NbPop)
        {
            fitnessvalue = 0; 
            if(Population[0][compteur].fitnessCalculated == false){
                for(int i = 0; i < NbVariable; i++){
                    fitnessvalue += Population[0][compteur].solution[0][i] * Price[0][i];
                }
                Population[0][compteur].FitnessValue = fitnessvalue; 
                Population[0][compteur].fitnessCalculated = true;
            }

            compteur++;


        }
    }

    void fitnessValueSample(){
        float fitnessvalue; 
        int compteur = 0;
        while(compteur < Nbind)
        {
            fitnessvalue = 0; 
            if(Echantillon[0][compteur].fitnessCalculated == false){
                for(int i = 0; i < NbVariable; i++){
                    fitnessvalue += Echantillon[0][compteur].solution[0][i] * Price[0][i];
                }
                Echantillon[0][compteur].FitnessValue = fitnessvalue; 
                Echantillon[0][compteur].fitnessCalculated = true;
            }

            compteur++;


        }


    }

    void Tournament(){
        Echantillon = new std::vector<Solution>;

        std::vector<Solution> List;
        int compteur = 0;
        int randomIndividual;
        while(compteur < Nbind){
            for(int i = 0; i < Nbind; i++){
            randomIndividual = rand() % NbPop;
            List.push_back(Population[0][randomIndividual]);

            }

         sort(List.begin(), List.end(),Solution());
         Echantillon->push_back(List[0]);
         compteur++; 




        }




    }

    void CrossoverMutation(){
        int ind_Parent1 = rand() % Nbind;
        int ind_Parent2 = rand() % Nbind;
        int ind_crossover = rand() % NbVariable; 
        int Getmuted;
        Solution Enfant1; 
        Solution Enfant2;
        /*for(int k = 0; k < NbVariable; k++){

        } */
        for(int i = 0; i < ind_crossover; i++){
            Enfant1.solution->push_back(Echantillon[0][ind_Parent1].solution[0][i]);
            Enfant2.solution->push_back(Echantillon[0][ind_Parent2].solution[0][i]);
            
        }

        for(int j = ind_crossover; j < NbVariable; j++){

            Enfant2.solution->push_back(Echantillon[0][ind_Parent1].solution[0][j]);
            Enfant1.solution->push_back(Echantillon[0][ind_Parent2].solution[0][j]);

        }

        Getmuted = rand() % 3;
        std::cout << "choixmutation: " << Getmuted << std::endl;
        if(Getmuted > 0){
        
        Addmutation(Enfant1);
        std::cout << "Enfant2" <<  std::endl;

        Addmutation(Enfant2);

        }
        
        sumconstraint(Enfant1);
        sumconstraint(Enfant2);

        CheckSampleindividual(Enfant1,0,ind_Parent1);
        CheckSampleindividual(Enfant2,0,ind_Parent2);


}

        void CheckSampleindividual(Solution & individual, int k, int ind){
        int compteur = k;
        bool check = true;
        for(int i = 0; i < NbConstraints; i++){
            std::cout << "La contrainte est: " << constraint[i][0] << std::endl;
            if( individual.SumConstraint[0][i] > constraint[i][0] || individual.SumConstraint[0][i] == 0){
             
                check = false;
                break;
            }
        }
        std::cout << "le booléen est: " << check << std::endl;
        if(check == false){
            std::cout << "La solution n'est pas admissible" << std::endl; 
        
            if(compteur < 1){
                RepaireSample(individual);
                compteur++;
                CheckSampleindividual(individual, compteur, ind);

            }
            }else{
                std::cout << "La solution est admissible" << std::endl; 
                Echantillon[0][ind] = individual;
                compteur++;
                }
            }



    void Addmutation(Solution & Enfant){

        std::cout << "mutation enfant" << std::endl;
        int compteur = 0;
        int nb_one = 0;
        int indice;
        int choix; 
        

        for(int i = 0; i < NbVariable; i++){
            if(Enfant.solution[0][i] < 1){
            nb_one++;  
            }
        }

        if(nb_one > 0){
        int listChoix[nb_one];
        std::cout << "nbone: " << nb_one << std::endl;
        for(int i = 0; i < NbVariable; i++){
            if(Enfant.solution[0][i] < 1){
                listChoix[compteur] = i;
                compteur++;
            }
        }

        indice = rand() % compteur;
        std::cout << "indice Enfant: " << indice << std::endl;
        choix = listChoix[indice];
        Enfant.solution[0][choix] = 1;
        std::cout << "Enfant Solution: " <<  Enfant.solution[0][choix] << std::endl;
        }else{
            std::cout << "Pas de mutation possible" << std::endl;
        }




    }




    void RepaireSample(Solution & Enfant){
        int compteur = 0;
        int nb_one = 0;
        int indice;
        int choix; 
        

        for(int i = 0; i < NbVariable; i++){
            if(Enfant.solution[0][i] > 0){
            nb_one++;  
            }
        }
        int listChoix[nb_one];
        for(int i = 0; i < NbVariable; i++){
            if(Enfant.solution[0][i] > 0){
                listChoix[compteur] = i;
                compteur++;
            }
        }

        indice = rand() % compteur;
        std::cout << "indice à supprimer: " << indice << std::endl;
        choix = listChoix[indice];
        Enfant.solution[0][choix] = 0;

    }


   void UpdateEllitismPopulation(){  

        int k = 0;    

        sort(Population[0].begin(), Population[0].end(),Solution());

        for(int i = 0; i < Nbind; i++){

            Population[0][NbPop - i - 1].solution = Echantillon[0][i].solution; 

        }
        
    fitnessValuePop();
    sort(Population[0].begin(), Population[0].end(),Solution());




   }

   void UpdateFusionPopulation(){
    fitnessValueSample();

    std::vector<Solution> List;

    for(int i = 0; i < NbPop; i++){
        List.push_back(Population[0][i]);
    }

    for(int j = 0; j < Nbind; j++){

        List.push_back(Echantillon[0][j]);
    }


    sort(List.begin(), List.end(),Solution());


    for(int k = 0; k < NbPop; k++){
        Population[0][k] = List[k];
    
    }
   }

void resolve(int Nbgen){ 
int nbCrossover;
initPopulation();
displayCostMatrix();
displayPopulation();
fitnessValuePop();
for(int i = 0; i < Nbgen; i++){
    Tournament();
    nbCrossover = rand() % Nbind;
    for(int k = 0; k < nbCrossover; k++){
    CrossoverMutation();
    }
    UpdateFusionPopulation();
   }

    sort(Population[0].begin(), Population[0].end(),Solution());

   displayPopulation();
   }

/*

    void displaycurrentsolution(){
        std::cout << "La solution courrante est: " << std::endl;
        for(int i = 0; i < NbVariable ; i++){
            std::cout <<   CurrentSolution[0][i]  << std::endl;
            }
        }
    
    
    void displayNeighborSolution(){
            std::cout << "La solution de voisinage est: " << std::endl;
        for(int i = 0; i < NbVariable ; i++){
            std::cout <<   NeighbourSolution[0][i]  << std::endl;
            }
        }

    void displayOptSolution(){

              std::cout << "La solution optimale est: " << std::endl;
        for(int i = 0; i < NbVariable ; i++){
            std::cout <<   OptSolution[0][i]  << std::endl;
            }
        }


    

    

    void CopyNeighborSolution(){
        for(int i = 0; i < NbVariable; i++){
                NeighbourSolution[0][i] = CurrentSolution[0][i];
            }
        }

        void CopyCurrentSolution(){
        for(int i = 0; i < NbVariable; i++){
               CurrentSolution[0][i] =  NeighbourSolution[0][i] ;
            
        }
        }
    
    void Sum_Constraint(){

          for(int i = 0; i < NbConstraints; i++){
                Sumconstraint[0][i] = 0;
            }

     
        for(int j = 0;j < NbConstraints; j++){
            for(int i = 0; i < NbVariable; i++){
                Sumconstraint[0][j] += CostMatrix[j][i] * NeighbourSolution[0][i];
            }
        }

        std::cout << Sumconstraint[0][0] << " " << Sumconstraint[0][1] << std::endl;


    }

    float Delta(){
        float Delta = 0;
        for(int i = 0; i < NbVariable; i++){
            Delta += NeighbourSolution[0][i] * Price[0][i] - CurrentSolution[0][i] * Price[0][i];
            }
            return Delta;
        }
        

       float DeltaZopt(){
        float delta = 0;
        for(int i = 0; i < NbVariable; i++){
            delta += NeighbourSolution[0][i] * Price[0][i] - OptSolution[0][i] * Price[0][i];
            }
            return delta;
        }

    

   


*/
};
