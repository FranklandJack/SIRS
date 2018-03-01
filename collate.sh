# If the data files that contain the collated data do not already exists create them.
rm p1p3Order.dat
rm p1p3Sus.dat
rm ImmuneOrder.dat

touch p1p3Order.dat
touch p1p3Sus.dat
touch ImmuneOrder.dat


# Iterate through each set of results.
for results in "$@"*
do
    # For p1p3.
    # Get the values of p1 from the input files and append it to collated data file.
    awk '/^(p_1:) /{printf $NF}' $results/Input.txt >> p1p3Order.dat
    awk '/^(p_1:) /{printf $NF}' $results/Input.txt >> p1p3Sus.dat

    # Put an empty column in the file.
    printf " " >> p1p3Order.dat
    printf " " >> p1p3Sus.dat

    # Get the values of p3 from the input files and append it to collated data file.
    awk '/^(p_3:) /{printf $NF}' $results/Input.txt >> p1p3Order.dat
    awk '/^(p_3:) /{printf $NF}' $results/Input.txt >> p1p3Sus.dat

    # Put an empty column in the file.
    printf " " >> p1p3Order.dat
    printf " " >> p1p3Sus.dat

    # Get the values of the order parameter from the results files and append it to collated data file.
    awk '/^(Order-Parameter:) /{print $(NF-2)}' $results/Results.txt >> p1p3Order.dat
    awk '/^(Susceptibility:) /{print $(NF-2)}' $results/Results.txt >> p1p3Sus.dat

    # For immune agents vs order parameter.
    # Get the fraction of immune agents from the input file and collate it to do data file.
    awk '/^(Immune-Fraction:) /{printf $NF}' $results/Input.txt >> ImmuneOrder.dat

    # Put an empty column in the file.
    printf " " >> ImmuneOrder.dat

    # Get the values of the order parameter from the results files and append it to collated data file.
    awk '/^(Order-Parameter:) /{printf $(NF-2)}' $results/Results.txt >> ImmuneOrder.dat

    # Put an empty column in the file.
    printf " " >> ImmuneOrder.dat

    # Get the error in the order parameter.
    awk '/^(Order-Parameter:) /{print $(NF)}' $results/Results.txt >> ImmuneOrder.dat

   


done

# Remove duplicate lines from files.
sort -u p1p3Order.dat -o p1p3Order.dat
sort -u p1p3Sus.dat -o p1p3Sus.dat

# Insert blank lines when first line entry differs in p1p3order and p1p3sus so they can be plotted via pm3d as heat maps.
touch tempp1p3Order.dat
touch tempp1p3Sus.dat
awk -v i=1 'NR>1 && $i!=p { print "" }{ p=$i } 1' p1p3Order.dat > tempp1p3Order.dat
awk -v i=1 'NR>1 && $i!=p { print "" }{ p=$i } 1' p1p3Sus.dat > tempp1p3Sus.dat
mv tempp1p3Order.dat p1p3Order.dat
mv tempp1p3Sus.dat p1p3Sus.dat

