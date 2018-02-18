#ifndef SIRSArray_hpp
#define SIRSArray_hpp

#include <vector> // For holding the data in the array.
#include <random> // For generating random numbers.
#include <iostream> // For outputting board.
#include <utility> // For std::pair.

/**
 * \file
 * \brief Class to model a 2D lattice of cells in the SIRS model that can be Susceptible, Infected 
 * or recovered and can move between those states stochastically.
 */
class SIRSArray
{
public:
    /** 
     * \enum State
     * \brief Enumeration type to hold the state of the cell, dead or alive.
     */
    enum State
    {
        Susceptible,
        Infected,
        Recovered,
        MAXSTATE,
    };

    /// Look-up table for alive/dead cells symbols for printing.
    static constexpr int stateSymbols[MAXSTATE] = {0,1,2};

private:
    /// Member variable that holds number of rows in lattice.
    int m_rowCount;

    /// Member variable that holds number of columns in lattice.
    int m_colCount;

    /// Member variable that holds the actual data in the lattice.
    std::vector<State> m_boardData;

    /// Member variable for the probability of going from susceptible to infected.
    double m_probSI;

    /// Member variable for the probability of going from infected to recovered.
    double m_probIR;

    /// Member variable for the probability of going from recovered to susceptible.
    double m_probRS;

public:
    /**
     *\brief operator overload for getting the state at a site.
     *
     * This method is implemented since the states are stored internally as a 1D vector, hence 
     * they need to be indexed in a special way in order to get the site that would correspond to 
     * the (i,j) site in matrix notation. This function allows the caller to treat the lattice as a 
     * 2D matrix without having to worry about the internal implementation.
     *
     *\param row row index of site.
     *\param col column index of site.
     *\return reference to state stored at site so called can use it or set it.
     */
    SIRSArray::State& operator()(int row, int col);

    /** 
     *\brief constant version of non-constant counterpart for use with constant SIRSArray object.
     *
     * See non-constant version for description.
     *
     *\param row row index of site.
     *\param col column index of site.
     *\return constant reference to state stored at site so called can use it only.
     */
    const SIRSArray::State& operator()(int row, int col) const;

    /**
     *\brief Constructor that initializes all cells to the state that is its arguments.
     *\param rows number of rows on the board.
     *\param cols number of columns on the board.
     *\param probSI probability of going from susceptible to infected state if cell is in contact with infected cell.
     *\param probIR probability of infected site going from infected to recovered.
     *\param probRS probability of recovered site becoming susceptible again.
     *\param state State instance to initialise all cells to will default to alive.
     */
    SIRSArray(
    	int rows = 50, 
    	int cols = 50, 
    	double probSI = 1.0, 
    	double probIR = 1.0, 
    	double probRS = 1.0, 
    	SIRSArray::State state = SIRSArray::Susceptible);

    /** 
     *\brief Constructor that randomises lattice to an even mix of states.
     *\param rows number of rows on the board.
     *\param cols number of columns on the board.
     *\param probSI probability of going from susceptible to infected state if cell is in contact with infected cell.
     *\param probIR probability of infected site going from infected to recovered.
     *\param probRS probability of recovered site becoming susceptible again.
     *\param generator std::default_random_engine reference for generating random numbers.
     */
    SIRSArray(
        std::default_random_engine &generator,
    	int rows = 50, 
    	int cols = 50, 
    	double probSI = 1.0, 
    	double probIR = 1.0, 
    	double probRS = 1.0
    	);

    /**
     *\brief Randomises the cells in the board with equal probability of being in each state.
     *\param std::deafult_random_engine reference for random number generation.
     */
    void randomise(std::default_random_engine &generator);

    /**
     *\brief Getter for the number of rows.
     *\return Integer value representing the number of rows.
     */
    int getRows() const;

    /**
     *\brief Getter for number of columns.
     *\return Integer value representing the number of columns.
     */
    int getCols() const;

    /**
     *\brief Getter for size of lattice #rows * #columns.
     *\return Integer value representing the size of the lattice.
     */
    int getSize() const;

    /**
     *\brief Getter for the probability of going from susceptible to infected upon contact between two cells.
     *\return Floating point value representing the probability of going from susceptible to infected upon contact.
     */
    double getProbSI() const;

    /**
     *\brief Getter for the probability of going from infected to recovered.
     *\return Floating point value representing the probability of going from infected to recovered.
     */
    double getProbIR() const;

    /**
     *\brief Getter for the probability of going from recovered to susceptible.
     *\return Floating point value representing the probability of going from recovered to susceptible.
     */
    double getProbRS() const;

    /**
     *\brief Setter for the probability of going from susceptible to infected upon contact between two cells.
     *\param prob floating point value representing the probability of going from susceptible to infected.
     */
    void setProbSI(double prob);

    /**
     *\brief Setter for the probability of going from infected to recovered.
     *\param prob floating point value representing the probability of going from infected to recovered.
     */
    void setProbIR(double prob);

    /**
     *\brief Setter for the probability of going from recovered to susceptible.
     *\param prob floating point value representing the probability of going from recovered to susceptible.
     */
    void setProbRS(double prob);


    /**
     *\brief Determines whether cell has an infected neighbour.
     *\param row row of cell in question.
     *\param col column of cell in question.
     *\return Boolean value representing whether the cell has an infected neighbour
     *
     * In the SIRS model we only consider neighbours as being N,E,S and W.
     */
    bool hasInfectedNeighbour(int row, int col) const;

    /**
     *\brief Updates the state of a single cell based on the current 
     * state of the cell, its neighbours and the probabilities.
     *\pram row Integer value representing the row of the cell in question.
     *\param col Integer value representing the column of the cell in question.
     *\param generator std::default_random_engine for random number generation.
     *\return the new updated state of the cell.
     */
    SIRSArray::State updateCell(int row, int col, std::default_random_engine& generator);

    /**
     *\brief Updates a random cell in the grid.
     *\param std::default_random_engine reference for random number generation.
     *\return the new updated state of the cell.
     */
    SIRSArray::State update(std::default_random_engine& generator);

    /**
     *\brief calculates the total fraction of cells in a given state.
     *\param state value representing the state of interest.
     *\return Floating point value representing the fraction of cells in the state of interest
     */
    double stateFraction(SIRSArray::State state) const;

    /**
     *\brief streams the board to an output stream in a nicely formatted way
     *\param out std::ostream reference that is being streamed to 
     *\param board SIRSArray reference to be printed
     *\return std::ostream reference to output can be chained.
     */
     friend std::ostream& operator<<(std::ostream& out, const SIRSArray &board);

};

#endif /* SIRSArray_hpp */