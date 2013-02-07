//
//  take.cpp
//  TakeXmlSettings
//
//  Created by Anette von Kapri on 9/29/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "take.h"


Take::Take():
m_filename_video("")
, m_filename_audio("")
, m_type(0)
, m_start(0)
, m_stop(0)
,m_audio_duration(0)
{

}

Take::Take(std::string filename_video, std::string filename_audio, int type,
	float start, float stop, int audio_duration):
	m_filename_video(filename_video)
	, m_filename_audio(filename_audio)
	, m_type(type)
	, m_start(start)
	, m_stop(stop)
	, m_audio_duration(audio_duration)
	{

	}

Take::~Take()
{

}
