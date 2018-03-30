for i in `seq 0 20`;
do
	for j in `seq 0 20`;
	do
		p1=$(python -c "print($i/20.0)")
		p3=$(python -c "print($j/20.0)")
		./sirs -p $p1 -q 0.5 -g $p3 
	done
done