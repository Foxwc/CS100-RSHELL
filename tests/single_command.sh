#!/bin/sh
echo "\\n\\nTest 1: mkdir dog\\nExpected: Directory dog created\\nBefore:\\n"
ls
printf "mkdir dog; exit\\n" | bin/rshell
printf "\\nAfter:\\n"
ls
printf "\\n\\nTest 2: rm -r dog\\nExpected: Directory dog removed\\nBefore:\\n"
ls
printf "rm -r dog; exit\\n" | bin/rshell
printf "\\nAfter:\\n"
ls
printf "\\n\\nTest 3: date\\n\\nExpected:\\n"
date
printf "\\n\\n"
printf "date; exit\\n" | bin/rshell
printf "\\n\\nTest 4: cat README.MD\\n\\nExpected:\\n"
cat README.MD
printf "\\n\\n\\n"
printf "cat README.MD; exit\\n" | bin/rshell
printf "\\n\\nTest 5: ls\\n\\nExpected:\\n"
ls
printf "\\n\\n"
printf "ls; exit\\n" | bin/rshell
printf "\\n\\nTest 6: echo hello world\\n\\nExpected:\\n"
echo hello world
printf "\\n\\n\\n"
printf "echo hello world; exit\\n" | bin/rshell
printf "\\n\\nTest 7: echo hello\\n\\nExpected:\\n"
echo hello
printf "\\n\\n\\n"
printf "echo hello; exit\\n" | bin/rshell
printf "\\nCreating directory dog for test 8\\n"
mkdir dog
printf "\\n\\nTest 8: rmdir dog\\nExpected: Directory dog removed\\nBefore:\\n"
ls
printf "rmdir dog; exit\\n" | bin/rshell
printf "\\nAfter:\\n"
ls
printf "\\n\\nTesting complete\\n"
