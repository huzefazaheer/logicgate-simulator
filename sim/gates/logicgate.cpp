#include <iostream>

enum gatetype{
    INPUT,
    AND,
    OR,
    NOR,
    NAND,
    NOT,
    XOR,
    XNOR,
    OTHER,
    OUTPUT
};

class logicgate
{
private:
bool a;
bool b;
gatetype type;
bool output;
    
public:
    logicgate(gatetype type, bool expr = 0){
        this->type = type;
    };
    // ~logicgate();

    bool getOutput(){
        switch (type)
        {
        case AND:
            output = a && b;
            break;
        case OR:
            output = a || b;
            break;
        case NAND:
            output = !(a && b);
            break;
        case NOR:
            output = !(a || b);
            break;
        case XOR:
            output = (a && !b) || (!a && b);
            break;
        case XNOR:
            output = (!a && !b) || (a && b);
            break;
        default:
            output = -1;
            break;
        }
        return output;
    };

    void setInputs(bool a1, bool b1){
        a = a1;
        b = b1;
    };
};

int main(){

    logicgate andgate = logicgate(XNOR);
    andgate.setInputs(0, 0);
    std::cout << andgate.getOutput();
    andgate.setInputs(0, 1);
    std::cout << andgate.getOutput();
    andgate.setInputs(1, 0);
    std::cout << andgate.getOutput();
    andgate.setInputs(1, 1);
    std::cout << andgate.getOutput();

    return 0;
}