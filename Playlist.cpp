#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include "Surah.cpp"
// #include "PlaylistManager.cpp"
using namespace std;
#pragma once

struct PLnode
{
    Surah Data;
    PLnode *next;
    PLnode *prev;
    PLnode() : Data(), next(nullptr), prev(nullptr) {};
    PLnode(Surah Element) : Data(Element), next(nullptr), prev(nullptr) {};
};

class Playlist
{
private:
    string PlaylistName;
    PLnode *head;
    PLnode *tail;
    unsigned int NumOfSurahs = 0;
    // Helper function
    bool IsEmpty() { return head == nullptr; }

public:
    // Constructor
    Playlist();
    // Destructor
    ~Playlist();
    // Set play list name
    void SetName(const string &PlaylistName);
    // Get play list name
    string GetName();
    // 1.Insert at begin
    void InsertBegin(const Surah &Element);
    // 2.Insert at end
    void InsertEnd(const Surah &Element);
    // 3.Insert at index
    void InsertIndex(const Surah &Element, int Index);
    // 4.Delete at begin
    void DeleteBegin();
    // 5.Delete at end
    void DeleteEnd();
    // 6.Delete at index
    void DeleteIndex(int Index);
    // 7.Display Surahs
    void Display();
    // 10.Get index Surah
    Surah GetIndex(int Index);
    // 11.Get number of Surahs
    int GetNumOfLists();
    // 12.Get by name
    Surah GetByName(string name);
};

Playlist::Playlist() : head(nullptr), tail(nullptr) {};

Playlist::~Playlist()
{
    PLnode *Current;
    PLnode *NToD = head;
    while (NToD != nullptr)
    {
        Current = NToD->next;
        delete NToD;
        NToD = Current;
    }
}

void Playlist::SetName(const string &PlaylistName) { this->PlaylistName = PlaylistName; }

string Playlist::GetName()
{
    return PlaylistName;
}

void Playlist::InsertBegin(const Surah &Element)
{

    PLnode *newPlaylist = new PLnode(Element);
    if (IsEmpty())
    {
        head = newPlaylist;
        tail = newPlaylist;
    }
    else
    {
        newPlaylist->next = head;
        head->prev = newPlaylist;
        head = newPlaylist;
    }
    NumOfSurahs++;
}

void Playlist::InsertEnd(const Surah &Element)
{
    if (IsEmpty())
        InsertBegin(Element);
    else
    {
        PLnode *newPlaylist = new PLnode(Element);
        newPlaylist->prev = tail;
        tail->next = newPlaylist;
        tail = newPlaylist;
        NumOfSurahs++;
    }
}

void Playlist::InsertIndex(const Surah &Element, int Index)
{

    if (Index < 1)
    {
        cout << "Invalid index!!\n";
        return;
    }
    if (Index == 1)
    {
        InsertBegin(Element);
        return;
    }
    PLnode *Current = head;
    for (int i = 1; Current != nullptr && i < Index - 1; i++)
    {
        Current = Current->next;
    }
    if (Current == nullptr)
    {
        cout << "Index out of range!!\n";
        return;
    }
    if (Current->next == nullptr)
    {
        InsertEnd(Element);
        return;
    }
    PLnode *newPlaylist = new PLnode(Element);
    newPlaylist->next = Current->next;
    newPlaylist->prev = Current;
    Current->next->prev = newPlaylist;
    Current->next = newPlaylist;
    NumOfSurahs++;
}

void Playlist::DeleteBegin()
{
    if (IsEmpty())
    {
        cout << "The list is already empty!!\n";
        return;
    }
    if (head->next == nullptr) // Checks if there is only one node
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        PLnode *Temp = head;
        head = head->next;
        head->prev = nullptr;
        delete Temp;
    }
    NumOfSurahs--;
}

void Playlist::DeleteEnd()
{

    if (IsEmpty())
    {
        cout << "The list is already empty!!\n";
        return;
    }
    if (head->next == nullptr)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        PLnode *NToD = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete NToD;
    }
    NumOfSurahs--;
}

void Playlist::DeleteIndex(int Index)
{
    if (Index < 1)
    {
        cout << "Index invalid!!\n";
        return;
    }
    if (IsEmpty())
    {
        cout << "There is no playlists to delete!!\n";
        return;
    }
    PLnode *Current = head;
    if (Index == 1)
    {
        DeleteBegin();
    }
    else
    {
        for (int i = 1; Current != nullptr && i < Index; i++)
        {
            Current = Current->next;
        }
        if (Current == nullptr)
        {
            cout << "Index out of bounds!!\n";
            return;
        }
        if (Current->next == nullptr)
        {
            DeleteEnd();
            return;
        }
        Current->next->prev = Current->prev;
        Current->prev->next = Current->next;
        delete Current;
        NumOfSurahs--;
    }
}

void Playlist::Display()
{
    if (head == nullptr)
        cout << "There is no surahs in the list!!\n";
    else
    {
        PLnode *Current = head;
        for (int i = 1; Current != nullptr; i++)
        {
            cout << i << ". " << Current->Data.GetName() << endl;
            Current = Current->next;
        }
    }
}

int Playlist::GetNumOfLists() { return NumOfSurahs; }

Surah Playlist::GetByName(string name)
{
    if (IsEmpty())
    {
        cout << "The playlist is empty!\n";
        return Surah();
    }
    PLnode *Current = head;
    while (Current != nullptr)
    {
        if (Current->Data.GetName() == name)
        {
            cout << "Surah " << name << " found in playlist " << PlaylistName << endl;
            return Current->Data;
        }
        Current = Current->next;
    }
    cout << "Surah " << name << " not found in playlist " << PlaylistName << endl;
    return Surah();
}
