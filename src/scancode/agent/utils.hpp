/*
 * Copyright (C) 2014-2015, Siemens AG
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SCANCODE_AGENT_UTILS_HPP
#define SCANCODE_AGENT_UTILS_HPP

#define AGENT_NAME "scancode"
#define AGENT_DESC "scancode agent"
#define AGENT_ARS  "scancode_ars"

#include <string>
#include <vector>
#include "files.hpp"
#include "licensematch.hpp"
#include "state.hpp"

extern "C" {
#include "libfossology.h"
}

using namespace std;

State getState(fo::DbManager& dbManager);
int queryAgentId(fo::DbManager& dbManager);
int writeARS(const State& state, int arsId, int uploadId, int success, fo::DbManager& dbManager);
void bail(int exitval);
bool processUploadId(const State& state, int uploadId, ScancodeDatabaseHandler& databaseHandler);
bool matchPFileWithLicenses(const State& state, unsigned long pFileId, ScancodeDatabaseHandler& databaseHandler);
bool matchFileWithLicenses(const State& state, const fo::File& file, ScancodeDatabaseHandler& databaseHandler);
bool saveLicenseMatchesToDatabase(const State& state, const vector<LicenseMatch>& matches, unsigned long pFileId, ScancodeDatabaseHandler& databaseHandler);

#endif // SCANCODE_AGENT_UTILS_HPP
