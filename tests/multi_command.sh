#!/bin/sh
printf "\n\nTest 1: rmdir cat || ls\nExpected:\\n" # testing || (fail)
rmdir cat || ls
printf "rmdir cat || ls\nexit\\n" | bin/rshell
printf "\n\nTest 2: rmdir cat && ls\nExpected:\\n" # testing && (fail)
rmdir cat && ls
printf "rmdir cat && ls\nexit\\n" | bin/rshell
printf "\n\nTest 3: ls; mkdir tests && ls || cat README.md\nExpected:\\n" # testing ; -> && and && -> || (&& passes)
ls; mkdir tests && ls || cat README.md
printf "ls; mkdir tests && ls || cat README.md\nexit\\n" | bin/rshell
printf "\n\nTest 4: ls; mkdir tests || ls && cat README.md\n\nExpected:\\n" # testing ; -> || and || -> && (|| passes)
ls; mkdir tests || ls && cat README.md
printf "ls; mkdir tests || ls && cat README.md\nexit\\n" | bin/rshell
printf "\n\nTest 5: ls || exit; ls\n\nExpected:\\n" # testing || -> ; (|| passes)
ls || exit; ls
printf "ls || exit; ls\nexit\\n" | bin/rshell
printf "\n\nTest 6: ls && ls; cat makefile\n\nExpected:\\n" # testing && -> ; (&& passes)
ls && ls; cat makefile
printf "ls && ls; cat makefile\nexit\\n" | bin/rshell
printf "\n\nTest 7: rmdir frog && ls; cat makefile\n\nExpected:\\n" # testing && -> ; (&& fails)
rmdir frog && ls; cat makefile
printf "rmdir frog && ls; cat makefile\nexit\\n" | bin/rshell
printf "\n\nTest 8: rmdir frog || ls;\n\nExpected:\\n" # testing || -> ; (|| fails)
rmdir frog || ls;
printf "rmdir frog || ls;\nexit\\n" | bin/rshell
printf "\n\nTest 9: echo hello|| ls\nExpected:\\n" # testing || (pass)
echo hello || ls
printf "echo hello || ls\nexit\\n" | bin/rshell
printf "\n\nTest 10: echo hello && ls\nExpected:\\n" # testing && (pass)
echo hello && ls
printf "echo hello && ls\nexit\\n" | bin/rshell
printf "\n\nTest 11: hello; ls\nExpected:\\n" # testing ; (pass)
hello; ls
printf "hello; ls\nexit\\n" | bin/rshell
printf "\n\nTest 12: rmdir frog; ls\nExpected:\\n" # testing ; (fail)
rmdir frog; ls
printf "rmdir frog; ls\nexit\\n" | bin/rshell
printf "\n\nTest 13: ls; cat dog || ls && cat README.md\n\nExpected:\\n" # testing ; -> || and || -> && (|| fails)
ls; cat dog || ls && cat README.md
printf "ls; cat dog || ls && cat README.md\nexit\\n" | bin/rshell
printf "\n\nTest 14: ls; cat dog && ls || cat README.md\nExpected:\\n" # testing ; -> && and && -> || (&& fails)
ls; cat dog && ls || cat README.md
printf "ls; cat dog && ls || cat README.md\nexit\\n" | bin/rshell
printf "\n\nTest 15: ls; ls; ls; ls; ls; ls\n\nExpected:\\n" # testing ; -> ; -> ........ -> ;
ls; ls; ls; ls; ls; ls
printf "\n\n\\n"
printf "ls; ls; ls; ls; ls; ls\nexit\\n" | bin/rshell
printf "\n\nTesting complete\\n"
