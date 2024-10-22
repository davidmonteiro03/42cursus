/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:17:08 by dcaetano          #+#    #+#             */
/*   Updated: 2024/10/22 13:30:41 by dcaetano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* ************************************************************************** */
/*                                   PRIVATE                                  */
/* ************************************************************************** */

void BitcoinExchange::_readCSV(std::string csv_file)
{
	std::ifstream ifs(csv_file.c_str());
	if (ifs.fail())
		throw CouldNotOpenFile();
	int fields_readed = 0;
	while (ifs.eof() == 0)
	{
		std::string line = "";
		std::getline(ifs, line);
		if (line.empty())
			continue;
		std::stringstream ss_line(line);
		std::string s_date, s_exchange;
		if (fields_readed == 0)
		{
			if (std::getline(ss_line, s_date, ',') && std::getline(ss_line, s_exchange, ','))
				fields_readed = 1;
			continue;
		}
		if (std::getline(ss_line, s_date, ',') && std::getline(ss_line, s_exchange, ','))
			_database[s_date] = std::strtod(s_exchange.c_str(), NULL);
	}
	ifs.close();
}

void BitcoinExchange::_readInput(std::string input_file)
{
	std::ifstream ifs(input_file.c_str());
	if (ifs.fail())
		throw CouldNotOpenFile();
	int fields_readed = 0;
	while (ifs.eof() == 0)
	{
		std::string line;
		std::getline(ifs, line);
		if (line.empty())
			continue;
		std::stringstream ss_line(line);
		std::string s_date, s_value;
		if (fields_readed == 0)
		{
			if (std::getline(ss_line, s_date, '|') && std::getline(ss_line, s_value, '|'))
				fields_readed = 1;
			continue;
		}
		if (std::getline(ss_line, s_date, '|') && std::getline(ss_line, s_value, '|'))
		{
			std::stringstream ss_date(s_date);
			std::string s_year, s_mounth, s_day;
			if (std::getline(ss_date, s_year, '-') && std::getline(ss_date, s_mounth, '-') && std::getline(ss_date, s_day, '-'))
			{
				if (ss_date.eof())
				{
					t_date date = _createDate(s_year, s_mounth, s_day);
					if (date.year > 0 && (date.mounth >= 1 && date.mounth <= 12))
					{
						unsigned num_days = _getNumDays(date);
						if (date.day >= 1 && date.day <= num_days)
						{
							double value = std::strtod(s_value.c_str(), NULL);
							if (value < 0)
								std::cerr << "Error: not a positive number." << std::endl;
							else if (value > 1000)
								std::cerr << "Error: too large a number." << std::endl;
							else
							{
								std::string s_date = _sDate(date);
								try
								{
									double exchange = value * _searchExchange(date);
									std::cout << s_date << " => " << value << " = " << exchange << std::endl;
								}
								catch (const std::exception &e)
								{
									std::cerr << e.what() << std::endl;
								}
							}
							continue;
						}
					}
				}
			}
		}
		std::cerr << "Error: bad input => " << line << std::endl;
	}
	if (fields_readed == 0)
		throw InvalidInputFile();
	ifs.close();
}

t_date BitcoinExchange::_createDate(std::string s_year, std::string s_mounth, std::string s_day)
{
	t_date date;
	date.year = std::atoi(s_year.c_str());
	date.mounth = std::atoi(s_mounth.c_str());
	date.day = std::atoi(s_day.c_str());
	return date;
}

unsigned int BitcoinExchange::_getNumDays(t_date date)
{
	if (date.year <= 0 || date.mounth < 1 || date.mounth > 12)
		return 0;
	unsigned feb_days = date.year % 400 == 0 || (date.year % 4 == 0 && date.year % 100 != 0) ? 29 : 28;
	if (date.mounth == 2)
		return feb_days;
	if ((date.mounth < 8 && date.mounth % 2 == 1) ||
		(date.mounth >= 8 && date.mounth % 2 == 0))
		return 31;
	return 30;
}

std::string BitcoinExchange::_sDate(t_date date)
{
	char buf_date[BUFSIZ];
	std::memset(buf_date, 0, sizeof(buf_date));
	std::sprintf(buf_date, "%u-%02u-%02u", date.year, date.mounth, date.day);
	return std::string(buf_date);
}

double BitcoinExchange::_searchExchange(t_date date)
{
	std::string s_date = _sDate(date);
	if (_database.find(s_date) != _database.end())
		return _database[s_date];
	while (date.year > 0)
	{
		while (date.mounth > 0)
		{
			while (date.day > 0)
			{
				std::string s_date = _sDate(date);
				if (_database.find(s_date) != _database.end())
					return _database[s_date];
				date.day--;
			}
			date.day = _getNumDays(date);
			date.mounth--;
		}
		date.year--;
		date.mounth = 12;
	}
	throw DateIsTooOld();
	return -1;
}

const char *BitcoinExchange::CouldNotOpenFile::what() const throw() { return COULD_NOT_OPEN_FILE; }

const char *BitcoinExchange::InvalidDatabaseCSV::what() const throw() { return INVALID_DATABASE_CSV; }

const char *BitcoinExchange::InvalidInputFile::what() const throw() { return INVALID_INPUT_FILE; }

const char *BitcoinExchange::DateIsTooOld::what() const throw() { return DATE_IS_TOO_OLD; }

/* ************************************************************************** */
/*                                   PUBLIC                                   */
/* ************************************************************************** */

BitcoinExchange::BitcoinExchange(void) { _readCSV("data.csv"); }

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::_execute(std::string input_file) { _readInput(input_file); }
