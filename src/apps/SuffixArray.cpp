/*
 * SuffixArray.cpp
 * 
 * Copyright 2015 Robert Bakaric <rbakaric@irb.hr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <streambuf>
#include <boost/program_options.hpp>

#include <SuffixArray.hpp>


namespace po = boost::program_options;
using namespace std;



void PrintAcknowledgements(){

cout <<"***************************************************************************************"<<"\n";
cout <<"                      SuffixArray - Suffix array computation tool                      "<<"\n";
cout <<"                                          by                                           "<<"\n";
cout <<"                                    Robert Bakaric                                     "<<"\n\n";
cout <<"CONTACT:                                                                               "<<"\n";
cout <<" Code written and maintained by Robert Bakaric,                                        "<<"\n";
cout <<" email: rbakaric@irb.hr , bakaric@evolbio.mpg.de                                       "<<"\n\n";
cout <<"ACKNOWLEDGEMENT:                                                                       "<<"\n";
cout <<"         1. Yuta Mori, 2010. https://sites.google.com/site/yuta256/sais                "<<"\n\n";
cout <<"         2. Ge Nong, Sen Zhang and Wai Hong Chan, Two Efficient Algorithms for         "<<"\n";
cout <<"            Linear Suffix Array Construction, 2008.                                    "<<"\n\n";
cout <<"LICENSE:                                                                               "<<"\n";
cout <<" The program is distributed under the GNU General Public License. You should have      "<<"\n";
cout <<" received a copy of the licence together  with this software. If not, see              "<<"\n";
cout <<" http://www.gnu.org/licenses/                                                          "<<"\n";
cout <<"***************************************************************************************"<<"\n\n\n";
}


template <typename INT, typename CHARA>
po::variables_map SetOptions(INT& argc, CHARA& argv){

    try {
        int opt;
        string version = "1.0";
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("version,v", "print version information")
            ("input-file,i", po::value< string >(), "input file")
        ;

        po::positional_options_description p;
        p.add("input-file,i", -1);
        
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).
                  options(desc).positional(p).run(), vm);
        po::notify(vm);
    
        if (vm.count("help")) {
            cout << "Usage: ./program [options]\n\n";
            PrintAcknowledgements();
            cout << desc;
            exit(0);
        }else if (vm.count("version")) {
            cout << "Program version:  " << version << "\n";
            exit(0);
        }
        if (!vm.count("input-file")){
            cout << "Input file is not defined \n";
            exit(0);
        }
        return vm;    
    }
    catch(std::exception& e)
    {
        cout << e.what() << "\n";
        exit(0);
    }    
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " ")); 
    return os;
}


void ReadFile(string & file, string & text){
   ifstream ifs (file.c_str());
   if ( !ifs.is_open()){
     cerr << "Cannot open file: "<<file <<"! Line:" << __LINE__<< endl;
     exit(-1);
   }

   ifs.seekg(0, std::ios::end);   
   text.reserve(ifs.tellg());
   ifs.seekg(0, std::ios::beg);

   text.assign((std::istreambuf_iterator<char>(ifs)),
            std::istreambuf_iterator<char>());
   ifs.close();
}



int main (int argc, char** argv){
  
/* Get cmd Options */  
   po::variables_map arg;
   arg = SetOptions(argc,argv);

   string file =  arg["input-file"].as<string>();
   string text;  
  

/* Read Text */  
   ReadFile(file, text);
   
/* Construct Sufix array */
   try{
      SuffixArray<int> SA(text);
      cout << SA.GetSuffixArray() << endl;
   }catch(runtime_error& e){
      cerr << e.what() << "\n";
   }
  return 0;
}
