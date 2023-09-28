#pragma once
#include<string>
#include<vector>

struct Task
{
	std::string description;
	bool done;
};

void SaveTasksToFile(const std::vector<Task>& tasks, const std::string& filename);
std::vector<Task> LoadTaskFromFile(const std::string& filename);

