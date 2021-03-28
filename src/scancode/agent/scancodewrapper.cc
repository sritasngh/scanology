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
  //cout<<"I am here"<<"\n";
  bool isSuccessful = scanner.parse(scancodeResult, scancodevalue);
  vector<LicenseMatch> result;
  if (isSuccessful)
  {
    //cout<<"I am here"<<"\n";
    Json::Value resultarrays = scancodevalue["files"];
    //cout<<resultarrays.size()<<endl;
    Json::Value temp = resultarrays[0];
    //cout<<temp.size()<<endl;
    Json::Value resultarray = temp["licenses"];
    //cout<<resultarray.size()<<endl;


    for (unsigned int i = 0; i < resultarray.size(); ++i)
    {
      Json::Value oneresult = resultarray[i];
      //cout<<oneresult.size()<<endl;
      try
      {
        // cout<<oneresult["short_name"].asString();
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