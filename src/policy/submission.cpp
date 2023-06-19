#include <cstdlib>
#include<iostream>


#include "../state/state.hpp"
#include "./submission.hpp"

//long long int count = 0;
int int_min1 = -1000000;
int int_max1 = 1000000;

/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move submission::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int maxScore = state->player==0 ?int_min1:int_max1;
  Move bestMove = actions[0];

  for(auto move : actions){
    State* nextState = state->next_state(move);

    //Call the minimax function to evaluate the score
    int score = minimax(nextState, depth-1, state->player, int_min1, int_max1);

    //Update the best move if the score is higher
    if(state->player==0&&score > maxScore){
        maxScore = score;
        bestMove = move;
    }
    else if(state->player==1&&score<maxScore){
        maxScore = score;
        bestMove = move;
    }
  }
 // fout<<"count: "<<count<<std::endl;
  return bestMove;
  //return actions[(rand()+depth)%actions.size()];
}

int submission::minimax(State *state, int depth, bool whiteplayer, int alpha, int beta){

  if(!state->legal_actions.size())
  state->get_legal_actions();
  
  //Base case: max depth reached or game over (terminal node)
  if (depth == 0 || state->legal_actions.empty()) {
    return state->evaluate();
  }
    if(whiteplayer){ //white player = find max
        int maxScore = int_min1;
        state->get_legal_actions();


        for (auto move : state->legal_actions){
            State* nextState = state->next_state(move);
            int score = minimax(nextState, depth-1, false, alpha, beta);
            maxScore = std::max(maxScore, score);
            alpha = std::max(alpha, score);

            //alpha beta pruning
            if(alpha>=beta){
                break;
            }
        }
        return maxScore;
    }else{ //black player = find minimal
        int minScore = int_max1;
        state->get_legal_actions();

        for (auto move : state->legal_actions){
            State* nextState = state->next_state(move);
            int score = minimax(nextState, depth-1, true, alpha, beta);
            minScore = std::min(minScore, score);
            beta = std::min(beta, score);

            //alpha beta pruning
            if(beta <= alpha){
                break;
            }
        }
        return minScore;   
    }
}