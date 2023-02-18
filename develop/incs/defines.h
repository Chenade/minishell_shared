
enum	token_type
{ 
	EMPTY = 0,
	CMD = 1,
	ARG = 2,
	ENV_DEF = 3,
	ENV_VAL = 4,
	OPTN = 5,
	INPUT = 6, // <
	OUTPUT = 7, // >
	DELIM = 8, // <<
	APPEN = 9, // >>
	PIPE = 10
};

enum	e_mini_error
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 4,
	DUPERR = 5,
	FORKERR = 6,
	PIPERR = 7,
	MEM = 8,
	IS_DIR = 9,
	NOT_DIR = 11,
	OP_NS = 12,
	SYNERR = 13,
};
