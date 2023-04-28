#!/bin/bash
# Otestuje program podle referenčních dat ze souborů *_in.txt a porovná je s referenčním výstupem *_out.txt
# Soubory musejí být uloženy ve složce "CZE"


TEST_DIR="test/"

# shellcheck disable=SC2231
for IN_FILE in ${TEST_DIR}*_IN.txt
do
	now=$(date +%s)sec
	REF_FILE=$(echo -n "$IN_FILE" | sed -e 's/_IN\(.*\)$/_OUT\1/')

	./a.out < "$IN_FILE" > my_out.txt

	if ! diff "$REF_FILE" my_out.txt > temp.txt
	then
		printf "\e[0;31mFail: %s\e[0m\n" "$IN_FILE"
		head -n 5 temp.txt
		# echo "Vstupni data:"
		# echo `cat "$IN_FILE"`
		# exit
	else
		printf "\e[0;32mOK:\e[0m %s \e[0;32m(%s)\e[0m\n" $IN_FILE $(TZ=UTC date --date now-$now +%S.%N)
		# printf "\e[0;32m%s\r" $(TZ=UTC date --date now-$now +%S.%N)
	fi
done

rm my_out.txt temp.txt
