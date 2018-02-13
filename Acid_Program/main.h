#include "Util.h"
#include "Protein.h"
#include <random>
#include <ctime>
#include <tuple>
#include <fstream>

struct Locations
{
    list<tuple<double, double, double>> locations1;
    list<tuple<double, double, double>> locations2;
    list<tuple<double, double, double>> locations3;
};

extern int requestAcidAmount(Protein protein, default_random_engine * randomEngine, int lastId);

extern void display(Protein protein);

extern void insertSolution ( Protein p1, Protein p2,Protein p3, default_random_engine * randomEngine);

extern void linkSolutionNodes(list<Acid> & acids, default_random_engine * randomEngine, list<Acid>::iterator iterator);

extern void attachSolution (list<Acid> & aList, Protein &p, int id);

extern int createNodes(list<Acid> & acids, default_random_engine * randomEngine, int numAcids, int lastId);

extern void linkNodes(list<Acid> & acids, default_random_engine * randomEngine, list<Acid>::iterator iterator);

extern void translateNodes(list<Acid> * acids, list<Acid>::iterator iterator, int bottomVertexId);

extern void rotateNodes(list<Acid> * acids, list<Acid>::iterator iterator, tuple<int, int> aicdIds);

extern void rotateNodesByMat(list<Acid> * acids, list<Acid>::iterator iterator, double mat[3][3]);

extern void gnuPlotOutput(ofstream& p1plot, ofstream& p2plot, ofstream& p3plot, ofstream& comout, Locations * locations);

/*
 * Tuple containing 3 tuple pairs.
 * Each pair contains the id of the acid that sits at the bottom of the "V" shape for the key,
 * and the acid that makes up the free vector.
 *
 * From the first acid id the Acid that makes up the standing vector may be found.
 */
extern tuple<tuple<int, int>, tuple<int, int>, tuple<int, int>> findMatchingKey(Protein protein1, Protein protein2,
                                                                         Protein protein3, Protein newProteinOrder[3]);

extern void compareKeys(list<Acid>::iterator iterator, list<Acid> * acids,
                 double length1a, double length1b, double angle1,
                 int & ida, int & idb);

extern double getAngle(list<Acid>::iterator & acid, Acid* a1, Acid* a2);

extern Locations* findLocations(Protein protein1, Protein protein2, Protein protein3);

