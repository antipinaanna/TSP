#include "conditions.h"
#include "DNA.h"
#include "solver.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{

	std::string folderPath = "./data";
    std::ofstream file_out("output_dataframe");
	if (file_out.is_open())
	{
		for (const auto &entry : fs::directory_iterator(folderPath)) 
		{
			if (entry.is_regular_file())
			{
				std::cout << "hello" << std::endl;
				std::string filePath = entry.path().string();
				std::ifstream file(filePath);
				if (file.is_open())
				{
					std::cout << "hello2" << std::endl;
                    float crossover = 0.3, mutation = 0;
                    unsigned n, population;
                    population = unsigned(crossover * n);
					file >> n;
					std::cout << n << std::endl;
					std::vector<std::vector<float>> distance(n, std::vector<float>(2, 0)); 
					for (int i = 0; i < n; i++)
					{
						file >> distance[i][0] >> distance[i][1];
					//	std::cout << distance[i][0] << " " << distance[i][1] << std::endl;
					}

					std::cout << "hello3" << std::endl;
					Solver solver(crossover, mutation, population, n, distance); 
					std::cout << "hello4" << std::endl;
					solver.solve();
		//			solver.print_ans();
					file_out << filePath << ", "<< std::endl;
					file.close();
				}
				else
					std::cout << "Не удалось открыть файл" << std::endl;
			}
		}
		file_out.close();
	}
}
