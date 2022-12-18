#pragma once

#include "problem.hpp"

#include <memory>

namespace aoc2022
{
	constexpr long long A_MAX_SIZE = 100000;

	constexpr long long B_DISK_SIZE = 70000000;
	constexpr long long B_UPDATE_SIZE = 30000000;

	struct file
	{
		file(const std::string& name, int size) : name{ name }, size{ size } {}

		std::string name;
		long long size;
	};

	struct directory
	{
		directory(const std::string& name, directory* parent) : name{ name }, parent{ parent } {}

		std::string name;

		directory* parent;

		std::vector<std::shared_ptr<directory>> subdirectories{};

		std::vector<std::shared_ptr<file>> files{};
	};

	class problem_07 : public problem
	{
	public:
		problem_07() : problem(7) {}

		A_IMPL()
		{
			process_commands(lines);

			long long result{ 0 };
			a_max_size_recursive(root, result);

			print_result(result);
		}

		B_IMPL()
		{
			process_commands(lines);

			long long available_space = B_DISK_SIZE - dir_size(root);
			long long space_required = B_UPDATE_SIZE - available_space;

			long long min = std::numeric_limits<long long>().max();
			b_min_size_recursive(root, space_required, min);

			print_result(min);
		}

	private:

		directory root{ "/", nullptr };

		directory* current_dir = nullptr;

		void a_max_size_recursive(const directory& directory, long long& total)
		{
			long long size = dir_size(directory);
			if (size <= A_MAX_SIZE)
			{
				total += size;
			}

			for (auto& subdir : directory.subdirectories)
			{
				a_max_size_recursive(*subdir, total);
			}
		}

		void b_min_size_recursive(const directory& directory, long long space_required, long long& min)
		{
			long long size = dir_size(directory);

			if (size > space_required && size < min)
			{
				min = size;
			}

			for (auto& subdir : directory.subdirectories)
			{
				b_min_size_recursive(*subdir, space_required, min);
			}
		}

		long long dir_size(const directory& directory)
		{
			long long size{ 0 };

			for (auto& subdir : directory.subdirectories)
			{
				size += dir_size(*subdir);
			}

			for (auto& file : directory.files)
			{
				size += file->size;
			}

			return size;
		}

		void process_commands(
			std::vector<std::string>& lines)
		{
			size_t i = 0;
			while (i < lines.size())
			{
				process_command(lines, i);
			}
		}

		void process_command(
			const std::vector<std::string>& lines,
			size_t& line_index)
		{
			auto& line = lines[line_index];

			auto tokens = split(line, ' ');
			auto& cmd = tokens[1];

			if (cmd == "cd")
			{
				auto& arg = tokens[2];

				if (arg == "/")
				{
					current_dir = &root;
				}
				else if (arg == "..")
				{
					current_dir = current_dir->parent;
				}
				else
				{
					for (auto& child : current_dir->subdirectories)
					{
						if (child->name == arg)
						{
							current_dir = child.get();
							break;
						}
					}
				}
				line_index++;
			}
			else if (cmd == "ls")
			{
				line_index++;

				while (line_index < lines.size())
				{
					auto& next_line = lines[line_index];

					if (next_line[0] == '$')
					{
						break;
					}
					else
					{
						auto ls_tokens = split(next_line, ' ');

						std::string& name = ls_tokens[1];

						if (ls_tokens[0] == "dir")
						{
							auto subdir = std::make_shared<directory>(name, nullptr);
							subdir->parent = current_dir;
							current_dir->subdirectories.push_back(subdir);
						}
						else
						{
							int file_size = atoi(ls_tokens[0].c_str());
							current_dir->files.push_back(std::make_shared<file>(name, file_size));
						}

						line_index++;
					}
				}
			}
		}
	};
}

