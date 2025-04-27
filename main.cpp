#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Transition
{
    char fromState;
    char toState;
    char inputSymbol;
    char stackTop;
    char pushSymbol;
};

bool simulatePDA(string input, Transition transitions[], int numTransitions, char startState, char acceptState)
{
    stack<char> pdaStack;
    pdaStack.push('$');
    char currentState = startState;
    int inputIndex = 0;

    while (true)
    {
        bool transitionFound = false;

        for (int i = 0; i < numTransitions; i++)
        {
            Transition t = transitions[i];

            bool inputMatches = (t.inputSymbol == 'e' || (inputIndex < input.length() && t.inputSymbol == input[inputIndex]));
            bool stackMatches = (t.stackTop == 'e' || (!pdaStack.empty() && t.stackTop == pdaStack.top()));

            if (t.fromState == currentState && inputMatches && stackMatches)
            {
                currentState = t.toState;

                if (t.stackTop != 'e' && !pdaStack.empty())
                {
                    pdaStack.pop();
                }

                if (t.pushSymbol != 'e')
                {
                    pdaStack.push(t.pushSymbol);
                }

                if (t.inputSymbol != 'e')
                {
                    inputIndex++;
                }

                transitionFound = true;
                break;
            }
        }

        if (!transitionFound)
        {
            break;
        }

        if (inputIndex == input.length())
        {
            bool epsilonTransitionExists = false;
            for (int i = 0; i < numTransitions; i++)
            {
                if (transitions[i].fromState == currentState && transitions[i].inputSymbol == 'e')
                {
                    epsilonTransitionExists = true;
                    break;
                }
            }
            if (!epsilonTransitionExists)
            {
                break;
            }
        }
    }

    if (!pdaStack.empty() && pdaStack.top() == '$')
    {
        pdaStack.pop();
    }
    return (inputIndex == input.length()) && (currentState == acceptState) && pdaStack.empty();
}

int main()
{
    int numTransitions = 4;
    Transition transitions[] = {
        {'A', 'A', 'a', 'e', 'A'},
        {'A', 'B', 'b', 'A', 'e'},
        {'B', 'B', 'b', 'A', 'e'},
        {'B', 'C', 'e', '$', 'e'}};

    for (int i = 0; i < numTransitions; i++)
    {
        cout << transitions[i].fromState << " " << transitions[i].toState << " "
             << transitions[i].inputSymbol << " " << transitions[i].stackTop << " "
             << transitions[i].pushSymbol << endl;
    }

    char startState = 'A';
    char acceptState = 'C';
    string input;

    cout << "Enter input string: ";
    cin >> input;

    bool accepted = simulatePDA(input, transitions, numTransitions, startState, acceptState);

    cout << "String is " << (accepted ? "ACCEPTED" : "REJECTED") << endl;

    return 0;
}
