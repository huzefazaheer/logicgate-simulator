#include <iostream>
#include <vector>

enum gatetype{
    AND,
    OR,
    NOR,
    NAND,
    NOT,
    XOR,
    XNOR,
};

class Node
{
public:
    std::vector <Node*> inputs;
    virtual bool getOutput() = 0;
    virtual ~Node() = default;
};

class InputNode: public Node
{
    private:
        bool input;

    public:
        InputNode(bool initalState = 0){
            input = initalState;
        }

        bool getOutput() override{
            return input;
        }

        bool setInput(bool val){
            this->input = val;
        }
};

class LogicGate: public Node
{
private:
gatetype type;
    
public:
    LogicGate(gatetype type){
        this->type = type;
    };

    LogicGate(gatetype type, Node* inputa, Node* inputb){
        this->type = type;
        addInput(inputa);
        addInput(inputb);
    };

    bool getOutput() override {
        switch(type) {
            case AND:
                return inputs[0]->getOutput() && inputs[1]->getOutput();
            case OR:
                return inputs[0]->getOutput() || inputs[1]->getOutput();
            case NOT:
                return !inputs[0]->getOutput();
            case NAND:
                return !(inputs[0]->getOutput() && inputs[1]->getOutput());
            case NOR:
                return !(inputs[0]->getOutput() || inputs[1]->getOutput());
            case XOR:
                return ((!inputs[0]->getOutput() && inputs[1]->getOutput())|| (inputs[0]->getOutput() && !inputs[1]->getOutput()));
            case XNOR:
                return ((!inputs[0]->getOutput() && !inputs[1]->getOutput())|| (inputs[0]->getOutput() && inputs[1]->getOutput()));
            default:
                return false;
        }
    }

    void addInput(Node* input){
        inputs.push_back(input);
    }
};

int main(){

    InputNode a = InputNode(0);
    InputNode b = InputNode(1);
    LogicGate andgate = LogicGate(AND, &a, &b);
    LogicGate xorgate = LogicGate(XNOR, &andgate, &a);
    std::cout << xorgate.getOutput();

    return 0;
}