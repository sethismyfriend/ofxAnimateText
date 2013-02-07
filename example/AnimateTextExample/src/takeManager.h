//
//  take_manager.h
//
//
//  Created by Anette von Kapri on 9/29/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _TAKE_MANAGER_H
#define _TAKE_MANAGER_H

#include <vector>
#include <map>


#include "take.h"

//stores a library of Takes
class TakeManager{
public:
    TakeManager();
    ~TakeManager();

    bool loadXMLFile(const std::string &filename, const bool verbose = false);

    Take* getTake(int type);

    //unplayed videos
    std::vector<Take*> circle_a; //of type 0
    std::vector<Take*> circle_b; // of type 1
    std::vector<Take*> corner; // of type 2
    std::vector<Take*> crossing_a; //type 3
    std::vector<Take*> crossing_b; //type 4
    std::vector<Take*> crossing_all; //type 5

    //played videos
    std::vector<Take*> circle_a_played; //of type 0
    std::vector<Take*> circle_b_played; // of type 1
    std::vector<Take*> corner_played; // of type 2
    std::vector<Take*> crossing_a_played; //type 3
    std::vector<Take*> crossing_b_played; //type 4
    std::vector<Take*> crossing_all_played; //type 5





protected:
    void cleanup();

    //assumption: unplayed and played are of same type
    Take* getTake(std::vector<Take*> &unplayed, std::vector<Take*> &played);



};

#endif
