//
//  main.cpp
//  IM
//
//  Created by Oli Lo on 2018/1/5.
//  Copyright © 2018年 Oli Lo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <string>
using namespace std;

struct Car {
    int turn;
    int cost = 0;
    int inrd;
    int pri;
};

typedef deque<Car> Carorder;
void cmpcf(Carorder a[4], int b[4]);
void greedy(Carorder schedule[],Carorder schedule_greedy[]);
int cmpcf2(Carorder a[4], int b[4], int minincominground);

int main(int argc, const char * argv[]) {

    //input file & ouput file
    ifstream InputFile;
    InputFile.open(argv[1], ifstream::in);
    ofstream upf;
    upf.open(argv[2], ofstream::out);
    
    string N, E, W, S;
    Carorder Schedule[4];
    
    getline(InputFile, N);
    getline(InputFile, E);
    getline(InputFile, S);
    getline(InputFile, W);
    
    for (unsigned i=1; i<N.length(); i=i+3)
    {
        switch (N.at(i)) {
                
            case '0':{
                Car a;
                a.turn = 0;
                a.inrd = (i-1)/3;
                a.pri = 0;
                Schedule[0].push_back(a);
                break;
            }
                
            case 'E':{
                Car b;
                b.turn = 1;
                b.inrd = (i-1)/3;
                b.pri = 9;
                Schedule[0].push_back(b);
                break;
            }
                
            case 'S':{
                Car c;
                c.turn = 2;
                c.inrd = (i-1)/3;
                c.pri = 4;
                Schedule[0].push_back(c);
                break;
            }
                
            case 'W':{
                Car d;
                d.turn = 3;
                d.inrd = (i-1)/3;
                d.pri = 1;
                Schedule[0].push_back(d);
                break;
            }
                
            default:{
                break;
            }
        }
    }
    
    for (unsigned i=1; i<E.length(); i=i+3)
    {
        switch (E.at(i)) {
                
            case '0':{
                Car a;
                a.turn = 0;
                a.inrd = (i-1)/3;
                a.pri = 0;
                Schedule[1].push_back(a);
                break;
            }
                
            case 'S':{
                Car b;
                b.turn = 1;
                b.inrd = (i-1)/3;
                b.pri = 9;
                Schedule[1].push_back(b);
                break;
            }
                
            case 'W':{
                Car c;
                c.turn = 2;
                c.inrd = (i-1)/3;
                c.pri = 4;
                Schedule[1].push_back(c);
                break;
            }
                
            case 'N':{
                Car d;
                d.turn = 3;
                d.inrd = (i-1)/3;
                d.pri = 1;
                Schedule[1].push_back(d);
                break;
            }
                
            default:{
                break;
            }
        }
    }
    
    for (unsigned i=1; i<S.length(); i=i+3)
    {
        switch (S.at(i)) {
                
            case '0':{
                Car a;
                a.turn = 0;
                a.inrd = (i-1)/3;
                a.pri = 0;
                Schedule[2].push_back(a);
                break;
            }
                
            case 'W':{
                Car b;
                b.turn = 1;
                b.inrd = (i-1)/3;
                b.pri = 9;
                Schedule[2].push_back(b);
                break;
            }
                
            case 'N':{
                Car c;
                c.turn = 2;
                c.inrd = (i-1)/3;
                c.pri = 4;
                Schedule[2].push_back(c);
                break;
            }
                
            case 'E':{
                Car d;
                d.turn = 3;
                d.inrd = (i-1)/3;
                d.pri = 1;
                Schedule[2].push_back(d);
                break;
            }
                
            default:{
                break;
            }
        }
    }
    
    for (unsigned i=1; i<W.length(); i=i+3)
    {
        switch (W.at(i)) {
                
            case '0':{
                Car a;
                a.turn = 0;
                a.inrd = (i-1)/3;
                a.pri = 0;
                Schedule[3].push_back(a);
                break;
            }
                
            case 'N':{
                Car b;
                b.turn = 1;
                b.inrd = (i-1)/3;
                b.pri = 9;
                Schedule[3].push_back(b);
                break;
            }
                
            case 'E':{
                Car c;
                c.turn = 2;
                c.inrd = (i-1)/3;
                c.pri = 4;
                Schedule[3].push_back(c);
                break;
            }
                
            case 'S':{
                Car d;
                d.turn = 3;
                d.inrd = (i-1)/3;
                d.pri = 1;
                Schedule[3].push_back(d);
                break;
            }
                
            default:{
                break;
            }
        }
    }

    Carorder Schedule_greedy[4];
    greedy(Schedule,Schedule_greedy);

    upf <<"N:";
    for (unsigned i=0; i<Schedule_greedy[0].size(); i++)
    {
        switch (Schedule_greedy[0].at(i).turn) {
                
            case 0:{
                upf<< " " <<"00";
                break;
            }
                
            case 1:{
                upf<< " " <<"1E";
                break;
            }
                
            case 2:{
                upf<< " " <<"1S";
                break;
            }
                
            case 3:{
                upf<< " " <<"1W";
                break;
            }
                
            default:{
                break;
            }
        }
    }
    upf <<endl;
    upf <<"E:";
    for (unsigned i=0; i<Schedule_greedy[1].size(); i++)
    {
        switch (Schedule_greedy[1].at(i).turn) {
                
            case 0:{
                upf<< " " <<"00";
                break;
            }
                
            case 1:{
                upf<< " " <<"1S";
                break;
            }
                
            case 2:{
                upf<< " " <<"1W";
                break;
            }
                
            case 3:{
                upf<< " " <<"1N";
                break;
            }
                
            default:{
                break;
            }
        }
    }
    upf <<endl;
    upf <<"S:";
    for (unsigned i=0; i<Schedule_greedy[2].size(); i++)
    {
        switch (Schedule_greedy[2].at(i).turn) {
                
            case 0:{
                upf<< " " <<"00";
                break;
            }
                
            case 1:{
                upf<< " " <<"1W";
                break;
            }
                
            case 2:{
                upf<< " " <<"1N";
                break;
            }
                
            case 3:{
                upf<< " " <<"1E";
                break;
            }
                
            default:{
                break;
            }
        }
    }
    upf <<endl;
    upf <<"W:";
    for (unsigned i=0; i<Schedule_greedy[3].size(); i++)
    {
        switch (Schedule_greedy[3].at(i).turn) {
                
            case 0:{
                upf<< " " <<"00";
                break;
            }
                
            case 1:{
                upf<< " " <<"1N";
                break;
            }
                
            case 2:{
                upf<< " " <<"1E";
                break;
            }
                
            case 3:{
                upf<< " " <<"1S";
                break;
            }
                
            default:{
                break;
            }
        }
    }
    upf <<endl;

    return 0;
}

//comparison function
void cmpcf(Carorder a[4], int b[4]){
    
    //declare imaginary car, which represent 0
    Car Imcar;
    Imcar.turn = 0;
    
    //initialization
    for (int j=0; j<4; j++) {
        b[j] = -1;
    }
    
    //conflict table
    bool CT[12][4] = {{1, 1, 1, 1}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 0, 0, 0}, {1, 0, 1, 1}, {1, 0, 1, 1}, {1, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 0, 0}, {1, 0, 0, 1}};
    
    //comparison of any two direction
    struct twocmp{
        //can go
        bool ok;
        //two direction
        int from;
        int to;
    };
    
    //comparison of any two direction
    twocmp check[6];
    
    check[0].ok = CT[a[1].front().turn][a[0].front().turn];
    check[1].ok = CT[a[2].front().turn][a[1].front().turn];
    check[2].ok = CT[a[3].front().turn][a[2].front().turn];
    check[3].ok = CT[a[2].front().turn+4][a[0].front().turn];
    check[4].ok = CT[a[3].front().turn+4][a[1].front().turn];
    check[5].ok = CT[a[3].front().turn+8][a[0].front().turn];
    
    check[0].from = 0;
    check[1].from = 1;
    check[2].from = 2;
    check[3].from = 0;
    check[4].from = 1;
    check[5].from = 0;
    
    check[0].to = 1;
    check[1].to = 2;
    check[2].to = 3;
    check[3].to = 2;
    check[4].to = 3;
    check[5].to = 3;
    
    int k=0;
    for (int i=0; i<6; i++) {
        if (check[i].ok) {
            k++;
            b[check[i].from] = a[check[i].from].front().turn;
            b[check[i].to] = a[check[i].to].front().turn;
            break;
        }
    }
    if (k == 0) {
        int OnlyOneCanGo = -1;
        int WhoCanGo = -1;
        for (int i=0; i<4; i++) {
            if (a[i].front().pri >= OnlyOneCanGo) {
                if (a[i].front().pri == OnlyOneCanGo) {
                    if (a[WhoCanGo].at(0).inrd > a[i].at(0).inrd) {
                        WhoCanGo = i;
                    }
                } else {
                    OnlyOneCanGo = a[i].front().pri;
                    WhoCanGo = i;
                }
            }
        }
        
        b[WhoCanGo] = a[WhoCanGo].front().turn;
        
    } else {
        while (1) {
            int TH = 0;
            bool checkth[4] = {false, false, false, false};
            //only three of four can go
            if (check[0].ok && check[1].ok && check[3].ok) {
                for (int j=0; j<4; j++) {
                    b[j] = -1;
                }
                b[check[0].from] = a[check[0].from].front().turn;
                b[check[1].from] = a[check[1].from].front().turn;
                b[check[1].to] = a[check[1].to].front().turn;
                checkth[0] = true;
                TH++;
                if (check[2].ok && check[4].ok && check[5].ok) {
                    b[check[2].to] = a[check[2].to].front().turn;
                    break;
                }
            }
            
            if (check[1].ok && check[2].ok && check[4].ok){
                for (int j=0; j<4; j++) {
                    b[j] = -1;
                }
                TH++;
                checkth[1] = true;
                b[check[1].from] = a[check[1].from].front().turn;
                b[check[2].from] = a[check[2].from].front().turn;
                b[check[2].to] = a[check[2].to].front().turn;
                
            }
            if (check[2].ok && check[3].ok && check[5].ok){
                for (int j=0; j<4; j++) {
                    b[j] = -1;
                }
                TH++;
                checkth[2] = true;
                b[check[3].from] = a[check[3].from].front().turn;
                b[check[2].from] = a[check[2].from].front().turn;
                b[check[2].to] = a[check[2].to].front().turn;
                
            }
            if (check[0].ok && check[4].ok && check[5].ok){
                for (int j=0; j<4; j++) {
                    b[j] = -1;
                }
                TH++;
                checkth[3] = true;
                b[check[0].from] = a[check[0].from].front().turn;
                b[check[4].from] = a[check[4].from].front().turn;
                b[check[4].to] = a[check[4].to].front().turn;
            }
            if (TH <= 1) {
                if (TH == 0) {
                    for (int j=0; j<4; j++) {
                        b[j] = -1;
                    }
                    int OnlyTwoCanGo = -1;
                    int WhoCanGo = -1;
                    for (int i=0; i<6; i++) {
                        if (check[i].ok) {
                            if (OnlyTwoCanGo <= a[check[i].from].front().pri + a[check[i].to].front().pri) {
                                if (OnlyTwoCanGo == a[check[i].from].front().pri + a[check[i].to].front().pri) {
                                    if (a[check[WhoCanGo].from].at(0).inrd + a[check[WhoCanGo].to].at(0).inrd > a[check[i].from].at(0).inrd + a[check[i].to].at(0).inrd)
                                    {
                                        WhoCanGo = i;
                                    }
                                } else {
                                    OnlyTwoCanGo = a[check[i].from].front().pri + a[check[i].to].front().pri;
                                    WhoCanGo = i;
                                }
                            }
                        }
                    }
                    b[check[WhoCanGo].from] = a[check[WhoCanGo].from].front().turn;
                    b[check[WhoCanGo].to] = a[check[WhoCanGo].to].front().turn;
                    break;
                }
                break;
            } else {
                for (int j=0; j<4; j++) {
                    b[j] = -1;
                }
                int OnlyThreeCanGo = -1;
                int WhoCanGo = -1;
                for (int i=0; i<4; i++) {
                    if (checkth[i]) {
                        if (OnlyThreeCanGo <= (a[i%4].front().pri + a[(i+1)%4].front().pri + a[(i+2)%4].front().pri)) {
                            if (OnlyThreeCanGo == (a[i%4].front().pri + a[(i+1)%4].front().pri + a[(i+2)%4].front().pri)) {
                                if ((a[i%4].at(0).inrd + a[(i+1)%4].at(0).inrd + a[(i+2)%4].at(0).inrd)<(a[WhoCanGo%4].at(0).inrd + a[(WhoCanGo+1)%4].at(0).inrd + a[(WhoCanGo+2)%4].at(0).inrd)) {
                                    WhoCanGo = i;
                                }
                            } else {
                                OnlyThreeCanGo = (a[i%4].front().pri + a[(i+1)%4].front().pri + a[(i+2)%4].front().pri);
                                WhoCanGo = i;
                            }
                        }
                    }
                }
                b[WhoCanGo%4] = a[WhoCanGo%4].front().turn;
                b[(WhoCanGo+1)%4] = a[(WhoCanGo+1)%4].front().turn;
                b[(WhoCanGo+2)%4] = a[(WhoCanGo+2)%4].front().turn;
                break;
            }
            break;
        }
    }
    return;
}


void greedy(Carorder schedule[],Carorder schedule_greedy[]){
    int p[4];
    Car Imcar;
    Imcar.turn = 0;
    while(1){
        cmpcf(schedule,p);
        int count = 0;
        for(int i=0;i<4;i++){
            if(p[i] == -1){
                for(int j = 0;j<schedule[i].size();j++){
                    if(schedule[i].at(j).turn != 0){
                        schedule[i].at(j).cost++;
                    } else {
                        schedule[i].erase(schedule[i].begin()+j);
                        break;
                    }
                }
                schedule_greedy[i].push_back(Imcar);
                continue;
            }
            schedule_greedy[i].push_back(schedule[i].front());
            schedule[i].pop_front();
            if(schedule[i].empty()){
                count++;
            }
        }
        if(count == 4){
            break;
        }
        unsigned long Lmax = schedule[0].size();
        for(int i=1;i<4;i++){
            if(schedule[i].size()>Lmax)
                Lmax = schedule[i].size();
        }
        for(int k=0;k<4;k++){
            if(schedule[k].size() != Lmax)
                schedule[k].push_back(Imcar);
        }
    }

    return;
}



