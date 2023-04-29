#!/bin/bash
# Otestuje program podle referenčních dat ze souborů *_in.txt a porovná je s referenčním výstupem *_out.txt
# Soubory musejí být uloženy ve složce "CZE"

TEST_DIR="test/"
counter=0
total_time_1_5=0
total_time_6_9=0
num_tests_1_5=5
num_tests_6_9=4

for IN_FILE in ${TEST_DIR}*_IN.txt
do
  counter=$((counter + 1))
  now=$(date +%s%N)
  REF_FILE=$(echo -n "$IN_FILE" | sed -e 's/_IN\(.*\)$/_OUT\1/')

  ./a.out < "$IN_FILE" > my_out.txt

  # Odstraň mezery na konci řádků v souboru my_out.txt
  sed -i 's/[[:space:]]*$//' my_out.txt

  if ! diff "$REF_FILE" my_out.txt > temp.txt
  then
    elapsed_time=$(($(date +%s%N) - now))
    printf "\e[0;31mFail: %s \e[0;32m(%d ms)\e[0m\n" "$IN_FILE" $((elapsed_time / 1000000))
    head -n 5 temp.txt
  else
    elapsed_time=$(($(date +%s%N) - now))
    printf "\e[0;32mOK:\e[0m %s \e[0;32m(%d ms)\e[0m\n" "$IN_FILE" $((elapsed_time / 1000000))
  fi

  if [[ $counter -le 5 ]]; then
    total_time_1_5=$((total_time_1_5 + elapsed_time))
  else
    total_time_6_9=$((total_time_6_9 + elapsed_time))
  fi
done

avg_time_1_5=$((total_time_1_5 / num_tests_1_5 / 1000000))
avg_time_6_9=$((total_time_6_9 / num_tests_6_9 / 1000000))

printf "\e[0;34mPrůměrná doba trvání testů 1 až 5: \e[0;32m%i ms\n" $avg_time_1_5
printf "\e[0;34mPrůměrná doba trvání testů 6 až 9: \e[0;32m%i ms\n" $avg_time_6_9

rm my_out.txt temp.txt