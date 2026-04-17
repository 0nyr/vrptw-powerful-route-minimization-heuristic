#ifndef EAMA_ROUTES_MINIMIZATION_HEURISTIC_EAMA_SOLVER_H
#define EAMA_ROUTES_MINIMIZATION_HEURISTIC_EAMA_SOLVER_H

#include <stdbool.h>
#include <time.h>

#include "customer.h"
#include "problem.h"
#include "solution.h"
#include "modification.h"

/**
 * Based on article "A powerful route minimization heuristic for the vehicle
 * routing problem with time windows" Yuichi Nagata, Olli Bräysy
 */

struct eama_solver {
    double alpha;
    double beta;
    clock_t deadline;
    /* TODO: make `p` a member of class `customer` */
    int64_t p[MAX_N_CUSTOMERS];
};

extern struct eama_solver eama_solver;

static inline bool
eama_solver_deadline_reached(void)
{
	if (eama_solver.deadline == 0)
		return false;
	return clock() >= eama_solver.deadline;
}

/** determine the minimum possible number of routes */
struct solution *
eama_solver_solve(void);

#endif //EAMA_ROUTES_MINIMIZATION_HEURISTIC_EAMA_SOLVER_H
