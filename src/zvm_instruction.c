#include "../includes/zvm.h"

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(add)
vm->cpu.R[output] = vm->cpu.R[left] + vm->cpu.R[right];
printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sub)
vm->cpu.R[output] = vm->cpu.R[left] - vm->cpu.R[right];
printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldi)
vm->cpu.R[left] = right;
printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(str)
/* STR reg, mem */
vm->program.data[right] = vm->cpu.R[left];
printf("MEM=%u\n", vm->program.data[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldm)
/* LDM reg, mem */
vm->cpu.R[left] = vm->program.data[right];
printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(lda)
uint8_t address = vm->cpu.R[left];
if (!zvm_is_address(address)) {
    zvm_raise(vm, EXECUTE, BAD_MEMORY_ADDRESS);
}
vm->cpu.R[right] = vm->program.data[address];
printf("R=%u\n", vm->cpu.R[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sta)
/* STA reg, reg */
uint8_t address = vm->cpu.R[left];
if (!zvm_is_address(address)) {
    zvm_raise(vm, EXECUTE, BAD_MEMORY_ADDRESS);
}
vm->program.data[address] = vm->cpu.R[right];
printf("address=%u\n", vm->program.data[address]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(push)

PUSH_STACK(vm, vm->cpu.R[left])

printf("stack=%u\n", vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(pop)
if (vm->cpu.SP < 0) {
    zvm_raise(vm, EXECUTE, STACK_UNDERFLOW) return false;
}

uint8_t value;
POP_STACK(vm, value)

vm->cpu.R[left] = value;
printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(inc)
/* INC reg*/
vm->cpu.R[left]++;
printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(dec)
/* DEC reg*/
vm->cpu.R[left]--;
printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(cmp)
/* CMP reg, reg*/

if (vm->cpu.R[left] - vm->cpu.R[right] == 0)
    vm->cpu.FLAGS = FLAG_ZERO;
else if (vm->cpu.R[left] - vm->cpu.R[right] < 0)
    vm->cpu.FLAGS = FLAG_NEGATIVE;
else
    vm->cpu.FLAGS = FLAG_POSITIVE;

printf("CPU_FLAGS: %d\n", vm->cpu.FLAGS);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jmp)
/* JMP imm*/

if (left >= vm->program.instructions_count) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}

vm->cpu.IP = left;

printf("CPU_IP: %d\n", vm->cpu.IP);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(je)
/* JE imm*/
if (left >= vm->program.instructions_count) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}
if (vm->cpu.FLAGS == FLAG_ZERO)
    vm->cpu.IP = left;

printf("CPU_IP: %d\n", vm->cpu.IP);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jg)
/* JG imm*/
if (left >= vm->program.instructions_count) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}
if (vm->cpu.FLAGS == FLAG_POSITIVE)
    vm->cpu.IP = left;

printf("CPU_IP: %d\n", vm->cpu.IP);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jge)
/* JGE imm*/
if (left >= vm->program.instructions_count) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}
if (vm->cpu.FLAGS != FLAG_NEGATIVE)
    vm->cpu.IP = left;

printf("CPU_IP: %d\n", vm->cpu.IP);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jl)
/* JL imm*/
if (left >= vm->program.instructions_count) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}
if (vm->cpu.FLAGS == FLAG_NEGATIVE)
    vm->cpu.IP = left;

printf("CPU_IP: %d\n", vm->cpu.IP);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jle)
/* JLE imm*/
if (left >= vm->program.instructions_count) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}
if (vm->cpu.FLAGS != FLAG_POSITIVE)
    vm->cpu.IP = left;

printf("CPU_IP: %d\n", vm->cpu.IP);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(jne)
/* JNE imm*/
if (left >= vm->program.instructions_count) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}
if (vm->cpu.FLAGS != FLAG_ZERO)
    vm->cpu.IP = left;

printf("CPU_IP: %d\n", vm->cpu.IP);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(mul)
// MUL, reg, reg, reg
vm->cpu.R[output] = vm->cpu.R[left] * vm->cpu.R[right];
printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(div)
// DIV, reg, reg, reg
if (vm->cpu.R[right] == 0) {
    zvm_raise(vm, EXECUTE, DIV_ZERO) return false;
}
vm->cpu.R[output] = vm->cpu.R[left] / vm->cpu.R[right];
printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(mod)
// MOD, reg, reg, reg
vm->cpu.R[output] = vm->cpu.R[left] % vm->cpu.R[right];
printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(and)
// AND reg, reg, reg
vm->cpu.R[output] = vm->cpu.R[left] & vm->cpu.R[right];
printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(or)
// OR, reg, reg, reg
vm->cpu.R[output] = vm->cpu.R[left] | vm->cpu.R[right];
printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(xor)
// XOR, reg, reg, reg
vm->cpu.R[output] = vm->cpu.R[left] ^ vm->cpu.R[right];
printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(not)
// NOT, reg
vm->cpu.R[right] = ~vm->cpu.R[left];
printf("R=%u\n", vm->cpu.R[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(shl)
// SHL, reg, imm
vm->cpu.R[left] = vm->cpu.R[left] << right;
printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(shr)
// SHR, reg, imm
vm->cpu.R[left] = vm->cpu.R[left] >> right;
printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(xchg)
// XCHG, reg, reg
uint8_t temp     = vm->cpu.R[left];
vm->cpu.R[left]  = vm->cpu.R[right];
vm->cpu.R[right] = temp;
printf("R0=%u, R1=%u\n", vm->cpu.R[left], vm->cpu.R[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ror)
// ROR, imm
uint8_t shift   = right % 8;
vm->cpu.R[left] = (vm->cpu.R[left] >> shift) | (vm->cpu.R[left] << (8 - shift));

printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(rol)
// ROL, imm
uint8_t shift   = right % 8;
vm->cpu.R[left] = (vm->cpu.R[left] << shift) | (vm->cpu.R[left] >> (8 - shift));

printf("R0=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(call)
// CALL, imm
if (left >= ZVM_PROGRAM_DEFAULT_CODE_SEGMENT_SIZE) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}

PUSH_STACK(vm, vm->cpu.IP)
vm->cpu.IP = left;

printf("stack: %d\n", vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP]);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ret)
// RET
POP_STACK(vm, vm->cpu.IP)

if (vm->cpu.IP >= ZVM_PROGRAM_DEFAULT_CODE_SEGMENT_SIZE) {
    zvm_raise(vm, EXECUTE, BAD_INSTRUCTION) return false;
}

printf("pop: %d\n", vm->cpu.IP);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(stp)
// STP

printf("STP(IP): %d\n", vm->cpu.IP);
exit(0);

ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(mov)
// MOV, reg, reg
vm->cpu.R[left] = vm->cpu.R[right];
printf("R0=%u, R1=%u\n", vm->cpu.R[left], vm->cpu.R[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END