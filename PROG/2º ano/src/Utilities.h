#pragma once

#include <string>
#include <iostream>

const std::string AGENCY_FILE_NAME = "agency.txt";

static const size_t npos = -1;

const int MAX_CLIENTS = 80;

const int MAX_PACKETS = 20;

// macros used to change certain function's functionalities
#define NO_PRINT 0
#define PRINT 1

unsigned int readInputNumber();

double readDoubleInputNumber(double lowNumber, double highNumber);

int readInputNumber(int lowNumber, int highNumber);

