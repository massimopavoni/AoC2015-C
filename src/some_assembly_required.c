#include "some_assembly_required.h"

#include <string.h>

#include "random_utils.h"

// ------------------------------------------------------------------------------------------------
// Types

enum Operation { ASSIGN, AND, OR, NOT, LSHIFT, RSHIFT, NOP };

// ------------------------------------------------------------------------------------------------
// Constants

#define OP_SHIFT 8
#define SIG1_CALL 0x0001
#define SIG2_CALL 0x0002

// ------------------------------------------------------------------------------------------------
// Macros

// First u16 in wires matrix packs operation and signals call flags
#define MAKE_CTRL(op, s1, s2)                                                  \
  (((op) << OP_SHIFT) | ((s1) ? SIG1_CALL : 0) | ((s2) ? SIG2_CALL : 0))

// ------------------------------------------------------------------------------------------------
// Parsers

static void parse_instructions(const char *input, u16 wires[676][3]) {
  enum Operation op;
  u16 signals[3];
  bool sig_calls[2];
  u8 current_sig;

  while (*input) {
    op = NOP;
    memset(signals, 0, sizeof(signals));
    memset(sig_calls, false, sizeof(sig_calls));
    current_sig = 0;

    while (*input != '\n') {
      switch (*input) {
      case '0' ... '9':
        PARSE_INT(input, signals[current_sig]);
        current_sig++;
        input++;
        break;
      case 'a' ... 'z':
        signals[current_sig] = *input - 'a' + 1;
        input++;
        if ('a' <= *input && *input <= 'z') {
          signals[current_sig] *= 26;
          signals[current_sig] += *input - 'a' + 1;
          input++;
        }
        if (current_sig < 2)
          sig_calls[current_sig] = true;
        current_sig++;
        if (*input == ' ')
          input++;
        break;
      case '-':
        if (op == NOP)
          op = ASSIGN;
        input += 3;
        current_sig = 2;
        break;
      case 'A':
        op = AND;
        input += 4;
        break;
      case 'O':
        op = OR;
        input += 3;
        break;
      case 'N':
        op = NOT;
        input += 4;
        break;
      case 'L':
        op = LSHIFT;
        input += 7;
        break;
      case 'R':
        op = RSHIFT;
        input += 7;
        break;
      }
    }

    wires[signals[2]][0] = MAKE_CTRL(op, sig_calls[0], sig_calls[1]);
    wires[signals[2]][1] = signals[0];
    wires[signals[2]][2] = signals[1];

    input++;
  }
}

// ------------------------------------------------------------------------------------------------
// Functions

static u16 simulate_wire(u16 wires[676][3], u16 wire) {
  // Recursively simulate wire value
#define SIG_CALL(sig)                                                          \
  ({                                                                           \
    if (wires[wire][0] & sig) {                                                \
      wires[wire][sig] = simulate_wire(wires, wires[wire][sig]);               \
      wires[wire][0] &= ~sig;                                                  \
    }                                                                          \
  })

#define BOTH_SIG_CALL                                                          \
  ({                                                                           \
    SIG_CALL(SIG1_CALL);                                                       \
    SIG_CALL(SIG2_CALL);                                                       \
  })

#define MAKE_CTRL_ASSIGN(op)                                                   \
  ({                                                                           \
    wires[wire][1] = wires[wire][1] op wires[wire][2];                         \
    wires[wire][0] = MAKE_CTRL(ASSIGN, false, false);                          \
    return wires[wire][1];                                                     \
  })

  switch (wires[wire][0] >> OP_SHIFT) {
  case ASSIGN:
    SIG_CALL(SIG1_CALL);
    return wires[wire][1];
  case AND:
    BOTH_SIG_CALL;
    MAKE_CTRL_ASSIGN(&);
  case OR:
    BOTH_SIG_CALL;
    MAKE_CTRL_ASSIGN(|);
  case NOT:
    SIG_CALL(SIG1_CALL);
    wires[wire][1] = ~wires[wire][1];
    wires[wire][0] = MAKE_CTRL(ASSIGN, false, false);
    return wires[wire][1];
  case LSHIFT:
    BOTH_SIG_CALL;
    MAKE_CTRL_ASSIGN(<<);
  case RSHIFT:
    BOTH_SIG_CALL;
    MAKE_CTRL_ASSIGN(>>);
  }

  return -1;
}

// ------------------------------------------------------------------------------------------------
// Exports

const char *wire_a_signal(const char *input) {
  u16 wires[676][3] = {0};
  parse_instructions(input, wires);

  // Simulate wire a signal
  return TO_STRING("%u", simulate_wire(wires, 1));
}

const char *rewired_a_signal(const char *input) {
  u16 wires[676][3] = {0};
  parse_instructions(input, wires);

  // Simulate wire a signal, do it all over again after rewiring to b
  u16 wires_a[676][3];
  memcpy(wires_a, wires, sizeof(wires));

  wires[2][1] = simulate_wire(wires_a, 1);
  wires[2][0] = MAKE_CTRL(ASSIGN, false, false);

  return TO_STRING("%u", simulate_wire(wires, 1));
}
