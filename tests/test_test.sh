#!/bin/sh
#test [ ] with each flag
printf "\\n\\nTest 1: [ -e src ]\\nExpected:\\n(True)" # -e, true
printf "\\n\\n"
printf "[ -e src ]; exit\\n" | bin/rshell
printf "\\n\\nTest 2: [ -e dog ]\\nExpected:\\n(False)" # -e, false
printf "\\n\\n"
printf "[ -e dog ]; exit\\n" | bin/rshell
printf "\\n\\nTest 3: [ -f src ]\\nExpected:\\n(False)" # -f, false
printf "\\n\\n"
printf "[ -f src ]; exit\\n" | bin/rshell
printf "\\n\\nTest 4: [ -f makefile ]\\nExpected:\\n(True)" # -f, true
printf "\\n\\n"
printf "[ -f makefile ]; exit\\n" | bin/rshell
printf "\\n\\nTest 5: [ -d src ]\\nExpected:\\n(True)" # -d, true
printf "\\n\\n"
printf "[ -d src ]; exit\\n" | bin/rshell
printf "\\n\\nTest 6: [ -d makefile ]\\nExpected:\\n(False)" # -d, false
printf "\\n\\n"
printf "[ -d makefile ]; exit\\n" | bin/rshell
printf "\\n\\nTest 7: [ src ]\\nExpected:\\n(True)" # [  ] true
printf "\\n\\n"
printf "[ src ]; exit\\n" | bin/rshell
printf "\\n\\nTest 8: [ frog ]\\nExpected:\\n(False)" # [  ] false
printf "\\n\\n"
printf "[ frog ]; exit\\n" | bin/rshell
# test "test" with each flag
printf "\\n\\nTest 9: test -e src\\nExpected:\\n(True)" # test -e true
printf "\\n\\n"
printf "test  -e src; exit\\n" | bin/rshell
printf "\\n\\nTest 10: test -e dog\\nExpected:\\n(False)" # test -e false
printf "\\n\\n"
printf "test  -e dog; exit\\n" | bin/rshell
printf "\\n\\nTest 11: test -f src\\nExpected:\\n(False)" # test -f false
printf "\\n\\n"
printf "test  -f src; exit\\n" | bin/rshell
printf "\\n\\nTest 12: test -f makefile\\nExpected:\\n(True)" # test -f true
printf "\\n\\n"
printf "test  -f makefile; exit\\n" | bin/rshell
printf "\\n\\nTest 13: test -d src\\nExpected:\\n(True)" # test -d true
printf "\\n\\n"
printf "test  -d src; exit\\n" | bin/rshell
printf "\\n\\nTest 14: test -d makefile\\nExpected:\\n(False)" # test -d false
printf "\\n\\n"
printf "test  -d makefile; exit\\n" | bin/rshell
printf "\\n\\nTest 15: test src\\nExpected:\\n(True)" # test   true
printf "\\n\\n"
printf "test src; exit\\n" | bin/rshell
printf "\\n\\nTest 16: test frog\\nExpected:\\n(False)" # test   false
printf "\\n\\n"
printf "test frog; exit\\n" | bin/rshell
#test if (True) and (False) properly set flag
printf "\\n\\nTest 17: [ -e src ] && ls\\nExpected:\\n(True)\\n" # true &&
ls
printf "\\n\\n"
printf "[ -e src ] && ls; exit\\n" | bin/rshell
printf "\\n\\nTest 18: [ -e log ] && ls\\nExpected:\\n(False)" # false &&
printf "\\n\\n"
printf "[ -e log ] && ls; exit\\n" | bin/rshell
printf "\\n\\nTest 19: [ -e cat ] || ls\\nExpected:\\n(False)\\n" # false ||
ls
printf "\\n\\n"
printf "[ -e cat ] || ls; exit\\n" | bin/rshell
printf "\\n\\nTest 20: [ -e src ] || ls\\nExpected:\\n(True)" # false &&
printf "\\n\\n"
printf "[ -e src ] || ls; exit\\n" | bin/rshell
# test [    ]
printf "\\n\\nTest 21: [  ]\\nExpected:\\n(False)" # empty [] (should be false)
printf "\\n\\n"
printf "[  ]; exit\\n" | bin/rshell
#test full directory paths
printf "\\n\\nTHE FOLLOWING TEST DEPENDS ON WHICH COMPUTER YOU ARE USING. The tests check for full directories, which will be different for each person running the command\\ntest_test.sh lines 73-75 must be editted"
printf "\\n\\nTest 22: [ -e /class/classes/jwils019/rshell-jerry-and-josh/ ]\\nExpected:\\n(True)" # full directory, change this depending on what your computer's full directory looks like (true)
printf "\\n\\n"
printf "[ -e /class/classes/jwils019/rshell-jerry-and-josh/ ]; exit\\n" | bin/rshell
printf "\\n\\nTest 23: [ -e /class/classes/jwils019/whale/ ]\\nExpected:\\n(False)" # full directory, change this depending on what your computer's full directory looks like (false)
printf "\\n\\n"
printf "[ -e /class/classes/jwils019/whale/ ]; exit\\n" | bin/rshell
printf "\\n\\nTesting complete\\n"
