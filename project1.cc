// Copyright 2022 Wook-shin Han
#include "./project1.h"
#include <cstring>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

void query1(int argc, char **argv) {
  FILE *cus = NULL;
  cus = fopen(argv[2], "r");
  FILE *zone = NULL;
  zone = fopen(argv[3], "r");
  int TorontoID = 0;

  if (zone != NULL) {
    char buffer[1000];
    for (int i = 0; i < 2; i++)
      if (fgets(buffer, sizeof(buffer), zone) == NULL) break;
    while (!feof(zone)) {
      if (fgets(buffer, sizeof(buffer), zone) == NULL) break;
      int zoneid;
      string zonedesc;
      string temp(buffer);
      zoneid = stoi(temp.substr(0, 6));
      zonedesc = temp.substr(7, 20);
      if (zonedesc == "Toronto             ") {
        TorontoID = zoneid;
        break;
      }
    }
  }

  if (cus != NULL) {
    char buffer[1000];
    for (int i = 0; i < 2; i++)
      if (fgets(buffer, sizeof(buffer), cus) == NULL) break;

    while (!feof(cus)) {
      if (fgets(buffer, sizeof(buffer), cus) == NULL) break;
      int zone;
      int active;
      string lname;
      string temp(buffer);
      lname = temp.substr(42, 20);
      zone = stoi(temp.substr(135, 6));
      active = stoi(temp.substr(243, 1));
      if (zone == TorontoID && active == 1) {
        cout << lname << endl;
      }
    }
  }
}

void query2(int argc, char **argv) {
  FILE *item = NULL;
  item = fopen(argv[2], "r");
  FILE *prod = NULL;
  prod = fopen(argv[3], "r");
  int check[100] = {0};
  string user[100];
  if (item != NULL) {
    char buffer[1000];
    for (int i = 0; i < 2; i++)
      if (fgets(buffer, sizeof(buffer), item) == NULL) break;

    while (!feof(item)) {
      if (fgets(buffer, sizeof(buffer), item) == NULL) break;
      string temp(buffer);
      string uname;
      int barcode;
      uname = temp.substr(0, 20);
      barcode = stoi(temp.substr(41, 20));
      if (user[barcode - 1000] == "") {
        user[barcode - 1000] = uname;
      } else if (user[barcode - 1000] != uname) {
        check[barcode - 1000] = 1;
      }
    }
  }
  if (prod != NULL) {
    char buffer[1000];
    for (int i = 0; i < 2; i++)
      if (fgets(buffer, sizeof(buffer), prod) == NULL) break;

    while (!feof(prod)) {
      if (fgets(buffer, sizeof(buffer), prod) == NULL) break;
      string temp(buffer);
      int barcode;
      string barcodestr;
      barcodestr = temp.substr(0, 20);
      barcode = stoi(barcodestr);
      if (check[barcode - 1000] == 1) {
        string desc;
        desc = temp.substr(32, 50);
        cout << barcodestr << " " << desc << endl;
      }
    }
  }
}

int main(int argc, char **argv) {
  /* fill this */
  if (strcmp(argv[1], "q1") == 0) {
    query1(argc, argv);
  } else {
    query2(argc, argv);
  }
  return 0;
}
