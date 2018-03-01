for i in `seq 0 100`;
do
	imunefrac=$(python -c "print(0.2+$i/1000.0)")
	./sirs -p 0.5 -q 0.5 -g 0.5 -m $imunefrac -b 10000
done