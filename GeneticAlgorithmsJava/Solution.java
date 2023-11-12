
public class Solution implements Comparable<Solution>{

    double[] solution;
    double[] SumConstraint; 
    float FitnessValue;
    boolean valid;
    boolean fitnessCalculated;

    Solution(int NbVariable, int NbConstraint){
        solution = new double[NbVariable];
        SumConstraint = new double[NbConstraint];
        FitnessValue = 0;
        valid = true;
        fitnessCalculated = false; 
    

    }
    

    public int compareTo(Solution s2) {

        int result; 
        if (this.FitnessValue > s2.FitnessValue){
            result = 1;
        }else{
            result = -1;
        }
        return result; 

    }






 
    
}
