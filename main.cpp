#include <iostream>
#include <stack>
#include <string>
using namespace std;

struct Transition
{
    char fromState;
    char toState;
    char inputSymbol;
    string stackTop;
    string pushSymbol;
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
            bool stackMatches = false;
            if (t.stackTop.length() == 1)
            {
                stackMatches = (t.stackTop == "e" || (!pdaStack.empty() && t.stackTop[0] == pdaStack.top()));
            }
            else
            {
                stack<char> tempStack;
                stackMatches = true;
                for (int j = 0; j < t.stackTop.length(); j++)
                {
                    if (!pdaStack.empty())
                    {
                        tempStack.push(pdaStack.top());
                        pdaStack.pop();
                    }
                    else
                    {
                        stackMatches = false;
                        break;
                    }
                }
                while (!tempStack.empty())
                {
                    pdaStack.push(tempStack.top());
                    tempStack.pop();
                }
            }

            if (t.fromState == currentState && inputMatches && stackMatches)
            {
                currentState = t.toState;

                if (t.stackTop != "e" && !pdaStack.empty())
                {
                    for (int j = 0; j < t.stackTop.length(); j++)
                    {
                        pdaStack.pop();
                    }
                }

                if (t.pushSymbol != "e")
                {
                    for (int j = 0; j < t.pushSymbol.length(); j++)
                    {
                        pdaStack.push(t.pushSymbol[j]);
                    }
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
        {'A', 'A', 'a', "e", "A"},
        {'A', 'B', 'b', "AA", "e"},
        {'B', 'B', 'b', "AA", "e"},
        {'B', 'C', 'e', "$", "e"}};

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
