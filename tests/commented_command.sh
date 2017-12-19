#!/bin/sh
printf "\\n\\nTest 1: exit #comment\\nExpected: (program exits)\\n"
printf "exit #comment\\n" | bin/rshell
printf "\\n\\nTest 2: #exit      ls        exit\\nExpected: ls then exit\\n"
printf "#exit\\nls\\nexit\\n" | bin/rshell
printf "\\n\\nTest 3: ls #cat README.md\\n\\nExpected: just ls\\n"
printf "ls #cat README.md\\nexit\\n" | bin/rshell
printf "\\n\\nTest 4: ls # cat README.md; README.md && README.md || README.md \\n\\nExpected: just ls\\n"
printf "ls # cat README.md; README.md && README.md || README.md\\nexit\\n" | bin/rshell
printf "\\n\\nTest 5: #comment\\nExpected:\\n(program exits)\\n\\n"
printf "#comment\\nexit\\n" | bin/rshell
printf "\\n\\nTest 6: (exit #comment)\\nExpected: syntax error: uneven parentheses\\n"
printf "(exit #comment)\\nexit\\n" | bin/rshell
printf "\\n\\nTest 7: ls #(ls)\\nExpected:\\n"
ls
printf "ls #(ls)\\nexit\\n" | bin/rshell
printf "\\n\\nTest 8: (ls && echo hi) #(ls)\\nExpected:\\n"
(ls && echo hi) #(ls)
printf "(ls && echo hi) #(ls)\\nexit\\n" | bin/rshell
printf "\\n\\nTesting complete\\n"
