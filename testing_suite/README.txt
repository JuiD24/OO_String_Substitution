Version 1.1

do_tests.bash 
--------------
This script will run your executable on a number of different test files.  
Usage: do_tests.bash your_executable
Where "your_executable" is the name of your compiled project to be tested


run_script_from_in_here
-----------------------
Because many files are generated for the tests, execute do_tests.bash from this directory:
cd run_scripts_from_in_here
bash ../do_tests.bash ../../somewhere/my_strsub_program

origfiles
---------
Do not change anything in this directory. This directory contains original
copies of text files your program will be tested on. The do_tests.bash copies
and renames these files to your current directory (presumably the
"run_script_from_in_here" directory) and then runs the tests on the copies.

expected_results
----------------
Do not change anything in this directory. This directory contains the expected
results of the tests that are run on copies of the files in the "origfiles"
directory. 

list_of_tests.txt
-----------------
Do not change this file. This file contains a list of each of the tests for
processing by do_tests.bash
