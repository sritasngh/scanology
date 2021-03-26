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

#ifndef SCANCODE_AGENT_SCANCODE_WRAPPER_HPP
#define SCANCODE_AGENT_SCANCODE_WRAPPER_HPP

#define AGENT_NAME "scancode"
#define AGENT_DESC "scancode agent"
#define AGENT_ARS  "scancode_ars"

#include <string>
#include <vector>
#include "files.hpp"
#include "licensematch.hpp"
#include "state.hpp"

using namespace std;

string scanFileWithScancode(const State& state, const fo::File& file);
vector<string> extractLicensesFromScancodeResult(string scancodeResult);
string extractLicensePartFromScancodeResult(string scancodeResult);
vector<string> splitLicensePart(string licensePart);
vector<LicenseMatch> createMatches(vector<string> scancodeLicenseNames);
string mapLicenseFromScancodeToFossology(string name);
bool isLicenseCollection(string scancodeLicenseName,vector<LicenseMatch>& matches);

#endif // SCANCODE_AGENT_SCANCODE_WRAPPER_HPP
