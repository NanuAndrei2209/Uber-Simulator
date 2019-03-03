// Copyright 2019 SD_Homework_Team

#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>  // NOLINT(build/c++11)
#include "./solver.h"

// DO NOT MODIFY THIS FILE

float call_solver(std::ifstream& fin, int task, solver* s) {
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;
	std::chrono::duration<double> elapsed;

	std::string task_name_out = "task_" + std::to_string(task) + ".out";

	std::ofstream fout(task_name_out);

	switch (task) {
		case 1:
			start = std::chrono::high_resolution_clock::now();
			s->task1_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
		case 2:
			start = std::chrono::high_resolution_clock::now();
			s->task2_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
		case 3:
			start = std::chrono::high_resolution_clock::now();
			s->task3_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
		case 4:
			start = std::chrono::high_resolution_clock::now();
			s->task4_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
		case 5:
			start = std::chrono::high_resolution_clock::now();
			s->task5_solver(fin, fout);
			end = std::chrono::high_resolution_clock::now();
			break;
	}

	fout.close();

	elapsed = end - start;
	return (float)elapsed.count();
}

int main() {
	solver* s = new solver();
	std::ifstream fin("test.in");
	std::ofstream fout("time.out");

	float time_task_1;
	float time_task_2;
	float time_task_3;
	float time_task_4;
	float time_task_5;


	time_task_1 = call_solver(fin, 1, s);
	time_task_2 = call_solver(fin, 2, s);
	time_task_3 = call_solver(fin, 3, s);
	time_task_4 = call_solver(fin, 4, s);
	time_task_5 = call_solver(fin, 5, s);

	fout << time_task_1 << "\n";
	fout << time_task_2 << "\n";
	fout << time_task_3 << "\n";
	fout << time_task_4 << "\n";
	fout << time_task_5 << "\n";

	fout.close();
	fin.close();

	delete s;
	return 0;
}
