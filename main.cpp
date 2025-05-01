#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

class Transition {
public:
    char fromState;
    char toState;
    char inputSymbol;
    string stackTop;
    string pushSymbol;

    Transition(char from, char to, char input, string top, string push)
        : fromState(from), toState(to), inputSymbol(input), stackTop(top), pushSymbol(push) {}
};

class PDA {
private:
    vector<Transition> transitions;
    char startState;
    char acceptState;

public:
    PDA(char start, char accept, vector<Transition> trans)
        : startState(start), acceptState(accept), transitions(trans) {}

    bool simulate(string input) {
        stack<char> pdaStack;
        pdaStack.push('$');
        char currentState = startState;
        int inputIndex = 0;

        while (true) {
            bool transitionFound = false;

            for (Transition& t : transitions) {
                bool inputMatches = (t.inputSymbol == 'e' || (inputIndex < input.length() && t.inputSymbol == input[inputIndex]));
                bool stackMatches = false;

                if (t.stackTop.length() == 1) {
                    stackMatches = (t.stackTop == "e" || (!pdaStack.empty() && t.stackTop[0] == pdaStack.top()));
                } else {
                    stack<char> temp;
                    stackMatches = true;
                    for (char ch : t.stackTop) {
                        if (!pdaStack.empty()) {
                            temp.push(pdaStack.top());
                            pdaStack.pop();
                        } else {
                            stackMatches = false;
                            break;
                        }
                    }
                    while (!temp.empty()) {
                        pdaStack.push(temp.top());
                        temp.pop();
                    }
                }

                if (t.fromState == currentState && inputMatches && stackMatches) {
                    currentState = t.toState;

                    if (t.stackTop != "e" && !pdaStack.empty()) {
                        for (int j = 0; j < t.stackTop.length(); j++) {
                            pdaStack.pop();
                        }
                    }

                    if (t.pushSymbol != "e") {
                        for (int j = t.pushSymbol.length() - 1; j >= 0; j--) {
                            pdaStack.push(t.pushSymbol[j]);
                        }
                    }

                    if (t.inputSymbol != 'e') {
                        inputIndex++;
                    }

                    transitionFound = true;
                    break;
                }
            }

            if (!transitionFound) break;

            if (inputIndex == input.length()) {
                bool epsilonExists = false;
                for (Transition& t : transitions) {
                    if (t.fromState == currentState && t.inputSymbol == 'e') {
                        epsilonExists = true;
                        break;
                    }
                }
                if (!epsilonExists) break;
            }
        }

        if (!pdaStack.empty() && pdaStack.top() == '$') {
            pdaStack.pop();
        }

        return (inputIndex == input.length()) && (currentState == acceptState) && pdaStack.empty();
    }
};

PDA getPDAForOption(int option) {
    switch (option) {
    case 1:
        return PDA('A', 'C', {
            {'A','A','a',"e","A"},
            {'A','B','b',"A","e"},
            {'B','B','b',"A","e"},
            {'B','C','e',"$","e"}
        });
    case 2:
        return PDA('A', 'C', {
            {'A','A','a',"e","A"},
            {'A','B','b',"AA","e"},
            {'B','B','b',"AA","e"},
            {'B','C','e',"$","e"}
        });
    case 3:
        return PDA('A', 'C', {
            {'A','A','a',"e","A"},
            {'A','B','b',"AAA","e"},
            {'B','B','b',"AAA","e"},
            {'B','C','e',"$","e"}
        });
    case 4:
        return PDA('A', 'D', {
            {'A','A','a',"e","A"},
            {'A','B','b',"e","e"},
            {'B','C','b',"A","e"},
            {'C','B','b',"e","e"},
            {'C','D','e',"$","e"}
        });
    case 5:
        return PDA('A', 'E', {
            {'A','A','a',"e","A"},
            {'A','B','b',"e","e"},
            {'B','C','b',"e","e"},
            {'C','D','b',"A","e"},
            {'D','C','b',"e","e"},
            {'D','E','e',"$","e"}
        });
    case 6:
        return PDA('A', 'F', {
            {'A','B','a',"e","e"},
            {'B','C','a',"e","A"},
            {'C','B','a',"e","e"},
            {'C','D','b',"e","e"},
            {'D','E','b',"A","e"},
            {'E','D','b',"e","e"},
            {'E','F','e',"$","e"}
        });
    case 7:
        return PDA('A', 'D', {
            {'A','A','a',"e","A"},
            {'A','B','b',"A","e"},
            {'B','B','b',"A","e"},
            {'B','C','e',"A","e"},
            {'C','D','e',"$","e"}
        });
    case 8:
        return PDA('A', 'D', {
            {'A','A','a',"e","A"},
            {'A','B','b',"e","B"},
            {'B','B','b',"e","B"},
            {'B','C','c',"A","e"},
            {'B','C','c',"B","e"},
            {'C','C','c',"A","e"},
            {'C','C','c',"B","e"},
            {'C','D','e',"$","e"}
        });
    case 9:
        return PDA('A', 'E', {
            {'A','A','a',"e","A"},
            {'A','B','b',"A","e"},
            {'B','B','b',"A","e"},
            {'B','C','c',"e","C"},
            {'C','C','c',"e","C"},
            {'C','D','d',"C","e"},
            {'D','D','d',"C","e"},
            {'D','E','e',"$","e"}
        });
    case 10:
        return PDA('A', 'E', {
            {'A','A','a',"e","A"},
            {'A','B','b',"e","B"},
            {'B','B','b',"e","B"},
            {'B','C','c',"B","e"},
            {'C','C','c',"B","e"},
            {'C','D','d',"A","e"},
            {'D','D','d',"A","e"},
            {'D','E','e',"$","e"}
        });
    default:
        cout << "Invalid option. Try again.\n";
        return PDA('A', 'A', {});
    }
}

int main() {
    int option;
    string input;

    do {
        cout << "\nSelect the language:\n";
        cout << "1. a^n b^n (n>0)\n2. a^2n b^n (n>0)\n3. a^3n b^n (n>0)\n4. a^n b^2n (n>0)\n5. a^n b^3n (n>0)\n";
        cout << "6. a^2n b^2n (n>0)\n7. a^n b^m (n>m>0)\n8. a^n b^m c^(n+m) (n,m>0)\n";
        cout << "9. a^n b^n c^m d^m (n,m>0)\n10. a^n b^m c^m d^n (n,m>0)\n11. Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        if (option >= 1 && option <= 10) {
            cout << "Enter input string: ";
            cin >> input;
            PDA pda = getPDAForOption(option);
            bool result = pda.simulate(input);
            cout << "String is " << (result ? "ACCEPTED" : "REJECTED") << endl;
        }
        else if (option != 11) {
            cout << "Invalid option. Try again.\n";
        }
    } while (option != 11);

    cout << "Exit Successfully. Thank You!\n";
    return 0;
}
