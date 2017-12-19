#!/bin/sh
printf "\\n\\nTest 1: exitdude     exit\\nExpected: Uknown Command\\n(program exits)"
printf "exitdude\\nexit" | bin/rshell
printf "\\n\\nTest 2: ls     exit\\nExpected:"
ls
printf "(program exits)"
printf "ls\\nexit" | bin/rshell
printf "\\n\\nTest 3: exit; ls\\n\\nExpected: (program exits)"
printf "exit; ls" | bin/rshell
printf "\\n\\nTest 4: exit\\n\\nExpected: (program exits)"
printf "exit" | bin/rshell
printf "\\n\\nTest 5: (exit)\\n\\nExpected: (program exits)"
printf "(exit)" | bin/rshell
printf "\\n\\nTest 6: (echo hi && (ls && exit))\\n\\nExpected:\\n"
echo hi && ls
printf "(echo hi && (ls && exit))" | bin/rshell
printf "\\n\\nTest 7: exit; (ls && ls)\\n\\nExpected: (program exits)"
printf "exit; (ls && ls)" | bin/rshell
printf "\\n\\nTest 8: ls; (exit; ls)\\n\\nExpected:\\n"
ls
printf "ls; (exit; ls)" | bin/rshell
printf "\\n\\nTesting complete"
