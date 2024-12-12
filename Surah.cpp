#include <iostream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include <tchar.h>
using namespace std;
#pragma once
#pragma comment(lib, "winmm.lib")

class Surah
{
private:
    string name, path, type;
    // Helper functions
    void playSound(const string &soundPath) // This function is used to convert the string into format that make the PlaySound work with it;
    {
        LPCSTR lpcstrsoundPath = soundPath.c_str();
        PlaySoundA(lpcstrsoundPath, NULL, SND_FILENAME | SND_SYNC);
    }

public:
    Surah() : name("null"), type("null"), path("null") {};
    Surah(const string &SurahName, const string &SurahType, const string &SurahPath)
    {
        name = SurahName;
        type = SurahType;
        path = SurahPath;
    }
    const void PrintName()
    {
        cout << "The name of the surah: " << name << endl;
    }
    const void PrintType()
    {
        cout << "The type of the surah: " << type << endl;
    }
    const void PrintPath()
    {
        cout << "The path of the surah: " << path << endl;
    }
    const void PlaySurah()
    {
        PrintName();
        PrintType();
        PrintPath();
        playSound(path);
        cout << "Surah is over.\n";
    }
    void SetData(const string &SurahName, const string &SurahType, const string &SurahPath)
    {
        name = SurahName;
        type = SurahType;
        path = SurahPath;
    }
    string GetName() { return name; }
    ~Surah() {};
};