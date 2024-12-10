#pragma once

#include <iostream>
#include <string>
#include <vector>

class Requests {
	public:
		static void login(const std::string& username, const std::string& password);
		static void createAccount(const std::string& username, const std::string& password);
};
