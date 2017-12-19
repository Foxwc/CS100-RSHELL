This repo is a project for CS100, the assignment is to create our own version of shell. Commands that are built into shell do not have to work, this includes things like cd. Commands that should work are the ones found in /bin/.

Usage: The make file in /rshell-jerry-and-josh will create a directory called /bin and place an executable called rshell inside of it.
make clean will remove the object files as well as the executalbe and the /bin directory.

The tests in the /tests directory should all be run from /rshell... like this tests/test.sh not from the tests directory. Attempting to run them from inside of the tests directory will not work.

Known Issues:
1) when using quotes with a command like echo, it prints the quotes instead of only whats inside (quotes may have other problems too, we didn't handle them very well in assignment 2)

2) some edge cases do not work on the test command (for example using lots of random spaces)

3) trying to use pipe just results in an error, to prevent further issues in our program I have commented out the pipe section and
simply added a clean error message explaining the problem
