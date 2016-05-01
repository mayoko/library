// 擬似コードです
State BeamSearch(State FirstState) {
    priority_queue<State> nowStates;
    nowStates.push(FirstState);
    const int k = 100; // beam width

    for (int t = 0; t < MaxTurn; t++) {
        priority_queue<State> nextStates;
        for (int i = 0; i < k; i++) {
            if (nowStates.empty()) break;
            State nowState = nowStates.top(); nowStates.pop();
            foreach (State nextState : nowState.getAllNextState()) {
                nextStates.push(nextState);
            }
        }
        nowStates = nextStates;
    }
    State bestState = nowStates.top();
    return bestState;
}
