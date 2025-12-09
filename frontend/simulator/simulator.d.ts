// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
interface WasmModule {
}

export interface ClassHandle {
  isAliasOf(other: ClassHandle): boolean;
  delete(): void;
  deleteLater(): this;
  isDeleted(): boolean;
  // @ts-ignore - If targeting lower than ESNext, this symbol might not exist.
  [Symbol.dispose](): void;
  clone(): this;
}
export interface LogicGate extends ClassHandle {
  getCurrentState(): boolean;
}

export interface Simulator extends ClassHandle {
  addGate(_0: LogicGate | null): void;
  Run(): void;
}

export interface InputNode extends LogicGate {
  setInput(_0: boolean): void;
}

export interface GateAND extends LogicGate {
}

export interface GateOR extends LogicGate {
}

export interface GateNAND extends LogicGate {
}

export interface GateNOR extends LogicGate {
}

export interface GateXOR extends LogicGate {
}

export interface GateXNOR extends LogicGate {
}

export interface GateNOT extends LogicGate {
}

interface EmbindModule {
  LogicGate: {};
  Simulator: {
    new(): Simulator;
  };
  InputNode: {
    new(_0: boolean): InputNode;
  };
  GateAND: {
    new(_0: LogicGate | null, _1: LogicGate | null): GateAND;
  };
  GateOR: {
    new(_0: LogicGate | null, _1: LogicGate | null): GateOR;
  };
  GateNAND: {
    new(_0: LogicGate | null, _1: LogicGate | null): GateNAND;
  };
  GateNOR: {
    new(_0: LogicGate | null, _1: LogicGate | null): GateNOR;
  };
  GateXOR: {
    new(_0: LogicGate | null, _1: LogicGate | null): GateXOR;
  };
  GateXNOR: {
    new(_0: LogicGate | null, _1: LogicGate | null): GateXNOR;
  };
  GateNOT: {
    new(_0: LogicGate | null): GateNOT;
  };
}

export type MainModule = WasmModule & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;
