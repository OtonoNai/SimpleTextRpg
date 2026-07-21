#pragma once

#include <string>
#include <map>
#include "JobTypes.h"

std::map<std::string, FJobData> LoadJobs(const std::string& FilePath);