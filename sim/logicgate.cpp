#include <iostream>

class LogicGate{
    public:
        LogicGate* node1;
        LogicGate* node2;

        LogicGate(LogicGate* a = nullptr, LogicGate* b = nullptr){
            node1 = a;
            node2= b;
        }

        virtual bool getOutput(){
            return 0;
        }
};

class InputNode: public LogicGate{
    private:
        bool input;

    public:
        InputNode(bool input){
            setInput(input);
        }

        void setInput(bool input){
            this->input = input;
        }

        bool getOutput() override{
            return input;
        }
};

class GateAND: public LogicGate{
    public:
        GateAND(LogicGate* in1, LogicGate* in2)
        : LogicGate(in1, in2) {}

        bool getOutput() override{
            return node1->getOutput() && node2->getOutput();
        }
};

int main(){
    InputNode a = InputNode(0);
    InputNode b = InputNode(0);
    GateAND andgate = GateAND(&a, &b);
    std::cout << andgate.getOutput();

    return 0;
}