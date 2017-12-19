#!/bin/sh
#test redirection < > >>
printf "\\n\\nTest 1: echo test1 > myoutput1\\n"
printf "Before:\\n" 
ls
printf "echo test1 > myoutput1; exit\\n" | bin/rshell
printf "\\nAfter:\\n" 
ls
printf "$ cat myoutput1\\n"
cat myoutput1

printf "\\n\\nTest 2: cat < myoutput1\\n"
printf "Expected:\\ntest1\\n" 
printf "cat < myoutput1; exit\\n" | bin/rshell

printf "\\n\\nTest 3: ls > myoutput1\\n"
printf "Before:\\ncat myoutput1\\n" 
cat myoutput1
printf "ls > myoutput1; exit\\n" | bin/rshell
printf "\\nAfter:\\ncat myoutput1\\n" 
cat myoutput1

printf "\\n\\nTest 3: tr < myoutput1 a-z A-Z > myoutput2\\n"
printf "Before:\\n" 
ls
printf "tr < myoutput1 a-z A-Z > myoutput2; exit\\n" | bin/rshell
printf "\\nAfter:\\n" 
ls
printf "cat myoutput2\\n"
cat myoutput2


printf "\\n\\nTest 4: echo appended! >> myoutput2\\n"
printf "Expected: cat myoutput2\\n" 
cat myoutput2
printf "\\nappended\\n"
printf "echo appended! >> myoutput2; exit\\n" | bin/rshell
cat myoutput2

printf "\\n\\nTest 5: cat > myoutput3\\n"
printf "Expected:\\nWhen you type in:\\n" 
printf "aaaa\\nbbbb\\ncccc\\nwith ctrl-d to end the loop, you can do cat myoutput3:\\n"
printf "aaaa\\nbbbb\\ncccc\\n"

printf "\\n\\nLast Test: rm myoutput1\\n"
printf "Before:\\n" 
ls
printf "rm myoutput1; exit\\n" | bin/rshell
printf "\\nAfter:\\n" 
ls
rm myoutput2
