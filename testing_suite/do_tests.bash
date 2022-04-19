#!/usr/bin/env bash

#ensure there is an argument
if [[ $# -ne 1 ]]
then
  echo "Usage: do_tests.bash your_executable"
  exit 1
fi

#ensure the provided argument is an executable
if [[ ! -x $1 ]]
then
  echo "Usage: do_tests.bash your_executable"
  echo "  I can't find your_executable. Perhaps it is not where you think it is"
  exit 1
fi
EXECUTABLE_NAME="$1"

#ensure this script is being run from the correct location
if [[ $(basename "$PWD") != "run_script_from_in_here" ]]
then
  echo "Your current directory must be \"run_script_from_in_here\" when running this script. Try this:"
  printf "\n  cd run-script_from_in_here\n  ../do_tests.bash your_executable\n\n"
  exit 1
fi

if [ ! -d ../origfiles ] 
then
  echo "I cannot find origfiles. Have you been moving stuff around?"
  exit 1
fi

cp ../origfiles/File01.txt Test01.txt
cp ../origfiles/File01.txt Test02.txt
cp ../origfiles/File01.txt Test03.txt
cp ../origfiles/File02.txt Test04.txt
cp ../origfiles/File02.txt Test05.txt
cp ../origfiles/File02.txt Test06.txt
cp ../origfiles/File03.txt Test07.txt
cp ../origfiles/File03.txt Test08.txt
cp ../origfiles/File03.txt Test09.txt
cp ../origfiles/File04.txt Test10.txt
cp ../origfiles/File05.txt Test11.txt
cp ../origfiles/File06.txt Test12.txt
cp ../origfiles/File07.txt Test13.txt
cp ../origfiles/File08.txt Test14.txt
cp ../origfiles/File09.txt Test15.txt
cp ../origfiles/File10.txt Test16.txt
cp ../origfiles/File11.txt Test17.txt
cp ../origfiles/File12.txt Test18.txt

chmod +w Test[01][0-9].txt

cat ../list_of_tests.dat | while read testname old new filename
do
  echo "================"
  echo $testname
  echo "================"
  $EXECUTABLE_NAME $old $new $testname.txt 
  diff $testname.txt ../expected_results/$testname.txt >/dev/null
  if [ $? -eq 0 ]
  then
    echo "$testname success!" 
  else
    echo "$testname failure <########################################"
    #only show contents of short files
    echo "Search for: $old, replace with: $new"
    if [ `wc -c ../origfiles/$filename|awk '{print $1}'` -lt 50 ]
    then
      echo -n "Original file:--->"
      cat ../origfiles/$filename
      echo "<-"
      echo -n "Expected result:->"
      cat ../expected_results/$testname.txt
      echo "<-"
      echo -n "Test result:----->"
      cat $testname.txt
      echo "<-"
    else
      echo "Original file: ../origfiles/$filename"
      echo "Expected results: ../expected_results/$testname.txt"
      echo "Test results: $testname.txt"
    fi
  fi
  echo
  echo
done
