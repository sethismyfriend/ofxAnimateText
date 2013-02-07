//
//  take.h
//  Take
//
//  Created by Anette von Kapri on 9/29/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _TAKE_H
#define _TAKE_H

#include <iostream>

class Take{
public:
    Take();
    Take(std::string filename_video, std::string filename_audio, int type,
		float start, float stop, int audio_duration);
    ~Take();

    //set
    void set_video(const std::string &filename_video){ m_filename_video = filename_video; };
    void set_audio(const std::string &filename_audio){ m_filename_audio = filename_audio; };

    void set_type(const int type){ m_type = type; };

    void set_start(const float start){ m_start = start; };
    void set_stop(const float stop){ m_stop = stop; };

    void set_audio_duration(const int audio_duration){ m_audio_duration = audio_duration; };
	void set_text_transcription(const std::string &transcript) { m_transcript = transcript; };



    //get
    const std::string& video() const { return m_filename_video; };
    const std::string& audio() const { return m_filename_audio; };
	const std::string& transcript() const {return m_transcript; };

    const int type() const { return m_type; };

    const float start() const { return m_start; };
    const float stop() const { return m_stop; };

    const int audio_duration() { return m_audio_duration;};



protected:
    std::string m_filename_video;
    std::string m_filename_audio;
	std::string m_transcript;

    int m_type; //< left circle = 0; right circle = 1; corner = 2; crossing left circle = 3; crossing rigth circle = 4; crossing all = 5

    float m_start; //< when action starts, in seconds
    float m_stop; //< when action stops, in seconds

    int m_audio_duration; //< in seconds

};

#endif
