#!/bin/bash


for file in "$@"; do
	echo "$file"

	awk '
		{
			avem = 0

			for (i=1; i<=NF; i++)
				if ($i ~ /-?[0-9]+/) {
					suma = suma + $i
					avem = 1
				}

			if (avem == 1)
				contor++
		}

		END {
			print("sum = ", suma)
			printf("%d/%d\n", contor, NR-contor)
		}
	' "$file"
done
