#include <iostream>

class LogicGate{
    private:
        bool currState = 0;
        bool nextState;

    public:
        LogicGate* node1;
        LogicGate* node2;

        LogicGate(LogicGate* a = nullptr, LogicGate* b = nullptr){
            node1 = a;
            node2 = b;
        }

        void setNextState(bool state){
            nextState = state;
        }

        bool getCurrentState(){
            return currState;
        }

        bool updateState(){
            if(currState != nextState){
                currState = nextState;  
                return true;
            }else return false;
        }

        virtual void getNextState(){
            return;
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

        void getNextState() override{
            setNextState(input);
        }
};

class GateNAND: public LogicGate{
    public:
        GateNAND(LogicGate* in1, LogicGate* in2)
        : LogicGate(in1, in2) {}

        void getNextState() override{
            bool output = !(node1->getCurrentState() && node2->getCurrentState());
            setNextState(output);
        }
};

struct node{
    LogicGate* gate;
    node* next = nullptr;
};

class Simulator
{
private:
    node* gates;
public:
    Simulator(){
        gates = nullptr;
    };
    ~Simulator(){
        node* current = gates;
        while (current != nullptr) {
            node* next = current->next;
            delete current; 
            current = next;
        }
    };

    void addGate(LogicGate* gate){
        node* newgate = new node;
        newgate->gate = gate;
        if(gates == nullptr){
            gates = newgate;
        }else {
            node* currgate = gates;
            while(currgate->next!=nullptr){
                currgate = currgate->next;
            }
            currgate->next = newgate;
        }
    }

    void Run(){
        int iterations = 0;
        bool changeOccured = true;

        while (changeOccured)
        {
            changeOccured = false;

            node* curr = gates;
            while(curr != nullptr){
                curr->gate->getNextState();
                curr = curr->next;
            }
            curr = gates;
            while(curr != nullptr){
                if(curr->gate->updateState()){
                    changeOccured = true;
                }
                curr = curr->next;
            }
        }
        
    }
};



int main(){
    InputNode a = InputNode(0);
    InputNode b = InputNode(1);
    GateNAND g1 = GateNAND(nullptr, nullptr);
    GateNAND g2 = GateNAND(nullptr, nullptr);
    g1.node1 = &a;
    g1.node2 = &g2;
    g2.node1 = &b;
    g2.node2 = &g1;

    Simulator sim = Simulator();
    sim.addGate(&a);
    sim.addGate(&b);
    sim.addGate(&g1);
    sim.addGate(&g2);
    sim.Run();
    std::cout << g1.getCurrentState();
    std::cout << g2.getCurrentState() << std::endl;
    a.setInput(1);
    sim.Run();
    std::cout << g1.getCurrentState();
    std::cout << g2.getCurrentState() << std::endl;
    a.setInput(1);
    b.setInput(0);
    sim.Run();
    std::cout << g1.getCurrentState();
    std::cout << g2.getCurrentState() << std::endl;
    a.setInput(1);
    b.setInput(1);
    sim.Run();
    std::cout << g1.getCurrentState();
    std::cout << g2.getCurrentState() << std::endl;
    a.setInput(0);
    b.setInput(0);
    sim.Run();
    std::cout << g1.getCurrentState();
    std::cout << g2.getCurrentState() << std::endl;
    

    return 0;
}