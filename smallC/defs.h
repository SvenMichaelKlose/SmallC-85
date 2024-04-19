// Intel 8080 architecture defs
#define INTSIZE 2

// Miscellaneous
#define FOREVER for(;;)
#define FALSE   0
#define TRUE    1
#define NO      0
#define YES     1

#define EOS     0
#define LF      10
#define BKSP    8
#define CR      13
#define FFEED   12
#define TAB     9

// System-wide name size (for symbols) 
#define NAMESIZE        33
#define NAMEMAX         32

struct symbol {
    // symbol name 
    char name[NAMESIZE];
    // variable, array, pointer,
    // function 
    int identity;
    // char, int, uchar, unit 
    int type;
    // public, auto, extern, static,
    // lstatic, defauto 
    int storage;
    // Offset 
    int offset;
    // Index of struct in tag table.
    int tagidx;
    // The size, in bytes, of a member
    // of a struct - only used for
    // member declarations.
    int struct_size;
};
#define SYMBOL struct symbol

#define NUMBER_OF_GLOBALS 100
#define NUMBER_OF_LOCALS 20

// Define the structure tag table parameters 
#define NUMTAG      10

struct tag_symbol {
    // structure tag name 
    char name[NAMESIZE];
    // size of struct in bytes 
    int size;
    // index of first member 
    int member_idx;
    // number of tag members 
    int number_of_members;
};
#define TAG_SYMBOL struct tag_symbol

#ifdef SMALL_C
#define NULL_TAG 0
#else
#define NULL_TAG (TAG_SYMBOL *)0
#endif

// Define the structure member table parameters 
#define NUMMEMB     30

// possible entries for "ident" 
#define VARIABLE        1
#define ARRAY           2
#define POINTER         3
#define FUNCTION        4

/*
  possible entries for "type"
  high order 14 bits give length of object
  low order 2 bits make type unique within length
*/
#define UNSIGNED        1
#define STRUCT          2
#define CCHAR           (1 << 2)
#define UCHAR           ((1 << 2) + 1)
#define CINT            (2 << 2)
#define UINT            ((2 << 2) + 1)

// possible entries for storage 
#define PUBLIC  1
#define AUTO    2
#define EXTERN  3

#define STATIC  4
#define LSTATIC 5
#define DEFAUTO 6

// "do"/"for"/"while"/"switch" statement stack 
#define WSTABSZ 20

struct while_rec {
    // symbol table address 
    int symbol_idx;
    // stack pointer 
    int stack_pointer;
    // type 
    int type;
    // case or test 
    int case_test;
    // continue label ? 
    int incr_def;
    // body of loop, switch ? 
    int body_tab;
    // exit label 
    int while_exit;
};
#define WHILE struct while_rec

// possible entries for "wstyp" 
#define WSWHILE 0
#define WSFOR   1
#define WSDO    2
#define WSSWITCH        3

// "switch" label stack 
#define SWSTSZ  100

// literal pool 
#define LITABSZ 5000
#define LITMAX  LITABSZ-1

// input line 
#define LINESIZE        150
#define LINEMAX (LINESIZE-1)
#define MPMAX   LINEMAX

// macro (define) pool 
#define MACQSIZE        1500
#define MACMAX  (MACQSIZE-1)

// "include" stack 
#define INCLSIZ     3

// statement types (tokens) 
#define STIF        1
#define STWHILE     2
#define STRETURN    3
#define STBREAK     4
#define STCONT      5
#define STASM       6
#define STEXP       7
#define STDO        8
#define STFOR       9
#define STSWITCH    10

#define DEFLIB  inclib()

#define FETCH  1
#define HL_REG 1<<1
#define DE_REG 1<<2

struct lvalue {
    // symbol table address, or 0 for constant 
    SYMBOL *symbol;
    // type of indirect object, 0 for static object 
    int indirect;
    // type of pointer or array, 0 for other idents 
    int ptr_type;
    // tag symbol address, 0 if not struct 
    TAG_SYMBOL *tagsym;
};
#define LVALUE struct lvalue

// path to include directories. set at compile time on host machine
char *inclib ();

WHILE *readwhile ();
WHILE *findwhile ();
WHILE *readswitch ();

// Output the variable symbol at scptr as an extrn or a public
void ppubext (SYMBOL * scptr);

// Output the function symbol at scptr as an extrn or a public
void fpubext (SYMBOL * scptr);

// fetch a static memory cell into the primary register
void gen_get_memory (SYMBOL * sym);

// fetch the specified object type indirect through the primary
// register into the primary register
void gen_get_indirect (char typeobj, int reg);

// asm - store the primary register into the specified static memory cell
void gen_put_memory (SYMBOL * sym);

// initialisation of global variables 
#define INIT_TYPE    NAMESIZE
#define INIT_LENGTH  NAMESIZE+1
#define INITIALS_SIZE 5*1024

struct initials_table {
    char name[NAMESIZE];        // symbol name 
    int type;                   // type 
    int dim;                    // length of data (possibly an array) 
    int data_len;               // index of tag or zero 
};
#define INITIALS struct initials_table

// determine if 'sname' is a member of the struct with tag 'tag'
SYMBOL *find_member (TAG_SYMBOL * tag, char *sname);
