#include "./logicgate.h"
using namespace std;

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
