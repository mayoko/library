// 擬似コードです
State ChokudaiSearch(State firstState) {
    const int maxTurn = 100;
    priority_queue<State> states[maxTurn+1];
    states.push(firstState);
    int chokudaiWidth = 1;
    while (timeCheck()) {
        for (int t = 0; t < maxTurn; t++) {
            for (int i = 0; i < chokudaiWidth; i++) {
                if (states[t].empty()) break;
                State nowState = states[t].top(); states[t].pop();
                foreach (State nextState : nowState.getAllNextState()) {
                    states[t+1].push(nextState);
                }
            }
        }
        chokudaiWidth++;
    }
    State bestState = states[maxTurn].top();
    return bestState;
}
