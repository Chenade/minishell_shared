## Notes
- be sure not have any error when you do valgrind -s

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


## Expanding

- [ ]  export a="cat filea fileb"
- [ ]  $a => return filea not found



if i do-> 
    export a="s -la"
and then->
    l$a $USER$USER$USER$FDSFDS$USER "$USER" '$USER'
it will be ->
    ls -la      "  ykuoykuoykuoykuo" "ykuo" '$USER'


$USER1"$USER" =>"ykuo"

if i do ->
    echo "            $USER"
it will be->
    echo             ykuo 


char * raw_line = l$a      "  $USER$USER$USER$FDSFDS$USER" "$USER" '$USER'



---------------------------------------------------------------------
l$a      "       $USER$USER$USER$FDSFDS$USER" "$USER" '$USER'

you count each caracter and when you are on a '$' and you are not inside '':
you have to check the value of the key inside youre env and count the len, and add it to your intial len, if you find nothing inside the env, its 0 and youre gonna replace it by nothing;

l = 1; $a= 5;      = 4;"  $USER$USER$USER$FDSFDS$USER"= 19; =1;"$USER" =6; =1;'$USER'= 7;
len = 47, now you do a malloc;

then you copy each char and if its a $value and its not inside a '' you have to copy not '$value' but the value inside the env:


char * clean =ls -la      "  ykuoykuoykuoykuo" "ykuo" '$USER'= 47len  

if str[i] == '$'
    malloc_len+=determinl_len_from_env;
    and the i should past the $value till the next separator

the separator can be:" "; "|"; "<"; ">"; "$"; "'"; """.
