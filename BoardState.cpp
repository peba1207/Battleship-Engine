//
// Created by peyto on 2/18/2025.
//

#include "BoardState.h"
using namespace std;
BoardState::BoardState(BoardState *pState) {
for (int i = 0; i<SIZE; i++){
for (int j = 0; j<SIZE; j++){
empty[i][j] = pState->empty[i][j];
ships[i][j] = pState->ships[i][j];
}
}
}

BoardState::BoardState(){
    for (int i = 0; i<SIZE; i++){
        for (int j = 0; j<SIZE; j++){
            empty[i][j] = false;
            ships[i][j] = false;
        }
    }
}
//empty[row][col]
vector<BoardState*>* BoardState::getAllBoards(){
    vector<int> shipSizes = {2, 2, 2, 3, 3, 3, 4};
    int shipCounts[SIZE][SIZE];

    for (auto & shipCount : shipCounts){
        for (int & j : shipCount){
            j = 0;
        }
    }
    vector<BoardState*>* boardStates = getAllBoardsHelper(shipSizes, this);
    for(BoardState* state: *boardStates){
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                shipCounts[i][j] += state->ships[i][j];
            }
        }
    }

    for (auto & shipCount : shipCounts){
        for (int & j : shipCount){
            cout<< j << " ";
        }
        cout << endl;
    }

    return nullptr;
}

vector<BoardState*>* BoardState::getAllBoardsHelper(const vector<int>& shipSizes, BoardState* state){
    /*for(int x :shipSizes){
        cout << x;
    }
    cout << endl;

    cout << state->toString() << endl;*/
    if(shipSizes.empty()){
        auto* end = new vector<BoardState*>;
        end->push_back(state);
        //cout << "AAA" << endl << (state->toString()) << endl;
        return end;
    }
    vector<int> newList = shipSizes;
    auto* output = new vector<BoardState*>();
    int size = newList.back();
    newList.pop_back();
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){

            if(size == 4){
                cout<<"("<<i <<"," << j << ")";
            }
            if (state->validSpot(j, i,size, false) ){
                //call allboardshelper with new state
                auto* newState = new BoardState(state);
                markShip(j, i, size, newState, false);
                vector<BoardState*>* completed = getAllBoardsHelper(newList, newState);
                output->reserve( output->size() + completed->size() );
                output->insert( output->end(), completed->begin(), completed->end() );
                delete completed;
            }
            if (state->validSpot(j, i,size, true) ){
                //call allboardshelper with new state
                auto* newState = new BoardState(state);
                markShip(j, i, size, newState, true);

                //REMOVE
                vector<BoardState*>* completed = getAllBoardsHelper(newList, newState);

                //VERY COSTLY
                output->reserve( output->size() + completed->size() );
                output->insert( output->end(), completed->begin(), completed->end() );

                delete completed;
            }
        }
    }
    delete state;
    return output;
}

bool BoardState::validSpot(int x, int y, int shipSize, bool vert){
    if(!vert){

        if(x+shipSize>SIZE){return false;}
        for(int i = 0; i<shipSize; i++){
            if(empty[y][x+i]){return false;}

        }
        return true;
    } else{
        if(y+shipSize>SIZE){return false;}

        for(int i = 0; i<shipSize; i++) {
            if (empty[y + i][x]) { return false; }
        }
        return true;
    }

}

void BoardState::markShip(int x, int y, int size, BoardState* state, bool vert) {
    int i = 0;
    int max = size;
    if(!vert) {
        if(x>0){i = -1;}
        if(x+size<SIZE){max++;}
        for (; i < max; i++) {
            state->empty[y][x + i] = true;
            if (y > 0) { state->empty[y - 1][x + i] = true; }
            if (y < SIZE - 1) { state->empty[y + 1][x + i] = true; }
        }
        for (int k = 0; k < size; k++) {
            state->ships[y][x + k] = true;
        }
    } else {
        if(y>0){i = -1;}
        if(y+size<SIZE){max++;}
        for (; i < max; i++) {
            state->empty[y+i][x] = true;
            if (x > 0) { state->empty[y + i][x - 1] = true; }
            if (x < SIZE - 1) { state->empty[y + i][x + 1] = true; }
        }
        for (int k = 0; k < size; k++) {
            state->ships[y + k][x] = true;
        }
    }


}

string BoardState::toString() {
    string output;
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(ships[i][j]){
                output += "x";
            }else if(empty[i][j]){
                output += "o";
            }else{
                output += ".";
            }

        }
        output+="\n";
    }
    return output;
}