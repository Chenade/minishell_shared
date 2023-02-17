## Notes
- be sure not have any error when you do valgrind -s
---
## Pre-Parsing
- [x] starting  by |
- [x] finishing by |
- [x] more than 1x | in a row so a||a its not ok but a|a|a is ok
- [x] <<< 
- [x] <>
- [x] ><
- [x] when you <, <<, >> or > you have to have a filename after, either its stick together or there as may many space in between
- [x] for the rule of "" '', you dont care what is in the middle

#### case that should not work:
- [x] fdsfds |
- [x] |
- [x] fsdfsd ||
- [x] >> fdsfds fds >>
- [x] "fsdfds "  >> <<
- [x] echo > > fdsfds
- [x] echo <> fsdfd
- [x] echo <<>
- [x] echo ><
- [x] <
- [x] "fsfds |" ""|
- [x] fdsfdssd|>|fsfsdf
- [x] f|       <<    |fds
- [x] ffd<|fdfd
- [x] "fdsfdsfsfds "'fdsfds'"|""""|
- [x]  '<'""|<

#### case that should work:
- [x] <"|"
- [x] "fsdfds>>"<">>>"
- [x] ""|da|a|>a|""
- [x] "fdsfds"|'|'|'|'
- [x] "" f "f" >> lol "|"
- [x]  <<"<" ->it work and the multi is normal because its an heredoc
- [x] >">"<"<"

---

## Expanding

- you count each caracter and when you are on a '$' and you are not inside '':
- you have to check the value of the key inside youre env and count the len, and add it to your intial len, if you find nothing inside the env, its 0 and youre gonna replace it by nothing;
- the separator can be:" "; "|"; "<"; ">"; "$"; "'"; """.
```
if str[i] == '$'
    malloc_len+=determinl_len_from_env;
    and the i should past the $value till the next separator
```

#### Example:

###### Case:
```
        $USER1"$USER" 
    =>  "ykuo"
        echo "            $USER"
    =>  echo             ykuo 
```
###### Case 2:
if i do-> 
```
   export a="s -la"
```
and then->
```
        l$a $USER$USER$USER$FDSFDS$USER "$USER" '$USER'
    =>  ls -la      "  ykuoykuoykuoykuo" "ykuo" '$USER'
```
Details:
```
Readline:
char * raw_line = l$a      "  $USER$USER$USER$FDSFDS$USER" "$USER" '$USER'
    =>  l = 1;
        $a= 5;
              = 4;
        "  $USER$USER$USER$FDSFDS$USER"= 19;
         =1;
        "$USER" =6;
         =1;
         '$USER'= 7;
    =>  len = 47
    - now you do a malloc;
    - then you copy each char and if its a $value and its not inside a '' you have to copy not '$value' but the value inside the env:

Result:
char * clean =ls -la      "  ykuoykuoykuoykuo" "ykuo" '$USER'= 47len  
```

---
## Tokenize

```
Input line:
    echo bonjour | cat
```
##### Struct
```
general_struct {
    char *clean = echo bonjour | cat;
    int Nbr of request; = nbr of pipe + 1
    tab_request[] *2
}

------------------------------

struct_request { A
    char *request; "echo bonjour" 
    tab_request; {"echo", "bonjour"} 
    nbr token; 2
    tab_token[]; x2
    input; STDIN
    output; fd of the inpipe;
}

struct_request { B
    char *request; "cat" 
    tab_request; {"cat"} 
    nbr token; 1
    tab_token[]; x1
    input; fd of the outpipe;
    output; STDOUT
}

------------------------------

struct_token { A.1

    char * token; echo
    int type;  1
}

struct_token { A.2

    char * token; bonjour
    int type; 2
}

------------------------------

struct_token { B

    char * token; cat
    int type; 1
}
```