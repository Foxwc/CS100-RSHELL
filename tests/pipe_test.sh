#!/bin/sh
#test pipe
printf "\\n\\nTest 1: echo test1 | tr a-z A-Z \\n"
printf "echo test1 | tr a-z A-Z; exit\\n" | bin/rshell

printf "\\n\\nTest 2: cat < myoutput1 | ls \\n"
printf "cat < myoutput1 | ls; exit\\n" | bin/rshell

printf "\\n\\nTest 3: ls | tr a-z A-Z > myoutput1\\n"
printf "ls | tr a-z A-Z > myoutput1; exit\\n" | bin/rshell
printf "\\n\\nResult:\\n"
cat myoutput1
rm myoutput1
