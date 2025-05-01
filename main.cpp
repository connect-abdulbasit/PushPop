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
    int option;
    int numTransitions;
    char startState;
    char acceptState;
    string input;
    bool accepted;

    do
    {
        cout << "Select what do you want : " << endl;
        cout << "1.a^n b^n \n2.a^2n b^2n \n3.a^nb^nc^md^m  \n4.a^nb^mc^md^n \n5.a^nb^2n \n6. \n7. \n8. \n9. \n10. \n11.Exit" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            numTransitions = 4;
            static Transition PDA1[] = {
                {'A', 'A', 'a', "e", "A"},
                {'A', 'B', 'b', "A", "e"},
                {'B', 'B', 'b', "A", "e"},
                {'B', 'C', 'e', "$", "e"}};

            startState = 'A';
            acceptState = 'C';

            cout << "Enter input string: ";
            cin >> input;

            accepted = simulatePDA(input, PDA1, numTransitions, startState, acceptState);

            cout << "String is " << (accepted ? "ACCEPTED" : "REJECTED") << endl;

            break;

        case 2:
            numTransitions = 4;
            static Transition PDA2[] = {
                {'A', 'A', 'a', "e", "A"},
                {'A', 'B', 'b', "AA", "e"},
                {'B', 'B', 'b', "AA", "e"},
                {'B', 'C', 'e', "$", "e"}};

            startState = 'A';
            acceptState = 'C';

            cout << "Enter input string: ";
            cin >> input;

            accepted = simulatePDA(input, PDA2, numTransitions, startState, acceptState);

            cout << "String is " << (accepted ? "ACCEPTED" : "REJECTED") << endl;

            break;

        case 3:
            numTransitions = 8;
            static Transition PDA3[] = {
                {'A', 'A', 'a', "e", "A"},
                {'A', 'B', 'b', "A", "e"},
                {'B', 'B', 'b', "A", "e"},
                {'B', 'C', 'c', "e", "C"},
                {'C', 'C', 'c', "e", "C"},
                {'C', 'D', 'd', "C", "e"},
                {'D', 'D', 'd', "C", "e"},
                {'D', 'E', 'e', "$", "e"}

            };

            startState = 'A';
            acceptState = 'E';

            cout << "Enter input string: ";
            cin >> input;

            accepted = simulatePDA(input, PDA3, numTransitions, startState, acceptState);

            cout << "String is " << (accepted ? "ACCEPTED" : "REJECTED") << endl;
            break;

        case 4:
            numTransitions = 8;
            static Transition PDA4[] = {
                {'A', 'A', 'a', "e", "A"},
                {'A', 'B', 'b', "e", "B"},
                {'B', 'B', 'b', "e", "B"},
                {'B', 'C', 'c', "B", "e"},
                {'C', 'C', 'c', "B", "e"},
                {'C', 'D', 'd', "A", "e"},
                {'D', 'D', 'd', "A", "e"},
                {'D', 'E', 'e', "$", "e"}

            };

            startState = 'A';
            acceptState = 'E';

            cout << "Enter input string: ";
            cin >> input;

            accepted = simulatePDA(input, PDA4, numTransitions, startState, acceptState);

            cout << "String is " << (accepted ? "ACCEPTED" : "REJECTED") << endl;
            break;

        case 5:

        numTransitions = 5;
            static Transition PDA5[] = {
                {'A', 'A', 'a', "e", "A"},
                {'A', 'B', 'b', "A", "e"},
                {'B', 'C', 'b', "e", "e"},
                {'C', 'A', 'e', "e", "e"},
                {'A', 'D', 'e', "$", "e"},
            
            };

            startState = 'A';
            acceptState = 'D';

            cout << "Enter input string: ";
            cin >> input;

            accepted = simulatePDA(input, PDA5, numTransitions, startState, acceptState);

            cout << "String is " << (accepted ? "ACCEPTED" : "REJECTED") << endl;

            break;

        case 6:

            break;

        case 7:
            break;

        case 8:
            break;

        case 9:
            break;

        case 10:
            break;

        case 11:
            cout << "Exit Successfully : Thank You !!" << endl;
            break;

        default:
            cout << "Invalid Option : Try Again !!" << endl;
            break;
        }
    } while (option != 11);

    return 0;
}
