#Compile the code
# if the file densemult exits then remove it
clear
if [ -f sort ]; then
    rm sort
fi
g++ -std=c++11 *.cpp -o sort
# if the file densemult does not exit then exit the test
if [ ! -f sort ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi
# clean
if [ -f *.out ]; then
    rm *.out
fi
if [ -f *.stderr ]; then
    rm *.stderr
fi
if [ -f *.stdcout ]; then
    rm *.stdcout
fi
#rm *.out *.stderr *.stdcout
# For test case 1
# input 1.txt and output 1.out
res1=$(date +%s.%N)
./sort "input=input31.txt;command=command31.txt;output=output31.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.00796
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test case 1 time: $diff"
echo "Desired test case 1 time interval: $desired-$error ~ $desired+$error"

# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu ans31.txt output31.txt > 1.diff
# if diff returns nothing, it means you pass the test case (Your ourput file 1.out is correct)
if [ $? -ne 0 ]; then
    # display "test case 1 FAILED" to the screen. The word "FAILED" is highlighted in Red color
    echo -e "Test case 1    \033[1;91mFAILED.\033[0m"
else
    # display "test case 1 PASSED" to the screen. The word "PASSED" is highlighted in Green color
    echo -e "Test case 1    \033[1;92mPASSED.\033[0m"
    # remove the file 1.diff
    rm -f 1.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 1 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]]; then
      echo -e "Test case 1 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 1 time  \033[1;92mPASSED.\033[0m"
fi


# For test case 2
res1=$(date +%s.%N)
./sort "input=input32.txt;command=command32.txt;output=output32.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.01015
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test case 2 time: $diff"
echo "Desired test case 2 time interval:$desired-$error ~ $desired+$error"
diff -iEBwu ans32.txt output32.txt > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
      echo -e "Test case 2 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 2 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 2 time  \033[1;92mPASSED.\033[0m"
fi

# For test case 3
res1=$(date +%s.%N)
./sort "input=input33.txt;command=command33.txt;output=output33.txt" 1>1.stdcout 2>1.stderr
res2=$(date +%s.%N)
diff=`echo "$res2 - $res1"|bc|awk '{printf "%f",$0}'`
desired=0.0086
error=`echo "$desired * 0.3"|bc|awk '{printf "%f",$0}'`
echo "Test Case 3 Time: $diff"
echo "Desired test case 3 time interval: $desired-$error ~ $desired+$error"
diff -iEBwu ans33.txt output33.txt > 3.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
    rm -f 3.diff
fi
if [[ `echo "$diff>($desired+$error)"|bc` -eq 1 ]]; then
       echo -e "Test case 3 time \033[1;91mERROR.\033[0m"
elif [[ `echo "$diff<($desired-$error)"|bc` -eq 1 ]];then
      echo -e "Test case 3 time \033[1;91mERROR.\033[0m"
else
    echo -e "Test case 3 time  \033[1;92mPASSED.\033[0m"
fi



