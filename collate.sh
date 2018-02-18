# If the data files that contain the collated data do not already exists create them.
rm p1p3.dat
touch p1p3.dat

# Iterate through each set of results.
for results in "$@"*
do
    # For p1p3.
    # Get the values of p1 from the input files and append it to collated data file.
    awk '/^(p_1:) /{printf $NF}' $results/Input.txt >> p1p3.dat

    # Put an empty column in the file.
    printf " " >> p1p3.dat

    # Get the values of p3 from the input files and append it to collated data file.
    awk '/^(p_3:) /{printf $NF}' $results/Input.txt >> p1p3.dat

    # Put an empty column in the file.
    printf " " >> p1p3.dat

    # Get the values of the order parameter from the results files and append it to collated data file.
    awk '/^(Order-Parameter:) /{print $(NF-2)}' $results/Results.txt >> p1p3.dat

   


done

# Remove duplicate lines from files.
sort -u p1p3.dat -o p1p3.dat

