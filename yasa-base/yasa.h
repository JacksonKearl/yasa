//
// yasa.h
//
// Defines main program constants and provides definitions for command hashes.
//


// How big of an array we're giving the program.
#ifndef ARR_LENGTH
#define ARR_LENGTH 1024
#endif

// How big of a command set we're giving program in REPL mode.
#ifndef REPL_LENGTH
#define REPL_LENGTH 128
#endif

// commands
#define CPY 31625
#define SHO 190815
#define DIS 40919
#define INC 91403
#define DEC 40503
#define IIN 90914
#define CIN 30914
#define PUS 162119
#define POP 161516
#define PUT 162120
#define GET 70520
#define ADD 10404
#define SUB 192102
#define MUL 132112
#define DIV 40922
#define RAN 180114
#define MOD 131504

// control flow
#define LBL 120212
#define MOV 131522
#define IFF 90606
#define EIF 50906
#define ELS 51219
#define END 51404

// conditionals
#define EQL 51712
#define GRT 71820