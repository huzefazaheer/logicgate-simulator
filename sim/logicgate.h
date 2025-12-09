#ifndef LOGICGATE_H
#define LOGICGATE_H

#include <iostream>

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

class GateAND: public LogicGate{
    public:
        GateAND(LogicGate* in1, LogicGate* in2)
        : LogicGate(in1, in2) {}

        void getNextState() override{
            bool output = (node1->getCurrentState() && node2->getCurrentState());
            setNextState(output);
        }
};

class GateNOR: public LogicGate{
    public:
        GateNOR(LogicGate* in1, LogicGate* in2)
        : LogicGate(in1, in2) {}

        void getNextState() override{
            bool output = !(node1->getCurrentState() || node2->getCurrentState());
            setNextState(output);
        }
};

class GateOR: public LogicGate{
    public:
        GateOR(LogicGate* in1, LogicGate* in2)
        : LogicGate(in1, in2) {}

        void getNextState() override{
            bool output = (node1->getCurrentState() || node2->getCurrentState());
            setNextState(output);
        }
};

class GateNOT: public LogicGate{
    public:
        GateNOT(LogicGate* in1)
        : LogicGate(in1, nullptr) {}

        void getNextState() override{
            bool output = !(node1->getCurrentState());
            setNextState(output);
        }
};

class GateXOR: public LogicGate{
    public:
        GateXOR(LogicGate* in1, LogicGate* in2)
        : LogicGate(in1, in2) {}

        void getNextState() override{
            bool output = (!node1->getCurrentState() && node2->getCurrentState()) || (node1->getCurrentState() && !node2->getCurrentState());
            setNextState(output);
        }
};

class GateXNOR: public LogicGate{
    public:
        GateXNOR(LogicGate* in1, LogicGate* in2)
        : LogicGate(in1, in2) {}

        void getNextState() override{
            bool output = (node1->getCurrentState() && node2->getCurrentState()) || (!node1->getCurrentState() && !node2->getCurrentState());
            setNextState(output);
        }
};

#endif