#define CycleFor(module, args...) { New->module.Cycle(&Old->module, &New->module, args); }

#define ResetFor(module) { New->module.Reset(&New->module); }

#define MAX(a, b) (((a) >= (b)) ? (a) : (b))