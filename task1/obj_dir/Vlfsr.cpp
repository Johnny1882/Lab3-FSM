// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vlfsr.h"
#include "Vlfsr__Syms.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vlfsr::Vlfsr(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vlfsr__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , en{vlSymsp->TOP.en}
    , data_out{vlSymsp->TOP.data_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vlfsr::Vlfsr(const char* _vcname__)
    : Vlfsr(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vlfsr::~Vlfsr() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vlfsr___024root___eval_initial(Vlfsr___024root* vlSelf);
void Vlfsr___024root___eval_settle(Vlfsr___024root* vlSelf);
void Vlfsr___024root___eval(Vlfsr___024root* vlSelf);
#ifdef VL_DEBUG
void Vlfsr___024root___eval_debug_assertions(Vlfsr___024root* vlSelf);
#endif  // VL_DEBUG
void Vlfsr___024root___final(Vlfsr___024root* vlSelf);

static void _eval_initial_loop(Vlfsr__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vlfsr___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vlfsr___024root___eval_settle(&(vlSymsp->TOP));
        Vlfsr___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void Vlfsr::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vlfsr::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vlfsr___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    vlSymsp->__Vm_activity = true;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vlfsr___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

const char* Vlfsr::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void Vlfsr::final() {
    Vlfsr___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vlfsr::hierName() const { return vlSymsp->name(); }
const char* Vlfsr::modelName() const { return "Vlfsr"; }
unsigned Vlfsr::threads() const { return 1; }
std::unique_ptr<VerilatedTraceConfig> Vlfsr::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vlfsr___024root__trace_init_top(Vlfsr___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vlfsr___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vlfsr___024root*>(voidSelf);
    Vlfsr__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->scopeEscape(' ');
    tracep->pushNamePrefix(std::string{vlSymsp->name()} + ' ');
    Vlfsr___024root__trace_init_top(vlSelf, tracep);
    tracep->popNamePrefix();
    tracep->scopeEscape('.');
}

VL_ATTR_COLD void Vlfsr___024root__trace_register(Vlfsr___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vlfsr::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vlfsr::trace()' shall not be called after 'VerilatedVcdC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vlfsr___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
