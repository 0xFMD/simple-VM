#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdbool.h>
#include <stdint.h>

// vm
typedef struct zvm_vm_t  zvm_vm_t;
typedef struct zvm_cpu_t zvm_cpu_t;

//io
typedef struct zvm_io_device_t zvm_io_device_t;
typedef void* (*zinout_io_handler_t)(zvm_vm_t* vm, uint8_t port, uint8_t type, void* args);

// program
typedef struct zvm_program_t zvm_program_t;

// instruction
typedef bool (*zfn_instruction_handler_t)(zvm_vm_t*, uint8_t, uint8_t, uint8_t);
typedef struct zvm_instruction_handler_t  zvm_instruction_handler_t;

typedef struct zvm_instruction_operand_t  zvm_instruction_operand_t;
typedef struct zvm_instruction_t          zvm_instruction_t;

typedef struct zvm_instruction_metadata_t zvm_instruction_metadata_t;
typedef struct zvm_operand_metadata_t     zvm_operand_metadata_t;

// exceptions
typedef struct zvm_exception_entry_t zvm_exception_entry_t;
typedef bool (*zxpt_exception_handler_t)(zvm_vm_t*, uint8_t);

#endif