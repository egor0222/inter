#ifndef BUILD_CPP
#define BUILD_CPP

#include <filesystem>
#include "../include/build.h"

//#include <experimental/filesystem>
//using namespace std::experimental::filesystem::v1;

//using namespace std::filesystem;
namespace fs = std::filesystem;


static fs::path main_path;
static fs::path stdpath;

static const std::string rs = ".txt";

static const std::string imp("import");
static const std::string def("def");
static const std::string var("var");

std::unordered_set<std::string> imported;

static fs::path find_file(std::string name){
	fs::path p1(main_path);
	p1.append(name + rs);
	if (exists(p1))
		return p1;

	p1.clear();
	p1 = fs::path(stdpath);
	if (exists(p1))
		return p1;

	#ifdef DEBUG
	std::cout << "File not found in this directory!\n";
	#endif
	std::terminate();
	// must to be fixed
}

void main_build(std::string mp, data *dt){
	imported.clear();
	main_path = fs::path(mp).parent_path();

	fs::path set(main_path);
	set.append("settings.txt");

	//#ifdef DEBUD
	std::cout << "Build started "<< set << '\n';
	//#endif

	std::ifstream fstr;
	fstr.open(fs::path(mp).parent_path());
	if (!fstr.is_open()) {
		dt = nullptr;
		fstr.close();
		return;
	}

	std::string str;
	std::getline(fstr, str);
	stdpath = fs::path(str);

	fstr.close();

	std::ifstream main_file(mp);

	//#ifdef DEBUG
	std::cout << "Open status: " << (bool)(main_file.is_open());
	//#endif

	if (!main_file.is_open()){

		#ifdef DEBUG
		std::cout << "File not opened\n";
		#endif

		dt = nullptr;
		return;
	}
	#ifdef DEBUG
	else {
		std::cout << "File " << mp << " opened\n";
	}
	#endif
	exit_status st = build(dt, main_file);

	if (!(st.error_code))
		dt = nullptr;
	main_file.close();
	return;
}

exit_status build(data *cur_data, std::ifstream &fstr)
{
	std::string cur;
	while (std::getline(fstr, cur))
	{
		line *cur_ln = new line(cur);
		if (cur_ln->empty())
			continue;

		#ifdef DEBUG
		std::cout << cur << '\n';
		#endif
			
		if (cur_ln->words[0] == imp)
		{
			if (cur_ln->priority != 0)
				return exit_status(SYNTAX_ERROR);
			if (cur_ln->words.size() < 2)
				return exit_status(BUILD_IMPORTATION_ERROR);

			fs::path pt = find_file(cur_ln->words[1]);

			if (imported.find(cur_ln->words[1]) != imported.end())
				continue;
			else
				imported.insert(cur_ln->words[1]);

			std::ifstream file(pt);
			if (!file.is_open())
				return exit_status(BUILD_IMPORTATION_ERROR);

			build(cur_data, file);

			file.close();
			continue;
		}
		else if (cur_ln->words[0] == def)
		{
			if (cur_ln->priority != 0)
				return exit_status(SYNTAX_ERROR);
			if (cur_ln->words.size() < 2)
				return exit_status(BUILD_IMPORTATION_ERROR);

			cur_data->places.push_back(
				func(cur_ln->words[1], cur_data->cur_line()));
		}
		else if (cur_ln->words[0] == var)
		{
			if (cur_ln->priority != 0)
				continue;
			if (cur_ln->words.size() < 2)
				return exit_status(SYNTAX_ERROR);
			cur_data->variables.push_back(
				glvar(cur_ln->words[0], cur_data->cur_line()));
		}
		cur_data->lines.push_back(cur_ln);
	}
	return exit_status(OK);
}

#endif
