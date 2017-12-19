#!/bin/sh
#all single operators inside single set of parentheses
echo "\\n\\nTest 1: (ls && ls)\\nExpected:\\n"
(ls && ls)
printf "\\n\\n"
printf "(ls && ls); exit\\n" | bin/rshell
echo "\\n\\nTest 2: (ls || ls)\\nExpected:\\n"
(ls || ls)
printf "\\n\\n"
printf "(ls || ls); exit\\n" | bin/rshell
echo "\\n\\nTest 3: (ls; ls)\\nExpected:\\n"
(ls; ls)
printf "\\n\\n"
printf "(ls; ls); exit\\n" | bin/rshell
echo "\\n\\nTest 4: (ls #ls)\\nExpected:\\n syntax error: uneven parentheses"
printf "\\n\\n"
printf "(ls #ls)\\nexit\\n" | bin/rshell
#two sets of parentheses connected by opperators
echo "\\n\\nTest 5: (ls && ls) && (ls && ls)\\nExpected:\\n"
(ls && ls) && (ls && ls)
printf "\\n\\n"
printf "(ls && ls) && (ls && ls); exit\\n" | bin/rshell # && and worked
echo "\\n\\nTest 6: (ls && ls) || (ls && ls)\\nExpected:\\n"
(ls && ls) || (ls && ls)
printf "\\n\\n"
printf "(ls && ls) || (ls && ls); exit\\n" | bin/rshell # || and worked
echo "\\n\\nTest 7: (dog || dog) && (ls && ls)\\nExpected:\\n"
(dog || dog) && (ls && ls)
printf "\\n\\n"
printf "(dog || dog) && (ls && ls); exit\\n" | bin/rshell # && and failed
echo "\\n\\nTest 8: (dog || dog) || (ls && ls)\\nExpected:\\n"
(dog || dog) || (ls && ls)
printf "\\n\\n"
printf "(dog || dog) || (ls && ls); exit\\n" | bin/rshell # || and failed
echo "\\n\\nTest 9: (ls && ls); (ls && ls)\\nExpected:\\n"
(ls && ls); (ls && ls)
printf "\\n\\n"
printf "(ls && ls); (ls && ls); exit\\n" | bin/rshell # ;
echo "\\n\\nTest 10: (ls && ls) # (ls && ls)\\nExpected:\\n"
(ls && ls) # (ls && ls)
printf "\\n\\n"
printf "(ls && ls) # (ls && ls)\\nexit\\n" | bin/rshell # #
#many parentheses in a row at once
echo "\\n\\nTest 11: (ls && ls); (ls && ls); (ls && ls); (ls && ls)\\nExpected:\\n"
(ls && ls); (ls && ls); (ls && ls); (ls && ls)
printf "\\n\\n"
printf "(ls && ls); (ls && ls); (ls && ls); (ls && ls); exit\\n" | bin/rshell # ; only
echo "\\n\\nTest 12: (ls && echo hi) || (echo hi && ls) || (echo hi && ls) && (ls && echo hi)\\nExpected:\\n"
(ls && echo hi) || (echo hi && ls) || (echo hi && ls) && (ls && echo hi)
printf "\\n\\n"
printf "(ls && echo hi) || (echo hi && ls) || (echo hi && ls) && (ls && echo hi); exit\\n" | bin/rshell #&& and || combined (parentheses worked)
echo "\\n\\nTest 13: (ls && dog) || (echo hi && dog) || (ls && dog) && (echo hi && dog)\\nExpected:\\n"
(ls && dog) || (echo hi && dog) || (ls && dog) && (echo hi && dog)
printf "\\n\\n"
printf "(ls && dog) || (echo hi && dog) || (ls && dog) && (echo hi && dog); exit\\n" | bin/rshell #&& and || combined (parentheses failed)
#parentheses inside of parentheses
echo "\\n\\nTest 14: ((ls && ls); (dog || dog)) || ls\\nExpected:\\n"
((ls && ls); (dog || dog)) || ls
printf "\\n\\n"
printf "((ls && ls); (dog || dog)) || ls; exit\\n" | bin/rshell # || after parentheses, failed
echo "\\n\\nTest 15: ((ls && ls); (dog || ls)) || ls\\nExpected:\\n"
((ls && ls); (dog || ls)) || ls
printf "\\n\\n"
printf "((ls && ls); (dog || ls)) || ls; exit\\n" | bin/rshell # || after parentheses, worked
echo "\\n\\nTest 16: ((ls && ls); (dog || dog)) && ls\\nExpected:\\n"
((ls && ls); (dog || dog)) && ls
printf "\\n\\n"
printf "((ls && ls); (dog || dog)) && ls; exit\\n" | bin/rshell # && after parentheses, failed
echo "\\n\\nTest 17: ((ls && ls); (dog || ls)) && ls\\nExpected:\\n"
((ls && ls); (dog || ls)) && ls
printf "\\n\\n"
printf "((ls && ls); (dog || ls)) && ls; exit\\n" | bin/rshell # && after parentheses, worked
#uneven parentheses
echo "\\n\\nTest 18: ((ls && ls)\\nExpected:\\nsyntax error: uneven parentheses"
printf "\\n\\n"
printf "((ls && ls) \\nexit\\n" | bin/rshell # ((     )
echo "\\n\\nTest 19: (ls && ls))\\nExpected:\\nsyntax error: uneven parentheses"
printf "\\n\\n"
printf "(ls && ls)) \\nexit\\n" | bin/rshell # (      ))
echo "\\n\\nTest 20: (ls && ls\\nExpected:\\nsyntax error: uneven parentheses"
printf "\\n\\n"
printf "(ls && ls \\nexit\\n" | bin/rshell # (
echo "\\n\\nTest 21: ls && ls)\\nExpected:\\nsyntax error: uneven parentheses"
printf "\\n\\n"
printf "ls && ls) \\nexit\\n" | bin/rshell #         )
#many levels of parentheses inside of parentheses
echo "\\n\\nTest 22: ((((ls && ls) || dog) && frog) || echo dog) && ls \\nExpected:\\n"
((((ls && ls) || dog) && frog) || echo dog) && ls
printf "\\n\\n"
printf "((((ls && ls) || dog) && frog) || echo dog) && ls; exit\\n" | bin/rshell
printf "\\n\\nTesting complete\\n"
