#include "SIRSArray.hpp"

constexpr int SIRSArray::stateSymbols[];

SIRSArray::State& SIRSArray::operator()(int row, int col)
{
    // Take into account periodic boundary conditions.
    row = (row + m_rowCount) % m_rowCount;
    col = (col + m_colCount) % m_colCount;

    // Return 1D index of 1D array corresponding to the 2D index.
    return m_boardData[col + row * m_colCount];
}

const SIRSArray::State& SIRSArray::operator()(int row, int col) const
{
    // Take into account periodic boundary conditions we add extra m_rowCount and m_colCount
    // terms here to take into account the fact that the caller may be indexing with -1.
    row = (row + m_rowCount) % m_rowCount;
    col = (col + m_colCount) % m_colCount;

    // Return 1D index of 1D array corresponding to the 2D index.
    return m_boardData[col + row * m_colCount];
}


SIRSArray::SIRSArray(
	int rows, 
	int cols, 
	double probSI, 
	double probIR, 
	double probRS, 
	SIRSArray::State state
	) : m_rowCount{rows},
		m_colCount{cols},
		m_probSI{probSI},
		m_probIR{probIR},
		m_probRS{probRS},
		m_boardData(rows*cols, state)
{}

SIRSArray::SIRSArray(
	std::default_random_engine &generator,
	int rows, 
	int cols, 
	double probSI, 
	double probIR, 
	double probRS
	) : m_rowCount{rows},
		m_colCount{cols},
		m_probSI{probSI},
		m_probIR{probIR},
		m_probRS{probRS}
{
    //TODO: This can probably be made more efficient.

    // Reserve the correct amount of space in the board data.
    m_boardData.reserve(rows * cols);
    static std::uniform_int_distribution<int> distribution(0,static_cast<int>(SIRSArray::MAXSTATE)-1);
    for(int i = 0; i < rows*cols; ++i)
    {
        m_boardData.push_back(static_cast<SIRSArray::State>(distribution(generator)));
    }
}

void SIRSArray::randomise(std::default_random_engine &generator)
{
    // Create a uniform distribution for the states on the board.
    static std::uniform_int_distribution<int> distribution(0,static_cast<int>(SIRSArray::MAXSTATE)-1);

    for(auto &cell : m_boardData)
    {
        cell = static_cast<SIRSArray::State>(distribution(generator));
    }

}


int SIRSArray::getRows() const
{
    return m_rowCount;
}

int SIRSArray::getCols() const
{
    return m_colCount;
}

int SIRSArray::getSize() const
{
    return m_colCount * m_rowCount;
}

bool SIRSArray::hasInfectedNeighbour(int row, int col) const
{
	// Make checks using overloaded () operator so that we take into account periodic
	// boundary conditions.

	// Check N E S W.
	if(SIRSArray::Infected==(*this)(row+1,col) 
	|| SIRSArray::Infected==(*this)(row,col+1)
	|| SIRSArray::Infected==(*this)(row-1,col) 
	|| SIRSArray::Infected==(*this)(row,col-1))
	{
		return true;
	}

	// Otherwise there are no infected neighbours.
	return false;
}


SIRSArray::State SIRSArray::updateCell(int row, int col, std::default_random_engine& generator)
{
	// Uniform random number generation for stochastically updating states. Since the distribution
	// is always the same we make its static.
	static std::uniform_real_distribution<double> distribution(0.0,1.0);

	switch((*this)(row,col))
	{
		case State::Susceptible :   if(hasInfectedNeighbour(row,col))	
									{
									(*this)(row,col) = (distribution(generator) < m_probSI) ? State::Infected : State::Susceptible;
									}
									break;
		case State::Infected : (*this)(row,col) = (distribution(generator) < m_probIR) ? State::Recovered : State::Infected;
								break;

		case State::Recovered : (*this)(row,col) = (distribution(generator) < m_probRS) ? State::Susceptible : State::Recovered;
								break;

		default: 
				break;

	}

	return (*this)(row,col);
}

double SIRSArray::getProbSI() const 
{
	return m_probSI;
}

double SIRSArray::getProbIR() const
{
	return m_probIR;
}

double SIRSArray::getProbRS() const
{
	return m_probRS;
}

void SIRSArray::setProbSI(double prob)
{
	m_probSI = prob;
}

void SIRSArray::setProbIR(double prob)
{
	m_probIR = prob;
}

void SIRSArray::setProbRS(double prob)
{
	m_probRS = prob;
}



SIRSArray::State SIRSArray::update(std::default_random_engine& generator)
{
	// Create a uniform distribution for the rows and columns remembering to subtract 1 for the closed limits.
	std::uniform_int_distribution<int> rowDistribution(0,m_rowCount-1);
	std::uniform_int_distribution<int> colDistribution(0,m_colCount-1);

	// Update a random cell and return the state of the updated cell.
	return updateCell(rowDistribution(generator), colDistribution(generator), generator);

}

double SIRSArray::stateFraction(SIRSArray::State state) const
{
	double total = 0;
	for(const auto& cellState : m_boardData)
	{
		if(state == cellState)
		{
			total++;
		}
	}

	return total/(m_colCount*m_rowCount);
}



std::ostream& operator<<(std::ostream& out, const SIRSArray &board)
{
    

    int maxRows = board.getRows();
    int maxCols = board.getCols();

    for(int row = 0; row < maxRows; ++row)
    {
        for(int col = 0; col < maxCols; ++ col)
        {
            out << SIRSArray::stateSymbols[board(row,col)] << ' ';
        }

        out << '\n';
    }

    return out;
}