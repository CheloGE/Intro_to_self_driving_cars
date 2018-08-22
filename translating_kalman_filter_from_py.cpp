#include <iostream>
#include <vector>
#include <string>
#include <numeric>

typedef std::string string;
typedef std::vector<double> tVectorFloat;
typedef std::vector<string> tVectorString;
typedef std::vector<int> tVectorInt;
const  tVectorString world = {"green","red","red","green","green"};
tVectorFloat sense (tVectorFloat, string);
tVectorFloat move (tVectorFloat, int);

int main(){
    tVectorFloat p(5,0.2);
    tVectorString measurements = {"red","red"};
    tVectorInt motions(2,1);
    for (int i = 0; i < measurements.size(); i++)
    {
        p = sense(p,measurements[i]);
        p = move(p, motions[i]);
    }
    
    for(auto element : p)
    {
        std::cout << element << ' ';
    }
    int a = -1;
    int b = 5;

    return 0;
}

tVectorFloat sense (tVectorFloat probabilities, string measurement){
    double pHit = 0.6;
    double pMiss = 0.2;
    tVectorFloat q;
    for (int i = 0; i < probabilities.size(); i++)
    {
        bool hit = (measurement==world[i]); 
        q.push_back(probabilities[i]*(hit*pHit+(1-hit)*pMiss));
    }
    double sum_of_elems = std::accumulate(q.begin(), q.end(), 0.0d);
    
    for (int i = 0; i < q.size(); i++)
    {
        q[i] = q[i]/sum_of_elems;
    }
    return q;
}
tVectorFloat move (tVectorFloat probabilities, int movement){
    double pExact = 0.8;
    double pOvershoot = 0.1;
    double pUndershoot = 0.1;
    tVectorFloat q;
    
    for (int i = 0; i < probabilities.size(); i++)
    {
        int size_p = probabilities.size();
        int shift = i-movement; 
        int shift_over = i-movement-1;
        int shift_under = i-movement+1;
        if (shift<0)
        {
            shift= size_p+(shift%size_p);
        } 
        else if(shift>=0)
        {
            shift = shift % size_p;
        }
        if (shift_over<0)
        {
            shift_over = size_p+(shift_over%size_p);
        } 
        else if(shift_over>=0)
        {
            shift_over = shift_over % size_p;
        }
        if (shift_under<0)
        {
            shift_under = size_p+(shift_under%size_p);
        } 
        else if (shift_under >=0)
        {
            shift_under = shift_under % size_p;
        }
        double prob_after_move = pExact * probabilities[shift];
        prob_after_move += pOvershoot * probabilities[shift_over];
        prob_after_move += pUndershoot * probabilities[shift_under];
        q.push_back(prob_after_move);
    }
    return q;
}
