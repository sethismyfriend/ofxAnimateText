//
//  takeManager.cpp
//  TakeXmlSettings
//
//  Created by Anette von Kapri on 9/29/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <ctime>//for time
#include <cstdlib>//for srand() and rand()

#include "ofxXmlSettings.h"
#include "takeManager.h"

TakeManager::TakeManager()
{
    srand(time(NULL));

}

TakeManager::~TakeManager()
{
    cleanup();
}


bool TakeManager::loadXMLFile(const std::string &filename, const bool verbose)
{
    cleanup();

    ofxXmlSettings XML;

    //we load our settings file
	if( XML.loadFile(filename) ){
        //    if( XML.loadFile("mySettings.xml") ){
		printf("%s loaded!\n", filename.c_str());
	}
    else{
		printf("unable to load %s check data/ folder\n", filename.c_str());
	}



	//lets see how many <take_list> </take_list> tags there are in the xml file
	int numTracks = XML.getNumTags("take");
    printf("number of drag tags %i\n", numTracks);

	//if there is at least one <take_list> tag we can read the list of points
	//and then try and draw it as a line on the screen
	if(numTracks > 0){

        for(int i=0; i<numTracks; i++)
        {
            Take * take = new Take();

            //we push into the last take tag
            //this temporarirly treats the tag as
            //the document root.
            XML.pushTag("take", i);

            take->set_video( XML.getValue("videofile","") );
            take->set_audio( XML.getValue("audiofile","") );

            take->set_type( XML.getValue("type", 0, 0));
            take->set_start(XML.getValue("start", 0, 0));
            take->set_stop(XML.getValue("stop", 0, 0));
            take->set_audio_duration(XML.getValue("audio_duration", 0, 0));
			
			take->set_text_transcription(XML.getValue("transcript",""));

            const int type = take->type();

            switch(type){
                case 0://circle a
                    circle_a.push_back(take);
                break;
                case 1://circle b
                    circle_b.push_back(take);
                break;
                case 2://corner
                    corner.push_back(take);
                break;
                case 3://crossing a
                    crossing_a.push_back(take);
                break;
                case 4://crossing b
                    crossing_b.push_back(take);
                break;
                case 5://crossing all
                    crossing_all.push_back(take);
                break;
                default:
                    std::cout << "[TakeManager:loadXMLFile] Sorry, type " << type << " not recognized" << std::endl;
                    std::cout << "[TakeManager:loadXMLFile] Should be between 0-5" << std::endl;
            }


            if(verbose)
            {
                printf("videofile %s\n", take->video().c_str());
                printf("audiofile %s\n", take->audio().c_str());

                printf("type %i\n", take->type());
                printf("start %f\n", take->start());
                printf("stop %f\n", take->stop());
				std::cout << "transcribe: " << take->transcript() << std::endl;
                std::cout << "audio_duration: " << take->audio_duration() << std::endl;
            }

            //this pops us out of the take tag
            //sets the root back to the xml document
            XML.popTag();

        }
	}

    if(verbose)
    {
        std::cout << "takes circle a: " << circle_a.size() << std::endl;
        std::cout << "takes circle b: " << circle_b.size() << std::endl;
        std::cout << "takes corner: " << corner.size() << std::endl;
        std::cout << "takes crossing a: " << crossing_a.size() << std::endl;
        std::cout << "takes crossing b: " << crossing_b.size() << std::endl;
        std::cout << "takes crossing all: " << crossing_all.size() << std::endl;

    }

    return true;
}


Take* TakeManager::getTake(const int type)
{
    switch(type)
    {
        case(0):
            return getTake(circle_a, circle_a_played);
        break;
        case 1:
            return getTake(circle_b, circle_b_played);
        break;
        case 2:
            return getTake(corner, corner_played);
        break;
        case 3:
            return getTake(crossing_a, crossing_a_played);
        break;
        case 4:
            return getTake(crossing_b, crossing_b_played);
        break;
        case 5:
            return getTake(crossing_all, crossing_all_played);
        break;
        default:
            std::cout << "[TakeManager:getTake] type " << type << " is unknown" << std::endl;

    }

}

Take* TakeManager::getTake(std::vector<Take*> &unplayed, std::vector<Take*> &played)
{
    //if unplayed is empty: swap
    int size = unplayed.size();
    if(size <= 0)
    {
        unplayed.swap(played);
        size = unplayed.size();
    }

    int rand = std::rand() % size;

    Take * take = unplayed.at(rand);

    //std::cout << "playing: " << take->video() << std::endl;

    unplayed.erase(unplayed.begin()+rand);
    played.push_back(take);

    return take;
}


void TakeManager::cleanup()
{
    //memory leak > use boost:shared_ptr for future projects or delete list items
    circle_a.clear();
    circle_b.clear();
    corner.clear();
    crossing_a.clear();
    crossing_b.clear();
    crossing_all.clear();
}

