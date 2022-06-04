#include "TravelingSalesperson.h"

void RUN_TSP()
{
	matrix graph1 =
	{ 
		{ 0, 10, 15, 20 },
		{ 10, 0, 35, 25 },
		{ 15, 35, 0, 30 },
		{ 20, 25, 30, 0 } 
	};
	TravelingSalesperson test1(graph1);
	int start_index = 0;
	test1.solve_tsp(start_index);
	test1.print_solution(start_index);
	cout << "\n______________________________________________________________\n";
	matrix graph2 =
	{
		{ 0, 2, 8, 5 },
		{ 2, 0, 3, 4 },
		{ 8, 3, 0, 7 },
		{ 5, 4, 7, 0 }
	};
	TravelingSalesperson test2(graph2);
	start_index = 0;
	test2.solve_tsp(start_index);
	test2.print_solution(start_index);
	cout << "\n______________________________________________________________\n";
}

int main()
{
	RUN_TSP();
}