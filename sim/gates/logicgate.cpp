#include <iostream>
#include <vector>
#include "../misc/linkedlist.h";

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
    LinkedList <Node*> inputs;
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

        void setInput(bool val){
            input = val;
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
        std::vector inputarr = inputs.getArray();
        switch(type) {
            case AND:
                return inputarr[0]->getOutput() && inputarr[1]->getOutput();
            case OR:
                return inputarr[0]->getOutput() || inputarr[1]->getOutput();
            case NOT:
                return !inputarr[0]->getOutput();
            case NAND:
                return !(inputarr[0]->getOutput() && inputarr[1]->getOutput());
            case NOR:
                return !(inputarr[0]->getOutput() || inputarr[1]->getOutput());
            case XOR:
                return ((!inputarr[0]->getOutput() && inputarr[1]->getOutput())|| (inputarr[0]->getOutput() && !inputarr[1]->getOutput()));
            case XNOR:
                return ((!inputarr[0]->getOutput() && !inputarr[1]->getOutput())|| (inputarr[0]->getOutput() && inputarr[1]->getOutput()));
            default:
                return false;
        }
    }

    void addInput(Node* input){
        inputs.appendAtTail(input);
    }
};

int main(){
    InputNode a = InputNode(0);
    InputNode b = InputNode(1);
    LogicGate andgate = LogicGate(AND, &a, &b);
    LogicGate xorgate = LogicGate(XNOR, &andgate, &a);
    std::cout << andgate.getOutput();
    a.setInput(1);
    std::cout << xorgate.getOutput();

    return 0;
}