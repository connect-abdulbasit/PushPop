#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Transitions
{
    char O; // Origin state
    char F; // Final state
    char I; // Input symbol
    char A; // Stack top symbol
    char D; // Push symbol
};

bool simulatePDA(string input, Transitions transitions[], int N, char startState, char acceptState)
{
    stack<char> PDAStack;
    PDAStack.push('$');
    char currentState = startState;
    for (int i = 0; i < input.length(); i++)
    {
        char inputSymbol = input[i];
        int transitionFound = 0;
        for (int j = 0; j < N; j++)
        {
            if (transitions[j].O == currentState && (transitions[j].I == inputSymbol || transitions[j].I == 'e'))
            {
                currentState = transitions[j].F;
                if (transitions[j].D != 'e')
                {
                    PDAStack.push(transitions[j].A);
                }
                if (transitions[j].A != 'e')
                {
                    PDAStack.pop();
                }
                transitionFound = 1;
                break;
            }
        }
        if (!transitionFound)
        {
            cout << "No transition found for input symbol " << inputSymbol << " in state " << currentState << endl;
            return false;
        }
    }
    if (PDAStack.top() == '$')
    {
        PDAStack.pop();
    }
    return currentState == acceptState && PDAStack.empty();
}

int main()
{
    int N;
    // cout << "Enter number of transitions: ";
    // cin >> N;

    // Transitions transition[N];
    // cout << "For each transition, enter:\n";
    // cout << "Origin state, Final state, Input symbol (e for epsilon),\n";
    // cout << "Stack top symbol, Push symbol (e for no push)\n";

    // for (int i = 0; i < N; i++) {
    //     cout << "Enter transition " << i + 1 << ": ";
    //     cin >> transition[i].O >> transition[i].F >> transition[i].I
    //         >> transition[i].A >> transition[i].D;
    // }
    N = 5;
    Transitions transition[N] = {
        {'A', 'B', 'e', '$', 'a'},
        {'B', 'B', 'a', 'a', 'a'},
        {'B', 'C', 'b', 'a', 'a'},
        {'C', 'C', 'b', 'a', 'a'},
        {'C', 'D', 'e', 'e', 'e'}};

    char startState, acceptState;
    // cout << "Enter start state: ";
    // cin >> startState;
    // cout << "Enter accept state: ";
    // cin >> acceptState;
    startState = 'A';
    acceptState = 'C';
    string input;
    cout << "Enter input string: ";
    cin >> input;

    bool accepted = simulatePDA(input, transition, N, startState, acceptState);
    cout << "String is " << (accepted ? "ACCEPTED" : "REJECTED") << endl;

    return 0;
}