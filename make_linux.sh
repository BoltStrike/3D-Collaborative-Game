if [ -f "3dcollaborativegame" ]
then
    rm -f "3dcollaborativegame"
fi
if [ ! -d objects ]
then
    mkdir objects
fi
make
if [ -f "3dcollaborativegame" ]
then
    echo -e "\e[32mCompilation Successful\e[0m"
else
    echo -e "\e[31mCOMPILATION FAILED\e[0m. CHECK YOUR CODE."
fi
