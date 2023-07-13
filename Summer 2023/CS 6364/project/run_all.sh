#!/bin/bash

input_board=$1
output_board=$2
depth=$3

echo Input Board is $input_board Output Board is $output_board Depth is $depth
echo Input Board contains
cat $input_board

pypy3='/home/pypy/pypy3.exe'

echo $'\n'

echo $pypy3 MiniMaxOpening.py $input_board $output_board $depth
$pypy3 MiniMaxOpening.py $input_board $output_board $depth

echo $'\n'

echo $pypy3 MiniMaxGame.py $input_board $output_board $depth
$pypy3 MiniMaxGame.py $input_board $output_board $depth

echo $'\n'

echo $pypy3 MiniMaxOpeningImproved.py $input_board $output_board $depth
$pypy3 MiniMaxOpeningImproved.py $input_board $output_board $depth

echo $'\n'

echo $pypy3 MiniMaxGameImproved.py $input_board $output_board $depth
$pypy3 MiniMaxGameImproved.py $input_board $output_board $depth

echo $'\n'

echo $pypy3 ABOpening.py $input_board $output_board $depth
$pypy3 ABOpening.py $input_board $output_board $depth

echo $'\n'

echo $pypy3 ABGame.py $input_board $output_board $depth
$pypy3 ABGame.py $input_board $output_board $depth

echo $'\n'

echo $pypy3 MiniMaxOpeningBlack.py $input_board $output_board $depth
$pypy3 MiniMaxOpeningBlack.py $input_board $output_board $depth

echo $'\n'

echo $pypy3 MiniMaxGameBlack.py $input_board $output_board $depth
$pypy3 MiniMaxGameBlack.py $input_board $output_board $depth

echo $'\n'
