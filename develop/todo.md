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

- [ ] for the rule of "" '', you dont care what is in the middle

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
- [x] ""f"f">>lol"|"
- [x]  <<"<" ->it work and the multi is normal because its an heredoc
- [x] >">"<"<"


## Expanding

- [ ]  export a="cat filea fileb"
- [ ]  $a => return filea not found