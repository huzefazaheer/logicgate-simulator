// bindings.cpp

#include <emscripten/bind.h>
#include "logicgate.h"        // Contains all LogicGate/InputNode/etc. definitions
#include "simulator.h"   // Contains the full definition of Simulator

using namespace emscripten;

EMSCRIPTEN_BINDINGS(LogicSimulatorModule) {
    // 1. Expose the base LogicGate class and its necessary methods
    class_<LogicGate>("LogicGate")
        .function("getCurrentState", &LogicGate::getCurrentState);
        // Deletion is handled by the C++ destructor once exposed properly, 
        // no need for delete_dummy.

    // 2. Expose the Simulator class
    class_<Simulator>("Simulator")
        .constructor()
        .function("addGate", &Simulator::addGate, allow_raw_pointers())
        .function("Run", &Simulator::Run);

    // 3. Expose the specialized InputNode for setting inputs
    class_<InputNode, base<LogicGate>>("InputNode")
        .constructor<bool>()
        .function("setInput", &InputNode::setInput);

    // 4. Expose the common 2-input gates
    
    // AND Gate (2 inputs)
    class_<GateAND, base<LogicGate>>("GateAND")
        .constructor<LogicGate*, LogicGate*>();
    
    // OR Gate (2 inputs)
    class_<GateOR, base<LogicGate>>("GateOR")
        .constructor<LogicGate*, LogicGate*>();

    // NAND Gate (2 inputs)
    class_<GateNAND, base<LogicGate>>("GateNAND")
        .constructor<LogicGate*, LogicGate*>();

    // NOR Gate (2 inputs)
    class_<GateNOR, base<LogicGate>>("GateNOR")
        .constructor<LogicGate*, LogicGate*>();

    // XOR Gate (2 inputs)
    class_<GateXOR, base<LogicGate>>("GateXOR")
        .constructor<LogicGate*, LogicGate*>();

    // XNOR Gate (2 inputs)
    class_<GateXNOR, base<LogicGate>>("GateXNOR")
        .constructor<LogicGate*, LogicGate*>();

    // NOT Gate (1 input - only uses node1, node2 is nullptr)
    class_<GateNOT, base<LogicGate>>("GateNOT")
        .constructor<LogicGate*>();
}