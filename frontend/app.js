// Function to run the SR Latch simulation for all possible inputs
function runSimulation(Module) {
  const outputElement = document.getElementById('output')
  let outputText = ''

  // --- 1. Instantiate the Simulator and Input Nodes ---
  const sim = new Module.Simulator()

  // S and R inputs must be InputNode types
  const inputS = new Module.InputNode(false)
  const inputR = new Module.InputNode(false)

  // --- 2. Create the Cross-Coupled NAND Gates ---
  // G1: Output is Q. Inputs: S and Q_not (from G2)
  // G2: Output is Q_not. Inputs: R and Q (from G1)

  // Note: We use 'null' initially for the cross-coupling inputs.
  const gateQ = new Module.GateNAND(inputS, null) // G1: S input, Q output
  const gateQnot = new Module.GateNAND(inputR, null) // G2: R input, Q_not output

  // Connect the cross-coupling (the 'memory' wires)
  gateQ.node2 = gateQnot // G1 input 2 is Q_not (Output of G2)
  gateQnot.node2 = gateQ // G2 input 2 is Q (Output of G1)

  // --- 3. Add all components to the Simulator's linked list ---
  // Order matters somewhat for initial convergence, but Run() handles iteration.
  sim.addGate(inputS)
  sim.addGate(inputR)
  sim.addGate(gateQ)
  sim.addGate(gateQnot)

  // --- 4. Define Test Cases ---
  const testCases = [
    { S: false, R: true, name: 'State 1: Reset (S=0, R=1)' },
    { S: false, R: false, name: 'State 2: Hold (S=0, R=0) after Reset' },
    { S: true, R: false, name: 'State 3: Set (S=1, R=0)' },
    { S: false, R: false, name: 'State 4: Hold (S=0, R=0) after Set' },
    { S: true, R: true, name: 'State 5: Forbidden (S=1, R=1)' },
  ]

  // --- 5. Run All Test Cases ---
  for (const test of testCases) {
    // Set Inputs
    inputS.setInput(test.S)
    inputR.setInput(test.R)

    // Run Simulation until stable
    sim.Run()

    // Retrieve Results
    const Q = gateQ.getCurrentState()
    const Qnot = gateQnot.getCurrentState()

    outputText += `\n--- ${test.name} ---\n`
    outputText += `Inputs: S=${test.S}, R=${test.R}\n`
    outputText += `Output Q: ${Q}\n`
    outputText += `Output Q_not (Q̄): ${Qnot}\n`

    if (test.S === true && test.R === true) {
      outputText += 'Note: S=R=1 is the forbidden/indeterminate state.\n'
    } else if (test.S === false && test.R === false) {
      outputText += 'Note: S=R=0 holds the previous state.\n'
    }
  }

  outputElement.textContent = outputText

  // --- 6. CRITICAL: Clean up Wasm Memory ---
  sim.delete()
  inputS.delete()
  inputR.delete()
  gateQ.delete()
  gateQnot.delete()
}

// Emscripten global initialization (remains unchanged)
LogicModule()
  .then((Module) => {
    console.log(
      'WebAssembly module initialized. Running SR Latch simulation...',
    )
    runSimulation(Module)
  })
  .catch((e) => {
    console.error('Error loading Wasm module:', e)
  })
