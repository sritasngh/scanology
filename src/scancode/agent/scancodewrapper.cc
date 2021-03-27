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

#include <iostream>
#include <boost/tokenizer.hpp>
#include "scancodewrapper.hpp"
#include "utils.hpp"


string scanFileWithScancode( const State &state, const fo::File &file){
  string hello("{\"file: \"\"nothing\"}");
  return hello;
}
string scanFileWithScancode( //const State &state, const fo::File &file
    string filename)
{
  FILE *in;
  char buffer[512];
  // ./scancode -clpieu --json-pp <output> <input>
  string command = "scancode -l --json-pp - " + filename;
  string result = "";

  if (!(in = popen(command.c_str(), "r")))
  {
    cout << "could not execute scancode command: " << command << endl;
    bail(1);
  }

  while (fgets(buffer, sizeof(buffer), in) != NULL)
  {
    result += buffer;
  }

  if (pclose(in) != 0)
  {
    cout << "could not execute scancode command: " << command << endl;
    bail(1);
  }

  int startjson = result.find("{");
  return result.substr(startjson, string::npos);
}

vector<LicenseMatch> extractLicensesFromScancodeResult(string scancodeResult)
{
  Json::Reader scanner;
  Json::Value scancodevalue;

  bool isSuccessful = scanner.parse(scancodeResult, scancodevalue);
  vector<LicenseMatch> result;
  if (isSuccessful)
  {
    Json::Value resultarray = scancodevalue["files"]["licenses"];

    for (unsigned int i = 0; i < resultarray.size(); ++i)
    {
      Json::Value oneresult = resultarray[i];
      try
      {
        string licensename = scancode_to_fossology_map.at(oneresult["short_name"].asString());
        result.push_back(LicenseMatch(licensename, oneresult["score"].asDouble()));
      }
      catch (out_of_range const &e)
      {
        cerr << "No mapping found for given license" << endl;
        cerr << e.what() << endl;
      }
    }
  }
  else
  {
    cerr << "JSON parsing failed " << scanner.getFormattedErrorMessages() << endl;
    bail(-30);
  }
  return result;
}

/*string mapLicenseFromScancodeToFossology(string name)
{
  if (name.compare("NONE") == 0)
    return string("No_license_found");
  if (name.compare("UNKNOWN") == 0)
    return string("UnclassifiedLicense");
  if (name.compare("spdxMIT") == 0)
    return string("MIT");
  if (name.compare("Apachev1.0") == 0)
    return string("Apache-1.0");
  if (name.compare("Apachev2") == 0 || name.compare("Apache-2") == 0)
    return string("Apache-2.0");
  if (name.compare("GPLv1+") == 0)
    return string("GPL-1.0+");
  if (name.compare("GPLv2") == 0)
    return string("GPL-2.0");
  if (name.compare("GPLv2+") == 0)
    return string("GPL-2.0+");
  if (name.compare("GPLv3") == 0)
    return string("GPL-3.0");
  if (name.compare("GPLv3+") == 0)
    return string("GPL-3.0+");
  if (name.compare("LGPLv2") == 0)
    return string("LGPL-2.0");
  if (name.compare("LGPLv2+") == 0)
    return string("LGPL-2.0+");
  if (name.compare("LGPLv2_1") == 0 || name.compare("LGPLv2.1") == 0)
    return string("LGPL-2.1");
  if (name.compare("LGPLv2_1+") == 0)
    return string("LGPL-2.1+");
  if (name.compare("LGPLv3") == 0)
    return string("LGPL-3.0");
  if (name.compare("LGPLv3+") == 0)
    return string("LGPL-3.0+");
  if (name.compare("GPLnoVersion") == 0)
    return string("GPL");
  if (name.compare("LesserGPLnoVersion") == 0 || name.compare("LibraryGPLnoVersion") == 0)
    return string("LGPL");
  if (name.compare("intelBSDLicense") == 0)
    return string("Intel-EULA");
  if (name.compare("spdxSleepyCat") == 0 || name.compare("SleepyCat") == 0)
    return string("Sleepycat");
  if (name.compare("spdxBSD2") == 0 || name.compare("BSD2") == 0)
    return string("BSD-2-Clause");
  if (name.compare("spdxBSD3") == 0 || name.compare("BSD3") == 0)
    return string("BSD-3-Clause");
  if (name.compare("BSD3") == 0)
    return string("BSD-4-Clause");
  if (name.compare("spdxMIT") == 0)
    return string("MIT");
  if (name.compare("ZLIB") == 0)
    return string("Zlib");
  if (name.compare("openSSL") == 0 || name.compare("openSSLvar1") == 0 || name.compare("openSSLvar3") == 0)
    return string("OpenSSL");
  if (name.compare("QPLt") == 0)
    return string("QT(Commercial)");
  if (name.compare("Cecill") == 0)
    return string("CECILL");
  if (name.compare("QPLv1") == 0)
    return string("QPL-1.0");
  if (name.compare("MPLv1_1") == 0)
    return string("MPL-1.1");
  if (name.compare("NPLv1_1") == 0)
    return string("NPL-1.1");
  if (name.compare("MPLv1_0") == 0)
    return string("MPL-1.0");
  if (name.compare("NPLv1_0") == 0)
    return string("NPL-1.0");
  if (name.compare("MPLv2") == 0)
    return string("MPL-2.0");
  if (name.compare("MITVariant") == 0)
    return string("MIT-style");
  if (name.compare("EPLv1") == 0)
    return string("EPL-1.0");
  if (name.compare("CDDLic") == 0)
    return string("CDDL");
  if (name.compare("CDDLicV1") == 0)
    return string("CDDL-1.0");
  if (name.compare("publicDomain") == 0)
    return string("Public-domain");
  if (name.compare("ClassPathExceptionGPLv2") == 0)
    return string("GPL-2.0-with-classpath-exception");
  if (name.compare("CPLv1") == 0)
    return string("CPL-1.0");
  if (name.compare("CPLv0.5") == 0)
    return string("CPL-0.5");
  if (name.compare("SeeFile") == 0)
    return string("See-file");
  if (name.compare("LibGCJLic") == 0)
    return string("LIBGCJ");
  if (name.compare("W3CLic") == 0)
    return string("W3C");
  if (name.compare("IBMv1") == 0)
    return string("IPL-1.0");
  if (name.compare("ArtisticLicensev1") == 0)
    return string("Artistic-1.0");
  if (name.compare("MX4JLicensev1") == 0)
    return string("MX4J-1.0");
  if (name.compare("phpLicV3.01") == 0)
    return string("PHP-3.01");
  if (name.compare("postgresql") == 0 || name.compare("postgresqlRef") == 0)
    return string("PostgreSQL");
  if (name.compare("FSFUnlimited") == 0)
    return string("FSF");

  return name;
};
*/

/*

  {
  "headers": [
    {
      "tool_name": "scancode-toolkit",
      "tool_version": "3.2.3",
      "options": {
        "input": [
          "new_lic.txt"
        ],
        "--json-pp": "out.json",
        "--license": true
      },
      "notice": "Generated with ScanCode and provided on an \"AS IS\" BASIS, WITHOUT WARRANTIES\nOR CONDITIONS OF ANY KIND, either express or implied. No content created from\nScanCode should be considered or used as legal advice. Consult an Attorney\nfor any legal advice.\nScanCode is a free software code scanning tool from nexB Inc. and others.\nVisit https://github.com/nexB/scancode-toolkit/ for support and download.",
      "start_timestamp": "2021-03-27T074148.031602",
      "end_timestamp": "2021-03-27T074226.232231",
      "duration": 38.200644731521606,
      "message": null,
      "errors": [],
      "extra_data": {
        "files_count": 1
      }
    }
  ],
  "files": [
    {
      "path": "new_lic.txt",
      "type": "file",
      "licenses": [
        {
          "key": "4suite-1.1",
          "score": 100.0,
          "name": "4Suite License v1.1",
          "short_name": "4Suite 1.1",
          "category": "Permissive",
          "is_exception": false,
          "owner": "Fourthought, Inc.",
          "homepage_url": null,
          "text_url": "",
          "reference_url": "https://scancode-licensedb.aboutcode.org/4suite-1.1",
          "scancode_text_url": "https://github.com/nexB/scancode-toolkit/tree/develop/src/licensedcode/data/licenses/4suite-1.1.LICENSE",
          "scancode_data_url": "https://github.com/nexB/scancode-toolkit/tree/develop/src/licensedcode/data/licenses/4suite-1.1.yml",
          "spdx_license_key": "LicenseRef-scancode-4suite-1.1",
          "spdx_url": "https://github.com/nexB/scancode-toolkit/tree/develop/src/licensedcode/data/licenses/4suite-1.1.LICENSE",
          "start_line": 1,
          "end_line": 64,
          "matched_rule": {
            "identifier": "4suite-1.1.LICENSE",
            "license_expression": "4suite-1.1",
            "licenses": [
              "4suite-1.1"
            ],
            "is_license_text": true,
            "is_license_notice": false,
            "is_license_reference": false,
            "is_license_tag": false,
            "is_license_intro": false,
            "matcher": "1-hash",
            "rule_length": 389,
            "matched_length": 389,
            "match_coverage": 100.0,
            "rule_relevance": 100
          }
        }
      ],
      "license_expressions": [
        "4suite-1.1"
      ],
      "percentage_of_license_text": 100.0,
      "scan_errors": []
    }
  ]
}
 
*/