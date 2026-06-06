#ifndef __MACROS_H__

#define __MACROS_H__

#define internal        static
#define local_persist   static
#define global_variable static

#define PUSH_STACK(vm, value)                                                  \
  if ((vm)->cpu.SP >= ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE) {                \
    zvm_raise(vm, EXECUTE, STACK_OVERFLOW) return false;                       \
  }                                                                            \
  (vm)->cpu.SP++;                                                              \
  (vm)->program                                                                \
      .stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP] =      \
      value;

#define POP_STACK(vm, dest)                                                    \
  if ((vm)->cpu.SP < 0) {                                                      \
    zvm_raise(vm, EXECUTE, STACK_UNDERFLOW) return false;                      \
  }                                                                            \
  (dest) =                                                                     \
      (vm)->program                                                            \
          .stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - (vm)->cpu.SP]; \
  (vm)->cpu.SP--;

#endif