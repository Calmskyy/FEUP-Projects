#pragma once

#include "types.h"

void checkNumberBounds(int number, int lowerBound, int higherBound, char *name);

void checkNumericalString(char string[], char *name);

void separateArgs();

void getAccountCreationArgs();

void getTransferArgs();

void readArgs(char *args[]);

char *createUserFIFO();

req_header_t createHeader();

req_value_t createTransferValue(req_header_t header);

req_value_t createBlankValue(req_header_t header);

req_value_t createAccountCreationValue(req_header_t header);

tlv_request_t createBalanceRequest(req_value_t value);

tlv_request_t createAccountCreationRequest(req_value_t value);

tlv_request_t createTransferRequest(req_value_t value);

tlv_request_t createShutdownRequest(req_value_t value);

void printError(ret_code_t code);
