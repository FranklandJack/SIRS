for i in `seq 0 10`;
do
	for j in `seq 0 10`;
	do
		p1=$(python -c "print($i/10.0)")
		p3=$(python -c "print($j/10.0)")
		./sirs -p $p1 -q 0.5 -g $p3 
	done
done